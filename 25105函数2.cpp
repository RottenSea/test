#include <stdio.h>

// 设计一个函数将十进制数转换成十六进制数（要求用递归来写），在主函数中调用该函数。

void decToHex(int n)
{
    if (n == 0)
        return;       // 递归出口
    decToHex(n / 16); // 递归调用处理高位

    int remainder = n % 16;
    if (remainder < 10)
        printf("%d", remainder); // 数字 0-9
    else
        printf("%c", 'A' + remainder - 10); // 字母 A-F
}

int main()
{
    int number;
    printf("请输入一个十进制整数：");
    scanf("%d", &number);

    printf("对应的十六进制为：");

    if (number == 0)
        printf("0");
    else
        decToHex(number);

    printf("\n");
    return 0;
}