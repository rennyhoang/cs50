def countLetters(string):
    numOfLetters = 0
    for letter in string:
        if letter.isalpha():
            numOfLetters += 1
    return numOfLetters

    
def countWords(str):
    numOfWords = 1
    for letter in str:
        if letter == " ":
            numOfWords += 1
    return numOfWords


def countSentences(str):
    numOfSentences = 0
    for letter in str:
        if letter == "!" or letter == "?" or letter == ".":
            numOfSentences += 1
    return numOfSentences
    
    
text = input("Text: ")
L = countLetters(text) * (100.0 / countWords(text))
S = countSentences(text) * (100.0 / countWords(text))
index = round(0.0588 * L - 0.296 * S - 15.8)

if index >= 16:
    print("Grade 16+")

elif index < 1:
    print("Before Grade 1")
    
else:
    print("Grade {}".format(int(index)))