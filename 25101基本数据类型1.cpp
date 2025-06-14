#include <stdio.h>

int main()
{
    // 定义三个变量a、b、c
    double a, b, c;
    // 提示用户输入三个实数
    printf("请输入三个实数（用空格分隔）：");
    scanf("%lf %lf %lf", &a, &b, &c);
    // 打印原始值
    printf("原始值：a = %.2f, b = %.2f, c = %.2f\n", a, b, c);
    // 交换值
    double temp = a;
    a = b;
    b = c;
    c = temp;
    // 打印交换后的值
    printf("交换后：a = %.2f, b = %.2f, c = %.2f\n", a, b, c);
    return 0;
}