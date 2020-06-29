import cs50
from sys import argv, exit
# Open students.db for SQLite
db = cs50.SQL("sqlite:///students.db")

if len(argv) != 2:
    print("missing command-line argument")
    exit(1)
h = argv[1]
rows = db.execute("SELECT DISTINCT first, middle, last, birth FROM students WHERE house == 'Gryffindor' ORDER BY first ASC, last ASC")
name = ""
for row in rows:
    print(row)
    if row['middle'] is None:
        name = row['first'] + " " + row['last']
    else:
        name = row['first'] + " " + row['middle'] + " " + row['last']
    
    print(name)
        
   
