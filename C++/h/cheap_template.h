/*cheap_template.h 用模板实现堆类*/
#ifndef CHEAP_TEMPLATE_H
#define CHEAP_TEMPLATE_H

#include <stdlib.h>
#include <memory.h>
#include "..\h\cheap.h"

#define HeapParent(npos) ((int)(((npos) - 1) / 2)) /*获取堆父节点*/
#define HeapLeft(npos) (((npos) * 2) + 1)          /*获取堆左节点*/
#define HeapRight(npos) (((npos) * 2) + 2)         /*获取堆右节点*/

template<class T>
class CHeap_Template
{
public:
	CHeap_Template(void);
	~CHeap_Template(void);

public:
	void HeapInit(int(*compare)(const T *key1, const T *key2), void(*destroy)(T *data));
	void HeapDestroy();
	int HeapInsert(const T *data);
	int HeapExtract(T **data);
public:
	int HeapSize()const { return this->size; }
	int(*compare)(const T *key1, const T *key2);
	void(*destroy)(T *data);
private:
	size_t size;
	void **tree;
};

template<class T>
CHeap_Template<T>::CHeap_Template(void)
{
	this->size = 0;
	this->tree = NULL;
}

template<class T>
CHeap_Template<T>::~CHeap_Template(void)
{
}

template<class T>
void CHeap_Template<T>::HeapInit(int(*compare)(const T *key1, const T *key2),
	void(*destroy)(T *data))
{
	this->compare = compare;
	this->destroy = destroy;

	return;
}

template<class T>
void CHeap_Template<T>::HeapDestroy()
{
	int i;

	/*删除heap所有结点*/
	if (this->destroy != NULL)
	{
		for (i = 0; i < this->HeapSize(); i++)
		{
			this->destroy(this->tree[i]);
		}
	}

	free(this->tree);
	memset(this, 0, sizeof(CHeap_Template));

	return;
}

template<class T>
int CHeap_Template<T>::HeapInsert(const T *data)
{
	void *temp;
	int ipos, ppos;

	/*将this->tree分配新的大小的内存*/
	if ((temp = (void **)realloc(this->tree, (this->HeapSize() + 1) * sizeof(void *))) == NULL)
	{
		return -1;
	}

	this->tree = (void **)temp;
	this->tree[this->HeapSize()] = (T *)data;

	ipos = this->HeapSize();
	ppos = HeapParent(ipos);

	/*新插入节点与父节点比较，如果大于则交换*/
	while (ipos > 0 && this->compare(this->tree[ppos], this->tree[ipos]) < 0)
	{
		temp = this->tree[ppos];
		this->tree[ppos] = this->tree[ipos];
		this->tree[ipos] = temp;

		ipos = ppos;
		ppos = HeapParent(ipos);
	}

	this->size++;
	return 0;
}

template<class T>
/*释放堆顶端节点*/
int CHeap_Template<T>::HeapExtract(T **data)
{
	void *save, *temp;
	int ipos, lpos, rpos, mpos;

	if (this->HeapSize() == 0)
		return -1;

	/*提取heap的首结点*/
	*data = this->tree[0];
	save = this->tree[this->HeapSize() - 1];

	if (this->HeapSize() - 1 > 0)
	{
		if ((temp = (void **)realloc(this->tree, (this->HeapSize() - 1) * sizeof(void *))) == NULL)
		{
			return -1;
		}

		this->tree = (void **)temp;
		this->size--;
	}
	else
	{
		/*最后一个结点，则直接清空heap*/
		free(this->tree);
		this->tree = NULL;
		this->size = 0;
		return 0;
	}

	/*将最后一个节点复制到顶端*/
	this->tree[0] = save;

	ipos = 0;
	lpos = HeapLeft(ipos);
	rpos = HeapRight(ipos);

	while (1)
	{
		lpos = HeapLeft(ipos);
		rpos = HeapRight(ipos);

		if (lpos < this->HeapSize() &&
			this->compare(this->tree[lpos], this->tree[ipos]) > 0)
		{
			mpos = lpos;
		}
		else
		{
			mpos = ipos;
		}

		if (rpos < this->HeapSize() &&
			this->compare(this->tree[rpos], this->tree[mpos]) > 0)
		{
			mpos = rpos;
		}

		/*mpos与ipos相等，证明heap已经恢复*/
		if (mpos == ipos)
		{
			break;
		}
		else
		{
			temp = this->tree[mpos];
			this->tree[mpos] = this->tree[ipos];
			this->tree[ipos] = temp;

			ipos = mpos;
		}
	}
	return 0;
}

#endif