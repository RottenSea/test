#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char str[100];
    int digits = 0, uppercase = 0, lowercase = 0;

    printf("请输入一个字符串: ");
    gets(str);
    str[strcspn(str, "\n")] = 0; // 移除换行符

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isdigit(str[i]))
            digits++;
        else if (isupper(str[i]))
            uppercase++;
        else if (islower(str[i]))
            lowercase++;
    }

    printf("数字个数: %d\n", digits);
    printf("大写字母个数: %d\n", uppercase);
    printf("小写字母个数: %d\n", lowercase);

    return 0;
}