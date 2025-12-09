#include <stdio.h>
void leftRotate(int A[], int n, int k)
{
    int B[n];  // 辅助数组
    k = k % n; // 防止 k > n
    if (k == 0)
        return;
    // 将元素左移 k 位
    for (int i = 0; i < n; i++)
    {
        B[i] = A[(i + k) % n];
    }
    // 将结果复制回原数组
    for (int i = 0; i < n; i++)
    {
        A[i] = B[i];
    }
}
int main()
{
    int n, k;
    printf("请输入数组长度 n: ");
    scanf("%d", &n);
    int A[n];
    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
    printf("请输入左移位数 k: ");
    scanf("%d", &k);
    leftRotate(A, n, k);
    printf("左移 %d 位后的结果: ", k);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
