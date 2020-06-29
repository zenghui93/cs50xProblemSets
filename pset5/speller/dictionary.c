// Implements a dictionary's functionality
#include <string.h>
#include <strings.h>
#include <cs50.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
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
const unsigned int N = 26;
int word_counter = 0;
bool load_success = false;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    bool found = false;
    int l = strlen(word);
    
    if (l <= 45)
    {
        char new_word[l + 1];
        for (int i = 0; word[i] != '\0'; i++)
        {
            if (isalpha(word[i]))
            {
                new_word[i] = tolower(word[i]);
            
            }
            if (word[i] == 39)
            {
                new_word[i] = 39;
            }
        
        }
        new_word[l] = '\0';
        int index = hash(new_word);
  
        if (table[index] != NULL)
        {
            for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
            {
                if (strcmp(cursor->word, new_word) == 0)
                {
                    found = true;
        
                }
            }
            
            
        }
     
    }
    return found;
    
}


// Hashes word to a number. 
unsigned int hash(const char *word)
{
 
    unsigned int index = 0;
    index = word[0] - 'a';
    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    unsigned int index;
    
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        load_success = false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    
    char word[LENGTH  +  1];
    
    while (fscanf(file, "%s", word) != EOF) 
    {
        node *n = malloc(sizeof(node));
        if (n != NULL)
        {
            strcpy(n->word, word);
            n->next = NULL;
           
        }
        index = hash(word);
        if (table[index] == NULL)
        {
            table[index] = n;
            word_counter++;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
            word_counter++;
                
        }
    }//while
    
    fclose(file);
   
    load_success = true;
   
    return load_success;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (!load_success)
    {
        return 0;
    }
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    if (!load_success)
    {
        return false;
    }
    
    for (int i = 0; i < N; i++)
    {
        
        if (table[i] != NULL)
        {
            node *cursor = table[i];
            while (cursor != NULL)
            {
                node *tmp = cursor;
                cursor = cursor->next;
                free(tmp);
            }
           
        }
    }
    
    return true;
}

