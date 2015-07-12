/*cstack.h*/
#ifndef CSTACK_H
#define CSTACK_H

#include <stdlib.h>
#include "clist.h"

class CStack: public Clist
{
public:
	CStack();
	~CStack();

public:
	int StackPush(const void *data);
	int StackPop(void **data);
	void* StackPeek() {
		(this->head == NULL ? NULL : this->head->data);
	}

};

#endif