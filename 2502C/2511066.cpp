#include <stdio.h>
#include <string.h>
#include <ctype.h> // 提供 isalpha() 函数
#define MAX 100
int main()
{
    char str[MAX];
    char stack[MAX];
    int top = -1; // 栈顶指针
    printf("请输入字符串: ");
    scanf("%s", str); // 假设输入不包含空格
    int len = strlen(str);
    // 第一次扫描：把字母压栈
    for (int i = 0; i < len; i++)
    {
        if (isalpha(str[i]))
        { // 判断是否为字母
            stack[++top] = str[i];
        }
    }
    // 第二次扫描：遇字母则弹出
    for (int i = 0; i < len; i++)
    {
        if (isalpha(str[i]))
        {
            str[i] = stack[top--]; // 从栈顶取出一个字母
        }
    }
    printf("逆置后的字符串: %s\n", str);
    return 0;
}
