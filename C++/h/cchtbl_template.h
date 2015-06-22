/* cchtbl_template.h */
#ifndef CCHTBL_TEMPLATE_H
#define CCHTBL_TEMPLATE_H

#include <stdlib.h>
#include "clist_template.h"

template<class T>
class CCHTbl_Template
{
public:
	CCHTbl_Template(void);
	~CCHTbl_Template(void);
public:
	int  Chtbl_Init(int buckets, int(*h)(const T *key),
		int (*match)(const T *key1, const T *key2), void(*destroy)(T *data));
	void Chtbl_Destroy();
	int  Chtbl_Insert(const T *data);
	int  Chtbl_Remove(T **data);
	int  Chtbl_Lookup(T **data);

	int(*h)(const T *key);
	int(*match)(const T *key1, const T *key2);
	void(*destroy)(T *data);
	int Chtbl_Size() const { return size; }

public:
	Clist_Template<T> *table;
private:
	int buckets;  //hash������Ͱ�ĸ���
	int size;
};

template<class T>
CCHTbl_Template<T>::CCHTbl_Template()
{
	size = 0;
	buckets = 0;
	table = NULL;
}

template<class T>
CCHTbl_Template<T>::~CCHTbl_Template()
{

}

template<class T>
int  CCHTbl_Template<T>::Chtbl_Init(int buckets, int(*h)(const T *key),
	int (*match)(const T *key1, const T *key2), void(*destroy)(T *data))
{
	int i;

	//������Ͱ������
	this->table = new Clist[buckets] {0};
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

template<class T>
void CCHTbl_Template<T>::Chtbl_Destroy()
{
	int i;

	//����ÿ��Ͱ�洢������
	for (i = 0; i < this->buckets; i++)
	{
		this->table[i].List_Destroy();
	}

	//�ͷŴ洢ÿ��Ͱ��������ڴ�
	delete[] this->table;
	memset(this, 0, sizeof(CCHTbl_Template));

	return;
}

template<class T>
int  CCHTbl_Template<T>::Chtbl_Insert(const T *data)
{
	T *temp = NULL;
	int  bucket = 0;
	int  result = 0;

	/* ��������Ѵ��ڣ��򷵻�*/
	temp = (T *)data;
	if (0 == this->Chtbl_Lookup(&temp))
		return 0;

	//����hashֵ
	bucket = this->h(data) % this->buckets;

	//�����ݲ���hashֵ������ͷ
	if (0 == (result = this->table[bucket].List_Ins_Next(NULL, data)))
		this->size++;

	return result;
}

template<class T>
int  CCHTbl_Template<T>::Chtbl_Remove(T **data)
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

template<class T>
int  CCHTbl_Template<T>::Chtbl_Lookup(T **data)
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

#endif