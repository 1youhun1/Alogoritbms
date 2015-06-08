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
	//先进：插入表头
	return this->List_Ins_Next(NULL, data);
}

int CStack::Stack_Pop(void **data)
{
	//先出：删除表头
	return this->List_Rem_Next(NULL, data);
}