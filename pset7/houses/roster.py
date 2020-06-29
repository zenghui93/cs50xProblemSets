import cs50
from sys import argv, exit
# Open students.db for SQLite
db = cs50.SQL("sqlite:///students.db")

if len(argv) != 2:
    print("missing command-line argument")
    exit(1)
rows = db.execute(
    "SELECT DISTINCT first, middle, last, birth FROM students WHERE house = ? ORDER BY last ASC, first ASC;", argv[1])
for row in rows:
    if row['middle'] is None:
        name = row['first'] + " " + row['last']
    else:
        name = row['first'] + " " + row['middle'] + " " + row['last'] 
    
    print(name + ", born " + str(row['birth']))
        
