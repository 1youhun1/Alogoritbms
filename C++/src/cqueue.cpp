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
	//�Ƚ�����������β
	return this->ListInsertNext(this->ListTail(), data);
}

int CQueue::QueueDequeue(void **data)
{
	//�Ƚ��������ȡ��ͷ
	return this->ListRemoveNext(NULL, data);
}
