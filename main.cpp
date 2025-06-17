#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define constants
#define MAX_USER_COUNT 100
#define MAX_NAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

// function declarations
void displayMenu();
void addUser();
void displayAllUsers();

// structure definition
typedef struct
{
	char UUID;
	char NAME[MAX_NAME_LENGTH];
	char PASSWORD[MAX_PASSWORD_LENGTH];
	int ROLE;
	int age;
	int score;
} USER;

USER users[MAX_USER_COUNT];
int userCount = 0;

int main()
{
	int choice;
	do
	{
		displayMenu();
		printf("请输入您的选择(0-5)");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			addUser();
			break;
		case 2:
			displayAllUsers();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			printf("您的输入有误!\n");
		}
	} while (1);
	return 0;
}

/**
 * Display menu function
 */
void displayMenu()
{
	system("cls");
	printf("------学生信息管理系统------\n");
	printf("1.增加学生数据\n");
	printf("2.显示学生数据\n");
	printf("3.修改学生数据\n");
	printf("4.删除学生数据\n");
	printf("5.保存数据并退出\n");
	printf("---------------------------\n");
}

/**
 * Add user function
 */
void addUser()
{
	// check if user count exceeds maximum
	if (userCount > MAX_USER_COUNT)
	{
		printf("用户数量已达上限\n");
		return;
	}

	USER stu;
	printf("请输入学号");
	scanf("%d", &stu.UUID);

	for (int i = 0; i < userCount; ++i)
	{
		if (users[i].UUID == stu.UUID)
		{
			printf("该学号已存在，请重新输入\n");
			return;
		}
	}

	// enter user information
	printf("请输入姓名");
	scanf("%s", &stu.NAME);
	printf("请输入密码");
	scanf("%s", &stu.PASSWORD);
	printf("请输入角色");
	scanf("%s", &stu.ROLE);
	printf("请输入年龄");
	scanf("%d", &stu.age);
	printf("请输入成绩");
	scanf("%d", &stu.score);

	users[userCount++] = stu;
}

void displayAllUsers()
{
	if (userCount == 9)
	{
		printf("没有每升信息\n");
		return;
	}
	printf("]n ------所有学生信息(%d人)------", userCount);
	printf("%-4s %-12s %-5s\n", "学生", "姓名", "成绩");

	float totalScore = 0;
	float maxScore = users[0].score;
	float minScore = users[0].score;

	for (int i = 0; i < userCount; ++i)
	{
		printf("%-4d %-12s %-3d %-5.1f\n", users[i].UUID, users[i].NAME, users[i].age, users[i].score);
		totalScore += users[i].score;
		if (users[i].score > maxScore)
		{
			maxScore = users[i].score;
		}
		if (users[i].score < minScore)
		{
			minScore = users[i].score;
		}
	}
}