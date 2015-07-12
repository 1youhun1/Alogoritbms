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
	int SetUnion(const CSet_Template *set1, const CSet_Template *set2); //�󲢼�
	int SetIntersection(const CSet_Template *set1, const CSet_Template *set2); //�󽻼�
	int SetDifference(const CSet_Template *set1, const CSet_Template *set2); //��	

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

	/*������ɾ����member*/
	for (member = this->ListHead(); member != NULL; member = member->next)
	{
		if (this->match(*data, member->data))
			break;
		//��������ɾ����Ҫǰ�ڵ㣬���������¼ɾ����memberǰһ��
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

	/*�Ƚ�Set1��Ԫ�ؿ�����Setu��*/
	for (member = set1->List_Head(); member != NULL; member = member->next)
	{
		data = member->data;
		if (0 != this->ListInsertNext(this->ListTail(), data))
		{
			this->SetDestroy();
			return -1;
		}
	}

	//��Set2��Ԫ���ų���ͬԪ�غ󿽱���SetU�У�
	for (member = set2->List_Head(); member != NULL; member = member->next)
	{
		if (set1->Set_is_Member(member->data))
		{
			continue; //ֻ������ͬ��
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

	/* ͬʱ�����������ϵ�Ԫ�زŲ��뵽Seti */
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

	/* ����set1����������Set2��Ԫ�زŲ���Setd */
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

	/*set1����Ԫ�ر��붼Ҫ��set2�в����Ӽ�*/
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
//�����ϴ�С��ͬ��������һ�������Ӽ����������ϱ���ͬ
int CSet_Template<T>::SetIsEqual(const CSet_Template *set)
{
	if (this->SetSize() != set->Set_Size())
		return false;

	return this->SetIsSubset(set);
}


#endif