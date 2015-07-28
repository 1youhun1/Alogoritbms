/* cbistree.h */
#ifndef CBISTREE_H
#define CBISTREE_H

#include "cbitree.h"

#define AVL_LFT_HEAVY 1
#define AVL_BALANCED 0
#define AVL_RGT_HEAVY -1

typedef struct AvlNode_
{
	void * data;
	int hidden;  //节点是否隐藏
	int factor;  //是否平衡
}AvlNode;

class CBisTree : public CBiTree
{
public:
	CBisTree();
	~CBisTree();
public:
	void Bistree_Init(int(*compare)(const void *key1, const void *key2), void(*destroy)(void *data));
	void BisTree_Destroy();
	int BisTree_Insert(const void *data);
	int BisTree_Remove(const void *data);
	int BisTree_Lookup(void **data);
	size_t BsiTree_Size() const { return size; }
public:
	void Rotate_Left(BiTreeNode **node);
	void Rotate_Right(BiTreeNode **node);
	void Destroy_Left(BiTreeNode *node);
	void Destroy_Right(BiTreeNode *node);
	int Insert(BiTreeNode **node, const void * data, int * balanced);
	int Hide(BiTreeNode *node, const void *data);
	int Lookup(BiTreeNode *node, void **data);

};

#endif
