/*cqueue.cpp*/
#include <stdlib.h>

#include "..\h\clist.h"
#include "..\h\cqueue.h"


CQueue::CQueue()
{
}

CQueue::~CQueue()
{
}

int CQueue::QueueEnqueue(const void *data)
{
	//先进后出：插入队尾
	return this->ListInsertNext(this->ListTail(), data);
}

int CQueue::QueueDequeue(void **data)
{
	//先进后出：获取队头
	return this->ListRemoveNext(NULL, data);
}
