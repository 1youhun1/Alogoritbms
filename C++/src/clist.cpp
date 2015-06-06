/*list.c*/
#include <stdlib.h>
#include <string.h>

#include "clist.h"

Clist::Clist()
{
	size = 0;
	head = NULL;
	tail = NULL;
	destroy = NULL;
	match = NULL;
}

Clist::~Clist()
{

}

void Clist::List_Init(void(*destroy)(void *data))
{
	this->destroy = destroy;
	return;
}

void Clist::List_Destroy()
{
	void *data;

	//ɾ��ÿһ��Ԫ��
	while (this->List_Size() > 0)
	{
		if (0 == List_Rem_Next(NULL, (void **)&data) &&
			(NULL != this->destroy))
		{
			this->destroy(data);
		}
	}
	memset(this, 0, sizeof(Clist));
	return;
}

int Clist::List_Ins_Next(ListElmt *element, const void *data)
{
	ListElmt *new_element = new ListElmt;

	new_element->data = (void *)data;
	if (NULL == element)
	{
		/*�׽ڵ����*/
		if (0 == this->List_Size())
		{
			this->tail = new_element; //β�ڵ�=�׽ڵ�
		}

		new_element->next = this->head;
		this->head = new_element;
	}
	else
	{
		if (NULL == element->next)
		{
			this->tail = new_element;
		}

		new_element->next = element->next;
		element->next = new_element;
	}

	this->size++;
	return 0;
}

/*û��ָ��ǰ���ڵ��ָ�룬Ϊ�˴�������ɾ��nextԪ��*/
int Clist::List_Rem_Next(ListElmt *element, void **data/*�ݴ���ͷ�Ԫ��*/)
{
	ListElmt *old_element;

	if (0 == this->List_Size())
	{
		return -1;
	}

	if (NULL == element) //���׽ڵ㿪ʼɾ��
	{
		*data = this->head->data;
		old_element = this->head;
		this->head = this->head->next;

		if (1 == this->List_Size())//��������һ��Ԫ�أ�β�ڵ��ÿ�
		{
			this->tail = NULL;
		}
	}
	else
	{
		if (NULL == element->next)
		{
			return -1;
		}

		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;

		if (NULL == element->next)
		{
			this->tail = element;
		}
	}

	delete(old_element);
	this->size--;
	return 0;
}