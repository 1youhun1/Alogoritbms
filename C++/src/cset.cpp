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

int CSet::Set_Union(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

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

int CSet::Set_Intersection(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

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
int CSet::Set_Difference(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

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

//�����ϴ�С��ͬ��������һ�������Ӽ����������ϱ���ͬ
int CSet::Set_is_Equal(const CSet *set)
{
	if (this->Set_Size() != set->Set_Size())
		return false;

	return this->Set_is_Subset(set);
}
