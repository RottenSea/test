#include <stdio.h>
#include <math.h>

// 设计一个函数判断一个数是否是素数，再设计一个函数用来验证一个偶数可以写成两个素数的和，并输出所有可能情况，通过主函数调用这两个函数。

int is_prime(int n)
{
    if (n <= 1)
        return 0; // 0 和 1 不是素数
    if (n == 2)
        return 1; // 2 是素数
    if (n % 2 == 0)
        return 0; // 偶数（除 2 外）不是素数
    int sqrt_n = (int)sqrt(n);
    for (int i = 3; i <= sqrt_n; i += 2)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

void verify_goldbach(int n)
{
    if (n <= 2 || n % 2 != 0)
    {
        printf("请输入大于 2 的偶数。\n");
        return;
    }
    printf("%d 可以表示为以下两个素数之和：\n", n);
    for (int i = 2; i <= n / 2; i++)
    {
        if (is_prime(i) && is_prime(n - i))
        {
            printf("%d = %d + %d\n", n, i, n - i);
        }
    }
}

int main()
{
    int number;
    printf("请输入一个大于 2 的偶数：");
    scanf("%d", &number);
    verify_goldbach(number);
    return 0;
}