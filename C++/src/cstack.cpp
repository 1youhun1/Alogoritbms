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

int CStack::StackPush(const void *data)
{
	//�Ƚ��������ͷ
	return this->ListInsertNext(NULL, data);
}

int CStack::StackPop(void **data)
{
	//�ȳ���ɾ����ͷ
	return this->ListRemoveNext(NULL, data);
}