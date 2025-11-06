#include <stdio.h>
#include <limits.h>

struct IntegerArray
{
    int a[101];
    int num;
};

void InputNumberToArray(IntegerArray *array)
{
    int n = 0;
    int num;
    printf("Input number of numbers (max 100) : ");
    scanf("%d", &n);
    if (0 > n > 100)
    {
        printf("Invalid input , set to 10.");
        n = 10;
    }
    for (int i = array->num; i < n; i++)
    {
        printf("Input number : ");
        scanf("%d", &num);
        array->a[i] = num;
        array->num++;
    }
}

int SearchMaxInArray(IntegerArray *array)
{
    int max = INT_MIN;
    int index;
    for (int i = 0; i < array->num; i++)
    {
        if (array->a[i] > max)
        {
            max = array->a[i];
            index = i;
        }
    }
    return index;
}

int main()
{
    IntegerArray array;
    array.num = 0;

    InputNumberToArray(&array);
    int index = SearchMaxInArray(&array);
    printf("index of max number in array : %d\n", index);
    printf("max number of array : %d\n", array.a[index]);
    return 0;
}