/*list.h*/
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct ListElmt_
{
    void *data;
    struct ListElmt_ *next;
}ListElmt;

typedef struct List_
{
    int size;
    int (*match)(const void *key1,const void *key2);
    void (*destroy)(void *data);
    ListElmt *head;
    ListElmt *tail;
}List;

/*公共接口*/
void List_Init(List *list,void (*destroy)(void *data));
void List_Destroy(List *list);
int List_Ins_Next(List *list,ListElmt *element,const void *data);
int List_Rem_Next(List *list,ListElmt *element,void **data);

#define List_Size(list) ((list)->size)
#define List_Head(list) ((list)->head)
#define List_Tail(list) ((list)->tail)
#define List_is_Head(list,element) ((element) == (list)->head ? 1 : 0)
#define List_is_Tail(element) ((element)->next == NULL ? 1 : 0)
#define List_Data(element) ((element)->data)
#define List_Next(element) ((element)->next)

#endif
