#include <stdio.h>
#include <stdlib.h> // abs()
#define MAXSIZE 100 // 栈最大容量
// 栈结构定义
typedef struct
{
    int data[MAXSIZE];
    int top;
} Stack;
// 初始化栈
void initStack(Stack *s)
{
    s->top = -1;
}
// 压栈
void push(Stack *s, int value)
{
    if (s->top == MAXSIZE - 1)
    {
        printf("栈溢出！\n");
        exit(1);
    }
    s->data[++(s->top)] = value;
}
// 出栈
int pop(Stack *s)
{
    if (s->top == -1)
    {
        printf("栈为空！\n");
        exit(1);
    }
    return s->data[(s->top)--];
}
// 十进制转任意进制
void convert(int num, int base)
{
    if (base < 2 || base > 16)
    {
        printf("错误：进制范围应为 2~16！\n");
        return;
    }
    Stack s;
    initStack(&s);
    int isNegative = 0;
    if (num < 0)
    {
        isNegative = 1;
        num = abs(num);
    }
    // 特殊情况：num == 0
    if (num == 0)
    {
        printf("0\n");
        return;
    }
    // 除基取余并入栈
    while (num != 0)
    {
        int remainder = num % base;
        push(&s, remainder);
        num /= base;
    }
    // 输出结果
    if (isNegative)
        printf("-");
    printf("转换结果：");
    while (s.top != -1)
    {
        int digit = pop(&s);
        if (digit >= 10)
            printf("%c", 'A' + (digit - 10)); // 映射 A-F
        else
            printf("%d", digit);
    }
    printf("\n");
}
// 主函数
int main()
{
    int num, base;
    printf("请输入十进制整数: ");
    scanf("%d", &num);
    printf("请输入目标进制(2-16): ");
    scanf("%d", &base);
    convert(num, base);
    return 0;
}
