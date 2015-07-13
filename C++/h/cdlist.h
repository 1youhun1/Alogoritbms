/*cdlist.h*/
#ifndef CDLIST_H
#define CDLIST_H

#include <stdlib.h>

struct DListElmt
{
	void *data;
	DListElmt *prev;
	DListElmt *next;
};

class CDoubleList
{
public:
	CDoubleList(void);
	~CDoubleList(void);

public:
	int(*match)(const void *key1, const void *key2); //�ȽϺ���
	void(*destroy)(void *data);    //ɾ���ڵ�����
	void DoubleListInit(void(*destroy)(void *data));
	void DoubleListDestroy();
	int DoubleListInsertNext(DListElmt *element, const void *data);
	int DoubleListInsertPrev(DListElmt *element, const void *data);
	int DoubleListRemove(DListElmt *element, void **data);

public:
	int DoubleListSize() const {return size;}
	DListElmt* DoubleListHead() const { return head; }
	DListElmt* DoubleListTail() const { return tail; }

	bool DoubleListIsHead(DListElmt *element) {
		return ((element)->prev == NULL ? true : false);
	}
	bool DoubleListIsTail(DListElmt *element) {
		return ((element)->next == NULL ? true : false);
	}

private:
	size_t size;
	DListElmt *head;
	DListElmt *tail;
};

#endif