// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;
int numOfWords = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = hash(word);

    node *tmp = table[index];

    while (tmp != NULL && (tmp->next != NULL || strcasecmp(word, tmp->word) == 0))
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }

        else
        {
            tmp = tmp->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Source for hash function: https://stackoverflow.com/questions/2571683/djb2-hash-function

    char copy[strlen(word) + 1];
    copy[strlen(word)] = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        copy[i] = tolower(word[i]);
    }

    int index = 0;
    unsigned int hash = 5381;
    int c;

    while ((c = copy[index++]++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + x*/

    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *openDict = fopen(dictionary, "r");

    if (openDict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    node *n = NULL;

    while (fscanf(openDict, "%s", word) != EOF)
    {
        numOfWords++;

        n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        int index = hash(word);

        if (table[index] == NULL)
        {
            table[index] = n;
        }

        else
        {
            n->next = table[index];
            table[index] = n;
        }
    }

    fclose(openDict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numOfWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor;
    node *tmp;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
