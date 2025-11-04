#include <stdio.h>

int main()
{
    int nums[10];
    int max1, max2; // max1存储最大值，max2存储次大值
    int i;

    // 输入10个数
    printf("请输入10个整数：\n");
    for (i = 0; i < 10; i++)
    {
        scanf("%d", &nums[i]);
    }

    // 初始化最大值和次大值
    if (nums[0] > nums[1])
    {
        max1 = nums[0];
        max2 = nums[1];
    }
    else
    {
        max1 = nums[1];
        max2 = nums[0];
    }

    // 遍历数组，更新最大值和次大值
    for (i = 2; i < 10; i++)
    {
        if (nums[i] > max1)
        {
            // 当前数比最大值还大，更新次大值为原来的最大值
            max2 = max1;
            max1 = nums[i];
        }
        else if (nums[i] > max2)
        {
            // 当前数介于最大值和次大值之间，更新次大值
            max2 = nums[i];
        }
    }

    // 输出结果
    printf("最大值是：%d\n", max1);
    printf("次大值是：%d\n", max2);

    return 0;
}
