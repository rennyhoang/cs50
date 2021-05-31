from cs50 import get_int

creditCardNumber = get_int("Number: ")
tempCreditCard = creditCardNumber
tempCreditCard2 = creditCardNumber
numberOfDigits = 2
checksumCounter = 0
ifEven = 1
firstTwoDigits = 0

while tempCreditCard2 / 10 > 10:
    numberOfDigits += 1
    tempCreditCard2 /= 10
    
while creditCardNumber >= 99:
    creditCardNumber = creditCardNumber - (creditCardNumber % 10)
    creditCardNumber /= 10

firstTwoDigits += creditCardNumber
firstDigit = ((firstTwoDigits - (firstTwoDigits % 10)) / 10)

while tempCreditCard > 0:

    if ifEven % 2 != 0:
        checksumCounter += tempCreditCard % 10
        
    elif (ifEven % 2 == 0):
        
        if ((tempCreditCard % 10) * 2) > 10:
            checksumCounter += (((tempCreditCard % 10) * 2) % 10) + 1
            
        elif ((tempCreditCard % 10) * 2) == 10:
            checksumCounter += 1
        else:
            checksumCounter += (tempCreditCard % 10) * 2
            
    ifEven += 1
    tempCreditCard -= tempCreditCard % 10
    tempCreditCard /= 10

if checksumCounter % 10 == 0:
    
    if (numberOfDigits == 15) and (firstTwoDigits == 34 or firstTwoDigits == 37):
        print("AMEX")
        
    elif (numberOfDigits == 16 or numberOfDigits == 13) and (firstDigit == 4):
        print("VISA")
        
    elif (numberOfDigits == 16) and (firstTwoDigits == 51 or firstTwoDigits == 52 or firstTwoDigits == 53 or firstTwoDigits == 54 or firstTwoDigits == 55):
        print("MASTERCARD")
        
    else:
        print("INVALID")
        
else:
    print("INVALID")