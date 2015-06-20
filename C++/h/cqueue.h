/*cqueue.h*/
#ifndef CQUEUE_H
#define CQUEUE_H

#include <stdlib.h>
#include "clist.h"

class CQueue:public Clist
{
public:
	CQueue();
	~CQueue();

public:
	int Queue_Enqueue(const void *data);
	int Queue_Dequeue(void **data);
	void* Queue_Peek() { return (this->head == NULL ? NULL : this->head->data); }
};

#endif