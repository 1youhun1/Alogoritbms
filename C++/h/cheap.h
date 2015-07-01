/*cheap.h ¶ÑÀà*/
#ifndef CHEAP_H
#define CHEAP_H

class CHeap
{
public:
	CHeap(void);
	~CHeap(void);

public:
	void HeapInit(int(*compare)(const void *key1, const void *key2), void(*destroy)(void *data));
	void HeapDestroy();
	int HeapInsert(const void *data);
	int HeapExtract(void **data);
public:
	int HeapSize()const { return this->size; }
	int(*compare)(const void *key1, const void *key2);
	void(*destroy)(void *data);
protected:
	int size;
	void **tree;
};

#endif