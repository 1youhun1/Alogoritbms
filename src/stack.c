/*stack.c 栈，用链表实现*/
#include <stdlib.h>

#include "list.h"
#include "stack.h"

int Stack_Push(Stack *stack, const void *data)
{
	//先进先出：插入表头
    return List_Ins_Next(stack, NULL, data); 
}

int Stack_Pop(Stack *stack, void **data)
{
	//先进先出：删除表头
    return List_Rem_Next(stack, NULL, data); 
}
