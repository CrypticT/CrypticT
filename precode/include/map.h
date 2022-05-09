/**
 * @file map.h
 * @author Steffen Viken Valvaag
 * @brief Defines a chained hash table.
 * @version 0.1
 */
#ifndef MAP_H
#define MAP_H

#include "common.h"

/**
 * @brief The type of the map.
 */
struct map;
typedef struct map map_t;


/**
 * @brief Creates a new empty hash table.
 * 
 * @param cmpfunc 
 * @param hashfunc 
 * @return map_t* 
 */
map_t *map_create(cmpfunc_t cmpfunc, hashfunc_t hashfunc);



/**
 * @brief Destroys the given map. Will also destroy keys and values if functions are supplied.
 * 
 * @param map The map to destroy.
 * @param destroy_key A pointer to a function to destroy the keys. Can be NULL.
 * @param destroy_val A pointer to a function to destroy the values. Can be NULL.
 * 
 * The function will destroy keys if the supplied destroy_key function is supplied.
 * The function will destroy values if the supplied destroy_values function is supplied.
 * If the arguments are NULL, the respective field is not touched.
 */
void map_destroy(map_t *map, void (*destroy_key)(void *), void (*destroy_val)(void *));


/**
 * @brief Maps the given key to the given value.
 * @warning If the given key exists in the map, its value will be overwritten.
 * @param map The map to insert the new entry into.
 * @param key The key to map.
 * @param value The value to map the key to.
 */
void map_put(map_t *map, void *key, void *value);



/**
 * @brief Check if a key is in the map.
 * 
 * @param map The map to check.
 * @param key The key to check.
 * @return int Returns 1 if the key is in the map, 0 otherwise.
 */
int map_haskey(map_t *map, void *key);



/**
 * @brief Returns the value the given key maps to.
 * 
 * @param map The map to get the key from.
 * @param key The key to get the value for.
 * @return void* A pointer to the element that the key is mapped to. NULL if the entry does not exist.
 */
void *map_get(map_t *map, void *key);


/**
 * @brief The djb2 hash algorithm.
 * 
 * @param bytes The bytes to hash.
 * @return unsigned long The hash.
 * 
 * Hash algorithm devised by Dan Bernstein.
 */
unsigned long djb2(void *bytes);


#endif
