// list.hpp
//
// Thread-safe linked-list implementation. 

#pragma once

#include <stdint.h>

 /* ----------------------------------------------------------------------------
     Global Types
 */

typedef struct list list_t;

typedef void(*deletefunc_f)(void*);
typedef void(*printfunc_f)(void*);

/* ----------------------------------------------------------------------------
    Global Functions
*/

/*
 * list_create
 * Initialize a new list data structure.
 *
 * Arguments:
 *	printfunc  - pointer to data-dependent print function
 *	deletefunc - pointer to data-dependent deallocation function
 *
 * Returns:
 *	pointer to newly initialized list
 *	nullptr on initialization error
 */
list_t* list_create(
    printfunc_f,
    deletefunc_f
    );

/*
 * list_size
 * Query the number of items in the list.
 *
 * Arguments:
 *  list - pointer to initialized list data structure
 *
 * Returns:
 *  number of elements in the list if successful
 *  -1 on error
 */
int list_size(list_t* list);

/*
 * list_find
 * Find item in list specified by key.
 *
 * Arguments:
 *	list - pointer to initialized list data structure
 *	key  - key to search for
 *
 * Returns:
 *	pointer to corresponding data if successful
 *	nullptr if key is not found, or other error occurs
 */
void* list_find(list_t* list, uint32_t key);

/*
 * list_insert
 * Insert element with specified data into list, keyed by key.
 *
 * Arguments:
 *	list - pointer to initialized list data structure
 *	key  - key of element to insert
 *	data - pointer to data associated with key
 *
 * Returns:
 *	 0 if insertion is successful
 *	 1 if data with given key is already in the list (insertion not performed)
 *	-1 if other error occurs during insertion
 */
int list_insert(list_t* list, uint32_t key, void* data);

/*
 * list_remove
 * Remove the element specified by key from the list.
 *
 * Arguments:
 *	list - pointer to initialized list data structure
 *	key  - key of element to remove
 *
 * Returns:
 *	pointer to data of element keyed by key
 *	nullptr if key not found, or error occurs during removal
 */
void* list_remove(list_t* list, uint32_t key);

/*
 * list_destroy
 * Deallocate existing list data structure, including contents.
 *
 * IMPORTANT:
 * This method is NOT thread-safe; multiple threads are (semantically)
 * permitted to call this method concurrently, but this will result in
 * undefined behavior. Programmer must ensure this does not occur.
 *
 * Arguments:
 *	list - pointer to initialized list data structure
 */
void list_destroy(list_t* list);

/*
 * list_print
 * Print a textual representation of list contents to stdout.
 *
 * Arguments:
 *	list - pointer to initialized list data structure
 */
void list_print(list_t* list);
