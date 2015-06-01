/*pqueue.h 优先级队列，用堆实现*/
#ifndef PQUEUE_H
#define PQUEUE_H

#include "heap.h"

typedef Heap PQueue;

#define pqueue_init heap_init
#define pqueue_destory heap_destroy
#define pqueue_insert heap_insert
#define pqueue_extract heap_extract
//获取优先级队列中优先级最高的元素
#define pqueue_peek(pqueue) ((pqueue)->tree == NULL ? NULL : (pqueue)->tree[0])
#define pqueue_size heap_size

#endif