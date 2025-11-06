#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

struct IntergerArray
{
    int data;
    struct IntergerArray *next;
};

void SetListNumber(IntergerArray *L);
void PushNumberToList(IntergerArray *L, int n);
char *CastToString(IntergerArray *L)
{
    static char str[30] = {};
    char temp[3];
    IntergerArray *p = L;
    while (p->next != NULL)
    {
        sprintf(temp, "%d", p->data);
        strcat(str, temp);
        p = p->next;
    }
    sprintf(temp, "%d", p->data);
    strcat(str, temp);
    return str;
}

int main()
{
    IntergerArray L;
    SetListNumber(&L);
    char str[30] = {};
    strcpy(str, CastToString(&L));

    bool flag = true;
    for (int i = 0; i < (strlen(str) / 2); i++)
    {
        if (str[i] != str[strlen(str) - 1 - i])
        {
            flag = false;
        }
    }

    switch (flag)
    {
    case true:
        printf("The list is a palindrome.\n");
        break;
    case false:
        printf("The list is not a palindrome.\n");
        break;
    }

    return 0;
}

void SetListNumber(IntergerArray *L)
{
    int n;
    printf("Input the number for the list (the number should be greater than 10): ");
    scanf("%d", &n);
    if (n <= 10)
    {
        printf("The number is too small, set to 12321\n");
        n = 12321;
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
