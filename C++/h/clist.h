/*list.h*/
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
	private:
		ListElmt *head;
		ListElmt *tail;
		int size;

	public:
		Clist(void);
		~Clist(void);
		int List_Size(void) { return size; }
		ListElmt *List_Head() { return head; }
		ListElmt *List_Tail() { return tail; }
		bool List_is_Head(ListElmt *element) {
			return ((element) == head ? true : false);
		}
		bool List_is_Tail(ListElmt *element) {
			return ((element)->next == NULL ? true : false);
		}

		int (*match)(const void *key1, const void *key2);
		void (*destroy)(void *data);
		void List_Init(void(*destroy)(void *data));
		void List_Destroy(void);
		int List_Ins_Next(ListElmt *element, const void *data);
		int List_Rem_Next(ListElmt *element, void **data);
	
};

#endif
