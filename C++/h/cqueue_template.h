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
	int Queue_Enqueue(const T *data);
	int Queue_Dequeue(T **data);
	T* Queue_Peek() { return (this->head == NULL ? NULL : this->head->data); }
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
int CQueue_Template<T>::Queue_Enqueue(const T *data)
{
	//先进后出：插入队尾
	return this->List_Ins_Next(this->List_Tail(), data);
}

template<class T>
int CQueue_Template<T>::Queue_Dequeue(T **data)
{
	//先进后出：获取队头
	return this->List_Rem_Next(NULL, data);
}


#endif