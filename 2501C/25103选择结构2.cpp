#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, c;
    printf("请输入a、b、c: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    double delta = b * b - 4 * a * c;
    if (delta > 0)

    {
        double x1 = (-b + sqrt(delta)) / (2 * a);
        double x2 = (-b - sqrt(delta)) / (2 * a);
        printf("方程有两个不相等的实根: %.2f 和 %.2f\n", x1, x2);
    }
    else if (delta == 0)

    {
        double x = -b / (2 * a);
        printf("方程有两个相等的实根: %.2f\n", x);
    }
    else
    {
        printf("方程没有实根，有两个共轭复根:\n");
    }
    return 0;
}