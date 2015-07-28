/* cbistree.cpp 搜索二叉树*/

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

	/*平衡二叉树某一节点的左孩子的左子树上插入一个新的节点，使得该节点不再平衡,
	这时只需要把树向右旋转一次即可*/
	if (AVL_LFT_HEAVY == ((AvlNode *)BiTreeData(left))->factor)
	{
		/* 进行 LL旋转 */
		(*node)->left = BiTreeRight(left);
		left->right = *node;
		((AvlNode *)BiTreeData(*node))->factor = AVL_BALANCED;
		((AvlNode *)BiTreeData(left))->factor = AVL_BALANCED;
		*node = left;
	}
	/*平衡二叉树某一节点的左孩子的右子树上插入一个新的节点，使得该节点不再平衡,
	这时需要旋转两次，仅一次的向左旋转是不能够使二叉树再次平衡,
	这时还需要再向右旋转一次。*/
	else
	{
		/* 进行 LR旋转 */
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

	/*平衡二叉树某一节点的右孩子的右子树上插入一个新的节点，使得该节点不再平衡,
	这时只需要把树向左旋转一次即可，*/
	if (AVL_RGT_HEAVY == ((AvlNode *)BiTreeData(right))->factor)
	{
		/* 进行 RR旋转 */
		(*node)->right = BiTreeLeft(right);
		right->left = *node;
		((AvlNode *)BiTreeData(*node))->factor = AVL_BALANCED;
		((AvlNode *)BiTreeData(right))->factor = AVL_BALANCED;
		*node = right;
	}
	/*平衡二叉树某一节点的右孩子的左子树上插入一个新的节点，使得该节点不再平衡,
	这时需要旋转两次，先向右旋转一次后再向左旋转一次*/
	else
	{
		/* 进行 RL旋转 */
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

/*递归调用，删除左子树*/
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

/*递归调用，删除右子树*/
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

	//尾节点则直接插入左子树
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
		/*递归调用插入左子树*/
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
			/*平衡调整*/
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
			/*递归调用插入右子树*/
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
			/*平衡调整*/
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
		//查询到相同节点，则替换
		else
		{
			if (destroy != NULL)
			{
				/*删除上次隐藏的数据 */
				destroy(((AvlNode*)BiTreeData(*node))->data);
			}
			((AvlNode*)BiTreeData(*node))->data = (void *)data;
			((AvlNode*)BiTreeData(*node))->hidden = 0;

			/* 树平衡未被破坏 */
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
		/* hidden为不隐藏的节点*/
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
