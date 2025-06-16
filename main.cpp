#include <stdio.h>
#include <stdlib.h>

// define constants
#define MAX_USER_COUNT 50

// function declarations
void displayMenu();
void choose();

typedef struct
{
	int ID;
	char UUID;
	int ROLE;
	char NAME[20];
	char PASSWORD[20];
} USER;

USER users[MAX_USER_COUNT];

int main()
{
	choose();
	return 0;
}

void displayMenu()
{
	system("cls");
	printf("-----学生信息管理系统------\n");
	printf("1.增加学生数据\n");
	printf("2.显示学生数据\n");
	printf("3.修改学生数据\n");
	printf("4.删除学生数据\n");
	printf("5.保存学生数据并退出\n");
	printf("-------------------------\n");
}

void choose()
{
	int choice;
	do
	{
		displayMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 0:
			exit(0);
		default:
			printf("您的输入有误!\n");
		}
	} while (1);
}
