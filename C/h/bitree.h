/* bitree */
#ifndef BITREE_H
#define BITREE_H
#include <stdlib.h>

typedef struct BiTreeNode_
{
    void *data;
    struct BiTreeNode_ *left;	//左子结点
    struct BiTreeNode_ *right;  //右子结点
}BiTreeNode;

typedef struct BiTree_
{
    int  size;
    int  (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    BiTreeNode *root;   //根结点
}BiTree;

void BiTree_Init(BiTree *tree, void (*destroy)(void *data));
void BiTree_Destroy(BiTree *tree);
int BiTree_Ins_Left(BiTree *tree, BiTreeNode *node, const void *data);
int BiTree_Ins_Right(BiTree *tree, BiTreeNode *node, const void *data);
void BiTree_Rem_Left(BiTree *tree, BiTreeNode *node);
void BiTree_Rem_Right(BiTree *tree, BiTreeNode *node);
int BiTree_Merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);

#define BiTree_Size(tree) ((tree)->size)
#define BiTree_Root(tree) ((tree)->root)
#define BiTree_Is_Endob(node) (NULL == (node)) //是否为分支结束
#define BiTree_Is_Leaf(node) (NULL == (node)->left && NULL == (node)->right)
#define BiTree_Data(node) ((node)->data)
#define BiTree_Left(node) ((node)->left)
#define BiTree_Right(node) ((node)->right)

#endif