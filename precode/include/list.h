/**
 * @file list.h
 * @author Steffen Viken Valvaag
 * @brief Defines a linked list.
 * @version 0.1
 * 
 * Defines the interface for a linked list, (implementation is of a doubly linked list).
 */
#ifndef LIST_H
#define LIST_H

#include "common.h"


/**
 * @brief The type of the list.
 * @struct list
 */
typedef struct list list_t;


/**
 * @brief Creates a new empty list.
 * 
 * @param cmpfunc The compare function to use for the list.
 * @return list_t* A pointer to the allocated list.
 * 
 * The comparison function should return the following values:
 * @code 
 * 0 -> a == b
 * < 0 -> a < b
 * > 0 -> a > b
 * @endcode
 */
list_t *list_create(cmpfunc_t cmpfunc);


/**
 * @brief Destroys the given list.
 * 
 * @warning Subsequently accessing the list leads to undefined behaviour. The elements of the list are not destroyed.
 * @param list The list to deallocate.
 */
void list_destroy(list_t *list);

/**
 * @brief Get the current size of the list.
 * 
 * @param list The list to get the size of.
 * @return int The size of the list, ie. the number of elements. 
 */
int list_size(list_t *list);


/**
 * @brief Adds the given element to the start of the list.
 * 
 * @param list The list to add the element to.
 * @param elem The element to add.
 * @return int Returns 1 on success, returns 0 if the operation fails.
 */
int list_addfirst(list_t *list, void *elem);

/**
 * @brief Adds the given element to the end of the list.
 * 
 * @param list The list to add the element to.
 * @param elem The element to add.
 * @return int Returns 1 on success, returns 0 if the operation fails.
 */
int list_addlast(list_t *list, void *elem);

/**
 * @brief Removes and returns the first element of the list.
 * 
 * @param list The list to remove the element from.
 * @return void* The pointer to the element.
 */
void *list_popfirst(list_t *list);

/**
 * @brief Removes and returns the last element of the list.
 * 
 * @param list The list to remove the element from.
 * @return void* The pointer to the element.
 */
void *list_poplast(list_t *list);



/**
 * @brief Checks whether an element is in the list.
 * 
 * @param list The list to check.
 * @param elem The element to find.
 * @return int Returns 1 if the element is in the list, 0 otherwise.
 * 
 * The function uses the comparison function in the list struct.
 */
int list_contains(list_t *list, void *elem);



/**
 * @brief Sorts the list elements using the compare function.
 * 
 * @param list The list to sort.
 */
void list_sort(list_t *list);

/**
 * @brief The type of the list iterator.
 */
typedef struct list_iter list_iter_t;



/**
 * @brief Creates a new iterator pointing to the start of the list.
 * 
 * @param list The list to iterate.
 * @return list_iter_t* A pointer to a list iterator.
 */
list_iter_t *list_createiter(list_t *list);


/**
 * @brief Destroys the given iterator.
 * 
 * @param iter The iterator to deallocate.
 */
void list_destroyiter(list_iter_t *iter);



/**
 * @brief Check if the list has another element.
 * 
 * @param iter The iter to check.
 * @return int Returns 1 if there are more elements, 0 if the iterator is at the end.
 */
int list_hasnext(list_iter_t *iter);



/**
 * @brief Returns the current element of the iterator and advances it one step forward.
 * 
 * @param iter The iterator of the list.
 * @return void* The current element pointed to by the iterator. NULL if there are no more elements.
 */
void *list_next(list_iter_t *iter);

#endif
