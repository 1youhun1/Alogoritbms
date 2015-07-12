/* cbitree.cpp 二叉树*/
#include <stdlib.h>
#include <string.h>

#include "..\h\cbitree.h"

CBiTree::CBiTree()
{
	this->size = 0;
	this->root = NULL;
	return;
}

CBiTree::~CBiTree()
{
}


void CBiTree::BiTreeInit(void(*destroy)(void *data))
{	
	this->destroy = destroy;
	return;
}

void CBiTree::BiTreeDestroy()
{
	BiTreeRemoveLeft(NULL);
	memset(this, 0, sizeof(CBiTree));

	return;
}

int CBiTree::BiTreeInsertLeft(BiTreeNode *node, const void *data)
{
	BiTreeNode *new_node = NULL, **position = NULL;

	/* 先确认插入节点的位置，位置地址存放在position指针里*/
	if (NULL == node)
	{
		if (this->BiTreeSize() > 0)
			return -1;
		position = &this->root;
	}
	else
	{
		if (node->left != NULL)
			return -1;
		position = &node->left;
	}

	new_node = new BiTreeNode;
	if (NULL == new_node)
		return -1;

	new_node->data = (void *)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;

	this->size++;
	return 0;
}

int CBiTree::BiTreeInsertRight(BiTreeNode *node, const void *data)
{
	BiTreeNode *new_node = NULL, **position = NULL;

	/* 先确认插入节点的位置 */
	if (NULL == node)
	{
		if (this->BiTreeSize() > 0)
			return -1;
		position = &this->root;
	}
	else
	{
		if (node->right != NULL)
			return -1;
		position = &node->right;
	}

	new_node = new BiTreeNode;
	if (NULL == new_node)
		return -1;

	new_node->data = (void *)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;

	this->size++;
	return 0;
}

void CBiTree::BiTreeRemoveLeft(BiTreeNode *node)
{
	BiTreeNode **position = NULL;

	if (0 == this->BiTreeSize())
		return;

	//获取删除节点的位置
	if (NULL == node)
		position = &this->root;
	else
		position = &node->left;

	if (*position != NULL)
	{
		this->BiTreeRemoveLeft(*position);
		this->BiTreeRemoveRight(*position);

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

void CBiTree::BiTreeRemoveRight(BiTreeNode *node)
{
	BiTreeNode **position = NULL;

	if (0 == this->BiTreeSize())
		return;

	//获取删除节点的位置
	if (NULL == node)
		position = &this->root;
	else
		position = &node->right;

	if (*position != NULL)
	{
		BiTreeRemoveLeft(*position);
		BiTreeRemoveRight(*position);

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

//合并两棵二叉树
int CBiTree::BiTreeMerge(CBiTree *left, CBiTree *right, const void *data)
{
	//初始化合并后的树
	this->BiTreeInit(left->destroy);

	//建立root节点
	if (this->BiTreeInsertLeft(NULL, data) != 0)
	{
		this->BiTreeDestroy();
		return -1;
	}

	this->BiTreeRoot()->left = this->BiTreeRoot();
	this->BiTreeRoot()->right = this->BiTreeRoot();

	this->size = this->size + left->BiTreeSize() + right->BiTreeSize();

	//解除原来树的根节点关系
	left->root = NULL;
	left->size = 0;
	right->root = NULL;
	right->size = 0;

	return 0;
}