/**
 * @file trie.h
 * @author Morten Grønnesby (morten.gronnesby@uit.no)
 * @brief Defines a trie.
 * @version 0.1
 * 
 * Defines a non-space optimized trie that uses the english alphabet as radix.
 */

#ifndef TRIE_H
#define TRIE_H

#include "common.h"


/**
 * @brief Struct to hold a trie.
 * @struct trie
 */
typedef struct trie trie_t;
typedef struct node node_t;
typedef struct word_posistion word_posistion_t;

struct word_posistion
{
    char *word;
    char *doc_name;
    int *pos;
};



/**
 * @brief Allocates an empty trie structure.
 * 
 * @return trie_t* Pointer to an empty trie
 */
trie_t *trie_create();


/*
 * Destroys the given trie and its nodes
 */

/**
 * @brief Destroys the given trie.
 * 
 * @param trie Pointer to the trie to destroy.
 * 
 * The given trie will be destroyed.
 * Allocated keys and values will not be destroyed.
 */
void trie_destroy(trie_t *trie);


/*
 * Inserts a key and value into the trie
 */

/**
 * @brief Insert a key and value into the trie.
 * 
 * @param trie Reference to the trie.
 * @param key A key to insert, this will be used to create the internal node path.
 * @param value An optional value, this is not used internally in the trie.
 * @return int Returns 0 on success and -1 on fail.
 * 
 * The trie only accepts alphabetical characters, will not insert words containing other symbols.
 * The key is used to insert into the trie, as the index into the nodes array.
 * The key and value reference of the internal nodes will be NULL, and the leaf node will contain pointers to the given key and value.
 */
int trie_insert(trie_t *trie, char *key, void *value, int wordpos, char *next_word);



/*
 * Finds a word in the trie.
 * IMPLEMENT THIS TO WORK WITH YOUR DESIGN.
 */

/**
 * @brief Find the closest word starting with prefix.
 * 
 * @param t Pointer to the trie
 * @param prefix The prefix to search for.
 * @return char* The closest word starting with prefix. NULL if no word was found.
 */
char *trie_find(trie_t *t, char *prefix);

//searches for the closest alphabetical word
char *trie_autocomplete(trie_t *trie, char *input);


#endif

