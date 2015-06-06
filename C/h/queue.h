/*queue.h*/
#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "list.h"

typedef List Queue;

#define Queue_Init List_Init
#define Queue_Destroy List_Destroy
int Queue_Enqueue(Queue *queue, const void *data);
int Queue_Dequeue(Queue *queue, void **data);
#define Queue_Peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)
#define Queue_Size List_Size

#endif