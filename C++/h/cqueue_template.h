/*cqueue_template.h*/
#ifndef CQUEUE_TEMPLATE_H
#define CQUEUE_TEMPLATE_H

#include "clist_template.h"

template<class T>
class CQueue_Template :public Clist_Template<T>
{
public:
	CQueue_Template();
	~CQueue_Template();

public:
	int QueueEnqueue(const T *data);
	int QueueDequeue(T **data);
	T* QueuePeek() { return (this->head == NULL ? NULL : this->head->data); }
};

template<class T>
CQueue_Template<T>::CQueue_Template()
{
}

template<class T>
CQueue_Template<T>::~CQueue_Template()
{
}

template<class T>
int CQueue_Template<T>::QueueEnqueue(const T *data)
{
	//�Ƚ�����������β
	return this->ListInsertNext(this->ListTail(), data);
}

template<class T>
int CQueue_Template<T>::QueueDequeue(T **data)
{
	//�Ƚ��������ȡ��ͷ
	return this->ListRemoveNext(NULL, data);
}


#endif