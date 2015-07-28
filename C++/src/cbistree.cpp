/* cbistree.cpp ����������*/

#include <stdlib.h>
#include <memory.h>
#include "..\h\cbistree.h"

CBisTree::CBisTree()
{
	this->size = 0;
	this->root = NULL;
	return;
}
CBisTree::~CBisTree()
{
}

void CBisTree::Rotate_Left(BiTreeNode **node)
{
	BiTreeNode * left = NULL, *grandchile = NULL;
	left = BiTreeLeft(*node);

	/*ƽ�������ĳһ�ڵ�����ӵ��������ϲ���һ���µĽڵ㣬ʹ�øýڵ㲻��ƽ��,
	��ʱֻ��Ҫ����������תһ�μ���*/
	if (AVL_LFT_HEAVY == ((AvlNode *)BiTreeData(left))->factor)
	{
		/* ���� LL��ת */
		(*node)->left = BiTreeRight(left);
		left->right = *node;
		((AvlNode *)BiTreeData(*node))->factor = AVL_BALANCED;
		((AvlNode *)BiTreeData(left))->factor = AVL_BALANCED;
		*node = left;
	}
	/*ƽ�������ĳһ�ڵ�����ӵ��������ϲ���һ���µĽڵ㣬ʹ�øýڵ㲻��ƽ��,
	��ʱ��Ҫ��ת���Σ���һ�ε�������ת�ǲ��ܹ�ʹ�������ٴ�ƽ��,
	��ʱ����Ҫ��������תһ�Ρ�*/
	else
	{
		/* ���� LR��ת */
		grandchile = BiTreeRight(left);
		left->right = BiTreeLeft(grandchile);
		grandchile->left = left;
		(*node)->left = BiTreeRight(grandchile);
		grandchile->right = *node;

		switch (((AvlNode *)BiTreeData(grandchile))->factor)
		{
		case AVL_LFT_HEAVY:
			((AvlNode *)BiTreeData(*node))->factor = AVL_RGT_HEAVY;
			((AvlNode *)BiTreeData(left))->factor = AVL_BALANCED;
			break;
		case AVL_BALANCED:
			((AvlNode *)BiTreeData(*node))->factor = AVL_BALANCED;
			((AvlNode *)BiTreeData(left))->factor = AVL_BALANCED;
			break;
		case AVL_RGT_HEAVY:
			((AvlNode *)BiTreeData(*node))->factor = AVL_BALANCED;
			((AvlNode *)BiTreeData(left))->factor = AVL_LFT_HEAVY;
			break;
		}
		((AvlNode *)BiTreeData(grandchile))->factor = AVL_BALANCED;
		*node = grandchile;
	}

	return;
}

void CBisTree::Rotate_Right(BiTreeNode **node)
{
	BiTreeNode * right = NULL, *grandchile = NULL;
	right = BiTreeLeft(*node);

	/*ƽ�������ĳһ�ڵ���Һ��ӵ��������ϲ���һ���µĽڵ㣬ʹ�øýڵ㲻��ƽ��,
	��ʱֻ��Ҫ����������תһ�μ��ɣ�*/
	if (AVL_RGT_HEAVY == ((AvlNode *)BiTreeData(right))->factor)
	{
		/* ���� RR��ת */
		(*node)->right = BiTreeLeft(right);
		right->left = *node;
		((AvlNode *)BiTreeData(*node))->factor = AVL_BALANCED;
		((AvlNode *)BiTreeData(right))->factor = AVL_BALANCED;
		*node = right;
	}
	/*ƽ�������ĳһ�ڵ���Һ��ӵ��������ϲ���һ���µĽڵ㣬ʹ�øýڵ㲻��ƽ��,
	��ʱ��Ҫ��ת���Σ���������תһ�κ���������תһ��*/
	else
	{
		/* ���� RL��ת */
		grandchile = BiTreeLeft(right);
		right->left = BiTreeRight(grandchile);
		grandchile->right = right;
		(*node)->right = BiTreeLeft(grandchile);
		grandchile->left = *node;

		switch (((AvlNode *)BiTreeData(grandchile))->factor)
		{
		case AVL_LFT_HEAVY:
			((AvlNode *)BiTreeData(*node))->factor = AVL_BALANCED;
			((AvlNode *)BiTreeData(right))->factor = AVL_RGT_HEAVY;
			break;
		case AVL_BALANCED:
			((AvlNode *)BiTreeData(*node))->factor = AVL_BALANCED;
			((AvlNode *)BiTreeData(right))->factor = AVL_BALANCED;
			break;
		case AVL_RGT_HEAVY:
			((AvlNode *)BiTreeData(*node))->factor = AVL_LFT_HEAVY;
			((AvlNode *)BiTreeData(right))->factor = AVL_BALANCED;
			break;
		}
		((AvlNode *)BiTreeData(grandchile))->factor = AVL_BALANCED;
		*node = grandchile;
	}
	return;
}

/*�ݹ���ã�ɾ��������*/
void CBisTree::Destroy_Left(BiTreeNode *node)
{
	BiTreeNode ** position = NULL;

	if (0 == BiTreeSize())
		return;

	if (NULL == node)
		position = &root;
	else
		position = &node->left;

	if (*position != NULL)
	{
		Destroy_Left(*position);
		Destroy_Right(*position);

		if (destroy != NULL)
		{
			destroy(((AvlNode*)(*position)->data)->data);
		}

		free((*position)->data);
		free(*position);
		*position = NULL;
		size--;
	}
	return;
}

/*�ݹ���ã�ɾ��������*/
void CBisTree::Destroy_Right(BiTreeNode *node)
{
	BiTreeNode ** position = NULL;

	if (0 == BiTreeSize())
		return;

	if (NULL == node)
		position = &root;
	else
		position = &node->right;

	if (*position != NULL)
	{
		Destroy_Left(*position);
		Destroy_Right(*position);

		if (destroy != NULL)
		{
			destroy(((AvlNode*)(*position)->data)->data);
		}

		free((*position)->data);
		free(*position);
		*position = NULL;
		size--;
	}
	return;
}

int CBisTree::Insert(BiTreeNode **node,const void * data, int * balanced)
{
	AvlNode* avl_data = NULL;
	int cmpval = 0, result = 0;
	BiTreeNode* leftNode = NULL;
	BiTreeNode* rightNode = NULL;

	//β�ڵ���ֱ�Ӳ���������
	if (BiTreeIsEndob(*node))
	{
		if (NULL == (avl_data = (AvlNode*)malloc(sizeof(AvlNode))))
			return -1;

		avl_data->factor = AVL_BALANCED;
		avl_data->hidden = 0;
		avl_data->data = (void *)data;

		return BiTreeInsertLeft(*node, avl_data);
	}
	else
	{
		cmpval = compare(data, ((AvlNode *)BiTreeData(*node))->data);
		/*�ݹ���ò���������*/
		if (cmpval < 0)
		{
			if (BiTreeIsEndob(BiTreeLeft(*node)))
			{
				if (NULL == (avl_data = (AvlNode *)malloc(sizeof(AvlNode))))
					return -1;
				avl_data->factor = AVL_BALANCED;
				avl_data->hidden = 0;
				avl_data->data = (void *)data;

				if (0 != BiTreeInsertLeft(*node, avl_data))
					return -1;
				*balanced = 0;
			}
			else
			{
				leftNode = BiTreeLeft(*node);
				if (0 != (result = Insert(&leftNode, data, balanced)))
				{
					return result;
				}
			}
			/*ƽ�����*/
			if (!(*balanced))
			{
				switch (((AvlNode *)BiTreeData(*node))->factor)
				{
				case AVL_LFT_HEAVY:
					Rotate_Left(node);
					*balanced = 1;
					break;

				case AVL_BALANCED:
					((AvlNode *)BiTreeData(*node))->factor = AVL_LFT_HEAVY;
					break;

				case AVL_RGT_HEAVY:
					((AvlNode *)BiTreeData(*node))->factor = AVL_BALANCED;
					*balanced = 1;
					break;
				}
			}
		}
		else if (cmpval > 0)
		{
			/*�ݹ���ò���������*/
			if (BiTreeIsEndob(BiTreeRight(*node)))
			{
				if (NULL == (avl_data = (AvlNode *)malloc(sizeof(AvlNode))))
					return -1;
				avl_data->factor = AVL_BALANCED;
				avl_data->hidden = 0;
				avl_data->data = (void *)data;

				if (0 != BiTreeInsertRight(*node, avl_data))
					return -1;
				*balanced = 0;
			}
			else
			{
				rightNode = BiTreeRight(*node);
				if (0 != (result = Insert(&rightNode, data, balanced)))
				{
					return result;
				}
			}
			/*ƽ�����*/
			if (!(*balanced))
			{
				switch (((AvlNode *)BiTreeData(*node))->factor)
				{
				case AVL_LFT_HEAVY:
					((AvlNode *)BiTreeData(*node))->factor = AVL_BALANCED;
					*balanced = 1;
					break;

				case AVL_BALANCED:
					((AvlNode *)BiTreeData(*node))->factor = AVL_RGT_HEAVY;
					break;

				case AVL_RGT_HEAVY:
					Rotate_Right(node);
					*balanced = 1;
					break;
				}
			}
		}
		//��ѯ����ͬ�ڵ㣬���滻
		else
		{
			if (destroy != NULL)
			{
				/*ɾ���ϴ����ص����� */
				destroy(((AvlNode*)BiTreeData(*node))->data);
			}
			((AvlNode*)BiTreeData(*node))->data = (void *)data;
			((AvlNode*)BiTreeData(*node))->hidden = 0;

			/* ��ƽ��δ���ƻ� */
			*balanced = 1;
		}
	}
	return 0;
}

int CBisTree::Hide(BiTreeNode *node, const void *data)
{
	int cmpval = 0, result = 0;

	if (BiTreeIsEndob(node))
		return -1;

	cmpval = compare(data, ((AvlNode*)BiTreeData(node))->data);
	if (cmpval < 0)
	{
		result = Hide(BiTreeLeft(node), data);
	}
	else if (cmpval > 0)
	{
		result = Hide(BiTreeRight(node), data);
	}
	else
	{
		((AvlNode*)BiTreeData(node))->hidden = 1;
		result = 0;
	}
	return result;
}

int CBisTree::Lookup(BiTreeNode *node, void **data)
{
	int cmpval = 0, result = 0;

	if (BiTreeIsEndob(node))
		return -1;

	cmpval = compare(*data, ((AvlNode*)BiTreeData(node))->data);
	if (cmpval < 0)
	{
		result = Lookup(BiTreeLeft(node), data);
	}
	else if (cmpval > 0)
	{
		result = Lookup(BiTreeRight(node), data);
	}
	else
	{
		/* hiddenΪ�����صĽڵ�*/
		if (!((AvlNode*)BiTreeData(node))->hidden)
		{
			*data = ((AvlNode*)BiTreeData(node))->data;
			result = 0;
		}
		else
		{
			return -1;
		}
	}
	return result;
}


void CBisTree::Bistree_Init(int(*compare)(const void *key1, const void *key2), void(*destroy)(void *data))
{
	BiTreeInit(destroy);
	compare = compare;
	return;
}
void CBisTree::BisTree_Destroy()
{
	Destroy_Left(NULL);
	memset(this, 0, sizeof(CBisTree));
	return;
}
int CBisTree::BisTree_Insert(const void *data)
{
	int balanced = 0;
	return Insert(&root, data, &balanced);
}
int CBisTree::BisTree_Remove(const void *data)
{
	return Hide(root, data);
}
int CBisTree::BisTree_Lookup(void **data)
{
	return Lookup(root, data);
}
