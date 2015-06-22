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
	void Set_Init(int(*match)(const T *key1, const T *key2),
		void(*destroy)(T *data));

	int Set_Insert(const T *data);
	int Set_Remove(T **data);
	int Set_Union(const CSet_Template *set1, const CSet_Template *set2); //�󲢼�
	int Set_Intersection(const CSet_Template *set1, const CSet_Template *set2); //�󽻼�
	int Set_Difference(const CSet_Template *set1, const CSet_Template *set2); //��	

public:
	int Set_is_Subset(const CSet_Template *set);
	int Set_is_Equal(const CSet_Template *set);
	int Set_is_Member(const T *data) const;

public:
	int Set_Size() const { return this->size; }
	void Set_Destroy() { this->List_Destroy(); }

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
void CSet_Template<T>::Set_Init(int(*match)(const T *key1, const T *key2),
	void(*destroy)(T *data))
{
	this->match = match;
	this->destroy = destroy;
	return;
}

template<class T>
int CSet_Template<T>::Set_Insert(const T *data)
{
	if (this->Set_is_Member(data))
		return true;

	return List_Ins_Next(this->List_Tail(), data);
}

template<class T>
int CSet_Template<T>::Set_Remove(T **data)
{
	ListElmt *member;
	ListElmt *prev = NULL;

	/*������ɾ����member*/
	for (member = this->List_Head(); member != NULL; member = member->next)
	{
		if (this->match(*data, member->data))
			break;
		//��������ɾ����Ҫǰ�ڵ㣬���������¼ɾ����memberǰһ��
		prev = member;
	}

	if (NULL == member)
		return -1;

	return this->List_Rem_Next(prev, data);
}

template<class T>
int CSet_Template<T>::Set_Union(const CSet_Template *set1, const CSet_Template *set2)
{
	ListElmt *member;
	T        *data;

	this->Set_Init(set1->match, set1->destroy);

	/*�Ƚ�Set1��Ԫ�ؿ�����Setu��*/
	for (member = set1->List_Head(); member != NULL; member = member->next)
	{
		data = member->data;
		if (0 != this->List_Ins_Next(this->List_Tail(), data))
		{
			this->Set_Destroy();
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
			if (0 != this->List_Ins_Next(this->List_Tail(), data))
			{
				this->Set_Destroy();
				return -1;
			}
		}
	}
	return 0;
}

template<class T>
int CSet_Template<T>::Set_Intersection(const CSet_Template *set1, const CSet_Template *set2)
{
	ListElmt *member;
	T        *data;

	this->Set_Init(set1->match, set1->destroy);

	/* ͬʱ�����������ϵ�Ԫ�زŲ��뵽Seti */
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

template<class T>
int CSet_Template<T>::Set_Difference(const CSet_Template *set1, const CSet_Template *set2)
{
	ListElmt *member;
	T        *data;

	this->Set_Init(set1->match, set1->destroy);

	/* ����set1����������Set2��Ԫ�زŲ���Setd */
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

template<class T>
int CSet_Template<T>::Set_is_Member(const T *data) const
{
	ListElmt *member;

	for (member = this->List_Head(); member != NULL; member = member->next)
	{
		if (this->match(data, member->data))
			return true;
	}

	return false;
}

template<class T>
int CSet_Template<T>::Set_is_Subset(const CSet_Template *set)
{
	ListElmt *member;

	/*set1����Ԫ�ر��붼Ҫ��set2�в����Ӽ�*/
	for (member = this->List_Head(); member != NULL; member = member->next)
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
int CSet_Template<T>::Set_is_Equal(const CSet_Template *set)
{
	if (this->Set_Size() != set->Set_Size())
		return false;

	return this->Set_is_Subset(set);
}


#endif