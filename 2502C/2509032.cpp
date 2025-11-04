#include <stdio.h>

int main()
{
    int nums[10];
    int min1, min2; // min1存储最小值，min2存储次小值
    int i;

    // 输入10个数
    printf("请输入10个整数：\n");
    for (i = 0; i < 10; i++)
    {
        scanf("%d", &nums[i]);
    }

    // 初始化最小值和次小值
    if (nums[0] < nums[1])
    {
        min1 = nums[0];
        min2 = nums[1];
    }
    else
    {
        min1 = nums[1];
        min2 = nums[0];
    }

    // 遍历数组，更新最小值和次小值
    for (i = 2; i < 10; i++)
    {
        if (nums[i] < min1)
        {
            // 当前数比最小值还小，更新次小值为原来的最小值
            min2 = min1;
            min1 = nums[i];
        }
        else if (nums[i] < min2)
        {
            // 当前数介于最小值和次小值之间，更新次小值
            min2 = nums[i];
        }
    }

    // 输出结果
    printf("最小值是：%d\n", min1);
    printf("次小值是：%d\n", min2);

    return 0;
}
