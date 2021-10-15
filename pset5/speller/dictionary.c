// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"

// For FNV-1a
#include <string.h>
#include <inttypes.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 32768;

// Hash table
node *table[N];

// Number of words in dictionary
int num_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *n = table[hash(word)];
    while (n)
    {
        if (!strcasecmp(n -> word, word))
        {
            return true;
        }
        n = n -> next;
    }
    return false;
}

// Hashes word to a number (FNV-1a)
unsigned int hash(const char *word)
{
    uint32_t h = 2166136261U;
    for (; *word != '\0'; word++)
    {
        h ^= tolower(*word);
        h *= 16777619;
    }
    return h % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char tmp[LENGTH + 1];
    while (fscanf(dict, "%s", tmp) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n)
        {
            unsigned int h = hash(tmp);
            strcpy(n -> word, tmp);
            n -> next = table[h];
            table[h] = n;
            num_words++;
        }
        else
        {
            return false;
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    unsigned int i = 0;
    for (; i < N; i++)
    {
        while (table[i])
        {
            node *tmp = table[i] -> next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
