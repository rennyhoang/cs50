#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long long creditCardNumber = get_long("Number: ");
    long long tempCreditCard = creditCardNumber;
    long long tempCreditCard2 = creditCardNumber;
    int numberOfDigits = 1;
    int checksumCounter = 0;
    int ifEven = 1;
    int firstTwoDigits = 0;
    
    
    while(tempCreditCard2 /= 10)
    {
        numberOfDigits += 1;
    }
    
    while(creditCardNumber >= 99)
    {
        creditCardNumber = creditCardNumber - (creditCardNumber % 10);
        creditCardNumber /= 10;
    }
    
    firstTwoDigits += creditCardNumber;
    int firstDigit = ((firstTwoDigits - (firstTwoDigits % 10)) / 10);
    
    while(tempCreditCard > 0)
    {
        if (ifEven % 2 != 0)
        {
            checksumCounter += tempCreditCard % 10;
        }
        
        else if (ifEven % 2 == 0)
        {
            if (((tempCreditCard % 10) * 2) > 10)
            {
                checksumCounter += (((tempCreditCard % 10) * 2) % 10) + 1;
            }
            else if (((tempCreditCard % 10) * 2) == 10)
            {
                checksumCounter++;
            }
            else
            {
            checksumCounter += (tempCreditCard % 10) * 2;
            }
        }
        
        ifEven++;
        tempCreditCard -= tempCreditCard % 10;
        tempCreditCard /= 10;
    }
    
    if (checksumCounter % 10 == 0)
    {
        if ((numberOfDigits == 15) && (firstTwoDigits == 34 || firstTwoDigits == 37))
        {
            printf("AMEX\n");
        }
        else if ((numberOfDigits == 16 || numberOfDigits == 13) && (firstDigit == 4))
        {
            printf("VISA\n");
        }
        else if ((numberOfDigits == 16) && (firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 || firstTwoDigits == 54 || firstTwoDigits == 55))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    
    else
    {
        printf("INVALID\n");
    }
    
}