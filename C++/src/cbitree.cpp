/* cbitree.cpp ������*/
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

	/* ��ȷ�ϲ���ڵ��λ�ã�λ�õ�ַ�����positionָ����*/
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

	/* ��ȷ�ϲ���ڵ��λ�� */
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

	//��ȡɾ���ڵ��λ��
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
			//���ú����ͷ�����
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

	//��ȡɾ���ڵ��λ��
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
			//���ú����ͷ�����
			this->destroy((*position)->data);
		}

		delete *position;
		*position = NULL;

		this->size--;
	}
	return;
}

//�ϲ����ö�����
int CBiTree::BiTreeMerge(CBiTree *left, CBiTree *right, const void *data)
{
	//��ʼ���ϲ������
	this->BiTreeInit(left->destroy);

	//����root�ڵ�
	if (this->BiTreeInsertLeft(NULL, data) != 0)
	{
		this->BiTreeDestroy();
		return -1;
	}

	this->BiTreeRoot()->left = this->BiTreeRoot();
	this->BiTreeRoot()->right = this->BiTreeRoot();

	this->size = this->size + left->BiTreeSize() + right->BiTreeSize();

	//���ԭ�����ĸ��ڵ��ϵ
	left->root = NULL;
	left->size = 0;
	right->root = NULL;
	right->size = 0;

	return 0;
}