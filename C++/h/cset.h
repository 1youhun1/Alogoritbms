/*cset.h*/
#ifndef CSET_H
#define CSET_H

#include <stdlib.h>
#include "clist.h"

class CSet : public Clist
{
public:
	CSet();
	~CSet();

public:
	void SetInit(int(*match)(const void *key1, const void *key2),
		void(*destroy)(void *data));

	int SetInsert(const void *data);
	int SetRemove(void **data);
	int SetUnion(const CSet *set1, const CSet *set2); //求并集
	int SetIntersection(const CSet *set1, const CSet *set2); //求交集
	int SetDifference(const CSet *set1, const CSet *set2); //求差集	

public:
	int SetIsSubset(const CSet *set);
	int SetIsEqual(const CSet *set);
	int SetIsMember(const void *data) const;

public:
	int SetSize() const {return this->size;}
	void SetDestroy() { this->ListDestroy(); }

};

#endif