/*cstack.c*/
#include <stdlib.h>

#include "clist.h"
#include "cstack.h"


CStack::CStack()
{
}

CStack::~CStack()
{
}

int CStack::Stack_Push(const void *data)
{
	//�Ƚ��������ͷ
	return this->List_Ins_Next(NULL, data);
}

int CStack::Stack_Pop(void **data)
{
	//�ȳ���ɾ����ͷ
	return this->List_Rem_Next(NULL, data);
}