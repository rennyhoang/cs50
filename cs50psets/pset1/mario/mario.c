#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int height = get_int("Height: ");
    
    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }

    for (int i = 0; i < height; i++)
    {
        int counter = height - i;
        int spaceCounter = height - 1;
        while (counter > 1)
        {
            printf(" ");
            counter -= 1;
            spaceCounter -= 1;
        }

        int spaceCounterCopy = spaceCounter;

        while (spaceCounter >= 0)
        {
            printf("#");
            spaceCounter -= 1;
        }

        printf("  ");

        while (spaceCounterCopy >= 0)
        {
            printf("#");
            spaceCounterCopy -= 1;
        }

        printf("\n");
    }
}