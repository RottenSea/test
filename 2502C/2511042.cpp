#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct IntegerArray
{
    int data;
    struct IntegerArray *next;
};

void InputNumberToArray(IntegerArray *array)
{
    int n = 0;
    int num;
    IntegerArray *p = array;

    printf("Input number of numbers (max 100) : ");
    scanf("%d", &n);
    if (n <= 0 || n > 100)
    {
        printf("Invalid input , set to 10.");
        n = 10;
    }

    for (int i = 0; i < n; i++)
    {
        printf("Input number : \n");
        scanf("%d", &num);
        p->data = num;
        if (i != n - 1)
        {
            p->next = (IntegerArray *)malloc(sizeof(IntegerArray));
            p = p->next;
        }
        else
        {
            p->next = NULL;
        }
    }
}

int SearchMaxInArray(IntegerArray *array, int *max)
{
    int maxindex;
    int index = 0;
    IntegerArray *p = array;
    do
    {
        if (p->data > *max)
        {
            *max = p->data;
            maxindex = index;
        }
        index += 1;
        p = p->next;
    } while (p->next != NULL);
    if (p->data > *max)
    {
        *max = p->data;
        maxindex = index;
    }
    return maxindex;
}

int main()
{
    IntegerArray array;
    array.next = NULL;
    int max = INT_MIN;

    InputNumberToArray(&array);
    int index = SearchMaxInArray(&array, &max);
    printf("index of max number in array : %d\n", index);
    printf("max number of array : %d\n", max);
    return 0;
}