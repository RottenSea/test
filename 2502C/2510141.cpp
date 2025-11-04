#include <stdio.h>
#include <stdlib.h>

typedef int Datatype;
typedef struct qnode
{
    Datatype data;
    struct qnode *next;
} LinkListQ;
typedef struct
{
    LinkListQ *front;
    LinkListQ *rear;
} LinkQueue;

LinkQueue *InitQueue()
{
    LinkQueue *Q;
    LinkListQ *p;
    Q = (LinkQueue *)malloc(sizeof(LinkQueue));
    p = (LinkListQ *)malloc(sizeof(LinkListQ));
    Q->front = p;
    Q->rear = p;
    return Q;
}

int EmptyQueue(LinkQueue *Q)
{
    if (Q->front == Q->rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void InQueue(LinkQueue *Q, Datatype x)
{
    LinkListQ *p;
    p = (LinkListQ *)malloc(sizeof(LinkListQ));
    p->data = x;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

int DeQueue(LinkQueue *Q, Datatype *x)
{
    LinkListQ *p;
    if (EmptyQueue(Q))
    {
        printf("Queue Empty!");
        return 0;
    }
    else
    {
        p = Q->front->next;
        *x = p->data;
        Q->front->next = p->next;
        if (p->next == NULL)
            Q->rear = Q->front;
        free(p);
        return 1;
    }
}

int GetFront(LinkQueue *Q, Datatype *x)
{
    if (EmptyQueue(Q))
    {
        printf("Queue Empty, no head element!");
        return 0;
    }
    else
    {
        *x = Q->front->next->data;
        return 1;
    }
}

void ShowQueue(LinkQueue *Q)
{
    if (EmptyQueue(Q))
    {
        printf("Queue Empty, no head element!");
        return;
    }
    else
    {
        int count = 0;
        LinkListQ *P = Q->front->next;
        while (P != NULL)
        {
            count++;
            printf("%5d %d\n", count, P->data);
            P = P->next;
        }
    }
}

int main()
{
    LinkQueue *Q;
    Q = InitQueue();
    Datatype x, y = 0;
    printf("input InQueue num : ");
    scanf("%d", &x);

    for (int i = 0; i < x; i++)
    {
        printf("input InQueue x (%d) : ", i + 1);
        scanf("%d", &y);
        InQueue(Q, y);
    }
    printf("InQueued\n");

    printf("GetFront\n");
    GetFront(Q, &x);
    printf("GetFront data : %d\n", x);

    printf("ShowQueue\n");
    ShowQueue(Q);

    DeQueue(Q, &x);
    printf("DeQueued\n");
    printf("DeQueue data : %d\n", x);

    printf("GetFront\n");
    GetFront(Q, &x);
    printf("GetFront data : %d\n", x);

    return 0;
}
