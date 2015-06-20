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
	int Stack_Push(const T *data);
	int Stack_Pop(T **data);
	T* Stack_Peek() {
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
int CStack_Template<T>::Stack_Push(const T *data)
{
	//先进：插入表头
	return this->List_Ins_Next(NULL, data);
}

template<class T>
int CStack_Template<T>::Stack_Pop(T **data)
{
	//先出：删除表头
	return this->List_Rem_Next(NULL, data);
}

#endif