#include <stdio.h>
#include <ctype.h>
#include <string.h>

// 凯撒密码加密函数
void caesar_encrypt(char *text, int shift)
{
    char *p = text;
    while (*p != '\0')
    {
        if (isupper(*p))
        {
            *p = ((*p - 'A' + shift) % 26) + 'A';
        }
        else if (islower(*p))
        {
            *p = ((*p - 'a' + shift) % 26) + 'a';
        }
        p++;
    }
}

int main()
{
    char message[100];
    int shift;

    printf("请输入明文：");
    fgets(message, sizeof(message), stdin);
    // 移除换行符
    message[strcspn(message, "\n")] = '\0';

    printf("请输入偏移量（正整数）：");
    scanf("%d", &shift);

    caesar_encrypt(message, shift);
    printf("加密后的密文：%s\n", message);

    return 0;
}