#include <stdio.h>
// 交换两个元素
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// 反转数组 A[left..right]
void reverse(int A[], int left, int right)
{
    while (left < right)
    {
        swap(&A[left], &A[right]);
        left++;
        right--;
    }
}
// 循环左移 k 位
void leftRotate(int A[], int n, int k)
{
    if (n == 0)
        return;
    k = k % n; // 防止 k > n
    if (k == 0)
        return;
    reverse(A, 0, k - 1); // ① 反转前 k 个元素
    reverse(A, k, n - 1); // ② 反转后 n-k 个元素
    reverse(A, 0, n - 1); // ③ 反转整个数组
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
