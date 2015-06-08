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
		void List_Init(void(*destroy)(void *data));
		void List_Destroy(void);
		int List_Ins_Next(ListElmt *element, const void *data);
		int List_Rem_Next(ListElmt *element, void **data);

	public:
		int List_Size(void) const { return size; }
		ListElmt *List_Head() const { return head; }
		ListElmt *List_Tail() const { return tail; }
		bool List_is_Head(ListElmt *element) {
			return ((element) == head ? true : false);
		}
		bool List_is_Tail(ListElmt *element) {
			return ((element)->next == NULL ? true : false);
		}

	private:
		ListElmt *head;
		ListElmt *tail;
		int size;	
};

#endif
