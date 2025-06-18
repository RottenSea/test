#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USER_NUMBER 100
#define MAX_ADMINISTRATOR_NUMBER 100
#define MAX_ENTERPRISE_NUMBER 100
#define MAX_FLIGHT_NUMBER 100

#define MAX_UUID_LENGTH 21
#define MAX_NAME_LENGTH 21
#define MAX_PASSWORD_LENGTH 21
#define MAX_PHONE_LENGTH 12
#define MAX_ID_LENGTH 31

const char *USER_FILE = "Users.dat";
const char *USER_FLIGHT_FILE = "UserFlight.dat";
const char *FLIGHTS_FILE = "Flights.dat";

void initialize();
void loadUsers();
void saveUsers();
void loadUserFlight();
void saveUserFlight();
void loadFlights();
void saveFlishts();

void reg();
void login();
void userMenu();
void adminMenu();
void enterMenu();

void pressEnterToContinue();

// 用户信息结构体
typedef struct
{
    char UUID[MAX_UUID_LENGTH];
    char NAME[MAX_NAME_LENGTH];
    char PASSWORD[MAX_PASSWORD_LENGTH];
    char PHONE[MAX_PHONE_LENGTH];
    int gender; // 0未知 1男 2女
    int age;
} USER;
USER users[MAX_USER_NUMBER];
int usersCount = 0;

// 管理员信息结构体
typedef struct
{
    char UUID[MAX_UUID_LENGTH];
    char NAME[MAX_NAME_LENGTH];
    char PASSWORD[MAX_PASSWORD_LENGTH];
    int ROLE; // 0用户管理员 1航班管理员
} ADMINISTRATOR;
ADMINISTRATOR admins[MAX_ADMINISTRATOR_NUMBER];
int adminsCount = 0;

// 企业信息结构体
typedef struct
{
    char UUID[MAX_UUID_LENGTH];
    char NAME[MAX_NAME_LENGTH];
    char PASSWORD[MAX_PASSWORD_LENGTH];
} ENTERPRISE;
ENTERPRISE enters[MAX_ENTERPRISE_NUMBER];
int entersCount = 0;

// 航班信息结构体
typedef struct
{
    char ID[MAX_ID_LENGTH];
    char MODEL[MAX_NAME_LENGTH];
    char COMPANY[MAX_NAME_LENGTH];
    time_t time;
    time_t duration;
    char GATE[MAX_NAME_LENGTH];
    char STARTING[MAX_NAME_LENGTH];
    char DESTINATION[MAX_NAME_LENGTH];
    int praise;
    int num;
    int curr;
} FLIGHT;
FLIGHT flights[MAX_FLIGHT_NUMBER];
int flightsCount = 0;

int main()
{

    int choice;
    do
    {
        system("cls");
        printf("---航班信息管理系统---\n");
        printf("1.注册\n");
        printf("2.登录\n");
        printf("3.退出系统\n");
        printf("---------------------\n");
        printf("请选择：");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            reg();
            break;
        case 2:
            login();
            break;

        default:
            printf("已退出系统\n");
            exit(0);
            break;
        }
    } while (1);
}

/**
 * 初始化数据
 */
void initialize()
{
    // 如果文件已经存在 跳过初始化
    FILE *fp = fopen(USER_FILE, "r");
    if (fp)
    {
        fclose(fp);
        return;
    }

    usersCount = 0;
    adminsCount = 0;
    entersCount = 0;

    // 添加示例用户
    USER u1;
    strcpy(u1.UUID, "001");
    strcpy(u1.NAME, "用户001");
    strcpy(u1.PASSWORD, "001");
    strcpy(u1.PHONE, "13300001111");
    u1.gender = 1;
    u1.age = 18;
    users[usersCount++] = u1;

    ADMINISTRATOR u2;
    strcpy(u1.UUID, "002");
    strcpy(u1.NAME, "用户管理员002");
    strcpy(u1.PASSWORD, "002");
    u2.ROLE = 0;
    admins[adminsCount++] = u2;

    strcpy(u1.UUID, "003");
    strcpy(u1.NAME, "航班管理员003");
    strcpy(u1.PASSWORD, "003");
    u2.ROLE = 1;
    admins[adminsCount++] = u2;

    ENTERPRISE u3;
    strcpy(u1.UUID, "004");
    strcpy(u1.NAME, "中国南方航空004");
    strcpy(u1.PASSWORD, "004");
    enters[entersCount++] = u3;

    saveUsers();

    flightsCount = 0;

    FLIGHT f1;
    strcpy(f1.ID, "001");
    strcpy(f1.MODEL, "波音737");
    f1.time = time(NULL);
    f1.duration = 14400;
    strcpy(f1.GATE, "A01");
    strcpy(f1.STARTING, "浙江");
    strcpy(f1.DESTINATION, "长春");
    f1.praise = 1000;
    f1.num = 162;
    f1.curr = 100;

    saveFlishts();
}

void loadUsers()
{
}

void saveUsers()
{
    FILE *fp = fopen(USER_FILE, "wb");
    if (fp == NULL)
    {
        printf("保存用户时文件打开失败！\n");
        return;
    }
    fwrite(&usersCount, sizeof(int), 1, fp);
    fwrite(users, sizeof(USER), usersCount, fp);
    fclose(fp);
}

void loadUserFlight()
{
}

void saveUserFlight()
{
}

void loadFlights()
{
}

void saveFlishts()
{
}

void reg()
{
}

void login()
{
    system("cls");
    if (usersCount == 0)
    {
        printf("系统还没有用户，请先注册");
    }

    char inputUUID[MAX_UUID_LENGTH];

    printf("UUID:");
    fgets(inputUUID, MAX_UUID_LENGTH, stdin);

    int choice = 0;

    // 在users中查找该用户
    for (int i = 0; i < usersCount; ++i)
    {
        if (users[i].UUID == inputUUID)
        {
            do
            {
                char inputPassword[MAX_PASSWORD_LENGTH];
                printf("password:");
                fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);

                if (users[i].PASSWORD == inputPassword)
                {
                    userMenu();
                    return;
                }
                else
                {
                    printf("密码输入错误,是否重新输入\n");
                    printf("0取消并返回上级目录\n");
                    printf("1重新输入密码\n");
                    printf("选择:");
                    scanf("%d", &choice);
                }
            } while (choice);
        }
    }

    // 在admins中查找该用户
    for (int i = 0; i < adminsCount; ++i)
    {
        if (admins[i].UUID == inputUUID)
        {
            do
            {
                char inputPassword[MAX_PASSWORD_LENGTH];
                printf("password:");
                fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);

                if (admins[i].PASSWORD == inputPassword)
                {
                    adminMenu();
                    return;
                }
                else
                {
                    printf("密码输入错误,是否重新输入\n");
                    printf("0取消并返回上级目录\n");
                    printf("1重新输入密码\n");
                    printf("选择:");
                    scanf("%d", &choice);
                }
            } while (choice);
        }
    }

    // 在enters中查找该用户
    for (int i = 0; i < entersCount; ++i)
    {
        if (enters[i].UUID == inputUUID)
        {
            do
            {
                char inputPassword[MAX_PASSWORD_LENGTH];
                printf("password:");
                fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);

                if (enters[i].PASSWORD == inputPassword)
                {
                    enterMenu();
                    return;
                }
                else
                {
                    printf("密码输入错误,是否重新输入\n");
                    printf("0取消并返回上级目录\n");
                    printf("1重新输入密码\n");
                    printf("选择:");
                    scanf("%d", &choice);
                }
            } while (choice);
        }
    }

    printf("UUID不存在");
}

void userMenu()
{
}

void adminMenu()
{
}

void enterMenu()
{
}

/**
 * 按回车键继续
 */
void pressEnterToContinue()
{
    printf("\n按回车键继续...");
    getchar();
}