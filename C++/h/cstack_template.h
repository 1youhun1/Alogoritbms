/*cstack_template.h*/
#ifndef CSTACK_TEMPLATE_H
#define CSTACK_TEMPLATE_H

#include "clist_template.h"

template<class T>
class CStack_Template : public Clist_Template<T>
{
public:
	CStack_Template();
	~CStack_Template();

public:
	int StackPush(const T *data);
	int StackPop(T **data);
	T* StackPeek() {
		return (this->head == NULL ? NULL : this->head->data);
	}

};

template<class T>
CStack_Template<T>::CStack_Template()
{
}

template<class T>
CStack_Template<T>::~CStack_Template()
{
}

template<class T>
int CStack_Template<T>::StackPush(const T *data)
{
	//先进：插入表头
	return this->ListInsertNext(NULL, data);
}

template<class T>
int CStack_Template<T>::StackPop(T **data)
{
	//先出：删除表头
	return this->ListRemoveNext(NULL, data);
}

#endif