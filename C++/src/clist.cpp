/*clist.cpp*/
#include <stdlib.h>
#include <string.h>

#include "..\h\clist.h"

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

void Clist::ListInit(void(*destroy)(void *data))
{
	this->destroy = destroy;
	return;
}

void Clist::ListDestroy()
{
	void *data;

	//删除每一个元素
	while (this->ListSize() > 0)
	{
		if (0 == ListRemoveNext(NULL, (void **)&data) &&
			(NULL != this->destroy))
		{
			this->destroy(data);
		}
	}
	memset(this, 0, sizeof(Clist));
	return;
}

int Clist::ListInsertNext(ListElmt *element, const void *data)
{
	ListElmt *new_element = new ListElmt{ 0 };

	new_element->data = (void *)data;
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

/*没有指向前驱节点的指针，为了处理方便删除next元素*/
int Clist::ListRemoveNext(ListElmt *element, void **data/*暂存待释放元素*/)
{
	ListElmt *old_element;

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
