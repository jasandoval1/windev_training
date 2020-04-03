// list.c
//
// Thread-safe linked-list implementation.

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "list.hpp"

 /* ----------------------------------------------------------------------------
	 Local Types
 */

typedef struct listnode {
	uint32_t         key;
	void* data;
	struct listnode* next;
	struct listnode* prev;
} listnode_t;

/* ----------------------------------------------------------------------------
	Global Types
*/

typedef struct list {
	struct listnode* head;          // first element in list 
	printfunc_f       printfunc;     // data print function
	deletefunc_f      deletefunc;    // data deallocation function 
	CRITICAL_SECTION  lock;          // lock for thread safety 
} list_t;

/* ----------------------------------------------------------------------------
	Local Functions
*/

/*
 * listnode_create
 * Initialize a new listnode structure.
 *
 * Returns:
 * 	pointer to new listnode on success
 *	NULL on initialization error
 */
listnode_t* listnode_create(uint32_t key, void* data)
{
	listnode_t* node = (listnode_t*)calloc(1, sizeof(struct listnode));
	if (nullptr == node)
	{
		return nullptr;
	}

	node->key = key;
	node->data = data;
	node->next = nullptr;
	node->prev = nullptr;

	return node;
}

/*
 * key_in_list
 * Determine if given key is in the list.
 *
 * Returns:
 *	True if element keyed by specified key is in list
 *	False otherwise
 */
bool key_in_list(list_t* list, uint32_t key)
{
	listnode_t* current = list->head;
	while (current != nullptr)
	{
		if (current->key == key)
		{
			return true;
		}

		current = current->next;
	}

	return false;
}

/*
 * is_empty
 * Determine if the list is empty.
 *
 * Returns:
 *	True if the list contains 0 elements
 *	False otherwise
 */
bool is_empty(list_t* list)
{
	return list->head == nullptr;
}

/* ----------------------------------------------------------------------------
	Global Functions
	See module header (list.h) for detailed function comments.
*/

list_t* list_create(printfunc_f printfunc, deletefunc_f deletefunc)
{
	if (nullptr == printfunc || nullptr == deletefunc)
	{
		return nullptr;
	}

	list_t* list = (list_t*)calloc(1, sizeof(struct list));
	if (nullptr == list)
	{
		return nullptr;
	}

	list->head = nullptr;
	list->printfunc = printfunc;
	list->deletefunc = deletefunc;

	::InitializeCriticalSection(&list->lock);

	return list;
}

int list_size(list_t* list)
{
	if (nullptr == list)
	{
		return -1;
	}

	::EnterCriticalSection(&list->lock);

	if (is_empty(list))
	{
		::LeaveCriticalSection(&list->lock);
		return 0;
	}

	int count = 0;

	listnode_t* current = list->head;
	while (current != nullptr)
	{
		++count;
		current = current->next;
	}

	::LeaveCriticalSection(&list->lock);

	return count;
}

void* list_find(list_t* list, uint32_t key)
{
	if (nullptr == list)
	{
		return nullptr;
	}

	// initialize to NULL 
	void* data = nullptr;

	::EnterCriticalSection(&list->lock);

	if (is_empty(list))
	{
		::LeaveCriticalSection(&list->lock);
		return nullptr;
	}

	listnode_t* current = list->head;
	while (current != nullptr)
	{
		if (current->key == key)
		{
			data = current->data;
			break;
		}
		current = current->next;
	}

	::LeaveCriticalSection(&list->lock);

	return data;
}

int list_insert(list_t* list, uint32_t key, void* data)
{
	if (nullptr == list)
	{
		return -1;
	}

	listnode_t* node = listnode_create(key, data);
	if (nullptr == node)
	{
		return 1;
	}

	int rc = 0;

	::EnterCriticalSection(&list->lock);

	if (is_empty(list))
	{
		list->head = node;
	}
	else if (key_in_list(list, key))
	{
		// do not perform insertion if already present 
		rc = 1;
	}
	else
	{
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}

	::LeaveCriticalSection(&list->lock);

	return rc;
}

void* list_remove(list_t* list, uint32_t key)
{
	if (nullptr == list)
	{
		return nullptr;
	}

	void* data = nullptr;

	::EnterCriticalSection(&list->lock);

	listnode_t* current = list->head;
	while (current != nullptr) {
		if (current->key == key) {
			data = current->data;

			if (current->next != nullptr && current->prev != nullptr)
			{
				// current is fully contained within list 
				current->next->prev = current->prev;
				current->prev->next = current->next;
			}
			else if (current->next != nullptr && current->prev == nullptr)
			{
				// current is at head of non-singleton list 
				current->next->prev = nullptr;
				list->head = current->next;
			}
			else if (current->next == nullptr && current->prev != nullptr)
			{
				// current is at tail of non-singleton list
				current->prev->next = nullptr;
			}
			else
			{
				// current is the only element in list 
				list->head = nullptr;
			}
			break;
		}
		current = current->next;
	}

	::LeaveCriticalSection(&list->lock);

	// if current is not NULL, element was removed 
	if (current != nullptr)
	{
		free(current);
	}

	return data;
}

void list_destroy(list_t* list)
{
	if (nullptr == list)
	{
		return;
	}

	listnode_t* current = list->head;

	while (current != nullptr)
	{
		list->head = current->next;

		(*list->deletefunc)(current->data);
		free(current);

		current = list->head;
	}

	::DeleteCriticalSection(&list->lock);

	free(list);
}

void list_print(list_t* list) {

	if (nullptr == list)
	{
		return;
	}

	printf("***HEAD***\n\n");

	listnode_t* current = list->head;
	while (current != nullptr)
	{
		printf("------\n");
		printf("key: %u\n", current->key);
		(*list->printfunc)(current->data);
		printf("------\n\n");
		current = current->next;
	}

	printf("***TAIL***\n");
}
