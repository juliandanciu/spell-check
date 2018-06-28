/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

//type define a trie structure into which we will load dictionary
    typedef struct trie{
        bool is_word; //make sure is_word is initally false?
        struct trie *next[27]; //make sure next is NULL initially?
    } trie;
    
    trie *root;

/**
 * Returns true if word is in dictionary else false.
 */
unsigned int count(trie *trav);
bool erase(trie *trav);
bool checkNULL(trie *trav);
void makeNULL(trie *trav);
int convert(char letter);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
