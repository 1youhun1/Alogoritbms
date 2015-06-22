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

	//������Ͱ������
	this->table = new Clist[buckets];
	if (NULL == this->table)
		return -1;

	this->buckets = buckets;
	/* ��ʼ����ϣ����ÿ��Ͱ */
	for (i = 0; i < this->buckets; i++)
	{
		this->table[i].List_Init(destroy);
	}
	//��hashֵ�ĺ���
	this->h = h;
	this->match = match;
	this->destroy = destroy;
	this->size = 0;

	return 0;
}

void CCHTbl::Chtbl_Destroy()
{
	int i;

	//����ÿ��Ͱ�洢������
	for (i = 0; i < this->buckets; i++)
	{
		this->table[i].List_Destroy();
	}

	//�ͷŴ洢ÿ��Ͱ��������ڴ�
	delete [] this->table;
	memset(this, 0, sizeof(CCHTbl));

	return;
}

int  CCHTbl::Chtbl_Insert(const void *data)
{
	void *temp = NULL;
	int  bucket = 0;
	int  result = 0;

	/* ��������Ѵ��ڣ��򷵻�*/
	temp = (void *)data;
	if (0 == this->Chtbl_Lookup(&temp))
		return 0;

	//����hashֵ
	bucket = this->h(data) % this->buckets;

	//�����ݲ���hashֵ������ͷ
	if (0 == (result = this->table[bucket].List_Ins_Next(NULL, data)))
		this->size++;

	return result;
}

int  CCHTbl::Chtbl_Remove(void **data)
{
	ListElmt *element = NULL;
	ListElmt *prev = NULL;  //�ݴ�ǰһ��Ԫ�ص����ݣ������ͷ�list
	ListElmt *start_element = NULL;
	int bucket = 0;

	bucket = this->h(*data) % this->buckets;
	start_element = this->table[bucket].List_Head();

	/* ��Ͱ��������� */
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

	//δ���ҵ�����
	return -1;
}

int  CCHTbl::Chtbl_Lookup(void **data)
{
	ListElmt *element = NULL;
	ListElmt *start_element = NULL;
	int bucket = 0;

	//��������Ͱ��λ��
	bucket = this->h(*data) % this->buckets;
	start_element = this->table[bucket].List_Head();

	/* ��Ͱ��������� */
	for (element = start_element; element != NULL; element = element->next)
	{
		if (this->match(*data, element->data))
		{
			*data = element->data;
			return 0;
		}
	}

	//δ���ҵ�����
	return -1;
}