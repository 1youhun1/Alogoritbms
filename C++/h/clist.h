/*clist.h µ•¡¥±Ì¿‡*/
#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

typedef struct ListElmt_
{
	void *data;
	struct ListElmt_ *next;
}ListElmt;

class Clist
{
public:
	Clist(void);
	~Clist(void);

public:
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	void ListInit(void(*destroy)(void *data));
	void ListDestroy(void);
	int ListInsertNext(ListElmt *element, const void *data);
	int ListRemoveNext(ListElmt *element, void **data);

public:
	int ListSize(void) const { return size; }
	ListElmt *ListHead() const { return head; }
	ListElmt *ListTail() const { return tail; }
	bool ListIsHead(ListElmt *element) {
		return ((element) == head ? true : false);
	}
	bool ListIsTail(ListElmt *element) {
		return ((element)->next == NULL ? true : false);
	}

protected:
	ListElmt *head;
	ListElmt *tail;
	int size;
};

#endif
