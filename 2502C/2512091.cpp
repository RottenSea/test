#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct bnode
{
    DataType data;
    struct bnode *lchild, *rchild;
} Bnode, *BTree;

/* 队列元素结构：保存结点及层号 */
typedef struct
{
    BTree node;
    int level;
} Elem;

/* 简单顺序队列 */
typedef struct
{
    Elem data[100];
    int front, rear;
} Queue;

void InitQueue(Queue *q)
{
    q->front = q->rear = 0;
}
int Empty(Queue *q)
{
    return q->front == q->rear;
}
void EnQueue(Queue *q, Elem x)
{
    q->data[q->rear++] = x;
}
Elem DeQueue(Queue *q)
{
    return q->data[q->front++];
}

/* 层序遍历 */
void LevelOrder(BTree root)
{
    if (!root)
        return;

    Queue q;
    InitQueue(&q);

    Elem e = {root, 1};
    EnQueue(&q, e);

    while (!Empty(&q))
    {
        Elem cur = DeQueue(&q);
        printf("%c (%d) ", cur.node->data, cur.level);

        if (cur.node->lchild)
        {
            Elem t = {cur.node->lchild, cur.level + 1};
            EnQueue(&q, t);
        }
        if (cur.node->rchild)
        {
            Elem t = {cur.node->rchild, cur.level + 1};
            EnQueue(&q, t);
        }
    }
}

/* 构造示例二叉树：
        A
       / \
      B   C
     / \   \
    D   E   F
*/
BTree CreateExampleTree()
{
    BTree A = (BTree)malloc(sizeof(Bnode));
    BTree B = (BTree)malloc(sizeof(Bnode));
    BTree C = (BTree)malloc(sizeof(Bnode));
    BTree D = (BTree)malloc(sizeof(Bnode));
    BTree E = (BTree)malloc(sizeof(Bnode));
    BTree F = (BTree)malloc(sizeof(Bnode));

    A->data = 'A';
    B->data = 'B';
    C->data = 'C';
    D->data = 'D';
    E->data = 'E';
    F->data = 'F';

    A->lchild = B;
    A->rchild = C;
    B->lchild = D;
    B->rchild = E;
    C->lchild = NULL;
    C->rchild = F;

    D->lchild = D->rchild = NULL;
    E->lchild = E->rchild = NULL;
    F->lchild = F->rchild = NULL;

    return A;
}

int main()
{
    BTree root = CreateExampleTree();
    printf("层序遍历输出：\n");
    LevelOrder(root);
    printf("\n");
    return 0;
}
