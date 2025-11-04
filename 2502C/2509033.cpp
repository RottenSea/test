#include <stdio.h>

// 函数声明
void circularShift(int arr[], int n, int k);
void printArray(int arr[], int n);

int main()
{
    int nums[10];
    int k;
    int i;

    // 输入10个整数
    printf("请输入10个整数：\n");
    for (i = 0; i < 10; i++)
    {
        scanf("%d", &nums[i]);
    }

    // 输入移动的位数
    printf("请输入要循环移动的位数k：");
    scanf("%d", &k);

    // 处理k为负数或大于10的情况
    k = k % 10;
    if (k < 0)
    {
        k += 10; // 负的k值转为正的等效移动
    }

    // 进行循环移动
    circularShift(nums, 10, k);

    // 输出移动后的结果
    printf("循环移动%d位后的结果为：\n", k);
    printArray(nums, 10);

    return 0;
}

// 循环右移k位的函数
void circularShift(int arr[], int n, int k)
{
    if (k == 0)
        return; // 移动0位直接返回

    int temp[k]; // 临时数组存储要移动的元素
    int i;

    // 将要移动的后k个元素存入临时数组
    for (i = 0; i < k; i++)
    {
        temp[i] = arr[n - k + i];
    }

    // 将前面的元素向后移动k位
    for (i = n - 1; i >= k; i--)
    {
        arr[i] = arr[i - k];
    }

    // 将临时数组中的元素放到前面
    for (i = 0; i < k; i++)
    {
        arr[i] = temp[i];
    }
}

// 打印数组元素
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
