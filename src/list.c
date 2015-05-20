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

    //删除每一个元素
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
        /*首节点插入*/
        if (0 == List_Size(list))
        {
            list->tail = new_element; //尾节点=首节点
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

/*没有指向前驱节点的指针，为了处理方便删除next元素*/
int List_Rem_Next(List *list,ListElmt *element,void **data/*暂存待释放元素*/)
{
    ListElmt *old_element;

    if (0 == List_Size(list))
    {
        return ERR;
    }

    if (NULL == element) //从首节点开始删除
    {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if (1 == List_Size(list))//如果是最后一个元素，尾节点置空
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