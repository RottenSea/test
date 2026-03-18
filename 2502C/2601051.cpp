#include <stdio.h>
#include <stdlib.h>

/* 二叉排序树结点定义 */
typedef struct BSTNode
{
    int data;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
} BSTNode;

/* 插入结点 */
BSTNode *InsertBST(BSTNode *root, int key)
{
    if (root == NULL)
    {
        root = (BSTNode *)malloc(sizeof(BSTNode));
        root->data = key;
        root->lchild = NULL;
        root->rchild = NULL;
        return root;
    }

    if (key < root->data)
        root->lchild = InsertBST(root->lchild, key);
    else
        root->rchild = InsertBST(root->rchild, key);

    return root;
}

/* 前序遍历 */
void PreOrder(BSTNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        PreOrder(root->lchild);
        PreOrder(root->rchild);
    }
}

/* 中序遍历 */
void InOrder(BSTNode *root)
{
    if (root != NULL)
    {
        InOrder(root->lchild);
        printf("%d ", root->data);
        InOrder(root->rchild);
    }
}

/* 后序遍历 */
void PostOrder(BSTNode *root)
{
    if (root != NULL)
    {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        printf("%d ", root->data);
    }
}

int main()
{
    BSTNode *root = NULL;
    int i, x;

    printf("请输入10个整数：\n");
    for (i = 0; i < 10; i++)
    {
        scanf("%d", &x);
        root = InsertBST(root, x);
    }

    printf("前序遍历结果：");
    PreOrder(root);
    printf("\n");

    printf("中序遍历结果：");
    InOrder(root);
    printf("\n");

    printf("后序遍历结果：");
    PostOrder(root);
    printf("\n");

    return 0;
}
