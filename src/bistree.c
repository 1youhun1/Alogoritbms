/*bistree.c 二叉搜索树（AVL树）*/
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "bistree.h"

static void Destroy_Right(BisTree *tree, BiTreeNode *node);


static void Rotate_Left(BiTreeNode **node)
{
	BiTreeNode * left = NULL, *grandchile = NULL;
	left = BiTree_Left(*node);

	/*平衡二叉树某一节点的左孩子的左子树上插入一个新的节点，使得该节点不再平衡,
		这时只需要把树向右旋转一次即可*/
	if (AVL_LFT_HEAVY == ((AvlNode *)BiTree_Data(left))->factor)
	{
		/* 进行 LL旋转 */
		BiTree_Left(*node) = BiTree_Right(left);
		BiTree_Right(left) = *node;
		((AvlNode *)BiTree_Data(*node))->factor = AVL_BALANCED;
		((AvlNode *)BiTree_Data(left))->factor = AVL_BALANCED;
		*node = left;
	}
	/*平衡二叉树某一节点的左孩子的右子树上插入一个新的节点，使得该节点不再平衡,
		这时需要旋转两次，仅一次的向左旋转是不能够使二叉树再次平衡,
		这时还需要再向右旋转一次。*/
	else
	{
		/* 进行 LR旋转 */
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

	/*平衡二叉树某一节点的右孩子的右子树上插入一个新的节点，使得该节点不再平衡,
		这时只需要把树向左旋转一次即可，*/
	if (AVL_RGT_HEAVY == ((AvlNode *)BiTree_Data(right))->factor)
	{
		/* 进行 RR旋转 */
		BiTree_Right(*node) = BiTree_Left(right);
		BiTree_Left(right) = *node;
		((AvlNode *)BiTree_Data(*node))->factor = AVL_BALANCED;
		((AvlNode *)BiTree_Data(right))->factor = AVL_BALANCED;
		*node = right;
	}
	/*平衡二叉树某一节点的右孩子的左子树上插入一个新的节点，使得该节点不再平衡,
		这时需要旋转两次，先向右旋转一次后再向左旋转一次*/
	else
	{
		/* 进行 RL旋转 */
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

/*递归调用，删除左子树*/
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

/*递归调用，删除右子树*/
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

	//尾节点则直接插入左子树
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
		/*递归调用插入左子树*/
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
			/*平衡调整*/
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
			/*递归调用插入右子树*/
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
			/*平衡调整*/
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
		//查询到相同节点，则替换
		else
		{
			if (tree->destroy != NULL)
			{
				/*删除上次隐藏的数据 */
				tree->destroy(((AvlNode*)BiTree_Data(*node))->data);
			}
			((AvlNode*)BiTree_Data(*node))->data = (void *)data;
			((AvlNode*)BiTree_Data(*node))->hidden = 0;

			/* 树平衡未被破坏 */
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
		/* hidden为不隐藏的节点*/
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
