#include <stdio.h>
int main()
{
    int n;
    printf("请输入数组长度: ");
    scanf("%d", &n);
    int A[n];
    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
    int max = A[0];
    int pos = 0;
    for (int i = 1; i < n; i++)
    {
        if (A[i] > max)
        {
            max = A[i];
            pos = i;
        }
    }
    printf("最大值为: %d\n", max);
    printf("第一次出现的位置(下标): %d\n", pos);
    return 0;
}
