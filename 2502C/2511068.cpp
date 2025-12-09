#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define DataType char

typedef struct tnode
{
    DataType data;                 /*定义数据域*/
    struct tnode *lchild, *rchild; /*定义左、右孩子指针域*/
} BT;

BT *CreateBTree()
{ /*以先序序列输入结点的值，创建二叉链表*/
    printf("请输入中结点：");
    BT *t;
    char ch;
    scanf("%c", &ch);
    getchar();     /*用于接收每次输入字符后的回车符*/
    if (ch == '0') /*读入0时，将相应结点置空*/
        t = NULL;
    else
    {
        t = (BT *)malloc(sizeof(BT)); /*新建结点*/
        t->data = ch;
        printf("请输入%c结点的左孩子结点：", t->data);
        t->lchild = CreateBTree();
        printf("请输入%c结点的右孩子结点：", t->data);
        t->rchild = CreateBTree();
    }
    return t;
}

void ShowBTree(BT *T)
{                  /*用广义表表示法显示二叉树子函数*/
    if (T != NULL) /*当二叉树非空时*/
    {
        printf("%c", T->data); /*输入该结点数据域*/
        if (T->lchild != NULL) /*若其左子树非空*/
        {
            printf("(");           /*输出左括号*/
            ShowBTree(T->lchild);  /*递归调用该函数输出其左子树各结点*/
            if (T->rchild != NULL) /*若其右子树非空*/
            {
                printf(",");          /*输出逗号*/
                ShowBTree(T->rchild); /*递归调用该函数输出其右子树各结点*/
            }
            printf(")");
        }
        else if (T->rchild != NULL) /*若其左子树为空，右子树不为空*/
        {
            printf("(");           /*输出左括号*/
            ShowBTree(T->lchild);  /*递归调用该函数输出其左子树各结点*/
            if (T->rchild != NULL) /*若其右子树非空*/
            {
                printf(",");          /*输出逗号*/
                ShowBTree(T->rchild); /*递归调用该函数输出其右子树各结点*/
            }
            printf(")");
        }
    }
}

void PreOrder(BT *T)
{
    if (T == NULL)
        return;
    else
    {
        printf("%c", T->data); /*输出结点的数据域*/
        PreOrder(T->lchild);   /*先序递归遍历左子树*/
        PreOrder(T->rchild);   /*先序递归遍历右子树*/
    }
}

void InOrder(BT *T)
{
    if (T == NULL)
        return;
    else
    {
        InOrder(T->lchild);    /*中序递归遍历左子树*/
        printf("%c", T->data); /*输出结点的数据域*/
        InOrder(T->rchild);    /*先序递归遍历右子树*/
    }
}

void PostOrder(BT *T)
{
    if (T == NULL)
        return;
    else
    {
        PostOrder(T->lchild);  /*后序递归遍历左子树*/
        PostOrder(T->rchild);  /*后序递归遍历右子树*/
        printf("%c", T->data); /*输出结点的数据域*/
    }
}

void LevelOrder(BT *T)
{
    int f, r;       /*定义队头队尾指针*/
    BT *p, *q[MAX]; /*定义循环队列，存放结点指针*/
    p = T;
    if (p != NULL)
    { /*若二叉树非空，则根结点地址入队*/
        f = 1;
        q[f] = p;
        r = 2;
    }
    while (f != r)
    { /*队列不空时*/
        p = q[f];
        printf("%c", p->data); /*访问队首结点的数据域*/
        if (p->lchild != NULL) /*将队首结点的左孩子入队*/
        {
            q[r] = p->lchild;
            r = (r + 1) % MAX;
        }
        if (p->rchild != NULL) /*将队首结点的右孩子入队*/
        {
            q[r] = p->rchild;
            r = (r + 1) % MAX;
        }
        f = (f + 1) % MAX;
    }
}

int main()
{
    BT *T = CreateBTree();
    printf("preorder : ");
    PreOrder(T);
    printf("\n");
    printf("inorder : ");
    InOrder(T);
    printf("\n");
    printf("postorder : ");
    PostOrder(T);
    printf("\n");
    printf("LevelOrder : ");
    LevelOrder(T);
    printf("\n");
    return 0;
}
