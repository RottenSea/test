#include <stdio.h>
#include <stdlib.h>

/* 单链表结点定义 */
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

/* 创建链表 */
Node *CreateList(int n)
{
    Node *head = NULL, *p, *tail = NULL;
    int x;

    printf("请输入%d个整数：\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        p = (Node *)malloc(sizeof(Node));
        p->data = x;
        p->next = NULL;

        if (head == NULL)
        {
            head = p;
            tail = p;
        }
        else
        {
            tail->next = p;
            tail = p;
        }
    }
    return head;
}

/* 直接插入排序（单链表） */
Node *InsertSort(Node *head)
{
    Node *sorted = NULL; // 已排序链表
    Node *cur = head;

    while (cur != NULL)
    {
        Node *next = cur->next;

        if (sorted == NULL || cur->data < sorted->data)
        {
            cur->next = sorted;
            sorted = cur;
        }
        else
        {
            Node *p = sorted;
            while (p->next != NULL && p->next->data < cur->data)
            {
                p = p->next;
            }
            cur->next = p->next;
            p->next = cur;
        }

        cur = next;
    }
    return sorted;
}

/* 输出链表 */
void PrintList(Node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    Node *head;

    head = CreateList(10);

    printf("排序前：");
    PrintList(head);

    head = InsertSort(head);

    printf("排序后：");
    PrintList(head);

    return 0;
}
