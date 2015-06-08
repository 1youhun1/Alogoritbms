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
		int(*match)(const void *key1, const void *key2); //比较函数
		void(*destroy)(void *data);    //删除节点内容
		void DoubleList_Init(void(*destroy)(void *data));
		void DoubleList_Destroy();
		int DoubleList_Ins_Next(DListElmt *element, const void *data);
		int DoubleList_Ins_Prev(DListElmt *element, const void *data);
		int DoubleList_Remove(DListElmt *element, void **data);

	public:
		int DoubleList_Size() const {return size;}
		DListElmt* DoubleList_Head() const { return head; }
		DListElmt* DoubleList_Tail() const { return tail; }

		bool DoubleList_is_Head(DListElmt *element) {
			return ((element)->prev == NULL ? true : false);
		}
		bool DoubleList_is_Tail(DListElmt *element) {
			return ((element)->next == NULL ? true : false);
		}

	private:
		int size;
		DListElmt *head;
		DListElmt *tail;
};

#endif