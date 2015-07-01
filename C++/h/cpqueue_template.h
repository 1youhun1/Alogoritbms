/*cpqueue_template.h 优先级队列，用堆实现*/
#ifndef CPQUEUE_TEMPLATE_H
#define CPQUEUE_TEMPLATE_H

#include "cheap_template.h"

template<class T>
class CPQueue_Template : public CHeap_Template<T>
{
public:
	CPQueue_Template();
	~CPQueue_Template();

public:
	void PqueueInit(int(*compare)(const T *key1, const T *key2), void(*destroy)(T *data))
	{
		return HeapInit(compare, destroy);
	}
	void PqueueDestory()
	{
		return HeapDestroy();
	}
	int PqueueInsert(const T *data)
	{
		return HeapInsert(data);
	}
	int PqueueExtract(T **data)
	{
		return HeapExtract(data);
	}

public:
	T *PqueuePeek()
	{
		return ((this)->tree == NULL ? NULL : (this)->tree[0]);
	}
	int PqueueSize()
	{
		return this->size;
	}
};

#endif