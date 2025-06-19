#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USER_NUMBER 100
#define MAX_ADMINISTRATOR_NUMBER 100
#define MAX_ENTERPRISE_NUMBER 100
#define MAX_USER_FLIGHT 10
#define MAX_FLIGHT_NUMBER 100

#define MAX_UUID_LENGTH 21
#define MAX_NAME_LENGTH 21
#define MAX_PASSWORD_LENGTH 21
#define MAX_PHONE_LENGTH 12
#define MAX_CODE_LENGTH 31

const char *USER_FILE = "Users.dat";
const char *FLIGHTS_FILE = "Flights.dat";

void initialize();
void loadUsers();
void saveUsers();
void loadFlights();
void saveFlights();

void reg();
void login();
void userMenu(int curr);
void adminMenu(int curr);
void enterMenu(int curr);

void listFlight(char *name);
void bookFlight();
void cancleflight();

void addUser();
void deleteUser();
void modifyUser();
void searchUser();

void addFlight();
void deleteflight();
void modifyFlight();

int findUserIndexByUUID(char *inputUUID);
int findAdminIndexByUUID(char *inputUUID);
int findEnterIndexByUUID(char *inputUUID);

bool isValidString(char *str);
time_t timeToTimeT(int year, int month, int day, int hour, int minute);
void pressEnterToContinue();

// 用户信息结构体
typedef struct
{
    char UUID[MAX_UUID_LENGTH];
    char NAME[MAX_NAME_LENGTH];
    char PASSWORD[MAX_PASSWORD_LENGTH];
    char PHONE[MAX_PHONE_LENGTH];
    char flights[MAX_USER_FLIGHT][MAX_CODE_LENGTH];
    int count;  // 已订航班数量
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
    char CODE[MAX_CODE_LENGTH];
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
    initialize();

    int choice;
    do
    {
        system("cls");
        printf("-----航班信息管理系统-----\n");
        printf("1.注册\n");
        printf("2.登录\n");
        printf("3.退出系统\n");
        printf("-------------------------\n");
        printf("请选择：");

        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            reg();
            break;
        case 2:
            login();
            break;
        case 3:
            exit(0);
            break;

        default:
            printf("输入有误\n");
            pressEnterToContinue();
            break;
        }
    } while (1);
    return 0;
}

/**
 * 初始化数据
 */
void initialize()
{
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;

    // 如果文件已经存在 跳过初始化
    fp1 = fopen(USER_FILE, "r");
    fp2 = fopen(FLIGHTS_FILE, "r");
    if (fp1)
        fclose(fp1);
    if (fp2)
        fclose(fp2);
    if (fp1 && fp2)
        return;

    fp1 = fopen(USER_FILE, "w");
    fp2 = fopen(FLIGHTS_FILE, "w");
    if (fp1 == NULL)
    {
        perror("文件创建失败");
        pressEnterToContinue();
        return;
    }
    if (fp2 == NULL)
    {
        perror("文件创建失败");
        pressEnterToContinue();
        return;
    }
    fclose(fp1);
    fclose(fp2);

    usersCount = 0;
    adminsCount = 0;
    entersCount = 0;
    flightsCount = 0;

    // 添加示例用户
    USER u1;
    strcpy(u1.UUID, "001");
    strcpy(u1.NAME, "用户001");
    strcpy(u1.PASSWORD, "001");
    strcpy(u1.PHONE, "13300001111");
    strcpy(u1.flights[0], "CZ6546");
    u1.count = 1;
    u1.gender = 1;
    u1.age = 18;
    users[usersCount++] = u1;

    ADMINISTRATOR u2;
    strcpy(u2.UUID, "002");
    strcpy(u2.NAME, "用户管理员");
    strcpy(u2.PASSWORD, "002");
    u2.ROLE = 0;
    admins[adminsCount++] = u2;

    strcpy(u2.UUID, "003");
    strcpy(u2.NAME, "航班管理员");
    strcpy(u2.PASSWORD, "003");
    u2.ROLE = 1;
    admins[adminsCount++] = u2;

    ENTERPRISE u3;
    strcpy(u3.UUID, "004");
    strcpy(u3.NAME, "中国南方航空");
    strcpy(u3.PASSWORD, "004");
    enters[entersCount++] = u3;

    // 添加示例航班
    FLIGHT f1;
    strcpy(f1.CODE, "CZ6546");
    strcpy(f1.MODEL, "A321neo");
    strcpy(f1.COMPANY, "中国南方航空");
    f1.time = timeToTimeT(2025, 6, 18, 8, 30);
    f1.duration = 11100;
    strcpy(f1.GATE, "411");
    strcpy(f1.STARTING, "杭州萧山国际机场");
    strcpy(f1.DESTINATION, "长春龙嘉国际机场");
    f1.praise = 1000;
    f1.num = 162;
    f1.curr = 100;
    flights[flightsCount++] = f1;

    saveUsers();
    saveFlights();
}

void loadUsers()
{
    FILE *fp = fopen(USER_FILE, "rb");
    if (fp == NULL)
    {
        printf("读取用户时文件打开失败！\n");
        return;
    }

    fread(&usersCount, sizeof(int), 1, fp);
    fread(&adminsCount, sizeof(int), 1, fp);
    fread(&entersCount, sizeof(int), 1, fp);

    fread(users, sizeof(USER), usersCount, fp);
    fread(admins, sizeof(ADMINISTRATOR), adminsCount, fp);
    fread(enters, sizeof(ENTERPRISE), entersCount, fp);

    fclose(fp);
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
    fwrite(&adminsCount, sizeof(int), 1, fp);
    fwrite(&entersCount, sizeof(int), 1, fp);

    fwrite(users, sizeof(USER), usersCount, fp);
    fwrite(admins, sizeof(ADMINISTRATOR), adminsCount, fp);
    fwrite(enters, sizeof(ENTERPRISE), entersCount, fp);

    fclose(fp);
}

void loadFlights()
{
    FILE *fp = fopen(FLIGHTS_FILE, "rb");
    if (fp == NULL)
    {
        printf("读取航班时文件打开失败！\n");
        return;
    }

    fread(&flightsCount, sizeof(int), 1, fp);
    fread(flights, sizeof(FLIGHT), flightsCount, fp);

    fclose(fp);
}

void saveFlights()
{
    FILE *fp = fopen(FLIGHTS_FILE, "wb");
    if (fp == NULL)
    {
        printf("保存航班时文件打开失败！\n");
        return;
    }

    fwrite(&flightsCount, sizeof(int), 1, fp);
    fwrite(users, sizeof(USER), usersCount, fp);

    fclose(fp);
}

void reg()
{
    printf("----------注册----------\n");
    if (usersCount > MAX_USER_NUMBER)
    {
        printf("用户数量已达上限");
        pressEnterToContinue();
        return;
    }

    USER u = {0};
    printf("UUID(3-20位字母和数字):");
    fgets(u.UUID, MAX_UUID_LENGTH, stdin);
    u.UUID[strcspn(u.UUID, "\n")] = '\0';
    if (strlen(u.UUID) < 3)
    {
        printf("UUID过短 至少为3位!\n");
        pressEnterToContinue();
    }
    if (!isValidString(u.UUID))
    {
    }

    if ((findUserIndexByUUID(u.UUID) >= 0) || (findAdminIndexByUUID(u.UUID) >= 0) || (findEnterIndexByUUID(u.UUID) >= 0))
    {
        printf("该用户名已存在\n");
        pressEnterToContinue();
        return;
    }

    printf("NAME:");
    fgets(u.NAME, MAX_NAME_LENGTH, stdin);
    u.NAME[strcspn(u.NAME, "\n")] = '\0';

    printf("PASSWORD:");
    fgets(u.PASSWORD, MAX_PASSWORD_LENGTH, stdin);
    u.PASSWORD[strcspn(u.PASSWORD, "\n")] = '\0';

    printf("PHONE:");
    fgets(u.PHONE, MAX_PHONE_LENGTH, stdin);
    u.PHONE[strcspn(u.PHONE, "\n")] = '\0';

    printf("是否立即补充其他信息?\n");
    printf("0否 1是");
    int choice = 0;
    scanf("%d", &choice);
    getchar();
    if (choice)
    {
        printf("gender:");
        scanf("%d", u.gender);
        getchar();
        printf("age:");
        scanf("%d", u.age);
        getchar();
    }

    users[usersCount++] = u;
    saveUsers();
}

void login()
{
    system("cls");
    if (usersCount == 0)
    {
        printf("系统还没有用户，请先注册\n");
        return;
    }

    char inputUUID[MAX_UUID_LENGTH];

    printf("UUID:");
    fgets(inputUUID, MAX_UUID_LENGTH, stdin);

    int choice = 0;
    int index = -1;

    // 在users中查找该用户
    index = findUserIndexByUUID(inputUUID);
    if (index >= 0)
    {
        do
        {
            char inputPassword[MAX_PASSWORD_LENGTH];
            printf("password:");
            fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);

            if (users[index].PASSWORD == inputPassword)
            {
                userMenu(index);
                return;
            }
            else
            {
                printf("密码输入错误,是否重新输入\n");
                printf("0取消并返回上级目录\n");
                printf("1重新输入密码\n");
                printf("选择:");
                scanf("%d", &choice);
                getchar();
            }
        } while (choice);
    }

    // 在admins中查找该用户
    index = findAdminIndexByUUID(inputUUID);
    if (index >= 0)
    {
        do
        {
            char inputPassword[MAX_PASSWORD_LENGTH];
            printf("password:");
            fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);

            if (admins[index].PASSWORD == inputPassword)
            {
                adminMenu(index);
                return;
            }
            else
            {
                printf("密码输入错误,是否重新输入\n");
                printf("0取消并返回上级目录\n");
                printf("1重新输入密码\n");
                printf("选择:");
                scanf("%d", &choice);
                getchar();
            }
        } while (choice);
    }

    // 在enters中查找该用户
    index = findEnterIndexByUUID(inputUUID);
    if (index >= 0)
    {
        do
        {
            char inputPassword[MAX_PASSWORD_LENGTH];
            printf("password:");
            fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);

            if (enters[index].PASSWORD == inputPassword)
            {
                enterMenu(index);
                return;
            }
            else
            {
                printf("密码输入错误,是否重新输入\n");
                printf("0取消并返回上级目录\n");
                printf("1重新输入密码\n");
                printf("选择:");
                scanf("%d", &choice);
                getchar();
            }
        } while (choice);
    }

    printf("UUID不存在\n");
    pressEnterToContinue();
    return;
}

void userMenu(int curr)
{
    int choice;

    do
    {
        system("cls");
        printf("-----用户界面-----\n");
        printf("欢迎!%s\n", users[curr].NAME);
        printf("1.查询航班\n");
        printf("2.订购航班\n");
        printf("3.退订航班\n");
        printf("4.注销并返回上级菜单\n");
        printf("-----------------\n");
        printf("请选择功能:");

        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            listFlight("");
            break;
        case 2:
            bookFlight();
            break;
        case 3:
            cancleflight();
            break;
        case 4:
            printf("已注销\n");
            pressEnterToContinue();
            return;

        default:
            printf("输入有误\n");
            break;
        }
    } while (choice != 4);
}

void adminMenu(int curr)
{
    int choice;

    if (admins[curr].ROLE == 0)
    {
        do
        {
            system("cls");
            printf("-----管理员界面-----\n");
            printf("欢迎!%s(用户管理员)\n", admins[curr].NAME);
            printf("1.增加用户\n");
            printf("2.删除用户\n");
            printf("3.修改用户\n");
            printf("4.查询用户\n");
            printf("5.注销并返回上级菜单\n");
            printf("-------------------\n");
            printf("请选择功能:");

            scanf("%d", &choice);
            getchar();
            switch (choice)
            {
            case 1:
                addUser();
                break;
            case 2:
                deleteUser();
                break;
            case 3:
                modifyUser();
                break;
            case 4:
                searchUser();
                break;
            case 5:
                printf("已注销\n");
                pressEnterToContinue();
                return;

            default:
                printf("输入有误\n");
                break;
            }
        } while (choice != 5);
    }

    // 航班管理员
    else
    {
        do
        {
            system("cls");
            printf("-----管理员界面-----\n");
            printf("欢迎!%s航班管理员\n", admins[curr].NAME);
            printf("1.查询航班\n");
            printf("2.增加航班\n");
            printf("3.删除航班\n");
            printf("4.修改航班\n");
            printf("5.注销并返回上级菜单\n");
            printf("-------------------\n");
            printf("请选择功能:");

            scanf("%d", &choice);
            getchar();
            switch (choice)
            {
            case 1:
                listFlight("");
                break;
            case 2:
                addFlight();
                break;
            case 3:
                deleteflight();
                break;
            case 4:
                modifyFlight();
                break;
            case 5:
                printf("已注销\n");
                pressEnterToContinue();
                return;

            default:
                printf("输入有误\n");
                break;
            }
        } while (choice != 5);
    }
}

void enterMenu(int curr)
{
    int choice;

    do
    {
        system("cls");
        printf("-----航司界面-----\n");
        printf("欢迎!%s\n", enters[curr].NAME);
        printf("1.查询航班\n");
        printf("2.增加航班\n");
        printf("3.删除航班\n");
        printf("4.修改航班\n");
        printf("5.注销并返回上级菜单\n");
        printf("-------------------\n");
        printf("请选择功能:");

        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            listFlight(enters[curr].NAME);
            break;
        case 2:
            addFlight();
            break;
        case 3:
            deleteflight();
            break;
        case 4:
            modifyFlight();
            break;
        case 5:
            printf("已注销\n");
            pressEnterToContinue();
            return;

        default:
            printf("输入有误\n");
            break;
        }
    } while (choice != 5);
}

void listFlight(char *name)
{
}

void bookFlight()
{
}

void cancleflight()
{
}

void addUser()
{
}

void deleteUser()
{
}

void modifyUser()
{
}

void searchUser()
{
}

void addFlight()
{
}

void deleteflight()
{
}

void modifyFlight()
{
}

int findUserIndexByUUID(char *inputUUID)
{
    for (int i = 0; i < usersCount; ++i)
    {
        if (users[i].UUID == inputUUID)
        {
            return i;
        }
    }

    return -1;
}

int findAdminIndexByUUID(char *inputUUID)
{
    for (int i = 0; i < adminsCount; ++i)
    {
        if (admins[i].UUID == inputUUID)
        {
            return i;
        }
    }

    return -1;
}

int findEnterIndexByUUID(char *inputUUID)
{
    for (int i = 0; i < entersCount; ++i)
    {
        if (enters[i].UUID == inputUUID)
        {
            return i;
        }
    }

    return -1;
}

bool isValidString(char *str)
{
}

/**
 * 将时间转化为time_t
 */
time_t timeToTimeT(int year, int month, int day, int hour, int minute)
{
    struct tm t = {0};

    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = 0;

    return mktime(&t);
}

/**
 * 按回车键继续
 */
void pressEnterToContinue()
{
    printf("\n按回车键继续...");
    getchar();
}
