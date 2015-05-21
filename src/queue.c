/*queue.c 队列，用链表实现*/
#include <stdlib.h>

#include "list.h"
#include "queue.h"

int Queue_Enqueue(Queue *queue, const void *data)
{
	//先进后出：插入队尾
    return List_Ins_Next(queue, List_Tail(queue), data);
}

int Queue_Dequeue(Queue *queue, void **data)
{
	//先进后出：获取队头
    return List_Rem_Next(queue, NULL, data);
}