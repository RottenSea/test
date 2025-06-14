#include <stdio.h>

int main()
{
    double numbers[4], sum = 0.0, average;
    // 读入4个double型的数据
    printf("请输入4个double型的数据：\n");
    for (int i = 0; i < 4; i++)

    {
        scanf("%lf", &numbers[i]);
        sum += numbers[i];
    }
    // 计算平均值并保留到小数点后第2位
    average = sum / 4;
    printf("平均值是：%.2lf\n", average);
    return 0;
}