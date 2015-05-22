/*set.h*/
#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include "list.h"

typedef List Set;

void Set_Init(Set *set, int (*match)(const void *key1, const void *key2), 
              void (*destroy)(void *data));
#define Set_Destroy List_Destroy
int Set_Insert(Set *set, const void *data);
int Set_Remove(Set *set, void **data);
int Set_Union(Set *setu, const Set *set1, const Set *set2);
int Set_Intersection(Set *seti, const Set *set1, const Set *set2);
int Set_Difference(Set *setd, const Set *set1, const Set *set2);
int Set_is_Member(const Set *set, const void *data);
int Set_is_Subset(const Set *set1, const Set *set2);
int Set_is_Equal(const Set *set1, const Set *set2);
#define Set_Size(set) ((set)->size)

#define TRUE 1

#endif