/*cset.cpp*/
#include <stdlib.h>
#include <windows.h>
#include "clist.h"
#include "cset.h"


CSet::CSet()
{
}

CSet::~CSet()
{
}

void CSet::Set_Init(int(*match)(const void *key1, const void *key2),
	void(*destroy)(void *data))
{
	this->match = match;
	this->destroy = destroy;
}

int CSet::Set_Insert(const void *data)
{
	if (this->Set_is_Member(data))
		return true;

	return List_Ins_Next(this->List_Tail(), data);
}

int CSet::Set_Remove(void **data)
{
	ListElmt *member;
	ListElmt *prev = NULL;

	/*查找需删除的member*/
	for (member = this->List_Head(); member != NULL; member = member->next)
	{
		if (this->match(*data, member->data))
			break;
		//单项链表删除需要前节点，所以这里记录删除的member前一项
		prev = member;
	}

	if (NULL == member)
		return -1;

	return this->List_Rem_Next(prev, data);
}

int CSet::Set_Union(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

	this->Set_Init(set1->match, set1->destroy);

	/*先将Set1中元素拷贝到Setu里*/
	for (member = set1->List_Head(); member != NULL; member = member->next)
	{
		data = member->data;
		if (0 != this->List_Ins_Next(this->List_Tail(), data))
		{
			this->Set_Destroy();
			return -1;
		}
	}

	//将Set2中元素排除相同元素后拷贝到SetU中，
	for (member = set2->List_Head(); member != NULL; member = member->next)
	{
		if (set1->Set_is_Member(member->data))
		{
			continue; //只拷贝不同项
		}
		else
		{
			data = member->data;
			if (0 != this->List_Ins_Next(this->List_Tail(), data))
			{
				this->Set_Destroy();
				return -1;
			}
		}
	}
	return 0;
}

int CSet::Set_Intersection(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

	this->Set_Init(set1->match, set1->destroy);

	/* 同时存在两个集合的元素才插入到Seti */
	for (member = set1->List_Head(); member != NULL; member = member->next)
	{
		if (set2->Set_is_Member(member->data))
		{
			data = member->data;
			if (0 != this->List_Ins_Next(this->List_Tail(), data))
			{
				this->Set_Destroy();
				return -1;
			}
		}
	}

	return 0;
}
int CSet::Set_Difference(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

	this->Set_Init(set1->match, set1->destroy);

	/* 存在set1，但不存在Set2的元素才插入Setd */
	for (member = set1->List_Head(); member != NULL; member = member->next)
	{
		if (!set2->Set_is_Member(member->data))
		{
			data = member->data;
			if (0 != this->List_Ins_Next(this->List_Tail(), data))
			{
				this->Set_Destroy();
				return -1;
			}
		}
	}

	return 0;
}

int CSet::Set_is_Member(const void *data) const
{
	ListElmt *member;

	for (member = this->List_Head(); member != NULL; member = member->next)
	{
		if (this->match(data, member->data))
			return true;
	}

	return false;
}

int CSet::Set_is_Subset(const CSet *set)
{
	ListElmt *member;

	/*set1所有元素必须都要在set2中才是子集*/
	for (member = this->List_Head(); member != NULL; member = member->next)
	{
		if (!set->Set_is_Member(member->data))
		{
			return false;
		}
	}

	return true;
}

//当集合大小相同，且是另一个集合子集，则两集合必相同
int CSet::Set_is_Equal(const CSet *set)
{
	if (this->Set_Size() != set->Set_Size())
		return false;

	return this->Set_is_Subset(set);
}
