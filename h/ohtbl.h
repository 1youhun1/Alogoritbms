/* ohtbl.h */
#ifndef OHTBL_H
#define OHTBL_H

#include <stdlib.h>

typedef struct OHTbl_
{
    int positions; //分配的表位数（不同于链式hash中的桶）
    void *vacated; //曾经删除的元素的位置，这里删除元素不能置NULL，而是指向vacated，最后一个元素才能置NULL

    int  (*h1)(const void *key);
    int  (*h2)(const void *key);
    int  (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    int  size;
    void **table;
}OHTbl;

int Ohtbl_Init(OHTbl *htbl, int positions, int (*h1)(const void *key),
               int (*h2)(const void *key), int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data));
void Ohtbl_Destroy(OHTbl *htbl);
int  Ohtbl_Insert(OHTbl *htbl, const void *data);
int  Ohtbl_Remove(OHTbl *htbl, void **data);
int  Ohtbl_Lookup(const OHTbl *htbl, void **data);

#define Ohtbl_Size(htbl) ((htbl)->size)

#endif