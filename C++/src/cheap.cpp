/*cheap.cpp*/
#include <stdlib.h>
#include <memory.h>
#include "..\h\cheap.h"

#define HeapParent(npos) ((int)(((npos) - 1) / 2)) /*��ȡ�Ѹ��ڵ�*/
#define HeapLeft(npos) (((npos) * 2) + 1)          /*��ȡ����ڵ�*/
#define HeapRight(npos) (((npos) * 2) + 2)         /*��ȡ���ҽڵ�*/

CHeap::CHeap(void)
{
	this->size = 0;
	this->tree = NULL;
}


CHeap::~CHeap(void)
{
}


void CHeap::HeapInit(int(*compare)(const void *key1, const void *key2),
	void(*destroy)(void *data))
{
	this->compare = compare;
	this->destroy = destroy;

	return;
}

void CHeap::HeapDestroy()
{
	int i;

	/*ɾ��heap���н��*/
	if (this->destroy != NULL)
	{
		for (i = 0; i < this->HeapSize(); i++)
		{
			this->destroy(this->tree[i]);
		}
	}

	free(this->tree);
	memset(this, 0, sizeof(CHeap));

	return;
}

int CHeap::HeapInsert(const void *data)
{
	void *temp;
	int ipos, ppos;

	/*��this->tree�����µĴ�С���ڴ�*/
	if ((temp = (void **)realloc(this->tree, (this->HeapSize() + 1) * sizeof(void *))) == NULL)
	{
		return -1;
	}

	this->tree = (void **)temp;
	this->tree[this->HeapSize()] = (void *)data;

	ipos = this->HeapSize();
	ppos = HeapParent(ipos);

	/*�²���ڵ��븸�ڵ�Ƚϣ���������򽻻�*/
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

/*�ͷŶѶ��˽ڵ�*/
int CHeap::HeapExtract(void **data)
{
	void *save, *temp;
	int ipos, lpos, rpos, mpos;

	if (this->HeapSize() == 0)
		return -1;

	/*��ȡheap���׽��*/
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
		/*���һ����㣬��ֱ�����heap*/
		free(this->tree);
		this->tree = NULL;
		this->size = 0;
		return 0;
	}

	/*�����һ���ڵ㸴�Ƶ�����*/
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

		/*mpos��ipos��ȣ�֤��heap�Ѿ��ָ�*/
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