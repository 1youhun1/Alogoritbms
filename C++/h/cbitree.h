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

	void BiTree_Init(void(*destroy)(void *data));
	void BiTree_Destroy();
	int BiTree_Ins_Left(BiTreeNode *node, const void *data);
	int BiTree_Ins_Right(BiTreeNode *node, const void *data);
	void BiTree_Rem_Left(BiTreeNode *node);
	void BiTree_Rem_Right(BiTreeNode *node);
	int BiTree_Merge(CBiTree *left, CBiTree *right, const void *data);

public:
	int BiTree_Size() const { 
		return (this->size); 
	}
	BiTreeNode* BiTree_Root() const {
		return (this->root);
	}
	//是否为分支结束
	bool BiTree_Is_Endob(BiTreeNode *node) {
		return (NULL == node);
	}
	bool BiTree_Is_Leaf(BiTreeNode *node) {
	return (NULL == node->left && NULL == node->right);
	}

protected:
	int  size;	
	BiTreeNode *root;   //根结点
};

#endif