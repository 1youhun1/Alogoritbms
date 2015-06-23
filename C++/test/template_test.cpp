#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "..\h\clist_template.h"
#include "..\h\cdlist_template.h"
#include "..\h\cqueue_template.h"
#include "..\h\cstack_template.h"
#include "..\h\cset_template.h"
#include "..\h\cchtbl_template.h"
#include "..\h\cbitree_template.h"

#include "template_test.h"

using namespace std;

void Test_clist_template()
{
	UINT32 a = 1;
	UINT32 b = 10;
	UINT32 *c = NULL;
	Clist_Template<UINT32> list;
	list.List_Init(NULL);

	list.List_Ins_Next(NULL, &a);
	list.List_Ins_Next(list.List_Head(), &b);
	CHECK_CONDITION(*(list.List_Tail()->data) == b);
	CHECK_CONDITION(list.List_Size() == 2);

	list.List_Rem_Next(list.List_Head(), &c);
	CHECK_CONDITION(*(list.List_Tail()->data) == a);
	CHECK_CONDITION(*c == b);
	CHECK_CONDITION(list.List_Size() == 1);

	list.List_Destroy();
	CHECK_CONDITION(list.List_Size() == 0);
	return;
}

struct CdlistTestType
{
	UINT32 ip;
	UINT32 port_id;
};

void destroy(CdlistTestType *data)
{
	delete data;
	data = NULL;
}
void Test_cdlist_template()
{
	CdlistTestType *destroy_element = NULL;
	CDoubleList_Template<CdlistTestType> dlist;
	dlist.DoubleList_Init(&destroy);

	CdlistTestType *a = new CdlistTestType{ 0 };
	a->ip = 0x01010101;
	a->port_id = 1;

	CdlistTestType *b = new CdlistTestType{ 0 };
	b->ip = 0x02020202;
	b->port_id = 2;

	CdlistTestType *c = new CdlistTestType{ 0 };
	c->ip = 0x03030303;
	c->port_id = 3;

	dlist.DoubleList_Ins_Next(NULL, a);
	CHECK_CONDITION(dlist.DoubleList_Size() == 1);

	dlist.DoubleList_Ins_Next(dlist.DoubleList_Head(), b);
	CHECK_CONDITION(dlist.DoubleList_Size() == 2);
	CHECK_CONDITION(dlist.DoubleList_Tail()->data == b);

	dlist.DoubleList_Ins_Prev(dlist.DoubleList_Tail(), c);
	CHECK_CONDITION(dlist.DoubleList_Size() == 3);
	CHECK_CONDITION(dlist.DoubleList_Tail()->prev->data == c);

	dlist.DoubleList_Remove(dlist.DoubleList_Tail(), &destroy_element);
	CHECK_CONDITION(dlist.DoubleList_Size() == 2);
	CHECK_CONDITION(destroy_element->ip == b->ip);
	CHECK_CONDITION(destroy_element->port_id == b->port_id);
	delete destroy_element;
	destroy_element = NULL;

	dlist.DoubleList_Destroy();
	CHECK_CONDITION(dlist.DoubleList_Size() == 0);
	CHECK_CONDITION(dlist.DoubleList_Tail() == NULL);
	return;
}

void Test_cqueue_template()
{
	UINT32 a = 1;
	UINT32 b = 10;
	UINT32 *c = NULL;

	CQueue_Template<UINT32> queue;
	queue.List_Init(NULL);

	queue.Queue_Enqueue(&a);
	CHECK_CONDITION(*(queue.List_Head()->data) == a);
	CHECK_CONDITION(queue.List_Size() == 1);

	queue.Queue_Enqueue(&b);
	CHECK_CONDITION(queue.List_Size() == 2);

	queue.Queue_Dequeue(&c);
	CHECK_CONDITION(queue.List_Size() == 1);
	CHECK_CONDITION(*c == a); //先进先出，获取的是a
	CHECK_CONDITION(*(queue.List_Tail()->data) == b);

	queue.List_Destroy();
	return;
}

void Test_cstack_template()
{
	UINT32 a = 1;
	UINT32 b = 10;
	UINT32 *c = NULL;

	CStack_Template<UINT32> stack;
	stack.List_Init(NULL);

	stack.Stack_Push(&a);
	CHECK_CONDITION(*(stack.List_Head()->data) == a);
	CHECK_CONDITION(stack.List_Size() == 1);

	stack.Stack_Push(&b);
	CHECK_CONDITION(stack.List_Size() == 2);

	stack.Stack_Pop(&c);
	CHECK_CONDITION(stack.List_Size() == 1);
	CHECK_CONDITION(*c == b); //先进h后出，获取的是b
	CHECK_CONDITION(*(stack.List_Tail()->data) == a);

	stack.List_Destroy();
	return;
}

int main(int argc, char* argv[])
{
	Test_clist_template();

	Test_cdlist_template();

	Test_cqueue_template();

	Test_cstack_template();

	system("pause");
	return 0;
}