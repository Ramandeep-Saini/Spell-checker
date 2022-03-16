// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
const unsigned int N = 50000;

// Hash table
node *table[N];

int d_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash word gets hash value
    int hash_value = hash(word);

    // Access linked list at that index in hash table
    node *n = table[hash_value];

    // Traverse linked list, looking for word (strcasecomp)
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // Function takes a string and returns a hash index
    // This hash function finds the sum of all the ASCII values of the characters in the word
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //opening dictionary file
    FILE *d_pointer = fopen(dictionary, "r");

    if (dictionary == NULL)
    {
        printf("Can't open %s\n", dictionary);
        return false;
    }

    //word array
    char next_w[LENGTH + 1];

    // Reading strings from dictionary file
    while (fscanf(d_pointer, "%s", next_w) != EOF)
    {
        // Creating new node for every word
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        // copying words into nodes
        strcpy(n->word, next_w);

        // Hash word gets hash value
        int hash_value = hash(next_w);

        // Insert node into hash table at location
        n->next = table[hash_value];
        table[hash_value] = n;
        d_size++;
    }

    // Close file
    fclose(d_pointer);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return d_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate hash table + free nodes in the linked lists
    for (int i = 0; i < N; i++)
    {
        // Assign cursor
        node *n = table[i];

        // Loop through linked list
        while (n != NULL)
        {
            // Make temp equal cursor;
            node *tmp = n;

            // Point cursor to next element
            n = n->next;

            // free temp
            free(tmp);
        }
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}