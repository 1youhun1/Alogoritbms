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
	//先进：插入表头
	return this->ListInsertNext(NULL, data);
}

int CStack::StackPop(void **data)
{
	//先出：删除表头
	return this->ListRemoveNext(NULL, data);
}