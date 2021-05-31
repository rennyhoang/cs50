#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string);
int count_words(string);
int count_sentences(string);

int main(void)
{
    string text = get_string("Text: ");
    float L = count_letters(text) * (100.0 / count_words(text));
    float S = count_sentences(text) * (100.0 / count_words(text));
    float index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int)index);
    }
}

int count_letters(string text)
{
    int numOfLetters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            numOfLetters++;
        }
        else
        {
            ;
        }
    }
    return (numOfLetters);
}

int count_words(string text)
{
    int numOfWords = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 32)
        {
            numOfWords++;
        }
        else
        {
            ;
        }
    }
    return (numOfWords);
}

int count_sentences(string text)
{
    int numOfSentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            numOfSentences++;
        }
        else
        {
            ;
        }
    }
    return (numOfSentences);
}