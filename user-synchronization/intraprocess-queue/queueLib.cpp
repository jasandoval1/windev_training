// queueLib.cpp : Defines the functions for the static library.

#include "pch.h"
#include <Windows.h>
#include <string>
#include "queueLib.h"


struct Queue
{
	struct QueueNode *head;
	struct QueueNode *tail;
	int				  size;
	int				  max;
};

struct QueueNode
{
	struct QueueNode *next;
	void			 *data;
};

typedef QueueNode QueueNode_t;
static QueueNode_t* QueuenodeInit(void* data);

Queue_t *QueueInit(int maxSize)
{
	if (1 > maxSize)
	{
		return NULL;
	}
	HANDLE heapHandle = GetProcessHeap();
	if (NULL == heapHandle)
	{
		return NULL;
	}
	Queue_t* newQueue = (Queue_t*)HeapAlloc(heapHandle, HEAP_ZERO_MEMORY, sizeof(Queue_t));
	if (NULL != newQueue)
	{
		newQueue->max = maxSize;
	}
	CloseHandle(heapHandle);
	return newQueue;
}

BOOL QueuePush(void* data)
{
	return FALSE;
}

void *QueuePop(void)
{
	return NULL;
}

void QueueDestroy(Queue_t* queue)
{
	return;
}

static QueueNode_t* QueueNodeInit(void* data)
{
	HANDLE heapHandle = GetProcessHeap();
	if (NULL == heapHandle)
	{
		return NULL;
	}
	QueueNode_t* newNode = (QueueNode_t*)HeapAlloc(heapHandle, HEAP_ZERO_MEMORY, sizeof(QueueNode_t));
	CloseHandle(heapHandle);
	return newNode;
}

