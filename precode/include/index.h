/** 
 * @file index.h
 * @brief The interface for the document index.
 *  
 * Defines the interface for a searchable document index.
 * 
 */


#ifndef INDEX_H
#define INDEX_H

#include "list.h"
#include "trie.h"


/**
 * @brief Reference to the index.
 * @struct index
 * 
 * The members of the struct are not exposed outside index.c.
 * Used with all index functions.
 */
typedef struct index index_t;


/**
 * @brief Reference to a single search result.
 * @struct search_result
 * 
 * The members of the struct are not exposed outside index.c.
 * 
 * Used as an iterator for the search results after a query.
 * The struct refers to a *single search* accross multiple documents.
 * Therefore the struct has to keep track of what the current result is, and what the current document is.
 */
typedef struct search_result search_result_t;


/**
 * @brief Struct used to hold a single search hit.
 * @struct search_hit
 * 
 * @warning You can add any member to this struct, but do not remove the existing members.
 * 
 * Used to represent a single search hit within a document.
 */
typedef struct search_hit search_hit_t;
struct search_hit
{
    int location; /**< The index of a search hit within the document text */
    int len;      /**< The length of the search hit */
};

/**
 * @brief Creates a new, empty index.
 * @return Pointer to an index_t struct. Returns NULL on error.
 *  
 * Allocates memory for the index struct and its members.
 * If the index_t struct contains other structures (lists or hashtables etc.) these should be initialized here.
 */
index_t *index_create();


/**
 * @brief Destroys the given index.
 * @param[in] index The index to deallocate.
 * 
 * The function deallocates all members of the index struct.
 * Any word that are contained in the index, should also be deallocated here (or in another appropriate function).
 */
void index_destroy(index_t *index);


/**
 * @brief Adds a new document to the index.
 * 
 * @param[in,out] idx The index which to add the new document.
 * @param[in] document_name The name of the document being added.
 * @param[in] words A linked list containing all the words and special characters in the document.
 * 
 * The function adds the content of a new document to the index.
 * The name of the document is not necessarily required, but could be preserved. It will be deallocated by the caller after the function.
 * 
 * The supplied list of words will be deallocated after this function, but not the words.
 * The callie is responsible for deallocating the words after use.
 */
void index_add_document(index_t *idx, char *document_name, list_t *words);


/**
 * @brief Searches the index for a query.
 * 
 * @param[in,out] idx The index to search.
 * @param[in] query The search string, given as is from the UI.
 * @return search_result_t* A pointer to an iterator for the results.
 * 
 * The function should search the index for the given query.
 * The query can be either a single word, or multiple words separated by spaces.
 * 
 * The function can *either* search for a continuous sentence, or each word individually.
 * If the function searches for sentences, then it should be an exact match between the query and the result.
 * Otherwise the spaces should be treated as separators between query words.
 * 
 * The function searches for the query accross multiple documents.
 * The return value must handle iteration of all search hits accross all documents.
 * 
 * The query string should be deallocated by the function before returning.
 */
search_result_t *index_find(index_t *idx, char *query);


/**
 * @brief Returns the most similar word to the given input.
 * 
 * @param[in,out] idx The index containing searchable words.
 * @param[in,out] input A partial string to complete.
 * @param[in] size The length of the input string, excluding the null-terminator.
 * @return char* A null-terminated string containing the word closest to the input. NULL if no word is found.
 * 
 * Completes a word starting with the string input. The return value should be the whole word and must be null-terminated.
 */
char *autocomplete(index_t *idx, char *input, size_t size);



// Result handling


/**
 * @brief Returns the content of the current document.
 * 
 * @param[in,out] res The result context (iterator).
 * @return char** An array of char arrays containing the words of the current document. NULL if there are no more documents.
 * 
 * Since there are multiple documents in the index, this function returns the content of the document pointed to by the struct.
 * Subsequent calls to this function should return the content for the next document, ie the function should only be called once per document.
 * The function is equivalent to calling a next function for documents.
 * The function returns NULL when there are no more documents in the search result.
 */
char **result_get_content(search_result_t *res);



/**
 * @brief Get the length of the current document.
 * 
 * @param[in] res The result context (iterator).
 * @return int The length (in number of words) of the current document.
 * 
 * Function returns the length of the current document.
 * Length is the number of words, or length in the first dimension of the char ** array returned by 
 * Subsequent calls returns the length of the same document.
 */
int result_get_content_length(search_result_t *res);



/**
 * @brief Get the next word in the result.
 * 
 * @param[in,out] res The result context (iterator).
 * @return search_hit_t* A pointer to the current search hit. Returns NULL when there are no more word hits.
 * 
 * The function should return a @sa search_hit_t struct, which represent the current search hit (location and length) in the current document.
 * Subsequent calls to this function advances the iterator.
 * The function is equivalent to a next function for search hits.
 * The function returns NULL when there are no more search hits in the current document.
 * 
 * To get the search results of the next document, result_get_content must be called first.
 * 
 */
search_hit_t *result_next(search_result_t *res);


#endif


