/* bitree.c ������*/
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "bitree.h"

void BiTree_Init(BiTree *tree, void (*destroy)(void *data))
{
    tree->size = 0;
    tree->destroy = destroy;
    tree->root = NULL;
    
    return;
}

void BiTree_Destroy(BiTree *tree)
{
    BiTree_Rem_Left(tree, NULL);
    memset(tree, 0 ,sizeof(BiTree));

    return;
}

int BiTree_Ins_Left(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *new_node = NULL, **position = NULL;

    /* ��ȷ�ϲ���ڵ��λ�ã�λ�õ�ַ�����positionָ����*/
    if (NULL == node)
    {
        if (BiTree_Size(tree) > 0)
            return ERR;
        position = &tree->root;
    } 
    else
    {
        if (BiTree_Left(node) != NULL)
            return ERR;
        position = &node->left;
    }

    if (NULL == (new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))))
        return ERR;

    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return OK;
}

int BiTree_Ins_Right(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *new_node = NULL, **position = NULL;

    /* ��ȷ�ϲ���ڵ��λ�� */
    if (NULL == node)
    {
        if (BiTree_Size(tree) > 0)
            return ERR;
        position = &tree->root;
    } 
    else
    {
        if (BiTree_Right(node) != NULL)
            return ERR;
        position = &node->right;
    }

    if (NULL == (new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))))
        return ERR;

    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return OK;
}

void BiTree_Rem_Left(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode **position = NULL;

    if (0 == BiTree_Size(tree))
        return;

    //��ȡɾ���ڵ��λ��
    if (NULL == node)
        position = &tree->root; 
    else
        position = &node->left;

    if (*position != NULL)
    {
        BiTree_Rem_Left(tree, *position);
        BiTree_Rem_Right(tree, *position);

        if (tree->destroy != NULL)
        {
            //���ú����ͷ�����
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;

        tree->size--;
    }
    return;
}

void BiTree_Rem_Right(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode **position = NULL;

    if (0 == BiTree_Size(tree))
        return;

    //��ȡɾ���ڵ��λ��
    if (NULL == node)
        position = &tree->root; 
    else
        position = &node->right;

    if (*position != NULL)
    {
        BiTree_Rem_Left(tree, *position);
        BiTree_Rem_Right(tree, *position);

        if (tree->destroy != NULL)
        {
            //���ú����ͷ�����
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;

        tree->size--;
    }
    return;
}

//�ϲ����ö�����
int BiTree_Merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
    BiTree_Init(merge, left->destroy); //��ʼ���ϲ������

    //����root�ڵ�
    if (BiTree_Ins_Left(merge, NULL, data) != 0)
    {
        BiTree_Destroy(merge);
        return ERR;
    }

    BiTree_Root(merge)->left = BiTree_Root(left);
    BiTree_Root(merge)->right = BiTree_Root(right);

    merge->size = merge->size + BiTree_Size(left) +BiTree_Size(right);

    //���ԭ�����Ľڵ��ϵ
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;

    return OK;
}