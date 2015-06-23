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


void CBiTree::BiTree_Init(void(*destroy)(void *data))
{	
	this->destroy = destroy;
	return;
}

void CBiTree::BiTree_Destroy()
{
	BiTree_Rem_Left(NULL);
	memset(this, 0, sizeof(CBiTree));

	return;
}

int CBiTree::BiTree_Ins_Left(BiTreeNode *node, const void *data)
{
	BiTreeNode *new_node = NULL, **position = NULL;

	/* ��ȷ�ϲ���ڵ��λ�ã�λ�õ�ַ�����positionָ����*/
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

int CBiTree::BiTree_Ins_Right(BiTreeNode *node, const void *data)
{
	BiTreeNode *new_node = NULL, **position = NULL;

	/* ��ȷ�ϲ���ڵ��λ�� */
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

void CBiTree::BiTree_Rem_Left(BiTreeNode *node)
{
	BiTreeNode **position = NULL;

	if (0 == this->BiTree_Size())
		return;

	//��ȡɾ���ڵ��λ��
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
			//���ú����ͷ�����
			this->destroy((*position)->data);
		}

		free(*position);
		*position = NULL;

		this->size--;
	}
	return;
}

void CBiTree::BiTree_Rem_Right(BiTreeNode *node)
{
	BiTreeNode **position = NULL;

	if (0 == this->BiTree_Size())
		return;

	//��ȡɾ���ڵ��λ��
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
int CBiTree::BiTree_Merge(CBiTree *left, CBiTree *right, const void *data)
{
	//��ʼ���ϲ������
	this->BiTree_Init(left->destroy);

	//����root�ڵ�
	if (this->BiTree_Ins_Left(NULL, data) != 0)
	{
		this->BiTree_Destroy();
		return -1;
	}

	this->BiTree_Root()->left = this->BiTree_Root();
	this->BiTree_Root()->right = this->BiTree_Root();

	this->size = this->size + left->BiTree_Size() + right->BiTree_Size();

	//���ԭ�����ĸ��ڵ��ϵ
	left->root = NULL;
	left->size = 0;
	right->root = NULL;
	right->size = 0;

	return 0;
}