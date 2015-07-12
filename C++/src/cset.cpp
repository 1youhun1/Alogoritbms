/*cset.cpp*/
#include <stdlib.h>
#include <windows.h>
#include "..\h\clist.h"
#include "..\h\cset.h"


CSet::CSet()
{
	this->size = 0;
	this->head = NULL;
	this->tail = NULL;
	this->match = NULL;
	this->destroy = NULL;
	return;
}

CSet::~CSet()
{
}

void CSet::SetInit(int(*match)(const void *key1, const void *key2),
	void(*destroy)(void *data))
{
	this->match = match;
	this->destroy = destroy;
	return;
}

int CSet::SetInsert(const void *data)
{
	if (this->SetIsMember(data))
		return true;

	return ListInsertNext(this->ListTail(), data);
}

int CSet::SetRemove(void **data)
{
	ListElmt *member;
	ListElmt *prev = NULL;

	/*查找需删除的member*/
	for (member = this->ListHead(); member != NULL; member = member->next)
	{
		if (this->match(*data, member->data))
			break;
		//单项链表删除需要前节点，所以这里记录删除的member前一项
		prev = member;
	}

	if (NULL == member)
		return -1;

	return this->ListRemoveNext(prev, data);
}

int CSet::SetUnion(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

	this->SetInit(set1->match, set1->destroy);

	/*先将Set1中元素拷贝到Setu里*/
	for (member = set1->ListHead(); member != NULL; member = member->next)
	{
		data = member->data;
		if (0 != this->ListInsertNext(this->ListTail(), data))
		{
			this->SetDestroy();
			return -1;
		}
	}

	//将Set2中元素排除相同元素后拷贝到SetU中，
	for (member = set2->ListHead(); member != NULL; member = member->next)
	{
		if (set1->SetIsMember(member->data))
		{
			continue; //只拷贝不同项
		}
		else
		{
			data = member->data;
			if (0 != this->ListInsertNext(this->ListTail(), data))
			{
				this->SetDestroy();
				return -1;
			}
		}
	}
	return 0;
}

int CSet::SetIntersection(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

	this->SetInit(set1->match, set1->destroy);

	/* 同时存在两个集合的元素才插入到Seti */
	for (member = set1->ListHead(); member != NULL; member = member->next)
	{
		if (set2->SetIsMember(member->data))
		{
			data = member->data;
			if (0 != this->ListInsertNext(this->ListTail(), data))
			{
				this->SetDestroy();
				return -1;
			}
		}
	}

	return 0;
}
int CSet::SetDifference(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

	this->SetInit(set1->match, set1->destroy);

	/* 存在set1，但不存在Set2的元素才插入Setd */
	for (member = set1->ListHead(); member != NULL; member = member->next)
	{
		if (!set2->SetIsMember(member->data))
		{
			data = member->data;
			if (0 != this->ListInsertNext(this->ListTail(), data))
			{
				this->SetDestroy();
				return -1;
			}
		}
	}

	return 0;
}

int CSet::SetIsMember(const void *data) const
{
	ListElmt *member;

	for (member = this->ListHead(); member != NULL; member = member->next)
	{
		if (this->match(data, member->data))
			return true;
	}

	return false;
}

int CSet::SetIsSubset(const CSet *set)
{
	ListElmt *member;

	/*set1所有元素必须都要在set2中才是子集*/
	for (member = this->ListHead(); member != NULL; member = member->next)
	{
		if (!set->SetIsMember(member->data))
		{
			return false;
		}
	}

	return true;
}

//当集合大小相同，且是另一个集合子集，则两集合必相同
int CSet::SetIsEqual(const CSet *set)
{
	if (this->SetSize() != set->SetSize())
		return false;

	return this->SetIsSubset(set);
}
