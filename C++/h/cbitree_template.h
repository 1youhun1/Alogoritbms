/* cbitree_template.h */
#ifndef CBITREE_TEMPLATE_H
#define CBITREE_TEMPLATE_H

#include <stdlib.h>

template<class T>
struct BiTreeNode
{
	T *data;
	BiTreeNode<T> *left;	//左子结点
	BiTreeNode<T> *right;  //右子结点
};

template<class T>
class CBiTree_Template
{
public:
	CBiTree_Template();
	~CBiTree_Template();
public:
	int(*compare)(const T *key1, const T *key2);
	void(*destroy)(T *data);

	void BiTree_Init(void(*destroy)(T *data));
	void BiTree_Destroy();
	int BiTree_Ins_Left(BiTreeNode<T> *node, const T *data);
	int BiTree_Ins_Right(BiTreeNode<T> *node, const T *data);
	void BiTree_Rem_Left(BiTreeNode<T> *node);
	void BiTree_Rem_Right(BiTreeNode<T> *node);
	int BiTree_Merge(CBiTree_Template<T> *left, CBiTree_Template<T> *right, const T *data);

public:
	int BiTree_Size() const {
		return (this->size);
	}
	BiTreeNode* BiTree_Root() const {
		return (this->root);
	}
	//是否为分支结束
	bool BiTree_Is_Endob(BiTreeNode<T> *node) {
		return (NULL == node);
	}
	bool BiTree_Is_Leaf(BiTreeNode<T> *node) {
		return (NULL == node->left && NULL == node->right);
	}

protected:
	int  size;
	BiTreeNode<T> *root;   //根结点
};

template<class T>
CBiTree_Template<T>::CBiTree_Template()
{
	this->size = 0;
	this->root = NULL;
	return;
}

template<class T>
CBiTree_Template<T>::~CBiTree_Template()
{
}

template<class T>
void CBiTree_Template<T>::BiTree_Init(void(*destroy)(T *data))
{
	this->destroy = destroy;
	return;
}

template<class T>
void CBiTree_Template<T>::BiTree_Destroy()
{
	BiTree_Rem_Left(NULL);
	memset(this, 0, sizeof(CBiTree_Template<T>));

	return;
}

template<class T>
int CBiTree_Template<T>::BiTree_Ins_Left(BiTreeNode<T> *node, const T *data)
{
	BiTreeNode<T> *new_node = NULL, **position = NULL;

	/* 先确认插入节点的位置，位置地址存放在position指针里*/
	if (NULL == node)
	{
		if (this->BiTree_Size() > 0)
			return -1;
		position = &this->root;
	}
	else
	{
		if (node->left != NULL)
			return -1;
		position = &node->left;
	}

	new_node = new BiTreeNode<T>{0};
	if (NULL == new_node)
		return -1;

	new_node->data = (T *)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;

	this->size++;
	return 0;
}

template<class T>
int CBiTree_Template<T>::BiTree_Ins_Right(BiTreeNode<T> *node, const T *data)
{
	BiTreeNode<T> *new_node = NULL, **position = NULL;

	/* 先确认插入节点的位置 */
	if (NULL == node)
	{
		if (this->BiTree_Size() > 0)
			return -1;
		position = &this->root;
	}
	else
	{
		if (node->right != NULL)
			return -1;
		position = &node->right;
	}

	new_node = new BiTreeNode<T>{ 0 };
	if (NULL == new_node)
		return -1;

	new_node->data = (T *)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;

	this->size++;
	return 0;
}

template<class T>
void CBiTree_Template<T>::BiTree_Rem_Left(BiTreeNode<T> *node)
{
	BiTreeNode<T> **position = NULL;

	if (0 == this->BiTree_Size())
		return;

	//获取删除节点的位置
	if (NULL == node)
		position = &this->root;
	else
		position = &node->left;

	if (*position != NULL)
	{
		this->BiTree_Rem_Left(*position);
		this->BiTree_Rem_Right(*position);

		if (this->destroy != NULL)
		{
			//调用函数释放数据
			this->destroy((*position)->data);
		}

		free(*position);
		*position = NULL;

		this->size--;
	}
	return;
}

template<class T>
void CBiTree_Template<T>::BiTree_Rem_Right(BiTreeNode<T> *node)
{
	BiTreeNode<T> **position = NULL;

	if (0 == this->BiTree_Size())
		return;

	//获取删除节点的位置
	if (NULL == node)
		position = &this->root;
	else
		position = &node->right;

	if (*position != NULL)
	{
		BiTree_Rem_Left(*position);
		BiTree_Rem_Right(*position);

		if (this->destroy != NULL)
		{
			//调用函数释放数据
			this->destroy((*position)->data);
		}

		delete *position;
		*position = NULL;

		this->size--;
	}
	return;
}

template<class T>
//合并两棵二叉树
int CBiTree_Template<T>::BiTree_Merge(CBiTree_Template<T> *left, CBiTree_Template<T> *right, const T *data)
{
	//初始化合并后的树
	this->BiTree_Init(left->destroy);

	//建立root节点
	if (this->BiTree_Ins_Left(NULL, data) != 0)
	{
		this->BiTree_Destroy();
		return -1;
	}

	this->BiTree_Root()->left = this->BiTree_Root();
	this->BiTree_Root()->right = this->BiTree_Root();

	this->size = this->size + left->BiTree_Size() + right->BiTree_Size();

	//解除原来树的根节点关系
	left->root = NULL;
	left->size = 0;
	right->root = NULL;
	right->size = 0;

	return 0;
}

#endif