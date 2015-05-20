/*list.c*/
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "list.h"

void List_Init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}

void List_Destroy(List *list)
{
    void *data;

    //ɾ��ÿһ��Ԫ��
    while(List_Size(list) > 0)
    {
        if (OK == List_Rem_Next(list, NULL, (void **)&data) &&
            (NULL != list->destroy))
        {
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(List));
    return;
}

int List_Ins_Next(List *list,ListElmt *element,const void *data)
{
    ListElmt *new_element;
    if (NULL == (new_element = (ListElmt *)malloc(sizeof(ListElmt))))
    {
        return ERR;
    }

    new_element->data = (void *)data;
    if (NULL == element)
    {
        /*�׽ڵ����*/
        if (0 == List_Size(list))
        {
            list->tail = new_element; //β�ڵ�=�׽ڵ�
        }

        new_element->next = list->head;
        list->head = new_element;
    }
    else
    {
        if (NULL == element->next)
        {
            list->tail = new_element;
        }
        
        new_element->next = element->next;
        element->next = new_element;
    }
    
    list->size++;
    return OK;
}

/*û��ָ��ǰ���ڵ��ָ�룬Ϊ�˴�����ɾ��nextԪ��*/
int List_Rem_Next(List *list,ListElmt *element,void **data/*�ݴ���ͷ�Ԫ��*/)
{
    ListElmt *old_element;

    if (0 == List_Size(list))
    {
        return ERR;
    }

    if (NULL == element) //���׽ڵ㿪ʼɾ��
    {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if (1 == List_Size(list))//��������һ��Ԫ�أ�β�ڵ��ÿ�
        {
            list->tail =  NULL;
        }
    } 
    else
    {
        if (NULL ==  element->next)
        {
            return ERR;
        }

        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        if (NULL == element->next)
        {
            list->tail = element;
        }
    }

    free(old_element);
    list->size--;
    return OK;
}