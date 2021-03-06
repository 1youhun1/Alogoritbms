/* cchtbl_template.h */
#ifndef CCHTBL_TEMPLATE_H
#define CCHTBL_TEMPLATE_H

#include <stdlib.h>
#include "clist_template.h"

template<class T>
class CCHTbl_Template
{
public:
	CCHTbl_Template(void);
	~CCHTbl_Template(void);
public:
	int  ChtblInit(int buckets, int(*h)(const T *key),
		int (*match)(const T *key1, const T *key2), void(*destroy)(T *data));
	void ChtblDestroy();
	int  ChtblInsert(const T *data);
	int  ChtblRemove(T **data);
	int  ChtblLookup(T **data);

	int(*h)(const T *key);
	int(*match)(const T *key1, const T *key2);
	void(*destroy)(T *data);
	int ChtblSize() const { return size; }

public:
	Clist_Template<T> *table;
private:
	int buckets;  //hash链分配桶的个数
	size_t size;
};

template<class T>
CCHTbl_Template<T>::CCHTbl_Template()
{
	size = 0;
	buckets = 0;
	table = NULL;
}

template<class T>
CCHTbl_Template<T>::~CCHTbl_Template()
{

}

template<class T>
int  CCHTbl_Template<T>::ChtblInit(int buckets, int(*h)(const T *key),
	int (*match)(const T *key1, const T *key2), void(*destroy)(T *data))
{
	int i;

	//申请存放桶的数组
	this->table = new Clist[buckets] {0};
	if (NULL == this->table)
		return -1;

	this->buckets = buckets;
	/* 初始化哈希链的每个桶 */
	for (i = 0; i < this->buckets; i++)
	{
		this->table[i].ListInit(destroy);
	}
	//求hash值的函数
	this->h = h;
	this->match = match;
	this->destroy = destroy;
	this->size = 0;

	return 0;
}

template<class T>
void CCHTbl_Template<T>::ChtblDestroy()
{
	int i;

	//销毁每个桶存储的链表
	for (i = 0; i < this->buckets; i++)
	{
		this->table[i].ListDestroy();
	}

	//释放存储每个桶的数组的内存
	delete[] this->table;
	memset(this, 0, sizeof(CCHTbl_Template));

	return;
}

template<class T>
int  CCHTbl_Template<T>::ChtblInsert(const T *data)
{
	T *temp = NULL;
	int  bucket = 0;
	int  result = 0;

	/* 如果数据已存在，则返回*/
	temp = (T *)data;
	if (0 == this->ChtblLookup(&temp))
		return 0;

	//计算hash值
	bucket = this->h(data) % this->buckets;

	//将数据插入hash值链的链头
	if (0 == (result = this->table[bucket].ListInsertNext(NULL, data)))
		this->size++;

	return result;
}

template<class T>
int  CCHTbl_Template<T>::ChtblRemove(T **data)
{
	ListElmt *element = NULL;
	ListElmt *prev = NULL;  //暂存前一项元素的内容，便于释放list
	ListElmt *start_element = NULL;
	int bucket = 0;

	bucket = this->h(*data) % this->buckets;
	start_element = this->table[bucket].ListHead();

	/* 在桶里查找数据 */
	for (element = start_element; element != NULL; element = element->next)
	{
		if (this->match(*data, element->data))
		{
			if (0 == this->table[bucket].ListRemoveNext(prev, data))
			{
				this->size--;
				return 0;
			}
			else
			{
				return -1;
			}
		}
		prev = element;
	}

	//未查找到数据
	return -1;
}

template<class T>
int  CCHTbl_Template<T>::ChtblLookup(T **data)
{
	ListElmt *element = NULL;
	ListElmt *start_element = NULL;
	int bucket = 0;

	//计算所在桶的位置
	bucket = this->h(*data) % this->buckets;
	start_element = this->table[bucket].ListHead();

	/* 在桶里查找数据 */
	for (element = start_element; element != NULL; element = element->next)
	{
		if (this->match(*data, element->data))
		{
			*data = element->data;
			return 0;
		}
	}

	//未查找到数据
	return -1;
}

#endif