#include <stdio.h>

// 2.输入一个数n，打印一个2n-1行的菱形。

void printBlank(int n, int a)
{
    for (int i = 0; i < n - a; i++)
    {
        printf(" ");
    }
}

void printShape(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("##");
    }
    printf("\n");
}

void printAll(int n)
{
    int col = 1;
    for (int i = 1; i < n; i++)
    {
        printf("%4d  ", col);
        printBlank(n, i);
        printShape(i);
        col += 1;
    }
    for (int i = n; i >= 1; i--)
    {
        printf("%4d  ", col);
        printBlank(n, i);
        printShape(i);
        col += 1;
    }
}

int main()
{
    int n;
    printf("Enter n : ");
    scanf("%d", &n);
    printAll(n);
    return 0;
}