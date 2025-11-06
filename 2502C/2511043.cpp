#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct IntergerArray
{
    int data;
    int index;
    struct IntergerArray *next;
};

void SetListNumber(IntergerArray *L);

void PushNumberToList(IntergerArray *L, int n);

int CalculateListNumber(IntergerArray *L);

void PrintListNumber(IntergerArray *L);

IntergerArray AddTwoListNumbers(IntergerArray *L1, IntergerArray *L2);

int main()
{
    IntergerArray L1;
    L1.index = 0;
    L1.next = NULL;
    IntergerArray L2;
    L2.index = 0;
    L2.next = NULL;

    SetListNumber(&L1);
    printf("Number in List1 : ");
    PrintListNumber(&L1);

    SetListNumber(&L2);
    printf("Number in List2 : ");
    PrintListNumber(&L2);

    IntergerArray L3;

    L3 = AddTwoListNumbers(&L1, &L2);
    printf("Added numbers of two lists : ");
    PrintListNumber(&L3);

    return 0;
}

void SetListNumber(IntergerArray *L)
{
    int n;
    printf("Input the number for the list (the number should be greater than 10): ");
    scanf("%d", &n);
    if (n <= 10)
    {
        printf("The number is too small, set to 123\n");
        n = 123;
    }
    PushNumberToList(L, n);
}

void PushNumberToList(IntergerArray *L, int n)
{
    int temp;
    IntergerArray *p = L;
    while (n > 0)
    {
        temp = n % 10;
        if (n >= 10)
        {
            p->data = temp;
            p->next = (IntergerArray *)malloc(sizeof(IntergerArray));
            p->next->index = p->index + 1;
            p = p->next;
        }
        else
        {
            p->data = temp;
            p->next = NULL;
        }
        n = n / 10;
    }
}

int CalculateListNumber(IntergerArray *L)
{
    int result = 0;

    IntergerArray *p = L;
    while (p->next != NULL)
    {
        result += p->data * pow(10, p->index);
        p = p->next;
    }
    result += p->data * pow(10, p->index);
    return result;
}

void PrintListNumber(IntergerArray *L)
{
    IntergerArray *p = L;

    while (p->next != NULL)
    {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("%d\n", p->data);
}

IntergerArray AddTwoListNumbers(IntergerArray *L1, IntergerArray *L2)
{
    IntergerArray result;
    result.index = 0;
    result.next = NULL;

    int n = CalculateListNumber(L1) + CalculateListNumber(L2);
    PushNumberToList(&result, n);
    return result;
}