/*cqueue.c*/
#include <stdlib.h>

#include "clist.h"
#include "cqueue.h"


CQueue::CQueue()
{
}

CQueue::~CQueue()
{
}

int CQueue::Queue_Enqueue(const void *data)
{
	//�Ƚ�����������β
	return this->List_Ins_Next(this->List_Tail(), data);
}

int CQueue::Queue_Dequeue(void **data)
{
	//�Ƚ��������ȡ��ͷ
	return this->List_Rem_Next(NULL, data);
}
