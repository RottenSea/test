#include <stdio.h>
#include <stdlib.h>

// 1. 定义链栈相关结构体
// 链栈节点结构体：存储单个余数及下一个节点地址
typedef struct StackNode
{
    int data;               // 存储余数（0-15，对应0-9、A-F）
    struct StackNode *next; // 指向后续节点的指针
} StackNode;

// 链栈结构体：通过栈顶指针管理整个链栈
typedef struct
{
    StackNode *top; // 栈顶指针（top=NULL表示空栈）
} LinkStack;

// 2. 链栈的基本操作函数
// 初始化链栈：将栈顶指针置为NULL，代表空栈
void InitStack(LinkStack *S)
{
    S->top = NULL;
}

// 判断链栈是否为空：栈顶为NULL则空，返回1；否则返回0
int StackEmpty(LinkStack S)
{
    return S.top == NULL ? 1 : 0;
}

// 入栈操作：创建新节点存储数据x，插入到栈顶
int Push(LinkStack *S, int x)
{
    // 1. 为新节点分配内存，判断是否分配成功
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL)
    {
        printf("内存分配失败，入栈操作终止！\n");
        return 0;
    }
    // 2. 给新节点赋值，并让其指向原栈顶
    newNode->data = x;
    newNode->next = S->top;
    // 3. 更新栈顶指针为新节点
    S->top = newNode;
    return 1;
}

// 出栈操作：取出栈顶节点的数据到x，释放该节点内存
int Pop(LinkStack *S, int *x)
{
    // 先判断栈是否为空
    if (StackEmpty(*S))
    {
        printf("栈已空，无法执行出栈操作！\n");
        return 0;
    }
    // 1. 暂存栈顶节点地址，避免释放后丢失后续节点
    StackNode *temp = S->top;
    // 2. 取出栈顶节点的数据
    *x = temp->data;
    // 3. 更新栈顶指针为下一个节点
    S->top = temp->next;
    // 4. 释放原栈顶节点的内存，避免内存泄漏
    free(temp);
    return 1;
}

// 销毁链栈：释放所有节点的内存，清空链栈
void DestroyStack(LinkStack *S)
{
    StackNode *temp;
    // 遍历所有节点，逐个释放内存
    while (S->top != NULL)
    {
        temp = S->top;
        S->top = S->top->next;
        free(temp);
    }
}

// 3. 核心转换函数：十进制数num转换为base进制（2<=base<=16）
void DecimalToAny(int num, int base)
{
    LinkStack S;
    InitStack(&S); // 初始化链栈，用于存储余数

    // 处理负数：先取绝对值转换，最后在结果前加负号
    int n = num < 0 ? -num : num;

    // 除base取余，余数入栈（do-while确保num=0时也能压入0，避免空栈）
    do
    {
        Push(&S, n % base); // 计算当前余数并压入栈
        n = n / base;       // 更新n为商，继续循环
    } while (n != 0);

    // 出栈并输出结果（逆序输出，得到最终进制结果）
    if (num < 0)
    { // 若原数为负，先输出负号
        printf("-");
    }
    int x; // 存储出栈的余数
    while (!StackEmpty(S))
    {
        Pop(&S, &x);
        // 处理10-15的余数：转换为对应的大写字母A-F
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

    DestroyStack(&S); // 转换完成后销毁栈，释放内存
}

// 4. 主函数：测试入口，获取用户输入并调用转换函数
int main()
{
    int decimal_num; // 存储用户输入的十进制整数
    int target_base; // 存储用户输入的目标进制（2-16）

    // 获取用户输入
    printf("请输入需要转换的十进制整数：");
    scanf("%d", &decimal_num);
    printf("请输入目标进制（范围：2-16）：");
    scanf("%d", &target_base);

    // 校验目标进制的合法性（必须在2-16之间）
    if (target_base < 2 || target_base > 16)
    {
        printf("错误：目标进制只能是2到16之间的整数，请重新运行程序！\n");
        return 1; // 非法输入，程序退出
    }

    // 调用转换函数并输出结果
    printf("转换结果（十进制%d → %d进制）：", decimal_num, target_base);
    DecimalToAny(decimal_num, target_base);

    return 0;
}