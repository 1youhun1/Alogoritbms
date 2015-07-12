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
#include "..\h\cheap_template.h"
#include "..\h\cpqueue.h"
#include "..\h\cpqueue_template.h"

#include "template_test.h"

using namespace std;

void Test_clist_template()
{
	UINT32 a = 1;
	UINT32 b = 10;
	UINT32 *c = NULL;
	Clist_Template<UINT32> list;
	list.ListInit(NULL);

	list.ListInsertNext(NULL, &a);
	list.ListInsertNext(list.ListHead(), &b);
	CHECK_CONDITION(*(list.ListTail()->data) == b);
	CHECK_CONDITION(list.ListSize() == 2);

	list.ListRemoveNext(list.ListHead(), &c);
	CHECK_CONDITION(*(list.ListTail()->data) == a);
	CHECK_CONDITION(*c == b);
	CHECK_CONDITION(list.ListSize() == 1);

	list.ListDestroy();
	CHECK_CONDITION(list.ListSize() == 0);
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
	dlist.DoubleListInit(&destroy);

	CdlistTestType *a = new CdlistTestType{ 0 };
	a->ip = 0x01010101;
	a->port_id = 1;

	CdlistTestType *b = new CdlistTestType{ 0 };
	b->ip = 0x02020202;
	b->port_id = 2;

	CdlistTestType *c = new CdlistTestType{ 0 };
	c->ip = 0x03030303;
	c->port_id = 3;

	dlist.DoubleListInsertNext(NULL, a);
	CHECK_CONDITION(dlist.DoubleListSize() == 1);

	dlist.DoubleListInsertNext(dlist.DoubleListHead(), b);
	CHECK_CONDITION(dlist.DoubleListSize() == 2);
	CHECK_CONDITION(dlist.DoubleListTail()->data == b);

	dlist.DoubleListInsertPrev(dlist.DoubleListTail(), c);
	CHECK_CONDITION(dlist.DoubleListSize() == 3);
	CHECK_CONDITION(dlist.DoubleListTail()->prev->data == c);

	dlist.DoubleListRemove(dlist.DoubleListTail(), &destroy_element);
	CHECK_CONDITION(dlist.DoubleListSize() == 2);
	CHECK_CONDITION(destroy_element->ip == b->ip);
	CHECK_CONDITION(destroy_element->port_id == b->port_id);
	delete destroy_element;
	destroy_element = NULL;

	dlist.DoubleListDestroy();
	CHECK_CONDITION(dlist.DoubleListSize() == 0);
	CHECK_CONDITION(dlist.DoubleListTail() == NULL);
	return;
}

void Test_cqueue_template()
{
	UINT32 a = 1;
	UINT32 b = 10;
	UINT32 *c = NULL;

	CQueue_Template<UINT32> queue;
	queue.ListInit(NULL);

	queue.QueueEnqueue(&a);
	CHECK_CONDITION(*(queue.ListHead()->data) == a);
	CHECK_CONDITION(queue.ListSize() == 1);

	queue.QueueEnqueue(&b);
	CHECK_CONDITION(queue.ListSize() == 2);

	queue.QueueDequeue(&c);
	CHECK_CONDITION(queue.ListSize() == 1);
	CHECK_CONDITION(*c == a); //先进先出，获取的是a
	CHECK_CONDITION(*(queue.ListTail()->data) == b);

	queue.ListDestroy();
	return;
}

void Test_cstack_template()
{
	UINT32 a = 1;
	UINT32 b = 10;
	UINT32 *c = NULL;

	CStack_Template<UINT32> stack;
	stack.ListInit(NULL);

	stack.StackPush(&a);
	CHECK_CONDITION(*(stack.ListHead()->data) == a);
	CHECK_CONDITION(stack.ListSize() == 1);

	stack.StackPush(&b);
	CHECK_CONDITION(stack.ListSize() == 2);

	stack.StackPop(&c);
	CHECK_CONDITION(stack.ListSize() == 1);
	CHECK_CONDITION(*c == b); //先进h后出，获取的是b
	CHECK_CONDITION(*(stack.ListTail()->data) == a);

	stack.ListDestroy();
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