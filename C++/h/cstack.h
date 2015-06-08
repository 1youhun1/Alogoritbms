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
	int Stack_Push(const void *data);
	int Stack_Pop(void **data);
	void* Stack_Peek() {
		(this->head == NULL ? NULL : this->head->data);
	}
private:

};

#endif