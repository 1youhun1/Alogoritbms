/* cchtbl.h */
#ifndef CCHTBL_H
#define CCHTBL_H

#include <stdlib.h>

#include "clist.h"

class CCHTbl
{
public:
	CCHTbl(void);
	~CCHTbl(void);
public:
	int  Chtbl_Init(int buckets, int(*h)(const void *key), int
		(*match)(const void *key1, const void *key2), void(*destroy)(void *data));
	void Chtbl_Destroy();
	int  Chtbl_Insert(const void *data);
	int  Chtbl_Remove(void **data);
	int  Chtbl_Lookup(void **data);

	int(*h)(const void *key);
	int(*match)(const void *key1, const void *key2);
	void(*destroy)(void *data);
	int Chtbl_Size() const { return size; }

public:
	Clist *table;
private:
	int buckets;  //hash链分配桶的个数
	int size;
};



#endif