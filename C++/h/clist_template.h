/*clist_template.h 用模板实现单向链表*/
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
	int ListSize(void) { return size; }
	ListNode<T> *ListHead() { return head; }
	ListNode<T> *ListTail() { return tail; }
	bool ListIsHead(ListNode<T> *element) {
		return ((element) == head ? true : false);
	}
	bool ListIsTail(ListNode<T> *element) {
		return ((element)->next == NULL ? true : false);
	}

public:
	int(*match)(const T *key1, const T *key2);
	void(*destroy)(T *data);
	void ListInit(void(*destroy)(T *data));
	void ListDestroy(void);
	int ListInsertNext(ListNode<T> *element, const T *data);
	int ListRemoveNext(ListNode<T> *element, T **data);

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
void Clist_Template<T>::ListInit(void(*destroy)(T *data))
{
	this->destroy = destroy;
	return;
}

template<class T>
void Clist_Template<T>::ListDestroy()
{
	T *data;

	//删除每一个元素
	while (this->ListSize() > 0)
	{
		if (0 == ListRemoveNext(NULL, (T **)&data) &&
			(NULL != this->destroy))
		{
			this->destroy(data);
		}
	}
	memset(this, 0, sizeof(Clist_Template));
	return;
}

template<class T>
int Clist_Template<T>::ListInsertNext(ListNode<T> *element, const T *data)
{
	ListNode<T> *new_element = new ListNode<T>;

	new_element->data = (T *)data;
	if (NULL == element)
	{
		/*首节点插入*/
		if (0 == this->ListSize())
		{
			this->tail = new_element; //尾节点=首节点
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
/*没有指向前驱节点的指针，为了处理方便删除next元素*/
int Clist_Template<T>::ListRemoveNext(ListNode<T> *element, T **data/*暂存待释放元素*/)
{
	ListNode<T> *old_element;

	if (0 == this->ListSize())
	{
		return -1;
	}

	if (NULL == element) //从首节点开始删除
	{
		*data = this->head->data;
		old_element = this->head;
		this->head = this->head->next;

		if (1 == this->ListSize())//如果是最后一个元素，尾节点置空
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