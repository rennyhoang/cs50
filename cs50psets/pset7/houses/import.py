# import modules
from cs50 import SQL
import csv
import sys

# open/create database
db = SQL("sqlite:///students.db")

# check if command line arguments are correct
if len(sys.argv) != 2 or sys.argv[1].endswith(".csv") == False:
    sys.exit()

# clear any existing rows
db.execute("DELETE FROM students;")

# open the csv for reading
with open(sys.argv[1]) as csvFile:
    # create dictreader to iterate over
    csvReader = csv.DictReader(csvFile, delimiter=",")
    for row in csvReader:
        # make variables for new values
        name = row['name']
        namesList = name.split()
        house = row['house']
        birth = int(row['birth'])
        # check if there's a middle name
        if len(namesList) == 2:
            db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?,?,?,?,?);",
                       namesList[0], None, namesList[1], house, birth)
        else:
            db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?,?,?,?,?);",
                       namesList[0], namesList[1], namesList[2], house, birth)