#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 定义单链表节点结构
typedef struct Node
{
    int data;
    struct Node *next;
} Node;
// 创建新节点
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// 反转链表（原地反转）
Node *reverseList(Node *head)
{
    Node *prev = NULL, *curr = head, *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
// 判断是否为回文链表
bool isPalindrome(Node *head)
{
    if (head == NULL || head->next == NULL)
        return true;
    // 1️⃣ 找中点（快慢指针）
    Node *slow = head, *fast = head;
    while (fast->next != NULL && fast->next->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    // 2️⃣ 反转后半部分
    Node *secondHalf = reverseList(slow->next);
    // 3️⃣ 比较前半部分和反转后的后半部分
    Node *p1 = head, *p2 = secondHalf;
    bool palindrome = true;
    while (p2 != NULL)
    {
        if (p1->data != p2->data)
        {
            palindrome = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    // 4️⃣ （可选）恢复链表
    slow->next = reverseList(secondHalf);
    return palindrome;
}
// 打印链表
void printList(Node *head)
{
    for (Node *p = head; p != NULL; p = p->next)
    {
        printf("%d ", p->data);
    }
    printf("\n");
}
// 主函数
int main()
{
    int n, val;
    printf("请输入链表长度: ");
    scanf("%d", &n);
    Node *head = NULL, *tail = NULL;
    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        Node *newNode = createNode(val);
        if (head == NULL)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    printf("链表为: ");
    printList(head);
    if (isPalindrome(head))
        printf("该链表是回文结构。\n");
    else
        printf("该链表不是回文结构。\n");
    return 0;
}
