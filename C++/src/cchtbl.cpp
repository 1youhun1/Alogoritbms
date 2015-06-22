/*cchtbl.cpp*/
#include <stdlib.h>
#include <string.h>

#include "..\h\cchtbl.h"

CCHTbl::CCHTbl()
{
	size = 0;
	buckets = 0;
	table = NULL;
}

CCHTbl::~CCHTbl()
{

}

int  CCHTbl::Chtbl_Init(int buckets, int(*h)(const void *key), int
	(*match)(const void *key1, const void *key2), void(*destroy)(void *data))
{
	int i;

	//申请存放桶的数组
	this->table = new Clist[buckets];
	if (NULL == this->table)
		return -1;

	this->buckets = buckets;
	/* 初始化哈希链的每个桶 */
	for (i = 0; i < this->buckets; i++)
	{
		this->table[i].List_Init(destroy);
	}
	//求hash值的函数
	this->h = h;
	this->match = match;
	this->destroy = destroy;
	this->size = 0;

	return 0;
}

void CCHTbl::Chtbl_Destroy()
{
	int i;

	//销毁每个桶存储的链表
	for (i = 0; i < this->buckets; i++)
	{
		this->table[i].List_Destroy();
	}

	//释放存储每个桶的数组的内存
	delete [] this->table;
	memset(this, 0, sizeof(CCHTbl));

	return;
}

int  CCHTbl::Chtbl_Insert(const void *data)
{
	void *temp = NULL;
	int  bucket = 0;
	int  result = 0;

	/* 如果数据已存在，则返回*/
	temp = (void *)data;
	if (0 == this->Chtbl_Lookup(&temp))
		return 0;

	//计算hash值
	bucket = this->h(data) % this->buckets;

	//将数据插入hash值链的链头
	if (0 == (result = this->table[bucket].List_Ins_Next(NULL, data)))
		this->size++;

	return result;
}

int  CCHTbl::Chtbl_Remove(void **data)
{
	ListElmt *element = NULL;
	ListElmt *prev = NULL;  //暂存前一项元素的内容，便于释放list
	ListElmt *start_element = NULL;
	int bucket = 0;

	bucket = this->h(*data) % this->buckets;
	start_element = this->table[bucket].List_Head();

	/* 在桶里查找数据 */
	for (element = start_element; element != NULL; element = element->next)
	{
		if (this->match(*data, element->data))
		{
			if (0 == this->table[bucket].List_Rem_Next(prev, data))
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

int  CCHTbl::Chtbl_Lookup(void **data)
{
	ListElmt *element = NULL;
	ListElmt *start_element = NULL;
	int bucket = 0;

	//计算所在桶的位置
	bucket = this->h(*data) % this->buckets;
	start_element = this->table[bucket].List_Head();

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