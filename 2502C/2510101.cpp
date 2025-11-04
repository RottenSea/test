#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 50 // 定义顺序栈的最大容量，满足常见十进制数转换需求

// 1. 定义顺序栈结构体 SeqStack
typedef struct
{
    int data[MAXSIZE]; // 存储转换过程中产生的余数（0-15，对应0-9、A-F）
    int top;           // 栈顶指针，-1 表示栈为空
} SeqStack;

// 2. 顺序栈的基本操作函数
// 初始化栈：将栈顶指针置为-1，代表空栈
void InitStack(SeqStack *S)
{
    S->top = -1;
}

// 判断栈是否为空：栈顶指针为-1则空，返回1；否则返回0
int StackEmpty(SeqStack S)
{
    return S.top == -1 ? 1 : 0;
}

// 入栈操作：将元素x压入栈，成功返回1，栈满失败返回0
int Push(SeqStack *S, int x)
{
    if (S->top == MAXSIZE - 1)
    { // 栈满判断
        printf("栈满，入栈失败！\n");
        return 0;
    }
    S->data[++S->top] = x; // 栈顶指针先加1，再存入元素
    return 1;
}

// 出栈操作：将栈顶元素弹出到x，成功返回1，栈空失败返回0
int Pop(SeqStack *S, int *x)
{
    if (StackEmpty(*S))
    { // 栈空判断
        printf("栈空，出栈失败！\n");
        return 0;
    }
    *x = S->data[S->top--]; // 先取出栈顶元素，再将栈顶指针减1
    return 1;
}

// 3. 核心转换函数：十进制数num转换为base进制（2<=base<=16）
void DecimalToAny(int num, int base)
{
    SeqStack S;
    InitStack(&S); // 初始化栈，用于存储余数

    // 处理负数：先取绝对值转换，最后补负号
    int n = num < 0 ? -num : num;

    // 除base取余，余数入栈（用do-while确保num=0时也能压入0，避免空栈）
    do
    {
        Push(&S, n % base); // 计算当前余数并压栈
        n = n / base;       // 更新n为商，继续循环
    } while (n != 0);

    // 余数出栈（逆序输出，得到最终进制结果）
    if (num < 0)
    { // 若原数为负，先输出负号
        printf("-");
    }
    int x; // 存储出栈的余数
    while (!StackEmpty(S))
    {
        Pop(&S, &x);
        // 处理10-15的余数：对应输出A-F（10→A，11→B，…，15→F）
        if (x >= 10)
        {
            printf("%c", 'A' + x - 10);
        }
        else
        {
            printf("%d", x);
        }
    }
    printf("\n");
}

// 4. 主函数：测试入口，获取用户输入并调用转换函数
int main()
{
    int decimal_num; // 存储用户输入的十进制数
    int target_base; // 存储用户输入的目标进制（2-16）

    // 获取用户输入
    printf("请输入需要转换的十进制整数：");
    scanf("%d", &decimal_num);
    printf("请输入目标进制（范围：2-16）：");
    scanf("%d", &target_base);

    // 校验目标进制合法性
    if (target_base < 2 || target_base > 16)
    {
        printf("错误：目标进制必须在 2-16 之间，请重新运行程序！\n");
        return 1; // 非法进制，程序退出
    }

    // 调用转换函数并输出结果
    printf("转换结果（十进制%d → %d进制）：", decimal_num, target_base);
    DecimalToAny(decimal_num, target_base);

    return 0;
}