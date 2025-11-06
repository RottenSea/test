#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int data[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q)
{
    q->front = q->rear = 0;
}

int isEmpty(Queue *q)
{
    return q->front == q->rear;
}

void enqueue(Queue *q, int x)
{
    q->data[q->rear++] = x;
}

int dequeue(Queue *q)
{
    return q->data[q->front++];
}

void printYangHui(int n)
{
    Queue q;
    initQueue(&q);

    enqueue(&q, 1);

    for (int i = 1; i <= n; i++)
    {

        int spaces = n - i;
        for (int k = 0; k < spaces; k++)
            printf(" ");

        Queue next;
        initQueue(&next);

        int prev = 0;
        int len = i;

        for (int j = 0; j < len; j++)
        {
            int curr = dequeue(&q);
            printf("%d ", curr);

            int sum = prev + curr;
            if (sum != 0)
                enqueue(&next, sum);

            prev = curr;
        }
        printf("\n");

        enqueue(&next, 1);

        q = next;
    }
}

int main()
{
    int n;
    printf("Please input output lines n : ");
    scanf("%d", &n);

    if (n < 1)
    {
        printf("Lines requires greatter than 1.\n");
        return 0;
    }

    printYangHui(n);
    return 0;
}
