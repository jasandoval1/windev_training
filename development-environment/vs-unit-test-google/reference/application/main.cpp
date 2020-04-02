// main.cpp
//
// Application entry point.

#include "list.hpp"

void custom_print(void* data)
{
	(void*)(data);
	// print a list element
}

void custom_delete(void* data)
{
	(void*)(data);
	// delete a list element
}

int main()
{
	list_t* l = list_create(custom_print, custom_delete);
	if (NULL == l)
	{
		// something went wrong...
	}

	// do things with my list!

	list_destroy(l);

	return 0;
}