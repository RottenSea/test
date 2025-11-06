#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char opStack[MAX];
int opTop = -1;

int valStack[MAX];
int valTop = -1;

void pushOp(char c)
{
    opStack[++opTop] = c;
}

char popOp()
{
    return opStack[opTop--];
}

char peekOp()
{
    return opStack[opTop];
}

int isEmptyOp()
{
    return opTop == -1;
}

void pushVal(int val)
{
    valStack[++valTop] = val;
}

int popVal()
{
    return valStack[valTop--];
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char c;
    for (i = 0; i < strlen(infix); i++)
    {
        c = infix[i];

        if (isdigit(c))
        {
            postfix[j++] = c;
            postfix[j++] = ' ';
        }
        else if (c == '(')
        {
            pushOp(c);
        }
        else if (c == ')')
        {
            while (!isEmptyOp() && peekOp() != '(')
                postfix[j++] = popOp(), postfix[j++] = ' ';
            popOp();
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            while (!isEmptyOp() && precedence(peekOp()) >= precedence(c))
                postfix[j++] = popOp(), postfix[j++] = ' ';
            pushOp(c);
        }
    }

    while (!isEmptyOp())
        postfix[j++] = popOp(), postfix[j++] = ' ';

    postfix[j] = '\0';
}

int evaluatePostfix(char postfix[])
{
    int i;
    for (i = 0; i < strlen(postfix); i++)
    {
        if (isdigit(postfix[i]))
        {
            int num = 0;
            while (isdigit(postfix[i]))
            {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            pushVal(num);
        }
        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/')
        {
            int b = popVal();
            int a = popVal();
            int res;
            switch (postfix[i])
            {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
                break;
            case '/':
                res = a / b;
                break;
            }
            pushVal(res);
        }
    }
    return popVal();
}

int main()
{
    char infix[MAX], postfix[MAX];
    printf("Please enter infix expression (such as (3+4)*5-6) : ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix experssion : %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("result : %d\n", result);

    return 0;
}
