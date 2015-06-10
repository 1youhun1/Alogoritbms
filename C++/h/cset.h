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
	void Set_Init(int(*match)(const void *key1, const void *key2),
		void(*destroy)(void *data));

	int Set_Insert(const void *data);
	int Set_Remove(void **data);
	int Set_Union(const CSet *set1, const CSet *set2); //求并集
	int Set_Intersection(const CSet *set1, const CSet *set2); //求交集
	int Set_Difference(const CSet *set1, const CSet *set2); //求差集	

public:
	int Set_is_Subset(const CSet *set);
	int Set_is_Equal(const CSet *set);
	int Set_is_Member(const void *data) const;

public:
	int Set_Size() const {return this->size;}
	void Set_Destroy() { this->List_Destroy(); }

};

#endif