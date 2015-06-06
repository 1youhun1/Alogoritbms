/*stack.c ջ��������ʵ��*/
#include <stdlib.h>

#include "list.h"
#include "stack.h"

int Stack_Push(Stack *stack, const void *data)
{
	//�Ƚ��ȳ��������ͷ
    return List_Ins_Next(stack, NULL, data); 
}

int Stack_Pop(Stack *stack, void **data)
{
	//�Ƚ��ȳ���ɾ����ͷ
    return List_Rem_Next(stack, NULL, data); 
}
