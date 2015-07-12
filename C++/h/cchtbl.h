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
	int  ChtblInit(int buckets, int(*h)(const void *key),
		int (*match)(const void *key1, const void *key2), void(*destroy)(void *data));
	void ChtblDestroy();
	int  ChtblInsert(const void *data);
	int  ChtblRemove(void **data);
	int  ChtblLookup(void **data);

	int(*h)(const void *key);
	int(*match)(const void *key1, const void *key2);
	void(*destroy)(void *data);
	int ChtblSize() const { return size; }

public:
	Clist *table;
private:
	int buckets;  //hash链分配桶的个数
	int size;
};



#endif