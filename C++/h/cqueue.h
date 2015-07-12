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
	int QueueEnqueue(const void *data);
	int QueueDequeue(void **data);
	void* QueuePeek() { return (this->head == NULL ? NULL : this->head->data); }
};

#endif