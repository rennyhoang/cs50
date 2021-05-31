# import modules
from cs50 import SQL
import sys

# open database file
db = SQL("sqlite:///students.db")

# check the command line arguments
if len(sys.argv) != 2:
    sys.exit()

# get the names/birth of students in a list of dictionaries
roster = db.execute("SELECT first,middle,last,birth FROM students WHERE house == ? ORDER BY last ASC;", sys.argv[1])

# iterate over dictionaries and print information to the user
for row in roster:
    if row['middle'] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")