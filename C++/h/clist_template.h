/*clist_template.h*/
#ifndef CLIST_TEMPLATE_H
#define CLIST_TEMPLATE_H

#include <stdlib.h>

template<class T>
struct ListNode
{
	T *data;
	ListNode<T> *next;
};

template<class T>
class Clist_Template
{
private:
	ListNode<T> *head;
	ListNode<T> *tail;
	int size;

public:
	Clist_Template(void);
	~Clist_Template(void);
	int List_Size(void) { return size; }
	ListNode<T> *List_Head() { return head; }
	ListNode<T> *List_Tail() { return tail; }
	bool List_is_Head(ListNode<T> *element) {
		return ((element) == head ? true : false);
	}
	bool List_is_Tail(ListNode<T> *element) {
		return ((element)->next == NULL ? true : false);
	}

	int(*match)(const T *key1, const T *key2);
	void(*destroy)(T *data);
	void List_Init(void(*destroy)(T *data));
	void List_Destroy(void);
	int List_Ins_Next(ListNode<T> *element, const T *data);
	int List_Rem_Next(ListNode<T> *element, T **data);

};

template<class T>
Clist_Template<T>::Clist_Template()
{
	size = 0;
	head = NULL;
	tail = NULL;
	destroy = NULL;
	match = NULL;
}

template<class T>
Clist_Template<T>::~Clist_Template()
{

}

template<class T>
void Clist_Template<T>::List_Init(void(*destroy)(T *data))
{
	this->destroy = destroy;
	return;
}

template<class T>
void Clist_Template<T>::List_Destroy()
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
	memset(this, 0, sizeof(Clist_Template));
	return;
}

template<class T>
int Clist_Template<T>::List_Ins_Next(ListNode<T> *element, const T *data)
{
	ListNode<T> *new_element = new ListNode<T>;

	new_element->data = (T *)data;
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

template<class T>
/*û��ָ��ǰ���ڵ��ָ�룬Ϊ�˴�����ɾ��nextԪ��*/
int Clist_Template<T>::List_Rem_Next(ListNode<T> *element, T **data/*�ݴ���ͷ�Ԫ��*/)
{
	ListNode<T> *old_element;

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


#endif