/*dlist.c ˫������*/
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "dlist.h"

void Dlist_Init(DList *list, void(*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}

void Dlist_Destroy(DList *list)
{
    void *data;

    while(Dlist_Size(list) > 0)
    {
        if (0 == DList_Remove(list, Dlist_Tail(list), ((void **)&data))
            && NULL != list->destroy)
        {
            list->destroy(data);
        }
    }

    memset(list, 0, sizeof(DList));
    return;
}

int Dlist_Ins_Next(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;

    //ֻ��listΪNULLʱ�������ڿ�element�������Ԫ��
    if (NULL == element && 0 != Dlist_Size(list))
        return ERR;

    if (NULL == (new_element = (DListElmt *)malloc(sizeof(DListElmt))))
        return ERR;

    new_element->data = (void *)data;

    if (0 == Dlist_Size(list))
    {
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = NULL;
    } 
    else
    {
		//����Ԫ��,�Ƚ�������ڵ�
        new_element->next = element->next;
        new_element->prev = element;

		//�ٱ����ڵ�
        if (NULL == element->next)
            list->tail = new_element;
        else
            element->next->prev = new_element;
		//���ǰ�ڵ�
        element->next = new_element;
    }

    list->size++;
    return OK;
}

int Dlist_Ins_Prev(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;

    //ֻ��listΪNULLʱ�������ڿ�elementǰ������Ԫ��
    if (NULL == element && 0 != Dlist_Size(list))
        return ERR;

    if (NULL == (new_element = (DListElmt *)malloc(sizeof(DListElmt))))
        return ERR;

    new_element->data = (void *)data;

    if (0 == Dlist_Size(list))
    {
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = NULL;
    }
    else
    {
        new_element->next = element;
        new_element->prev = element->prev;

        if (NULL == element->prev)
            list->head = new_element;
        else
            element->prev->next = new_element;

        element->prev = new_element;
    }

    list->size++;
    return OK;
}

int DList_Remove(DList *list, DListElmt *element, void **data)
{
    if (NULL == element || 0 == Dlist_Size(list))
        return ERR;

    *data = element->data;

    if (element == list->head)
    {
        list->head = element->next;

        if (NULL == list->head)
            list->tail = NULL; 
        else
            element->next->prev = NULL; //�׽ڵ�ǰ�ڵ���ΪNULL
    } 
    else
    {
        element->prev->next = element->next;

        if (NULL == element->next)
            list->tail = element->prev;
        else
            element->next->prev = element->prev;
    }

    free(element);
    list->size--;
    return OK;
}
