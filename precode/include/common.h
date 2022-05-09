/**
 * @file common.h
 * @author Steffen Viken Valvaag\n
 * Modified by: Morten Grønnesby (morten.gronnesby@uit.no)
 * @brief Defines common utility functions.
 * @version 0.1
 * 
 * Common utility functions mostly for interacting with files and the file system.
 */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdarg.h>

struct list;

/**
 * @brief Defines the compare function type.
 */
typedef int (*cmpfunc_t)(void *, void *);

/**
 * @brief Defines the exhange function type.
 */
typedef void (*exchfunc_t)(void *, void *);

/**
 * @brief Defines the hash function type.
 */
typedef unsigned long (*hashfunc_t)(void *);



/**
 * @brief Reads the given file and parses it into words (tokens).
 * 
 * @param[in] filepath The string containing the path to the file to be read.
 * @param[in,out] list The list to put the tokens into.
 * 
 * Function opens and reads the given filepath and breaks the text into words (tokens).
 * All tokens are put into the given list in the order that they occur.
 * 
 * The tokenizer preserves the following special characters:
 * "* \n\t\".,!:;?()-*"
 * 
 * In addition to each word, the tokenizer inserts whitespace in between each token that is not a special character.
 * This is to accurately represent the text in the file.
 */
void tokenize_file(const char *filepath, struct list *list);


/**
 * @brief Recursively finds the names of all files under the given root directory.
 * 
 * @param[in] root The root directory to start scanning from.
 * @return struct list* A list of filenames scanned recursively from the root directory.
 */
struct list *find_files(const char *root);

/**
 * @brief Compares two strings using strcmp.
 * 
 * @param a The first string.
 * @param b The second string.
 * @return int Returns 0 if the strings are equal. Returns another number otherwise (both negative and positive).
 */
int compare_strings(void *a, void *b);

/**
 * @brief Hashes a string.
 * 
 * @param s A null terminated input string.
 * @return unsigned long The hash of the string.
 */
unsigned long hash_string(void *s);



/**
 * @brief Compares two pointers.
 * 
 * @param a The first pointer.
 * @param b The second pointer.
 * @return int Returns 0 if the pointers are equal. Returns > 0 if a is larger, returns < 0 if b is larger.
 * 
 * Compares two pointers ordering, i.e. by
 * comparing the actual addresses that they point to.
 */
int compare_pointers(void *a, void *b);


/**
 * @brief Concatenates a number of strings.
 * 
 * @param num_strings Number of strings to concatenate.
 * @param first The first string to concatenate.
 * @param ... Any number of strings to concatenate.
 * @return char* The complete concatenated string (allocated using malloc).
 */
char *concatenate_strings (int num_strings, const char *first, ...);


/**
 * @brief Checks if the given path is a valid directory.
 * 
 * @param dirpath The directory path to check.
 * @return int returns 1 if valid, 0 otherwise.
 */
int is_valid_directory (const char *dirpath);



/**
 * @brief Checks if the given path is a valid regular file.
 * 
 * @param filepath The file path to check.
 * @return int Returns 1 if valid, 0 otherwise.
 */
int is_valid_file (const char *filepath);


/**
 * @brief Get the current time in microseconds
 * 
 * @return unsigned long long The current UNIX time in microseconds (may wrap around).
 */
unsigned long long gettime();

#endif
