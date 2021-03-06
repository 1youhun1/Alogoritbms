/*cdlist_template.h 用模板实现双向链表*/
#ifndef CDLIST_TEMPLATE_H
#define CDLIST_TEMPLATE_H

template<class T>
struct DListElmt
{
	T *data;
	DListElmt<T> *prev;
	DListElmt<T> *next;
};

template<class T>
class CDoubleList_Template
{
public:
	CDoubleList_Template(void);
	~CDoubleList_Template(void);

public:
	int(*match)(const T *key1, const T *key2); //比较函数
	void(*destroy)(T *data);    //删除节点内容
	void DoubleListInit(void(*destroy)(T *data));
	void DoubleListDestroy();
	int DoubleListInsertNext(DListElmt<T> *element, const T *data);
	int DoubleListInsertPrev(DListElmt<T> *element, const T *data);
	int DoubleListRemove(DListElmt<T> *element, T **data);

public:
	int DoubleListSize() const { return size; }
	DListElmt<T>* DoubleListHead() const { return head; }
	DListElmt<T>* DoubleListTail() const { return tail; }

	bool DoubleListIsHead(DListElmt<T> *element) {
		return ((element)->prev == NULL ? true : false);
	}
	bool DoubleListIsTail(DListElmt<T> *element) {
		return ((element)->next == NULL ? true : false);
	}

private:
	size_t size;
	DListElmt<T> *head;
	DListElmt<T> *tail;
};

template<class T>
CDoubleList_Template<T>::CDoubleList_Template(void)
{
	size = 0;
	head = NULL;
	tail = NULL;
	destroy = NULL;
	match = NULL;
}

template<class T>
CDoubleList_Template<T>::~CDoubleList_Template(void)
{

}

template<class T>
void CDoubleList_Template<T>::DoubleListInit(void(*destroy)(T *data))
{
	this->destroy = destroy;
	return;
}

template<class T>
void CDoubleList_Template<T>::DoubleListDestroy()
{
	T *data;

	while (this->DoubleListSize() > 0)
	{
		if (0 == DoubleListRemove(this->DoubleListTail(), ((T **)&data))
			&& NULL != this->destroy)
		{
			this->destroy(data);
		}
	}

	memset(this, 0, sizeof(CDoubleList_Template));
	return;
}

template<class T>
int CDoubleList_Template<T>::DoubleListInsertNext(DListElmt<T> *element, const T *data)
{
	//只有list为NULL时才允许在空element后插入新元素
	if (NULL == element && 0 != this->DoubleListSize())
		return -1;

	DListElmt<T> *new_element = new DListElmt<T>{ 0 };
	if (NULL == new_element)
		return -1;

	new_element->data = (T *)data;

	if (0 == this->DoubleListSize())
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

template<class T>
int CDoubleList_Template<T>::DoubleListInsertPrev(DListElmt<T> *element, const T *data)
{
	//只有list为NULL时才允许在空element前插入新元素
	if (NULL == element && 0 != this->DoubleListSize())
		return -1;

	DListElmt<T> *new_element = new DListElmt<T>{ 0 };
	if (NULL == new_element)
		return -1;

	new_element->data = (T *)data;

	if (0 == this->DoubleListSize())
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

template<class T>
int CDoubleList_Template<T>::DoubleListRemove(DListElmt<T> *element, T **data)
{
	if (NULL == element || 0 == this->DoubleListSize())
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

#endif