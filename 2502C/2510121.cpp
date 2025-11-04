#include <stdio.h>

#define MAXSIZE 100   /*顺序队列存储空间的总分配量*/
typedef int DataType; /*定义DataType为int类型*/
typedef struct        /*顺序栈存储类型*/
{
    DataType data[MAXSIZE]; /*存放顺序队列的数组*/
    int front;              /*记录队头元素位置的变量*/
    int rear;               /*记录队尾元素位置的变量*/
} SeqQueue;

void InitQueue(SeqQueue *Q)
{
    /*初始化队列*/
    Q->front = Q->rear = 0; /*指针初始化*/
}

int EmptyQueue(SeqQueue *Q)
{
    /*判断队列空函数*/
    if (Q->front == Q->rear) /*队列为空*/
        return 1;
    else
        return 0;
}

int InQueue(SeqQueue *Q, DataType x)
{
    /*入队*/
    if ((Q->rear + 1) % MAXSIZE == Q->front) /*队列为满*/
    {
        printf("队列满，不能入队！");
        return 0;
    }
    else
    {
        Q->rear = (Q->rear + 1) % MAXSIZE; /*队尾指针增1*/
        Q->data[Q->rear] = x;
        return 1;
    }
}

int DeQueue(SeqQueue *Q, DataType *x)
{
    /*出队*/
    if (EmptyQueue(Q)) /*判断队列是否空*/
    {
        printf("队列空，不能出队！");
        return 0;
    }
    else
    {
        Q->front = (Q->front + 1) % MAXSIZE; /*队头指针增1*/
        *x = Q->data[Q->front];              /*队头元素赋给指针x所指变量*/
        return 1;
    }
}

int GetFront(SeqQueue *Q, DataType *x)
{
    /*取队头元素*/
    if (EmptyQueue(Q)) /*判断队列是否空*/
    {
        printf("队列空，无队头元素！");
        return 0;
    }
    else
    {
        *x = Q->data[(Q->front + 1) % MAXSIZE];
        return 1;
    }
}

void ShowQueue(SeqQueue *Q)
{
    /*显示队列元素*/
    int p = Q->front;
    if (p == Q->rear)
        printf("队列空，无元素！");
    else
    {
        printf("Elements : ");
        while (p != Q->rear)
        {
            printf("% 5d", Q->data[p + 1]);
            p++;
        }
    }
}

int main()
{
    SeqQueue Q;
    int i, x, y;
    printf("input int number : ");
    scanf("%d", &x);
    InitQueue(&Q);
    for (i = 0; i < x; i++)
    {
        printf("input int : ");
        scanf("%d", &y);
        InQueue(&Q, y);
    }
    ShowQueue(&Q);
    printf("\nDeQueue\n");
    DeQueue(&Q, &y);
    printf("DeQueue element : %d\n", y);
    ShowQueue(&Q);
}