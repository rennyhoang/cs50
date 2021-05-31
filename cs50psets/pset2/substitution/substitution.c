#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int checkKey(int argc, string argv[]);

int main(int argc, string argv[])
{
    string ciphertext = "";
    if (checkKey(argc, argv) == 0)
    {
        string plaintext = get_string("Plaintext: ");
        printf("ciphertext: ");
        for (int i = 0; i < strlen(plaintext); i++)
        {
            if (isalpha(plaintext[i]))
            {
                if islower(plaintext[i])
                {
                    printf("%c", tolower(argv[1][plaintext[i] - 97]));
                }

                else if isupper(plaintext[i])
                {
                    printf("%c", toupper(argv[1][plaintext[i] - 65]));
                }
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
    }
    else
    {
        return 1;
    }
}

int checkKey(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i += 1)
    {
        if (isalpha(argv[1][i]))
        {
            ;
        }

        else
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    for (int j = 0; j < 26; j += 1)
    {
        char character = argv[1][j];

        for (int k = j + 1; k < 26; k += 1)
        {
            char character2Upper = toupper(argv[1][k]);
            char character2Lower = tolower(argv[1][k]);

            if (character == character2Upper || character == character2Lower)
            {
                printf("Key must not contain repeated letters.\n");
                return 1;
            }
        }
    }

    return 0;
}