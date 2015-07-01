/*cpqueue.h 优先级队列，用堆实现*/
#ifndef CPQUEUE_H
#define CPQUEUE_H

#include "cheap.h"

class CPQueue : public CHeap
{
public:
	CPQueue();
	~CPQueue();

public:
	void PqueueInit(int(*compare)(const void *key1, const void *key2), void(*destroy)(void *data))
	{
		return HeapInit(compare, destroy);
	}
	void PqueueDestory()
	{
		return HeapDestroy();
	}
	int PqueueInsert(const void *data)
	{
		return HeapInsert(data);
	}
	int PqueueExtract(void **data)
	{
		return HeapExtract(data);
	}

public:
	void *PqueuePeek()
	{
		return ((this)->tree == NULL ? NULL : (this)->tree[0]);
	}
	int PqueueSize()
	{
		return this->size;
	}
};

#endif