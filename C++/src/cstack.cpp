/*cstack.cpp*/
#include <stdlib.h>

#include "..\h\clist.h"
#include "..\h\cstack.h"


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