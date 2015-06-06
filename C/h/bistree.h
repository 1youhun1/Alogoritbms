/* bistree.h */
#ifndef BISTREE_H
#define BISTREE_H

#include "bitree.h"

#define AVL_LFT_HEAVY 1
#define AVL_BALANCED 0
#define AVL_RGT_HEAVY -1

typedef struct AvlNode_
{
	void * data;
	int hidden;  //�ڵ��Ƿ�����
	int factor;  //�Ƿ�ƽ��
}AvlNode;

typedef BiTree BisTree;

void Bistree_Init(BisTree *tree, int(*compare)(const void *key1, const void *key2), void(*destroy)(void *data));
void BisTree_Destroy(BisTree *tree);
int BisTree_Insert(BisTree *tree, const void *data);
int BisTree_Remove(BisTree *tree, const void *data);
int BisTree_Lookup(BisTree *tree, void **data);
#define BsiTree_Size(tree) ((tree)->size)

#endif
