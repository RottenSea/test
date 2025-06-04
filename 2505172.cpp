#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char str[100];
    int i, j, isPalindrome = 1;

    printf("请输入一个字符串: ");
    gets(str);
    str[strcspn(str, "\n")] = 0; // 移除换行符

    i = 0;
    j = strlen(str) - 1;

    while (i < j)
    {
        if (str[i] != str[j])
        {
            isPalindrome = 0;
            break;
        }
        i++;
        j--;
    }

    if (isPalindrome)
        printf("是回文串\n");
    else
        printf("不是回文串\n");

    return 0;
}