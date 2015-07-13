/* cbitree.h */
#ifndef CBITREE_H
#define CBITREE_H

typedef struct BiTreeNode_
{
	void *data;
	struct BiTreeNode_ *left;	//左子结点
	struct BiTreeNode_ *right;  //右子结点
}BiTreeNode;

class CBiTree
{
public:
	CBiTree();
	~CBiTree();
public:
	int(*compare)(const void *key1, const void *key2);
	void(*destroy)(void *data);

	void BiTreeInit(void(*destroy)(void *data));
	void BiTreeDestroy();
	int BiTreeInsertLeft(BiTreeNode *node, const void *data);
	int BiTreeInsertRight(BiTreeNode *node, const void *data);
	void BiTreeRemoveLeft(BiTreeNode *node);
	void BiTreeRemoveRight(BiTreeNode *node);
	int BiTreeMerge(CBiTree *left, CBiTree *right, const void *data);

public:
	int BiTreeSize() const { 
		return (this->size); 
	}
	BiTreeNode* BiTreeRoot() const {
		return (this->root);
	}
	//是否为分支结束
	bool BiTreeIsEndob(BiTreeNode *node) const{
		return (NULL == node);
	}
	bool BiTreeIsLeaf(BiTreeNode *node) const{
		return (NULL == node->left && NULL == node->right);
	}

protected:
	size_t  size;
	BiTreeNode *root;   //根结点
};

#endif