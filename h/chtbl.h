/* chtbl.h */
#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "list.h"

typedef struct CHTbl_
{
    int buckets;  //hash链分配桶的个数

    int (*h)(const void *key);
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    int size;
    List *table;
}CHTbl;

int  Chtbl_Init(CHTbl *htbl, int buckets, int (*h)(const void *key), int 
           (*match)(const void *key1, const void *key2), void (*destroy)(void *data));
void Chtbl_Destroy(CHTbl *htbl);
int  Chtbl_Insert(CHTbl *htbl, const void *data);
int  Chtbl_Remove(CHTbl *htbl, void **data);
int  Chtbl_Lookup(CHTbl *htbl, void **data);

#define Chtbl_Size(htbl) ((htbl)->size)
#define TRUE 1

#endif