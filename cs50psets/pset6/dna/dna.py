import csv
import sys

# import the dna database as dictionary
with open(sys.argv[1], mode="r") as csv_file:
    csv_reader = csv.DictReader(csv_file)
    lineCount = 0
    for row in csv_reader:
        if lineCount == 0:
            lineCount += 1

# import the dna sequence as string
openSequence = open(sys.argv[2], mode="r")
dnaSequence = openSequence.read()

sequenceCounter = 0
sequenceDict = {}
numOfSequences = 0

# iterate through sequences in database
for i in row:
    
    sequenceLen = len(i)

    # skip the names column
    if sequenceCounter == 0:
        sequenceCounter += 1
        continue

    sequenceDict[i] = 0
    consecutiveCounter = 0
    numOfSequences += 1

    # iterate through every letter in DNA sequence
    for j in range(len(dnaSequence)):
        k = j
        while k + sequenceLen < len(dnaSequence):
            if dnaSequence[k:k+sequenceLen] == i:
                consecutiveCounter += 1
                k += sequenceLen
                if consecutiveCounter > sequenceDict[i]:
                    sequenceDict[i] = consecutiveCounter
            else:
                consecutiveCounter = 0
                break

# open database again to check for match
with open(sys.argv[1], mode="r") as csv_file:
    csv_reader = csv.DictReader(csv_file)
    match = False
    
    # iterate through rows
    for row in csv_reader:
        sequenceCheck = 0
        nameCheck = False
        
        # iterate through sequences in row
        for i in row:
            if nameCheck == False:
                nameCheck = True
                continue
            if int(sequenceDict[i]) == int(row[i]):
                sequenceCheck += 1
        if sequenceCheck == numOfSequences:
            print(row['name'])
            match = True

if match == False:
    print("No match")