/* cbitree_template.h */
#ifndef CBITREE_TEMPLATE_H
#define CBITREE_TEMPLATE_H

#include <stdlib.h>

template<class T>
struct BiTreeNode
{
	T *data;
	BiTreeNode<T> *left;	//���ӽ��
	BiTreeNode<T> *right;  //���ӽ��
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

	void BiTreeInit(void(*destroy)(T *data));
	void BiTreeDestroy();
	int BiTreeInsertLeft(BiTreeNode<T> *node, const T *data);
	int BiTreeInsertRight(BiTreeNode<T> *node, const T *data);
	void BiTreeRemoveLeft(BiTreeNode<T> *node);
	void BiTreeRemoveRight(BiTreeNode<T> *node);
	int BiTreeMerge(CBiTree_Template<T> *left, CBiTree_Template<T> *right, const T *data);

public:
	int BiTreeSize() const {
		return (this->size);
	}
	BiTreeNode* BiTreeRoot() const {
		return (this->root);
	}
	//�Ƿ�Ϊ��֧����
	bool BiTreeIsEndob(BiTreeNode<T> *node) {
		return (NULL == node);
	}
	bool BiTreeIsLeaf(BiTreeNode<T> *node) {
		return (NULL == node->left && NULL == node->right);
	}

protected:
	size_t  size;
	BiTreeNode<T> *root;   //�����
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
void CBiTree_Template<T>::BiTreeInit(void(*destroy)(T *data))
{
	this->destroy = destroy;
	return;
}

template<class T>
void CBiTree_Template<T>::BiTreeDestroy()
{
	BiTreeRemoveLeft(NULL);
	memset(this, 0, sizeof(CBiTree_Template<T>));

	return;
}

template<class T>
int CBiTree_Template<T>::BiTreeInsertLeft(BiTreeNode<T> *node, const T *data)
{
	BiTreeNode<T> *new_node = NULL, **position = NULL;

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
int CBiTree_Template<T>::BiTreeInsertRight(BiTreeNode<T> *node, const T *data)
{
	BiTreeNode<T> *new_node = NULL, **position = NULL;

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
void CBiTree_Template<T>::BiTreeRemoveLeft(BiTreeNode<T> *node)
{
	BiTreeNode<T> **position = NULL;

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

template<class T>
void CBiTree_Template<T>::BiTreeRemoveRight(BiTreeNode<T> *node)
{
	BiTreeNode<T> **position = NULL;

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

template<class T>
//�ϲ����ö�����
int CBiTree_Template<T>::BiTreeMerge(CBiTree_Template<T> *left, CBiTree_Template<T> *right, const T *data)
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

#endif