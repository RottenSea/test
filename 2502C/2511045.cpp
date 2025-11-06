#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int value;
    struct ListNode *next;
};

ListNode *InitList()
{
    ListNode *L = (ListNode *)malloc(sizeof(ListNode));
    L->next = NULL;
    return L;
}

void CreateList(ListNode *L)
{
    int val;
    int n = 0;
    ListNode *p = L;
    printf("Input value for the list (single number | negative number to finish) : ");
    scanf("%d", &val);
    if (val >= 0)
    {
        L->value = val;
        n++;
    }

    do
    {
        printf("Input value for the list (single number | negative number to finish) : ");
        scanf("%d", &val);
        if (val < 0)
        {
            break;
        }
        ListNode *newnode = (ListNode *)malloc(sizeof(ListNode));
        newnode->value = val;
        newnode->next = NULL;
        p->next = newnode;
        p = p->next;
        n++;
    } while (1);

    if (n < 3)
    {
        printf("The list should contain no less than 3 nodes!(%d node(s) contain)", n);
    }
}

struct ListNode *reverseList(struct ListNode *L)
{
    struct ListNode *prev = NULL;
    struct ListNode *curr = L;
    while (curr)
    {
        struct ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

bool isPalindrome(struct ListNode *L)
{
    struct ListNode *slow = L;
    struct ListNode *fast = L;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast != NULL)
    {
        slow = slow->next;
    }

    struct ListNode *secondHalf = reverseList(slow);
    struct ListNode *secondHalfCopy = secondHalf;
    struct ListNode *firstHalf = L;

    bool result = true;
    while (secondHalf != NULL)
    {
        if (firstHalf->value != secondHalf->value)
        {
            result = false;
            break;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    reverseList(secondHalfCopy);

    return result;
}

int main()
{
    ListNode *L = InitList();
    CreateList(L);

    if (isPalindrome(L))
    {
        printf("The list is a palindrome.\n");
    }
    else
    {
        printf("The list is not a palindrome.\n");
    }
}