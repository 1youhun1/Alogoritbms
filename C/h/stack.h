/*stack.h*/
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "list.h"

typedef List Stack;

#define Stack_Init List_Init
#define Stack_Destroy List_Destroy
int Stack_Push(Stack *stack, const void *data);
int Stack_Pop(Stack *stack, void **data);
#define Stack_Peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)
#define Stack_Size List_Size

#endif
