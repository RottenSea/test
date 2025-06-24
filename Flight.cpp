/**
 * 别忘了把 fgets 加上跨平台缓冲区清空
 * 如果假如 void safeInput(char *dest, int maxLen);
 * 只要调用一次 safeInput(u.UUID, MAX_UUID_LENGTH); 就能自动完成以上所有处理
 * 有待讨论
 *
 * 检查fgets的逻辑 是否需要循环
 *
 * wprintf需要更改逻辑
 *
 * scanf需要检查缓冲区
 *
 * 用户航班的保存需要日期
 *
 * listflights函数输出错误 考虑改为普通printf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

#define MAX_USER_NUMBER 100
#define MAX_ADMINISTRATOR_NUMBER 100
#define MAX_ENTERPRISE_NUMBER 100
#define MAX_USER_FLIGHT 10
#define MAX_FLIGHT_NUMBER 100

#define MAX_UUID_LENGTH 21
#define MAX_NAME_LENGTH 31
#define MAX_PASSWORD_LENGTH 21
#define MAX_PHONE_LENGTH 12
#define MAX_CODE_LENGTH 31
#define MAX_DATE_LENGTH 11
#define MAX_TIME_LENGTH 6

const char *USER_FILE = "Users.dat";
const char *FLIGHTS_FILE = "Flights.dat";

void initialize();
void loadUsers();
void saveUsers();
void loadFlights();
void saveFlights();

void reg();
void login();
void userMenu(int index);
void adminMenu(int index);
void enterMenu(int index);

void listFlight(const char *name);
wchar_t *departureTime(int index);
wchar_t *arrivalTime(int index);
int countFlightRemain(int index);
wchar_t *calStatus(int index);
void bookFlight(int index);
void cancleFlight(int index);

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

bool isValidStringUUID(char *str);
bool isValidStringNAME(char *str);
bool isValidStringPASSWORD(char *str);
bool isValidStringPHONE(char *str);
bool isValidGender(int gender);
bool isValidAge(int age);

int findFlightIndexByCode(char *str);

bool isValidStringCode(char *str);
bool isValidStringModel(char *str);
bool isValidStringCompany(char *str);
bool isValidStringDate(char *str);
bool isValidStringTime(char *str);
bool isValidStringGate(char *str);
bool isValidStringStarting(char *str);
bool isValidStringDestination(char *str);

int visualWidth(const wchar_t *str);
void wprintAlign(const wchar_t *str, int total_width);
time_t dateTotime(const char *str, int hour, int minute);
time_t timeToTimeT(int year, int month, int day, int hour, int minute);
void clearInputBuffer();
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
    char date[MAX_DATE_LENGTH];
    time_t time;
    time_t duration;
    char GATE[MAX_NAME_LENGTH];
    char STARTING[MAX_NAME_LENGTH];
    char DESTINATION[MAX_NAME_LENGTH];
    int prise;
    int num;
    int curr;
} FLIGHT;
FLIGHT flights[MAX_FLIGHT_NUMBER];
int flightsCount = 0;

int main()
{
    setlocale(LC_ALL, "");

    initialize();
    loadUsers();
    loadFlights();

    int choice;
    char c;
    do
    {
        system("cls");
        printf("-----航班信息管理系统-----\n");
        printf("1 注册\n");
        printf("2 登录\n");
        printf("0 退出系统\n");
        printf("--------------------------\n");
        printf("请选择：");

        if (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice < 0 || choice > 2)
        {
            printf("无效输入 请输入一个有效的数字选项\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
        else
        {
            switch (choice)
            {
            case 1:
                reg();
                break;
            case 2:
                login();
                break;
            case 0:
                printf("退出系统\n");
                break;
            default:
                printf("无效选项 请输入一个有效的数字选项\n");
            }
        }
    } while (choice != 0);

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
    strcpy(f1.date, "2025-06-18");
    f1.time = dateTotime(f1.date, 11, 50);
    f1.duration = 11100;
    strcpy(f1.GATE, "411");
    strcpy(f1.STARTING, "杭州萧山国际机场");
    strcpy(f1.DESTINATION, "长春龙嘉国际机场");
    f1.prise = 1000;
    f1.num = 200;
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
    system("cls");
    printf("----------注册----------\n");
    if (usersCount >= MAX_USER_NUMBER)
    {
        printf("用户数量已达上限\n");
        pressEnterToContinue();
        return;
    }

    USER u = {0};
    printf("UUID(3-20位字母和数字):");
    fgets(u.UUID, MAX_UUID_LENGTH, stdin);
    if (strchr(u.UUID, '\n') == NULL)
    {
        clearInputBuffer();
    }
    u.UUID[strcspn(u.UUID, "\n")] = '\0';
    if (!isValidStringUUID(u.UUID))
    {
        printf("UUID 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    if ((findUserIndexByUUID(u.UUID) >= 0) || (findAdminIndexByUUID(u.UUID) >= 0) || (findEnterIndexByUUID(u.UUID) >= 0))
    {
        printf("该用户名已存在\n");
        pressEnterToContinue();
        return;
    }

    printf("NAME(3-20个字符): ");
    fgets(u.NAME, MAX_UUID_LENGTH, stdin);
    if (strchr(u.NAME, '\n') == NULL)
    {
        clearInputBuffer();
    }
    u.NAME[strcspn(u.NAME, "\n")] = '\0';
    if (!isValidStringNAME(u.NAME))
    {
        printf("NAME 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    printf("PASSWORD(3-20位字母和数字): ");
    fgets(u.PASSWORD, MAX_UUID_LENGTH, stdin);
    if (strchr(u.PASSWORD, '\n') == NULL)
    {
        clearInputBuffer();
    }
    u.PASSWORD[strcspn(u.PASSWORD, "\n")] = '\0';
    if (!isValidStringPASSWORD(u.PASSWORD))
    {
        printf("PASSWORD 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    printf("PHONE(3-20位字母和数字): ");
    fgets(u.PHONE, MAX_UUID_LENGTH, stdin);
    if (strchr(u.PHONE, '\n') == NULL)
    {
        clearInputBuffer();
    }
    u.PHONE[strcspn(u.PHONE, "\n")] = '\0';
    if (!isValidStringPHONE(u.PHONE))
    {
        printf("PASSWORD 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    int choice;
    char c;
    printf("是否立即补充其他信息?\n");
    printf("0否 1是\n");
    printf("选择: ");
    while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice != 0 && choice != 1)
    {
        printf("无效输入 请输入一个有效的数字选项\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    if (choice)
    {
        while (1)
        {
            printf("0 默认\n");
            printf("1 男\n");
            printf("2 女\n");
            printf("gender:");

            if (scanf("%d%c", &u.gender, &c) == 2 && c == '\n' && isValidGender(u.gender))
            {
                break;
            }
            printf("输入不符合规范\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

        while (1)
        {
            printf("age(0-150):");

            if (scanf("%d%c", &u.age, &c) == 2 && c == '\n' && isValidAge(u.age))
            {
                break;
            }
            printf("输入不符合规范\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
    }

    users[usersCount++] = u;
    saveUsers();
}

void login()
{
    system("cls");
    printf("-----登录-----\n");
    if (usersCount == 0)
    {
        printf("暂无用户\n");
        return;
    }

    char inputUUID[MAX_UUID_LENGTH];
    printf("UUID: ");
    fgets(inputUUID, MAX_UUID_LENGTH, stdin);
    if (strchr(inputUUID, '\n') == NULL)
    {
        clearInputBuffer();
    }
    inputUUID[strcspn(inputUUID, "\n")] = '\0';

    int choice;
    char c;
    int index = -1;

    // 在users中查找该用户
    index = findUserIndexByUUID(inputUUID);
    if (index >= 0)
    {
        do
        {
            char inputPassword[MAX_PASSWORD_LENGTH];
            printf("PASSWORD: ");
            fgets(inputPassword, MAX_UUID_LENGTH, stdin);
            if (strchr(inputPassword, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputPassword[strcspn(inputPassword, "\n")] = '\0';

            if (strcmp(users[index].PASSWORD, inputPassword) == 0)
            {
                userMenu(index);
                return;
            }
            else
            {
                printf("密码输入错误,是否重新输入\n");
                printf("0 取消并返回上级目录\n");
                printf("1 重新输入密码\n");
                printf("选择:");
                while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice != 0 && choice != 1)
                {
                    printf("无效输入 请输入一个有效的数字选项\n");
                    while ((c = getchar()) != '\n' && c != EOF)
                        ;
                }
            }
        } while (choice);
        pressEnterToContinue();
        return;
    }

    // 在admins中查找该用户
    index = findAdminIndexByUUID(inputUUID);
    if (index >= 0)
    {
        do
        {
            char inputPassword[MAX_PASSWORD_LENGTH];
            printf("PASSWORD: ");
            fgets(inputPassword, MAX_UUID_LENGTH, stdin);
            if (strchr(inputPassword, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputPassword[strcspn(inputPassword, "\n")] = '\0';

            if (strcmp(admins[index].PASSWORD, inputPassword) == 0)
            {
                adminMenu(index);
                return;
            }
            else
            {
                printf("密码输入错误,是否重新输入\n");
                printf("0 取消并返回上级目录\n");
                printf("1 重新输入密码\n");
                printf("选择:");
                while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice != 0 && choice != 1)
                {
                    printf("无效输入 请输入一个有效的数字选项\n");
                    while ((c = getchar()) != '\n' && c != EOF)
                        ;
                }
            }
        } while (choice);
        pressEnterToContinue();
        return;
    }

    // 在enters中查找该用户
    index = findEnterIndexByUUID(inputUUID);
    if (index >= 0)
    {
        do
        {
            char inputPassword[MAX_PASSWORD_LENGTH];
            printf("PASSWORD: ");
            fgets(inputPassword, MAX_UUID_LENGTH, stdin);
            if (strchr(inputPassword, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputPassword[strcspn(inputPassword, "\n")] = '\0';

            if (strcmp(enters[index].PASSWORD, inputPassword) == 0)
            {
                enterMenu(index);
                return;
            }
            else
            {
                printf("密码输入错误,是否重新输入\n");
                printf("0 取消并返回上级目录\n");
                printf("1 重新输入密码\n");
                printf("选择:");
                while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice != 0 && choice != 1)
                {
                    printf("无效输入 请输入一个有效的数字选项\n");
                    while ((c = getchar()) != '\n' && c != EOF)
                        ;
                }
            }
        } while (choice);
        pressEnterToContinue();
        return;
    }

    printf("UUID 不存在\n");
    pressEnterToContinue();
    return;
}

void userMenu(int index)
{
    int choice;
    char c;

    do
    {
        system("cls");
        printf("-----用户界面-----\n");
        printf("欢迎! %s\n", users[index].NAME);
        printf("1 查询航班\n");
        printf("2 订购航班\n");
        printf("3 退订航班\n");
        printf("0 注销并返回上级菜单\n");
        printf("-----------------\n");
        printf("请选择功能: ");

        while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice != 0 && choice != 1)
        {
            printf("无效输入 请输入一个有效的数字选项\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
        switch (choice)
        {
        case 1:
            listFlight("");
            break;
        case 2:
            bookFlight(index);
            break;
        case 3:
            cancleFlight(index);
            break;
        case 0:
            printf("已注销\n");
            pressEnterToContinue();
            return;

        default:
            printf("输入有误\n");
            break;
        }
    } while (choice != 0);
}

void adminMenu(int index)
{
    int choice;
    char c;

    if (admins[index].ROLE == 0)
    {
        do
        {
            system("cls");
            printf("-----管理员界面-----\n");
            printf("欢迎! %s(用户管理员)\n", admins[index].NAME);
            printf("1 增加用户\n");
            printf("2 删除用户\n");
            printf("3 修改用户\n");
            printf("4 查询用户\n");
            printf("0 注销并返回上级菜单\n");
            printf("-------------------\n");
            printf("请选择功能: ");

            while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice != 0 && choice != 1)
            {
                printf("无效输入 请输入一个有效的数字选项\n");
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }
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
            case 0:
                printf("已注销\n");
                pressEnterToContinue();
                return;

            default:
                printf("输入有误\n");
                break;
            }
        } while (choice != 0);
    }

    // 航班管理员
    else
    {
        do
        {
            system("cls");
            printf("-----管理员界面-----\n");
            printf("欢迎! %s(航班管理员)\n", admins[index].NAME);
            printf("1 查询航班\n");
            printf("2 增加航班\n");
            printf("3 删除航班\n");
            printf("4 修改航班\n");
            printf("0 注销并返回上级菜单\n");
            printf("-------------------\n");
            printf("请选择功能: ");

            while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice != 0 && choice != 1)
            {
                printf("无效输入 请输入一个有效的数字选项\n");
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }
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
            case 0:
                printf("已注销\n");
                pressEnterToContinue();
                return;

            default:
                printf("输入有误\n");
                break;
            }
        } while (choice != 0);
    }
}

void enterMenu(int index)
{
    int choice;
    char c;

    do
    {
        system("cls");
        printf("-----航司界面-----\n");
        printf("欢迎! %s\n", enters[index].NAME);
        printf("1 查询航班\n");
        printf("2 增加航班\n");
        printf("3 删除航班\n");
        printf("4 修改航班\n");
        printf("0 注销并返回上级菜单\n");
        printf("-------------------\n");
        printf("请选择功能:");

        while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice != 0 && choice != 1)
        {
            printf("无效输入 请输入一个有效的数字选项\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
        switch (choice)
        {
        case 1:
            listFlight(enters[index].NAME);
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
        case 0:
            printf("已注销\n");
            pressEnterToContinue();
            return;

        default:
            printf("输入有误\n");
            break;
        }
    } while (choice != 0);
}

void listFlight(const char *name)
{
    system("cls");
    printf("当前航班数量: %d\n", flightsCount);
    printf("----------航班列表----------\n");
    wprintAlign(L"航班号", 10);
    wprintAlign(L"机型", 10);
    wprintAlign(L"承办公司", 20);
    wprintAlign(L"日期", 12);
    wprintAlign(L"出发时间", 12);
    wprintAlign(L"到达时间", 12);
    wprintAlign(L"始发地", 20);
    wprintAlign(L"目的地", 20);
    wprintAlign(L"价格", 8);
    wprintAlign(L"剩余", 8);
    wprintAlign(L"状态", 8);
    wprintf(L"\n");

    wchar_t tempStr[64];
    if (strlen(name) == 0)
    {
        for (int i = 0; i < flightsCount; ++i)
        {
            mbstowcs(tempStr, flights[i].CODE, 64);
            wprintAlign(tempStr, 10);
            mbstowcs(tempStr, flights[i].MODEL, 64);
            wprintAlign(tempStr, 10);
            mbstowcs(tempStr, flights[i].COMPANY, 64);
            wprintAlign(tempStr, 20);
            mbstowcs(tempStr, flights[i].date, 64);
            wprintAlign(tempStr, 12);
            wprintAlign(departureTime(i), 12);
            wprintAlign(arrivalTime(i), 12);
            mbstowcs(tempStr, flights[i].STARTING, sizeof(flights[i].STARTING));
            wprintAlign(tempStr, 20);
            mbstowcs(tempStr, flights[i].DESTINATION, sizeof(flights[i].DESTINATION));
            wprintAlign(tempStr, 20);
            wchar_t priceStr[16], remainStr[16];
            swprintf(priceStr, 16, L"%d", flights[i].prise);
            swprintf(remainStr, 16, L"%d", countFlightRemain(i));
            wprintAlign(priceStr, 8);
            wprintAlign(remainStr, 8);
            wprintAlign(calStatus(i), 8);
            wprintf(L"\n");
        }
    }
    else
    {
        for (int i = 0; i < flightsCount; ++i)
            if (strcmp(flights[i].COMPANY, name) == 0)
            {
                mbstowcs(tempStr, flights[i].CODE, 64);
                wprintAlign(tempStr, 10);
                mbstowcs(tempStr, flights[i].MODEL, 64);
                wprintAlign(tempStr, 10);
                mbstowcs(tempStr, flights[i].COMPANY, 64);
                wprintAlign(tempStr, 20);
                mbstowcs(tempStr, flights[i].date, 64);
                wprintAlign(tempStr, 12);
                wprintAlign(departureTime(i), 12);
                wprintAlign(arrivalTime(i), 12);
                mbstowcs(tempStr, flights[i].STARTING, sizeof(flights[i].STARTING));
                wprintAlign(tempStr, 20);
                mbstowcs(tempStr, flights[i].DESTINATION, sizeof(flights[i].DESTINATION));
                wprintAlign(tempStr, 20);
                wchar_t priceStr[16], remainStr[16];
                swprintf(priceStr, 16, L"%d", flights[i].prise);
                swprintf(remainStr, 16, L"%d", countFlightRemain(i));
                wprintAlign(priceStr, 8);
                wprintAlign(remainStr, 8);
                wprintAlign(calStatus(i), 8);
                wprintf(L"\n");
            }
    }

    pressEnterToContinue();
}

wchar_t *departureTime(int index)
{
    static wchar_t buffer[6];
    struct tm *timeinfo = localtime(&(flights[index].time));
    swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
    return buffer;
}

wchar_t *arrivalTime(int index)
{
    static wchar_t buffer[6];
    time_t arrivalTime = flights[index].time + flights[index].duration;
    struct tm *timeinfo = localtime(&arrivalTime);
    swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
    return buffer;
}

int countFlightRemain(int index)
{
    return (flights[index].num - flights[index].curr);
}

wchar_t *calStatus(int index)
{
    static wchar_t buffer[6];
    time_t curr = time(NULL);
    if (curr < flights[index].time)
    {
        wcscpy(buffer, L"未起飞");
    }
    else if ((curr >= flights[index].time) && (curr < flights[index].time + flights[index].duration))
    {
        wcscpy(buffer, L"飞行中");
    }
    else
    {
        wcscpy(buffer, L"已到达");
    }

    return buffer;
}

void bookFlight(int index)
{
    if (users[index].count > MAX_USER_FLIGHT)
    {
        printf("超过可订购航班数量\n");
        pressEnterToContinue();
        return;
    }

    char inputCode[MAX_CODE_LENGTH];
    printf("请输入你想要订购的航班号(CODE): ");
    fgets(inputCode, MAX_UUID_LENGTH, stdin);
    if (strchr(inputCode, '\n') == NULL)
    {
        clearInputBuffer();
    }
    inputCode[strcspn(inputCode, "\n")] = '\0';

    int findFlightIndex[MAX_FLIGHT_NUMBER] = {0};
    int p = 0;
    for (int i = 0; i < flightsCount; ++i)
    {
        if (flights[i].CODE == inputCode)
        {
            findFlightIndex[p++] = i;
        }
    }

    if (p == 0)
    {
        printf("未找到航班号为 %s 的航班\n", inputCode);
        pressEnterToContinue();
        return;
    }
    printf("找到的航班号:\n");
    for (int i = 0; i < p; ++i)
    {
        printf("%d %s\n", i, flights[findFlightIndex[i]].date);
    }

    int inputBookFlight;
    printf("请输入你想要订购的航班(序号): ");
    scanf("%d", inputBookFlight);
    getchar();
    if ((inputBookFlight <= 0) || (inputBookFlight > p))
    {
        printf("输入错误\n");
        pressEnterToContinue();
        return;
    }

    printf("请支付金额: %d元\n", flights[findFlightIndex[inputBookFlight - 1]].prise);
    bool payRes = false;
    printf("是否成功支付(0失败 1成功): \n");
    scanf("%d", &payRes);
    getchar();
    if (!payRes)
    {
        printf("预定失败\n");
        pressEnterToContinue();
        return;
    }

    strcpy(users[index].flights[users[index].count++], inputCode);
    printf("预定成功\n");
}

void cancleFlight(int index)
{
    if (users[index].count == 0)
    {
        printf("没有已预定的航班\n");
        pressEnterToContinue();
        return;
    }

    printf("当前已预定航班: \n");
    for (int i = 0; i < users[index].count; ++i)
    {
        printf("%d %s", i + 1, users[index].flights[i]);
    }

    int inputCancleFlight;
    printf("请输入你想要取消的航班(序号): \n");
    scanf("%d", inputCancleFlight);
    getchar();

    // 依次前移删除指向的航班
    for (int i = inputCancleFlight - 1; i < users[index].count - 1; ++i)
    {
        strcpy(users[index].flights[i], users[index].flights[i + 1]);
    }
    strcpy(users[index].flights[users[index].count - 1], "");
    users[index].count--;
}

/* printf("1 增加用户\n");
printf("2 删除用户\n");
printf("3 修改用户\n");
printf("4 查询用户\n");
 */

void addUser()
{
    system("cls");
    printf("-----增加用户-----");
    if (usersCount >= MAX_USER_NUMBER)
    {
        printf("用户数量已达上限\n");
        pressEnterToContinue();
        return;
    }

    USER u = {0};
    printf("UUID(3-20位字母和数字):");
    fgets(u.UUID, MAX_UUID_LENGTH, stdin);
    if (strchr(u.UUID, '\n') == NULL)
    {
        clearInputBuffer();
    }
    u.UUID[strcspn(u.UUID, "\n")] = '\0';
    if (!isValidStringUUID(u.UUID))
    {
        printf("UUID 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    if ((findUserIndexByUUID(u.UUID) >= 0) || (findAdminIndexByUUID(u.UUID) >= 0) || (findEnterIndexByUUID(u.UUID) >= 0))
    {
        printf("该用户名已存在\n");
        pressEnterToContinue();
        return;
    }

    printf("NAME(3-20个字符): ");
    fgets(u.NAME, MAX_UUID_LENGTH, stdin);
    if (strchr(u.NAME, '\n') == NULL)
    {
        clearInputBuffer();
    }
    u.NAME[strcspn(u.NAME, "\n")] = '\0';
    if (!isValidStringNAME(u.NAME))
    {
        printf("NAME 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    printf("PASSWORD(3-20位字母和数字): ");
    fgets(u.PASSWORD, MAX_UUID_LENGTH, stdin);
    if (strchr(u.PASSWORD, '\n') == NULL)
    {
        clearInputBuffer();
    }
    u.PASSWORD[strcspn(u.PASSWORD, "\n")] = '\0';
    if (!isValidStringPASSWORD(u.PASSWORD))
    {
        printf("PASSWORD 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    printf("PHONE(11位数字): ");
    fgets(u.PHONE, MAX_UUID_LENGTH, stdin);
    if (strchr(u.PHONE, '\n') == NULL)
    {
        clearInputBuffer();
    }
    u.PHONE[strcspn(u.PHONE, "\n")] = '\0';
    if (!isValidStringPHONE(u.PHONE))
    {
        printf("PASSWORD 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    int choice;
    char c;
    printf("是否立即补充其他信息?\n");
    printf("0否 1是\n");
    printf("选择: ");
    while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice != 0 && choice != 1)
    {
        printf("无效输入 请输入一个有效的数字选项\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    if (choice)
    {
        while (1)
        {
            printf("0 默认\n");
            printf("1 男\n");
            printf("2 女\n");
            printf("gender:");

            if (scanf("%d%c", &u.gender, &c) == 2 && c == '\n' && isValidGender(u.gender))
            {
                break;
            }
            printf("输入不符合规范\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

        while (1)
        {
            printf("age(0-150):");

            if (scanf("%d%c", &u.age, &c) == 2 && c == '\n' && isValidAge(u.age))
            {
                break;
            }
            printf("输入不符合规范\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
    }

    users[usersCount++] = u;
    saveUsers();
}

void deleteUser()
{
    system("cls");
    printf("-----删除用户-----");
    if (usersCount == 0)
    {
        printf("暂无用户\n");
        pressEnterToContinue();
        return;
    }

    char inputUUID[MAX_UUID_LENGTH];
    printf("UUID(3-20位字母和数字): ");
    fgets(inputUUID, MAX_UUID_LENGTH, stdin);
    if (strchr(inputUUID, '\n') == NULL)
    {
        clearInputBuffer();
    }
    inputUUID[strcspn(inputUUID, "\n")] = '\0';

    int index = findUserIndexByUUID(inputUUID);
    if (index == -1)
    {
        printf("该用户不存在\n");
        pressEnterToContinue();
        return;
    }

    for (int i = index; i < usersCount - 1; ++i)
    {
        users[i] = users[i + 1];
    }
    usersCount--;

    saveUsers();
}

void modifyUser()
{
    system("cls");
    printf("-----修改用户-----");
    if (usersCount == 0)
    {
        printf("暂无用户\n");
    }

    char inputUUID[MAX_UUID_LENGTH];
    printf("UUID(3-20位字母和数字): ");
    fgets(inputUUID, MAX_UUID_LENGTH, stdin);
    if (strchr(inputUUID, '\n') == NULL)
    {
        clearInputBuffer();
    }
    inputUUID[strcspn(inputUUID, "\n")] = '\0';

    int index = findUserIndexByUUID(inputUUID);
    if (index == -1)
    {
        printf("该用户不存在\n");
        pressEnterToContinue();
        return;
    }

    int choice = 1;
    char c;
    while (choice)
    {
        system("cls");
        printf("请选择想要更改的内容\n");
        printf("1 UUID\n");
        printf("2 NAME\n");
        printf("3 PASSWORD\n");
        printf("4 PHONE\n");
        printf("5 gender\n");
        printf("6 age\n");
        printf("0 退出\n");

        while (scanf("%d%c", &choice) != 1 || choice < 0 || choice > 6)
        {
            printf("无效输入 请输入一个有效的数字选项\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

        switch (choice)
        {
        case 1:
        {
            char inputUUID[MAX_UUID_LENGTH];
            printf("NEW UUID(3-20位字母和数字): ");
            fgets(inputUUID, MAX_UUID_LENGTH, stdin);
            if (strchr(inputUUID, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputUUID[strcspn(inputUUID, "\n")] = '\0';

            if (!isValidStringUUID(inputUUID))
            {
                printf("UUID 不符合规范\n");
                pressEnterToContinue();
                break;
            }
            if ((findUserIndexByUUID(inputUUID) >= 0) || (findAdminIndexByUUID(inputUUID) >= 0) || (findEnterIndexByUUID(inputUUID) >= 0))
            {
                printf("UUID 已存在\n");
                pressEnterToContinue();
                break;
            }

            strcpy(users[index].UUID, inputUUID);
            saveUsers();
            break;
        }

        case 2:
        {
            char inputName[MAX_NAME_LENGTH];
            printf("NEW NAME(3-20个字符): ");
            fgets(inputName, MAX_NAME_LENGTH, stdin);
            if (strchr(inputName, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputName[strcspn(inputName, "\n")] = '\0';

            if (!isValidStringNAME(inputName))
            {
                printf("NAME 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            strcpy(users[index].NAME, inputName);
            saveUsers();
            break;
        }

        case 3:
        {
            char inputPassword[MAX_PASSWORD_LENGTH];
            printf("NEW PASSWORD(3-20位字母和数字): ");
            fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);
            if (strchr(inputPassword, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputPassword[strcspn(inputPassword, "\n")] = '\0';

            if (!isValidStringPASSWORD(inputPassword))
            {
                printf("PASSWORD 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            strcpy(users[index].PASSWORD, inputPassword);
            saveUsers();
            break;
        }
        case 4:
        {
            char inputPhone[MAX_PHONE_LENGTH];
            printf("NEW PHONE(11数字): ");
            fgets(inputPhone, MAX_PHONE_LENGTH, stdin);
            if (strchr(inputPhone, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputPhone[strcspn(inputPhone, "\n")] = '\0';

            if (!isValidStringPHONE(inputPhone))
            {
                printf("PHONE 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            strcpy(users[index].PHONE, inputPhone);
            saveUsers();
            break;
        }

        case 5:
        {
            int inputGender;
            char c;
            printf("NEW gender:\n");
            while (scanf("%d%c", &inputGender, &c) != 2 || c != '\n' || inputGender < 0 || inputGender > 2)
            {
                printf("无效输入 请输入一个有效的数字选项\n");
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }

            if (!isValidGender(inputGender))
            {
                printf("gender 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            users[index].gender = inputGender;
            saveUsers();
            break;
        }

        case 6:
        {
            int inputAge;
            char c;
            printf("NEW age(0-150): ");
            while (scanf("%d%c", &inputAge, &c) != 2 || c != '\n' || inputAge < 0 || inputAge > 150)
            {
                printf("无效输入 请输入一个有效的数字选项\n");
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }

            if (!isValidAge(inputAge))
            {
                printf("age 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            users[index].age = inputAge;
            saveUsers();
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

void searchUser()
{
    system("cls");
    printf("-----查询用户-----");
    if (usersCount == 0)
    {
        printf("暂无用户\n");
        pressEnterToContinue();
        return;
    }

    char inputUUID[MAX_UUID_LENGTH];
    printf("UUID(3-20位字母和数字): ");
    fgets(inputUUID, MAX_UUID_LENGTH, stdin);
    if (strchr(inputUUID, '\n') == NULL)
    {
        clearInputBuffer();
    }
    inputUUID[strcspn(inputUUID, "\n")] = '\0';
    int index = findUserIndexByUUID(inputUUID);
    if (index == -1)
    {
        printf("该用户不存在\n");
        pressEnterToContinue();
        return;
    }

    printf("UUID: %s\n", users[index].UUID);
    printf("NAME: %s\n", users[index].NAME);
    printf("PASSWORD: %s\n", users[index].PASSWORD);
    printf("PHONE: %s\n", users[index].PHONE);
    printf("gender: %d\n", users[index].gender);
    printf("age: %d\n", users[index].age);

    pressEnterToContinue();
}

void addFlight()
{
    system("cls");
    printf("-----增加航班-----");
    if (flightsCount >= MAX_FLIGHT_NUMBER)
    {
        printf("航班数量已达上限\n");
    }

    FLIGHT f = {0};
    char c;
    printf("CODE(3-20位字母和数字): ");
    fgets(f.CODE, MAX_CODE_LENGTH, stdin);
    if (strchr(f.CODE, '\n') == NULL)
    {
        clearInputBuffer();
    }

    if (!isValidStringCode(f.CODE))
    {
        printf("CODE 不符合规范\n");
        pressEnterToContinue();
        return;
    }
    if (findFlightIndexByCode(f.CODE) >= 0)
    {
        printf("该航班编号已存在\n");
        pressEnterToContinue();
        return;
    }
    f.CODE[strcspn(f.CODE, "\n")] = '\0';

    printf("MODEL(2-30位字母与数字): ");
    fgets(f.MODEL, MAX_NAME_LENGTH, stdin);
    if (strchr(f.MODEL, '\n') == NULL)
    {
        clearInputBuffer();
    }
    if (!isValidStringModel(f.MODEL))
    {
        printf("MODEL 不符合规范\n");
        pressEnterToContinue();
        return;
    }
    f.MODEL[strcspn(f.MODEL, "\n")] = '\0';

    printf("COMPANY(2-10个汉字): ");
    fgets(f.COMPANY, MAX_NAME_LENGTH, stdin);
    if (strchr(f.COMPANY, '\n') == NULL)
    {
        clearInputBuffer();
    }
    if (!isValidStringCompany(f.COMPANY))
    {
        printf("COMPANY 不符合规范\n");
        pressEnterToContinue();
        return;
    }
    f.COMPANY[strcspn(f.COMPANY, "\n")] = '\0';

    printf("DATE(YYYY-MM-DD): ");
    fgets(f.date, MAX_DATE_LENGTH, stdin);
    if (strchr(f.date, '\n') == NULL)
    {
        clearInputBuffer();
    }
    if (!isValidStringDate(f.date))
    {
        printf("DATE 不符合规范\n");
        pressEnterToContinue();
        return;
    }
    f.date[strcspn(f.date, "\n")] = '\0';

    char inputTime[MAX_TIME_LENGTH];
    int hour, minute;
    printf("TIME(HH:MM): ");
    fgets(inputTime, MAX_TIME_LENGTH, stdin);
    if (strchr(inputTime, '\n') == NULL)
    {
        clearInputBuffer();
    }
    if (!isValidStringTime(inputTime))
    {
        printf("TIME 不符合规范\n");
        pressEnterToContinue();
        return;
    }
    sscanf(inputTime, "%d:%d", &hour, &minute);
    f.time = dateTotime(f.date, hour, minute);

    printf("DURATION(MM)(总计分钟): ");
    while (scanf("%d%c", &minute, &c) != 2 || c != '\n' || minute < 0 || minute > 1440)
    {
        printf("无效输入 请输入一个有效的数字选项\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    f.duration = minute * 60;

    printf("GATE(2-30个字母): ");
    fgets(f.GATE, MAX_NAME_LENGTH, stdin);
    if (strchr(f.GATE, '\n') == NULL)
    {
        clearInputBuffer();
    }
    if (!isValidStringGate(f.GATE))
    {
        printf("GATE 不符合规范\n");
        pressEnterToContinue();
        return;
    }
    f.GATE[strcspn(f.GATE, "\n")] = '\0';

    printf("STARTING(2-10个汉字): ");
    fgets(f.STARTING, MAX_NAME_LENGTH, stdin);
    if (strchr(f.STARTING, '\n') == NULL)
    {
        clearInputBuffer();
    }
    if (!isValidStringStarting(f.STARTING))
    {
        printf("STARTING 不符合规范\n");
        pressEnterToContinue();
        return;
    }
    f.STARTING[strcspn(f.STARTING, "\n")] = '\0';

    printf("DESTINATION(2-10个汉字): ");
    fgets(f.DESTINATION, MAX_NAME_LENGTH, stdin);
    if (strchr(f.DESTINATION, '\n') == NULL)
    {
        clearInputBuffer();
    }
    if (!isValidStringDestination(f.DESTINATION))
    {
        printf("DESTINATION 不符合规范\n");
        pressEnterToContinue();
        return;
    }
    f.DESTINATION[strcspn(f.DESTINATION, "\n")] = '\0';

    printf("PRIZE(1-10000): ");
    while (scanf("%d%c", &f.prise, &c) != 2 || c != '\n' || f.prise < 0 || f.prise > 10000)
    {
        printf("无效输入 请输入一个有效的数字选项\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    printf("最大乘客数量(10-500)");
    while (scanf("%d%c", &f.num, &c) != 2 || c != '\n' || f.num < 10 || f.num > 500)
    {
        printf("无效输入 请输入一个有效的数字选项\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    flights[flightsCount++] = f;
    saveFlights();
}

void deleteflight()
{
    system("cls");
    printf("-----删除航班-----");
    if (flightsCount == 0)
    {
        printf("暂无航班\n");
        pressEnterToContinue();
        return;
    }

    char inputCode[MAX_CODE_LENGTH];
    printf("航班编号(3-20位字母和数字): ");
    fgets(inputCode, MAX_CODE_LENGTH, stdin);
    if (strchr(inputCode, '\n') == NULL)
    {
        clearInputBuffer();
    }
    inputCode[strcspn(inputCode, "\n")] = '\0';

    int index = findFlightIndexByCode(inputCode);
    if (index == -1)
    {
        printf("该航班不存在\n");
    }

    for (int i = index; i < flightsCount - 1; ++i)
    {
        flights[i] = flights[i + 1];
    }
    flightsCount--;
}

void modifyFlight()
{
    system("cls");
    printf("-----修改航班-----");
    if (flightsCount == 0)
    {
        printf("暂无航班\n");
        pressEnterToContinue();
        return;
    }

    char inputCode[MAX_CODE_LENGTH];
    printf("CODE(3-20位字母和数字): ");
    fgets(inputCode, MAX_CODE_LENGTH, stdin);
    if (strchr(inputCode, '\n') == NULL)
    {
        clearInputBuffer();
    }
    inputCode[strcspn(inputCode, "\n")] = '\0';

    int index = findFlightIndexByCode(inputCode);
    if (index == -1)
    {
        printf("该航班不存在\n");
        pressEnterToContinue();
        return;
    }

    int choice = 1;
    char c;
    while (choice)
    {
        system("cls");
        printf("请选择想要更改的内容\n");
        printf("1 CODE\n");
        printf("2 MODEL\n");
        printf("3 COMPANY\n");
        printf("4 DATE\n");
        printf("5 time\n");
        printf("6 duration\n");
        printf("7 GATE\n");
        printf("8 STARTING\n");
        printf("9 DESTINATION\n");
        printf("10 prise\n");
        printf("11 num\n");
        printf("0 退出");

        while (scanf("%d%c", &choice) != 1 || choice < 0 || choice > 11)
        {
            printf("无效输入 请输入一个有效的数字选项\n");
        }
        switch (choice)
        {
        case 1:
        {
            char inputCode[MAX_CODE_LENGTH];
            printf("NEW CODE(3-20位字母和数字): ");
            fgets(inputCode, MAX_CODE_LENGTH, stdin);
            if (strchr(inputCode, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputCode[strcspn(inputCode, "\n")] = '\0';

            if (!isValidStringCode(inputCode))
            {
                printf("CODE 不符合规范\n");
                pressEnterToContinue();
                break;
            }
            if (findFlightIndexByCode(inputCode) >= 0)
            {
                printf("该航班编号已存在\n");
                pressEnterToContinue();
                break;
            }

            strcpy(flights[index].CODE, inputCode);
            saveFlights();
            break;
        }

        case 2:
        {
            char inputModel[MAX_NAME_LENGTH];
            printf("NEW MODEL(2-30位字母与数字): ");
            fgets(inputModel, MAX_NAME_LENGTH, stdin);
            if (strchr(inputModel, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputModel[strcspn(inputModel, "\n")] = '\0';

            if (!isValidStringModel(inputModel))
            {
                printf("MODEL 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            strcpy(flights[index].MODEL, inputModel);
            saveFlights();
            break;
        }

        case 3:
        {
            char inputCompany[MAX_NAME_LENGTH];
            printf("NEW COMPANY(2-10个汉字): ");
            fgets(inputCompany, MAX_NAME_LENGTH, stdin);
            if (strchr(inputCompany, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputCompany[strcspn(inputCompany, "\n")] = '\0';

            if (!isValidStringCompany(inputCompany))
            {
                printf("COMPANY 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            strcpy(flights[index].COMPANY, inputCompany);
            saveFlights();
            break;
        }

        case 4:
        {
            char inputDate[MAX_DATE_LENGTH];
            printf("NEW DATE(YYYY-MM-DD): ");
            fgets(inputDate, MAX_DATE_LENGTH, stdin);
            if (strchr(inputDate, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputDate[strcspn(inputDate, "\n")] = '\0';

            if (!isValidStringDate(inputDate))
            {
                printf("DATE 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            strcpy(flights[index].date, inputDate);
            saveFlights();
            break;
        }

        case 5:
        {
            char inputTime[MAX_TIME_LENGTH];
            int hour, minute;
            printf("NEW TIME(HH:MM): ");
            fgets(inputTime, MAX_TIME_LENGTH, stdin);
            if (strchr(inputTime, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputTime[strcspn(inputTime, "\n")] = '\0';

            if (!isValidStringTime(inputTime))
            {
                printf("TIME 不符合规范\n");
            }

            sscanf(inputTime, "%d:%d", &hour, &minute);
            flights[index].time = dateTotime(flights[index].date, hour, minute);
            saveFlights();
            break;
        }

        case 6:
        {
            int minute;
            printf("NEW duration(MM)(总计分钟): ");
            while (scanf("%d%c", &minute, &c) != 2 || c != '\n' || minute < 0 || minute > 1440)
            {
                printf("无效输入 请输入一个有效的数字选项\n");
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }

            flights[index].duration = minute * 60;
            saveFlights();
            break;
        }

        case 7:
        {
            char inputGate[MAX_NAME_LENGTH];
            printf("NEW GATE(2-30个字母): ");
            fgets(inputGate, MAX_NAME_LENGTH, stdin);
            if (strchr(inputGate, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputGate[strcspn(inputGate, "\n")] = '\0';

            if (!isValidStringGate(inputGate))
            {
                printf("GATE 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            strcpy(flights[index].GATE, inputGate);
            saveFlights();
            break;
        }
        case 8:
        {
            char inputStarting[MAX_NAME_LENGTH];
            printf("NEW STARTING(2-10个汉字): ");
            fgets(inputStarting, MAX_NAME_LENGTH, stdin);
            if (strchr(inputStarting, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputStarting[strcspn(inputStarting, "\n")] = '\0';

            if (!isValidStringStarting(inputStarting))
            {
                printf("STARTING 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            strcpy(flights[index].STARTING, inputStarting);
            saveFlights();
            break;
        }

        case 9:
        {
            char inputDestination[MAX_NAME_LENGTH];
            printf("NEW DESTINATION(2-10个汉字): ");
            fgets(inputDestination, MAX_NAME_LENGTH, stdin);
            if (strchr(inputDestination, '\n') == NULL)
            {
                clearInputBuffer();
            }
            inputDestination[strcspn(inputDestination, "\n")] = '\0';

            if (!isValidStringDestination(inputDestination))
            {
                printf("DESTINATION 不符合规范\n");
                pressEnterToContinue();
                break;
            }

            strcpy(flights[index].DESTINATION, inputDestination);
            saveFlights();
            break;
        }

        case 10:
        {
            int prise;
            printf("NEW prise(1-10000): ");
            while (scanf("%d%c", &prise, &c) != 2 || c != '\n' || prise < 0 || prise > 10000)
            {
                printf("无效输入 请输入一个有效的数字选项\n");
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }

            flights[index].prise = prise;
            saveFlights();
            break;
        }

        case 11:
        {
            int num;
            printf("NEW num(10-500): ");
            while (scanf("%d%c", &num, &c) != 2 || c != '\n' || num < 10 || num > 500)
            {
                printf("无效输入 请输入一个有效的数字选项\n");
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }

            flights[index].num = num;
            saveFlights();
            break;
        }
        }
    }
}

int findUserIndexByUUID(char *inputUUID)
{
    for (int i = 0; i < usersCount; ++i)
    {
        if (strcmp(users[i].UUID, inputUUID) == 0)
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
        if (strcmp(admins[i].UUID, inputUUID) == 0)
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
        if (strcmp(enters[i].UUID, inputUUID) == 0)
        {
            return i;
        }
    }

    return -1;
}

bool isValidStringUUID(char *str)
{
    int len = strlen(str);
    if (len < 3)
    {
        printf("UUID 过短 至少为3位\n");
        return false;
    }
    if (len > 20)
    {
        printf("UUID 过长 最多为20位\n");
        return false;
    }

    for (int i = 0; i < len; ++i)
    {
        if (!(((str[i] >= 'a') && (str[i] <= 'z')) || ((str[i] >= 'A') && (str[i] <= 'Z')) || ((str[i] >= '0') && (str[i] <= '9'))))
        {
            printf("UUID 只能包含字母和数字\n");
            return false;
        }
    }

    return true;
}

bool isValidStringNAME(char *str)
{
    int len = strlen(str);
    if (len < 3)
    {
        printf("NAME 过短 至少为3位\n");
        return false;
    }
    if (len > 20)
    {
        printf("NAME 过长 最多为20位\n");
        return false;
    }

    return true;
}

bool isValidStringPASSWORD(char *str)
{
    int len = strlen(str);
    if (len < 3)
    {
        printf("PASSWORD 过短 至少为3位\n");
        return false;
    }
    if (len > 20)
    {
        printf("PASSWORD 过长 最多为20位\n");
        return false;
    }

    for (int i = 0; i < len; ++i)
    {
        if (!(((str[i] >= 'a') && (str[i] <= 'z')) || ((str[i] >= 'A') && (str[i] <= 'Z')) || ((str[i] >= '0') && (str[i] <= '9'))))
        {
            printf("PASSWORD 只能包含字母和数字\n");
            return false;
        }
    }

    return true;
}

bool isValidStringPHONE(char *str)
{
    int len = strlen(str);
    if (len < 11)
    {
        printf("PHONE 过短 只能为11位\n");
        return false;
    }
    if (len > 11)
    {
        printf("PHONE 过长 只能位11位\n");
        return false;
    }

    for (int i = 0; i < len; ++i)
    {
        if (!((str[i] >= '0') && (str[i] <= '9')))
        {
            printf("PHONE 只能为数字\n");
            return false;
        }
    }

    return true;
}

bool isValidGender(int gender)
{
    if (gender < 0)
    {
        return false;
    }
    else if (gender > 2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool isValidAge(int age)
{
    if (age < 0)
    {
        return false;
    }
    else if (age <= 150)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int findFlightIndexByCode(char *str)
{
    for (int i = 0; i < flightsCount; ++i)
    {
        if (strcmp(flights[i].CODE, str) == 0)
        {
            return i;
        }
    }

    return -1;
}

/**
 * printf("NEW CODE(3-20位字母和数字): ");
 */
bool isValidStringCode(char *str)
{
    int len = strlen(str);

    if (len < 3)
    {
        printf("CODE 过短 至少为3位\n");
        pressEnterToContinue();
        return false;
    }
    if (len > 20)
    {
        printf("CODE 过长 最多为20位\n");
        pressEnterToContinue();
        return false;
    }

    for (int i = 0; i < len; ++i)
    {
        if (!(((str[i] >= 'a') && (str[i] <= 'z')) || ((str[i] >= 'A') && (str[i] <= 'Z')) || ((str[i] >= '0') && (str[i] <= '9'))))
        {
            printf("CODE 只能包含字母和数字\n");
            pressEnterToContinue();
            return false;
        }
    }

    return true;
}

/**
 * printf("NEW MODEL(2-30位字母与数字): ");
 */
bool isValidStringModel(char *str)
{
    int len = strlen(str);

    if (len < 2)
    {
        printf("MODEL 过短 至少为2位\n");
        pressEnterToContinue();
        return false;
    }
    if (len > 30)
    {
        printf("MODEL 过长 最多为30位\n");
        pressEnterToContinue();
        return false;
    }

    for (int i = 0; i < len; ++i)
    {
        if (!(((str[i] >= 'a') && (str[i] <= 'z')) || ((str[i] >= 'A') && (str[i] <= 'Z')) || ((str[i] >= '0') && (str[i] <= '9'))))
        {
            printf("MODEL 只能包含字母和数字\n");
            pressEnterToContinue();
            return false;
        }
    }

    return true;
}

/**
 * printf("NEW COMPANY(2-10个汉字): ");
 */
bool isValidStringCompany(char *str)
{
    int len = strlen(str);

    if (len < 2)
    {
        printf("COMPANY 过短 至少为2位\n");
        pressEnterToContinue();
        return false;
    }
    if (len > 10)
    {
        printf("COMPANY 过长 最多为10位\n");
        pressEnterToContinue();
        return false;
    }

    for (int i = 0; i < len; ++i)
    {
        if (!((str[i] >= 0x4e00) && (str[i] <= 0x9fff)))
        {
            printf("COMPANY 只能包含汉字\n");
            pressEnterToContinue();
            return false;
        }
    }

    return true;
}

/**
 * printf("NEW DATE(YYYY-MM-DD): ");
 */
bool isValidStringDate(char *str)
{
    int year, month, day;

    if (sscanf(str, "%d-%d-%d", &year, &month, &day) != 3)
    {
        printf("日期格式错误: %s\n", str);
        pressEnterToContinue();
        return false;
    }
    if (year < 1900 || year > 2100)
    {
        printf("日期格式错误: %s\n", str);
        pressEnterToContinue();
        return false;
    }
    if (month < 1 || month > 12)
    {
        printf("日期格式错误: %s\n", str);
        pressEnterToContinue();
        return false;
    }
    if (day < 1 || day > 31)
    {
        printf("日期格式错误: %s\n", str);
        pressEnterToContinue();
        return false;
    }

    return true;
}

/**
 * printf("NEW TIME(HH:MM): ");
 */
bool isValidStringTime(char *str)
{
    int hour, minute;

    if (sscanf(str, "%d:%d", &hour, &minute) != 2)
    {
        printf("时间格式错误: %s\n", str);
        pressEnterToContinue();
        return false;
    }
    if (hour < 0 || hour > 23)
    {
        printf("时间格式错误: %s\n", str);
        pressEnterToContinue();
        return false;
    }
    if (minute < 0 || minute > 59)
    {
        printf("时间格式错误: %s\n", str);
        pressEnterToContinue();
        return false;
    }

    return true;
}

/**
 * printf("NEW GATE(2-30个字母): ");
 */
bool isValidStringGate(char *str)
{
    int len = strlen(str);

    if (len < 2)
    {
        printf("GATE 过短 至少为2位\n");
        pressEnterToContinue();
        return false;
    }
    if (len > 30)
    {
        printf("GATE 过长 最多为30位\n");
        pressEnterToContinue();
        return false;
    }
    for (int i = 0; i < len; ++i)
    {
        if (!(((str[i] >= 'a') && (str[i] <= 'z')) || ((str[i] >= 'A') && (str[i] <= 'Z'))))
        {
            printf("GATE 只能包含字母\n");
            pressEnterToContinue();
            return false;
        }
    }

    return true;
}

/**
 * printf("NEW STARTING(2-10个汉字): ");
 */
bool isValidStringStarting(char *str)
{
    int len = strlen(str);

    if (len < 2)
    {
        printf("STARTING 过短 至少为2位\n");
        pressEnterToContinue();
        return false;
    }
    if (len > 10)
    {
        printf("STARTING 过长 最多为10位\n");
        pressEnterToContinue();
        return false;
    }

    for (int i = 0; i < len; ++i)
    {
        if (!((str[i] >= 0x4e00) && (str[i] <= 0x9fff)))
        {
            printf("STARTING 只能包含汉字\n");
            pressEnterToContinue();
            return false;
        }
    }
    return true;
}

/**
 * printf("NEW DESTINATION(2-10个汉字): ");
 */
bool isValidStringDestination(char *str)
{
    int len = strlen(str);

    if (len < 2)
    {
        printf("DESTINATION 过短 至少为2位\n");
        pressEnterToContinue();
        return false;
    }
    if (len > 10)
    {
        printf("DESTINATION 过长 最多为10位\n");
        pressEnterToContinue();
        return false;
    }

    for (int i = 0; i < len; ++i)
    {
        if (!((str[i] >= 0x4e00) && (str[i] <= 0x9fff)))
        {
            printf("DESTINATION 只能包含汉字\n");
            pressEnterToContinue();
            return false;
        }
    }
    return true;
}

int visualWidth(const wchar_t *str)
{
    int width = 0;
    while (*str)
    {
        if (*str >= 0x4e00 && *str <= 0x9fff) // 中文基本区
            width += 2;
        else
            width += 1;
        str++;
    }
    return width;
}

void wprintAlign(const wchar_t *str, int total_width)
{
    int width = visualWidth(str);
    wprintf(L"%ls", str);
    for (int i = 0; i < total_width - width; ++i)
    {
        wprintf(L" ");
    }
}

time_t dateTotime(const char *str, int hour, int minute)
{
    int year, month, day;
    if (sscanf(str, "%d-%d-%d", &year, &month, &day) != 3)
    {
        fprintf(stderr, "日期格式错误: %s\n", str);
        return 0;
    }
    return timeToTimeT(year, month, day, hour, minute);
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

void clearInputBuffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

/**
 * 按回车键继续
 */
void pressEnterToContinue()
{
    printf("\n按回车键继续...");
    while (getchar() != '\n')
        ;
}
