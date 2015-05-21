/*queue.c ���У�������ʵ��*/
#include <stdlib.h>

#include "list.h"
#include "queue.h"

int Queue_Enqueue(Queue *queue, const void *data)
{
	//�Ƚ�����������β
    return List_Ins_Next(queue, List_Tail(queue), data);
}

int Queue_Dequeue(Queue *queue, void **data)
{
	//�Ƚ��������ȡ��ͷ
    return List_Rem_Next(queue, NULL, data);
}