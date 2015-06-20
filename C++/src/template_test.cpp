#include <stdlib.h>
#include <string.h>

#include "clist_template.h"
#include "cdlist_template.h"
#include "cqueue_template.h"
#include "cstack_template.h"

void Test_clist_template()
{
	int a = 1;
	int b = 2;
	int *c = new int{ 0 };
	Clist_Template<int> list;
	list.List_Ins_Next(NULL, &a);
	list.List_Ins_Next(list.List_Head(), &b);
	list.List_Rem_Next(list.List_Head(), &c);
	return;
}

void Test_cdlist_template()
{

}

int main(int argc, char* argv[])
{
	Test_clist_template();

	system("pause");
	return 0;
}