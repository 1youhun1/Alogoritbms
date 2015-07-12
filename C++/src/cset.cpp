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

int CSet::SetUnion(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

	this->SetInit(set1->match, set1->destroy);

	/*�Ƚ�Set1��Ԫ�ؿ�����Setu��*/
	for (member = set1->ListHead(); member != NULL; member = member->next)
	{
		data = member->data;
		if (0 != this->ListInsertNext(this->ListTail(), data))
		{
			this->SetDestroy();
			return -1;
		}
	}

	//��Set2��Ԫ���ų���ͬԪ�غ󿽱���SetU�У�
	for (member = set2->ListHead(); member != NULL; member = member->next)
	{
		if (set1->SetIsMember(member->data))
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

int CSet::SetIntersection(const CSet *set1, const CSet *set2)
{
	ListElmt *member;
	void     *data;

	this->SetInit(set1->match, set1->destroy);

	/* ͬʱ�����������ϵ�Ԫ�زŲ��뵽Seti */
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

	/* ����set1����������Set2��Ԫ�زŲ���Setd */
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

	/*set1����Ԫ�ر��붼Ҫ��set2�в����Ӽ�*/
	for (member = this->ListHead(); member != NULL; member = member->next)
	{
		if (!set->SetIsMember(member->data))
		{
			return false;
		}
	}

	return true;
}

//�����ϴ�С��ͬ��������һ�������Ӽ����������ϱ���ͬ
int CSet::SetIsEqual(const CSet *set)
{
	if (this->SetSize() != set->SetSize())
		return false;

	return this->SetIsSubset(set);
}
