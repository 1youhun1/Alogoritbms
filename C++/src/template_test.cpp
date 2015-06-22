#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "..\h\clist_template.h"
#include "..\h\cdlist_template.h"
#include "..\h\cqueue_template.h"
#include "..\h\cstack_template.h"

using namespace std;
#define CHECK_CONDITION(a) do\
{\
	if (!(a)) {\
		cout << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << endl; \
		return; \
	}\
}while(0)

void Test_clist_template()
{
	int a = 1;
	int b = 2;
	int *c = new int{ 0 };
	Clist_Template<int> list;
	list.List_Ins_Next(NULL, &a);
	list.List_Ins_Next(list.List_Head(), &b);
	list.List_Rem_Next(list.List_Head(), &c);
	CHECK_CONDITION(*c == a);
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