/* cbitree.h */
#ifndef CBITREE_H
#define CBITREE_H

typedef struct BiTreeNode_
{
	void *data;
	struct BiTreeNode_ *left;	//���ӽ��
	struct BiTreeNode_ *right;  //���ӽ��
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
	//�Ƿ�Ϊ��֧����
	bool BiTree_Is_Endob(BiTreeNode *node) {
		return (NULL == node);
	}
	bool BiTree_Is_Leaf(BiTreeNode *node) {
	return (NULL == node->left && NULL == node->right);
	}

protected:
	int  size;	
	BiTreeNode *root;   //�����
};

#endif