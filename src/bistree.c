/*bistree.c ������������AVL����*/
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "bistree.h"

static void Destroy_Right(BisTree *tree, BiTreeNode *node);


static void Rotate_Left(BiTreeNode **node)
{
	BiTreeNode * left = NULL, *grandchile = NULL;
	left = BiTree_Left(*node);

	/*ƽ�������ĳһ�ڵ�����ӵ��������ϲ���һ���µĽڵ㣬ʹ�øýڵ㲻��ƽ��,
		��ʱֻ��Ҫ����������תһ�μ���*/
	if (AVL_LFT_HEAVY == ((AvlNode *)BiTree_Data(left))->factor)
	{
		/* ���� LL��ת */
		BiTree_Left(*node) = BiTree_Right(left);
		BiTree_Right(left) = *node;
		((AvlNode *)BiTree_Data(*node))->factor = AVL_BALANCED;
		((AvlNode *)BiTree_Data(left))->factor = AVL_BALANCED;
		*node = left;
	}
	/*ƽ�������ĳһ�ڵ�����ӵ��������ϲ���һ���µĽڵ㣬ʹ�øýڵ㲻��ƽ��,
		��ʱ��Ҫ��ת���Σ���һ�ε�������ת�ǲ��ܹ�ʹ�������ٴ�ƽ��,
		��ʱ����Ҫ��������תһ�Ρ�*/
	else
	{
		/* ���� LR��ת */
		grandchile = BiTree_Right(left);
		BiTree_Right(left) = BiTree_Left(grandchile);
		BiTree_Left(grandchile) = left;
		BiTree_Left(*node) = BiTree_Right(grandchile);
		BiTree_Right(grandchile) = *node;

		switch (((AvlNode *)BiTree_Data(grandchile))->factor)
		{
			case AVL_LFT_HEAVY:
				((AvlNode *)BiTree_Data(*node))->factor = AVL_RGT_HEAVY;
				((AvlNode *)BiTree_Data(left))->factor = AVL_BALANCED;
				break;
			case AVL_BALANCED:
				((AvlNode *)BiTree_Data(*node))->factor = AVL_BALANCED;
				((AvlNode *)BiTree_Data(left))->factor = AVL_BALANCED;
				break;
			case AVL_RGT_HEAVY:
				((AvlNode *)BiTree_Data(*node))->factor = AVL_BALANCED;
				((AvlNode *)BiTree_Data(left))->factor = AVL_LFT_HEAVY;
				break;
		}
		((AvlNode *)BiTree_Data(grandchile))->factor = AVL_BALANCED;
		*node = grandchile;
	}

	return;
}

static void Rotate_Right(BiTreeNode **node)
{
	BiTreeNode * right = NULL, *grandchile = NULL;
	right = BiTree_Left(*node);

	/*ƽ�������ĳһ�ڵ���Һ��ӵ��������ϲ���һ���µĽڵ㣬ʹ�øýڵ㲻��ƽ��,
		��ʱֻ��Ҫ����������תһ�μ��ɣ�*/
	if (AVL_RGT_HEAVY == ((AvlNode *)BiTree_Data(right))->factor)
	{
		/* ���� RR��ת */
		BiTree_Right(*node) = BiTree_Left(right);
		BiTree_Left(right) = *node;
		((AvlNode *)BiTree_Data(*node))->factor = AVL_BALANCED;
		((AvlNode *)BiTree_Data(right))->factor = AVL_BALANCED;
		*node = right;
	}
	/*ƽ�������ĳһ�ڵ���Һ��ӵ��������ϲ���һ���µĽڵ㣬ʹ�øýڵ㲻��ƽ��,
		��ʱ��Ҫ��ת���Σ���������תһ�κ���������תһ��*/
	else
	{
		/* ���� RL��ת */
		grandchile = BiTree_Left(right);
		BiTree_Left(right) = BiTree_Right(grandchile);
		BiTree_Right(grandchile) = right;
		BiTree_Right(*node) = BiTree_Left(grandchile);
		BiTree_Left(grandchile) = *node;

		switch (((AvlNode *)BiTree_Data(grandchile))->factor)
		{
			case AVL_LFT_HEAVY:
				((AvlNode *)BiTree_Data(*node))->factor = AVL_BALANCED;
				((AvlNode *)BiTree_Data(right))->factor = AVL_RGT_HEAVY;
				break;
			case AVL_BALANCED:
				((AvlNode *)BiTree_Data(*node))->factor = AVL_BALANCED;
				((AvlNode *)BiTree_Data(right))->factor = AVL_BALANCED;
				break;
			case AVL_RGT_HEAVY:
				((AvlNode *)BiTree_Data(*node))->factor = AVL_LFT_HEAVY;
				((AvlNode *)BiTree_Data(right))->factor = AVL_BALANCED;
				break;
		}
		((AvlNode *)BiTree_Data(grandchile))->factor = AVL_BALANCED;
		*node = grandchile;
	}
	return;
}

/*�ݹ���ã�ɾ��������*/
static void Destroy_Left(BisTree *tree, BiTreeNode *node)
{
	BiTreeNode ** position = NULL;

	if (0 == BiTree_Size(tree))
		return;

	if (NULL == node)
		position = &tree->root;
	else
		position = &node->left;

	if (*position != NULL)
	{
		Destroy_Left(tree, *position);
		Destroy_Right(tree, *position);

		if (tree->destroy != NULL)
		{
			tree->destroy(((AvlNode*)(*position)->data)->data);
		}

		free((*position)->data);
		free(*position);
		*position = NULL;
		tree->size--;
	}
	return;
}

/*�ݹ���ã�ɾ��������*/
static void Destroy_Right(BisTree *tree, BiTreeNode *node)
{
	BiTreeNode ** position = NULL;

	if (0 == BiTree_Size(tree))
		return;

	if (NULL == node)
		position = &tree->root;
	else
		position = &node->right;

	if (*position != NULL)
	{
		Destroy_Left(tree, *position);
		Destroy_Right(tree, *position);

		if (tree->destroy != NULL)
		{
			tree->destroy(((AvlNode*)(*position)->data)->data);
		}

		free((*position)->data);
		free(*position);
		*position = NULL;
		tree->size--;
	}
	return;
}

static int Insert(BisTree *tree, BiTreeNode **node,
	const void * data, int * balanced)
{
	AvlNode * avl_data = NULL;
	int cmpval = 0, result = 0;

	//β�ڵ���ֱ�Ӳ���������
	if (BiTree_Is_Endob(*node))
	{
		if (NULL == (avl_data = (AvlNode*)malloc(sizeof(AvlNode))))
			return ERR;

		avl_data->factor = AVL_BALANCED;
		avl_data->hidden = 0;
		avl_data->data = (void *)data;

		return BiTree_Ins_Left(tree, *node, avl_data);
	}
	else
	{
		cmpval = tree->compare(data, ((AvlNode *)BiTree_Data(*node))->data);
		/*�ݹ���ò���������*/
		if (cmpval < 0)
		{
			if (BiTree_Is_Endob(BiTree_Left(*node)))
			{
				if (NULL == (avl_data = (AvlNode *)malloc(sizeof(AvlNode))))
					return ERR;
				avl_data->factor = AVL_BALANCED;
				avl_data->hidden = 0;
				avl_data->data = (void *)data;

				if (OK != BiTree_Ins_Left(tree, *node, avl_data))
					return ERR;
				*balanced = 0;
			}
			else
			{
				if (OK != (result = Insert(tree, &BiTree_Left(*node), data, balanced)))
				{
					return result;
				}
			}
			/*ƽ�����*/
			if (!(*balanced))
			{
				switch (((AvlNode *)BiTree_Data(*node))->factor)
				{
					case AVL_LFT_HEAVY:
						Rotate_Left(node);
						*balanced = 1;
						break;

					case AVL_BALANCED:
						((AvlNode *)BiTree_Data(*node))->factor = AVL_LFT_HEAVY;
						break;

					case AVL_RGT_HEAVY:
						((AvlNode *)BiTree_Data(*node))->factor = AVL_BALANCED;
						*balanced = 1;
						break;
				}
			}
		}
		else if (cmpval > 0)
		{
			/*�ݹ���ò���������*/
			if (BiTree_Is_Endob(BiTree_Right(*node)))
			{
				if (NULL == (avl_data = (AvlNode *)malloc(sizeof(AvlNode))))
					return ERR;
				avl_data->factor = AVL_BALANCED;
				avl_data->hidden = 0;
				avl_data->data = (void *)data;

				if (OK != BiTree_Ins_Right(tree, *node, avl_data))
					return ERR;
				*balanced = 0;
			}
			else
			{
				if (OK != (result = Insert(tree, &BiTree_Right(*node), data, balanced)))
				{
					return result;
				}
			}
			/*ƽ�����*/
			if (!(*balanced))
			{
				switch (((AvlNode *)BiTree_Data(*node))->factor)
				{
				case AVL_LFT_HEAVY:
					((AvlNode *)BiTree_Data(*node))->factor = AVL_BALANCED;
					*balanced = 1;
					break;

				case AVL_BALANCED:
					((AvlNode *)BiTree_Data(*node))->factor = AVL_RGT_HEAVY;
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
			if (tree->destroy != NULL)
			{
				/*ɾ���ϴ����ص����� */
				tree->destroy(((AvlNode*)BiTree_Data(*node))->data);
			}
			((AvlNode*)BiTree_Data(*node))->data = (void *)data;
			((AvlNode*)BiTree_Data(*node))->hidden = 0;

			/* ��ƽ��δ���ƻ� */
			*balanced = 1;
		}
	}
	return OK;
}

static int Hide(BisTree *tree, BiTreeNode *node, const void *data)
{
	int cmpval = 0, result = 0;

	if (BiTree_Is_Endob(node))
		return ERR;

	cmpval = tree->compare(data, ((AvlNode*)BiTree_Data(node))->data);
	if (cmpval < 0)
	{
		result = Hide(tree, BiTree_Left(node), data);
	}
	else if (cmpval > 0)
	{
		result = Hide(tree, BiTree_Right(node), data);
	}
	else
	{
		((AvlNode*)BiTree_Data(node))->hidden = 1;
		result = OK;
	}
	return result;
}

static int Lookup(BisTree *tree, BiTreeNode *node, void **data)
{
	int cmpval = 0, result = 0;

	if (BiTree_Is_Endob(node))
		return ERR;

	cmpval = tree->compare(*data, ((AvlNode*)BiTree_Data(node))->data);
	if (cmpval < 0)
	{
		result = Lookup(tree, BiTree_Left(node), data);
	}
	else if (cmpval > 0)
	{
		result = Lookup(tree, BiTree_Right(node), data);
	}
	else
	{
		/* hiddenΪ�����صĽڵ�*/
		if (!((AvlNode*)BiTree_Data(node))->hidden)
		{
			*data = ((AvlNode*)BiTree_Data(node))->data;
			result = OK;
		}
		else
		{
			return ERR;
		}
	}
	return result;
}

void Bistree_Init(BisTree *tree, int(*compare)(const void *key1, const void *key2), void(*destroy)(void *data))
{
	BiTree_Init(tree, destroy);
	tree->compare = compare;
	return;
}

void BisTree_Destroy(BisTree *tree)
{
	Destroy_Left(tree, NULL);
	memset(tree, 0, sizeof(BisTree));
	return;
}

int BisTree_Insert(BisTree *tree, const void *data)
{
	int balanced = 0;
	return Insert(tree, &BiTree_Root(tree), data, &balanced);
}

int BisTree_Remove(BisTree *tree, const void *data)
{
	return Hide(tree, BiTree_Root(tree), data);
}

int BisTree_Lookup(BisTree *tree, void **data)
{
	return Hide(tree, BiTree_Root(tree), data);
}
