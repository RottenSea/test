#include "stdio.h"

int main()
{
    int month, day, days = 0;
    int months[13] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    printf("输入月和日\n");
    scanf("%d %d", &month, &day);
    while (month > 1)

    {
        days += months[month - 2];
        month -= 1;
    }
    days = days + day + 1;
    printf("一年中的第%d天\n", days);
    return 0;
}