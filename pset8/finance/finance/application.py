import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Query database for username
    rows = db.execute("SELECT symbol, SUM(shares) AS shares FROM stocks WHERE user_id = :user_id and symbol in (SELECT symbol FROM stocks WHERE user_id = :user_id) GROUP BY symbol",
                          user_id =session["user_id"])
    cash = db.execute("SELECT cash  FROM users WHERE id = :user_id",
                          user_id =session["user_id"])
    
    tot_value=0
    for row in rows:
        quoted = lookup(row["symbol"])
        row["name"] = quoted['name']
        row["current_price"] = float(quoted['price'])
        row["total"] = row["shares"] * quoted['price']
        tot_value = tot_value + row["total"]
    
    tot_value = tot_value + cash[0]["cash"]

    
    return render_template("index.html", rows=rows, cash=cash[0]["cash"], tot_value=tot_value)
    

        
    
  

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol") or lookup(request.form.get("symbol"))==None :
            return apology("must provide a valid symbol", 403)
        else:
            quoted=lookup(request.form.get("symbol"))
            
            # Check how many cash the user has
            row = db.execute("SELECT cash FROM users WHERE id = :user_id",
                          user_id=session["user_id"])
            # Ensure that the user has enough money to buy the shares
            if row[0]["cash"] >= quoted['price'] * request.form.get("shares"):
                db.execute("INSERT INTO stocks(user_id, symbol, shares, price) values(:user_id, :symbol, :shares, :price)",
                       user_id=session["user_id"],
                       symbol=request.form.get("symbol"),
                       shares=request.form.get("shares"),
                       price=quoted['price'])
                # Update the cash after having bought the shares
                row[0]["cash"] = row[0]["cash"] - (request.form.get("shares") * quoted['price'])
                db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                           cash=row[0]["cash"],
                           user_id=session["user_id"])
                         
    
                return redirect("/")
                
            else:
                return apology("Sorry, you do not have enough money to complete the purchase.")
            
            
            
    
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")
    


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    
    rows = db.execute("SELECT * FROM stocks WHERE user_id = :user_id",
                          user_id=session["user_id"])
    for row in rows:
        quoted=lookup(row["symbol"])
        row["name"] = quoted['name']
    
    return render_template("history.html", rows=rows)
    
    
        
                          


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)
        else:
            quoted=lookup(request.form.get("symbol"))
            return render_template("quoted.html", quoted=quoted)
    
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")
            


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
            
        # Ensure the confirmation was submitted and it corresponds to password
        elif not request.form.get("confirmation"):
            return apology("must confirm the password", 403)
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("Your password and confirm password did not match", 403)
        
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) == 1:
            return apology("username is already taken ", 403)
        else:
            db.execute("INSERT INTO users(username, hash) values(:username, :password)",
                       username=request.form.get("username"),
                       password=generate_password_hash(request.form.get("password")))
                       

        # Redirect user to log in page
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")
        
        


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol") or lookup(request.form.get("symbol"))==None :
            return apology("must provide a valid symbol", 403)
        else:
            quoted=lookup(request.form.get("symbol"))
            
            # Ensure that the user has enough shares to sell
            row = db.execute("SELECT SUM(shares) AS shares FROM stocks WHERE user_id = :user_id and symbol = :symbol",
                          user_id=session["user_id"],
                          symbol=request.form.get("symbol"))
            if row[0]["shares"] == 0 or (int(row[0]["shares"]) < int(request.form.get("shares"))):
                return apology("Sorry, you cannot sell that amount shares of stock.")
            
            else:
                # Sell the shares
                db.execute("INSERT INTO stocks(user_id, symbol, shares, price) values(:user_id, :symbol, :shares, :price)",
                       user_id=session["user_id"],
                       symbol=request.form.get("symbol"),
                       shares= int(request.form.get("shares")) * (-1),
                       price=quoted['price'])
                # Update the cash after having bought the shares
                # Check how many cash the user has
                row_cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                          user_id=session["user_id"])
                row_cash[0]["cash"] = row_cash[0]["cash"] + (float(request.form.get("shares")) * quoted['price'])
                db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                           cash=row_cash[0]["cash"],
                           user_id=session["user_id"])
                         
    
                return redirect("/")
            
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
