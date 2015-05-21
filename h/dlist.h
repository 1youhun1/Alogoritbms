/*dlist.h*/
#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

typedef struct DlistElmt_
{
    void *data;
    struct DlistElmt_ *prev;
    struct DlistElmt_ *next;
}DListElmt;

typedef struct DList_
{
    int size;
    int (*match)(const void *key1, const void *key2); //比较函数
    void (*destroy)(void *data);    //删除节点内容
    DListElmt *head;
    DListElmt *tail;
}DList;

void Dlist_Init(DList *list, void(*destroy)(void *data));
void Dlist_Destroy(DList *list);
int Dlist_Ins_Next(DList *list, DListElmt *element, const void *data);
int Dlist_Ins_Prev(DList *list, DListElmt *element, const void *data);
int DList_Remove(DList *list, DListElmt *element, void **data);

#define Dlist_Size(list) ((list)->size)
#define Dlist_Head(list) ((list)->head)
#define Dlist_Tail(list) ((list)->tail)
#define DList_is_Head(element) ((element)->prev == NULL ? 1 : 0)
#define DList_is_Tail(element) ((element)->next == NULL ? 1 : 0)
#define DList_Data(element) ((element)->data)
#define DList_Next(element) ((element)->next)
#define DList_Prev(element) ((element)->prev)

#endif