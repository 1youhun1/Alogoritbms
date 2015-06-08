/*clist.c*/
#include <stdlib.h>
#include <string.h>

#include "cdlist.h"

CDoubleList::CDoubleList()
{
	size = 0;
	head = NULL;
	tail = NULL;
	destroy = NULL;
	match = NULL;
}

CDoubleList::~CDoubleList()
{

}

void CDoubleList::DoubleList_Init(void(*destroy)(void *data))
{
	this->destroy = destroy;
	return;
}

void CDoubleList::DoubleList_Destroy()
{
	void *data;

	while (this->DoubleList_Size() > 0)
	{
		if (0 == DoubleList_Remove(this->DoubleList_Tail(), ((void **)&data))
			&& NULL != this->destroy)
		{
			this->destroy(data);
		}
	}

	memset(this, 0, sizeof(CDoubleList));
	return;
}

int CDoubleList::DoubleList_Ins_Next(DListElmt *element, const void *data)
{
	//只有list为NULL时才允许在空element后插入新元素
	if (NULL == element && 0 != this->DoubleList_Size())
		return -1;

	DListElmt *new_element = new DListElmt{ 0 };
	if (NULL == new_element)
		return -1;

	new_element->data = (void *)data;

	if (0 == this->DoubleList_Size())
	{
		this->head = new_element;
		this->head->prev = NULL;
		this->head->next = NULL;
		this->tail = NULL;
	}
	else
	{
		//增加元素,先将变更本节点
		new_element->next = element->next;
		new_element->prev = element;

		//再变更后节点
		if (NULL == element->next)
			this->tail = new_element;
		else
			element->next->prev = new_element;
		//变更前节点
		element->next = new_element;
	}

	this->size++;
	return 0;
}

int CDoubleList::DoubleList_Ins_Prev(DListElmt *element, const void *data)
{
	//只有list为NULL时才允许在空element前插入新元素
	if (NULL == element && 0 != this->DoubleList_Size())
		return -1;

	DListElmt *new_element = new DListElmt{ 0 };
	if (NULL == new_element)
		return -1;

	new_element->data = (void *)data;

	if (0 == this->DoubleList_Size())
	{
		this->head = new_element;
		this->head->prev = NULL;
		this->head->next = NULL;
		this->tail = NULL;
	}
	else
	{
		new_element->next = element;
		new_element->prev = element->prev;

		if (NULL == element->prev)
			this->head = new_element;
		else
			element->prev->next = new_element;

		element->prev = new_element;
	}

	this->size++;
	return 0;
}

int CDoubleList::DoubleList_Remove(DListElmt *element, void **data)
{
	if (NULL == element || 0 == this->DoubleList_Size())
		return -1;

	*data = element->data;

	if (element == this->head)
	{
		this->head = element->next;

		if (NULL == this->head)
			this->tail = NULL;
		else
			element->next->prev = NULL; //首节点前节点置为NULL
	}
	else
	{
		element->prev->next = element->next;

		if (NULL == element->next)
			this->tail = element->prev;
		else
			element->next->prev = element->prev;
	}

	delete(element);
	this->size--;
	return 0;
}