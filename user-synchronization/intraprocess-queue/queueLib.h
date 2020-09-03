#pragma once

typedef struct Queue Queue_t;

Queue_t* QueueInit(int maxSize);

BOOL QueuePush(void* data);

void* QueuePop(void);

void QueueDestroy(Queue_t* queue);