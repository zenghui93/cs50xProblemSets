import cs50
import csv
from sys import argv
# Open students.db for SQLite
db = cs50.SQL("sqlite:///students.db")
# Open csv file
with open(argv[1], "r") as students:
    # Create DictReader
    reader = csv.DictReader(students)
    for row in reader:
        name = row['name'].split()
        # if length of name is 3 that means that there is a middle name
        if len(name) == 3:
            first = name[0]
            middle = name[1]
            last = name[2]
        else:
            first = name[0]
            last = name[1]
            middle = None
        house = row['house']
        birth = row['birth']
        db.execute(
            "INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)
