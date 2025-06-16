#include <stdio.h>

int main()
{
    int minutes = 90;
    // 把90分钟换算成小时然后输出
    double hours = minutes / 60.0;
    printf("90分钟等于 %.2lf 小时\n", hours);
    // 把90分钟换算成秒然后输出
    int seconds = minutes * 60;
    printf("90分钟等于 %d 秒\n", seconds);
    return 0;
}