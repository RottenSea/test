#include <stdio.h>
#include <string.h>

char stack[100] = {0};
int onTop = -1;

void Push(char character, int position)
{
    stack[position] = character;
    onTop = position;
}

char Popcharacter()
{
    char character;
    while (stack[onTop] == 0)
    {
        onTop--;
    }
    return stack[onTop--];
}

void ProcessStr(char *str)
{
    int len = strlen(str);
    char *p = str;
    while (*p != '\0')
    {
        if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z'))
        {
            Push(*p, (int)(p - str));
        }
        p++;
    }
    p = str;

    while (*p != '\0')
    {
        if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z'))
        {
            *p = Popcharacter();
        }
        p++;
    }
}

int main()
{
    char str[100];
    printf("Please input str (max length is 100) : ");
    scanf("%s", str);

    ProcessStr(str);
    printf("result : %s", str);
    return 0;
}