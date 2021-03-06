/*cset_template.h*/
#ifndef CSET_TEMPLATE_H
#define CSET_TEMPLATE_H

#include <stdlib.h>
#include "clist_template.h"

template<class T>
class CSet_Template : public Clist_Template<T>
{
public:
	CSet_Template();
	~CSet_Template();

public:
	void SetInit(int(*match)(const T *key1, const T *key2),
		void(*destroy)(T *data));

	int SetInsert(const T *data);
	int SetRemove(T **data);
	int SetUnion(const CSet_Template *set1, const CSet_Template *set2); //求并集
	int SetIntersection(const CSet_Template *set1, const CSet_Template *set2); //求交集
	int SetDifference(const CSet_Template *set1, const CSet_Template *set2); //求差集	

public:
	int SetIsSubset(const CSet_Template *set);
	int SetIsEqual(const CSet_Template *set);
	int SetIsMember(const T *data) const;

public:
	int SetSize() const { return this->size; }
	void SetDestroy() { this->ListDestroy(); }
};

template<class T>
CSet_Template<T>::CSet_Template()
{
	this->size = 0;
	this->head = NULL;
	this->tail = NULL;
	this->match = NULL;
	this->destroy = NULL;
	return;
}

template<class T>
CSet_Template<T>::~CSet_Template()
{
}

template<class T>
void CSet_Template<T>::SetInit(int(*match)(const T *key1, const T *key2),
	void(*destroy)(T *data))
{
	this->match = match;
	this->destroy = destroy;
	return;
}

template<class T>
int CSet_Template<T>::SetInsert(const T *data)
{
	if (this->SetIsMember(data))
		return true;

	return ListInsertNext(this->ListTail(), data);
}

template<class T>
int CSet_Template<T>::SetRemove(T **data)
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

template<class T>
int CSet_Template<T>::SetUnion(const CSet_Template *set1, const CSet_Template *set2)
{
	ListElmt *member;
	T        *data;

	this->SetInit(set1->match, set1->destroy);

	/*先将Set1中元素拷贝到Setu里*/
	for (member = set1->List_Head(); member != NULL; member = member->next)
	{
		data = member->data;
		if (0 != this->ListInsertNext(this->ListTail(), data))
		{
			this->SetDestroy();
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
			if (0 != this->ListInsertNext(this->ListTail(), data))
			{
				this->SetDestroy();
				return -1;
			}
		}
	}
	return 0;
}

template<class T>
int CSet_Template<T>::SetIntersection(const CSet_Template *set1, const CSet_Template *set2)
{
	ListElmt *member;
	T        *data;

	this->SetInit(set1->match, set1->destroy);

	/* 同时存在两个集合的元素才插入到Seti */
	for (member = set1->List_Head(); member != NULL; member = member->next)
	{
		if (set2->Set_is_Member(member->data))
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

template<class T>
int CSet_Template<T>::SetDifference(const CSet_Template *set1, const CSet_Template *set2)
{
	ListElmt *member;
	T        *data;

	this->SetInit(set1->match, set1->destroy);

	/* 存在set1，但不存在Set2的元素才插入Setd */
	for (member = set1->List_Head(); member != NULL; member = member->next)
	{
		if (!set2->Set_is_Member(member->data))
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

template<class T>
int CSet_Template<T>::SetIsMember(const T *data) const
{
	ListElmt *member;

	for (member = this->ListHead(); member != NULL; member = member->next)
	{
		if (this->match(data, member->data))
			return true;
	}

	return false;
}

template<class T>
int CSet_Template<T>::SetIsSubset(const CSet_Template *set)
{
	ListElmt *member;

	/*set1所有元素必须都要在set2中才是子集*/
	for (member = this->ListHead(); member != NULL; member = member->next)
	{
		if (!set->Set_is_Member(member->data))
		{
			return false;
		}
	}

	return true;
}

template<class T>
//当集合大小相同，且是另一个集合子集，则两集合必相同
int CSet_Template<T>::SetIsEqual(const CSet_Template *set)
{
	if (this->SetSize() != set->Set_Size())
		return false;

	return this->SetIsSubset(set);
}


#endif