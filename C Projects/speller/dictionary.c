// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of nodes (words) in a hash table
int SIZE = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *tmp = table[hash(word)];
    // Iterate over the linked list in the right bucket
    while (tmp != NULL)
    {
        // Check if the word is there
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the file and check if it's opened correctly
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        printf("Error while opening file\n");
        return false;
    }

    // Declare word variable that tends to store dictionary words
    char word[LENGTH + 1];

    // Iterate over each word in the file
    while (fscanf(f, "%s", word) != EOF)
    {
        // Calculate the hash value for the word
        int value = hash(word);

        // Create a node for every word and link it to its bucket list
        // Allocate memory for the node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Memory error\n");
            return false;
        }
        // Link the node to the right bucket linked list
        strcpy(n->word, word);
        n->next = table[value];
        table[value] = n;
        SIZE++;
    }

    // Close the dictionary file
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return SIZE;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        // Iterate over each node in the bucket
        node *tmp1 = table[i], *tmp2 = table[i];
        while (tmp1 != NULL)
        {
            tmp2 = tmp1;
            tmp1 = tmp1->next;
            free(tmp2);
        }
    }
    return true;
}
