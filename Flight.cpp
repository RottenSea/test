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
 *
 * 只有一个用户管理员/一个航班管理员/一个航司管理员
 *
 * 航司就不改了 原本是航司只能管理自家的航班 现在只实现了能够查询自家的航班 其他功能和航班管理员差不多
 *
 * 没有考虑在航班时间结束后修改用户已订购航班
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

// 定义常量
#define MAX_USER_NUMBER 100
#define MAX_ADMINISTRATOR_NUMBER 100
#define MAX_ENTERPRISE_NUMBER 100
#define MAX_USER_FLIGHT 10
#define MAX_FLIGHT_NUMBER 100

// 定义最大长度
#define MAX_UUID_LENGTH 21
#define MAX_NAME_LENGTH 31
#define MAX_PASSWORD_LENGTH 21
#define MAX_PHONE_LENGTH 12
#define MAX_CODE_LENGTH 21
#define MAX_DATE_LENGTH 11
#define MAX_TIME_LENGTH 6

// 定义文件名
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

// 定义查询航班
void listFlight(const char *name);
char *departureTime(int index);
char *arrivalTime(int index);
int countFlightRemain(int index);
char *calStatus(int index);
void bookFlight(int index);
void listUserBookedFlights(int index);
void cancleFlight(int index);

// 定义用户管理
void addUser();
void deleteUser();
void modifyUser();
void searchUser();

// 定义航班管理
void addFlight();
void deleteflight();
void modifyFlight();

// 定义查找用户函数
int findUserIndexByUUID(char *inputUUID);
int findAdminIndexByUUID(char *inputUUID);
int findEnterIndexByUUID(char *inputUUID);

// 定义用户验证函数
bool isValidStringUUID(char *str);
bool isValidStringNAME(char *str);
bool isValidStringPASSWORD(char *str);
bool isValidStringPHONE(char *str);
bool isValidGender(int gender);
bool isValidAge(int age);

// 定义航班管理函数
int findFlightIndexByCode(char *str);

// 定义航班验证函数
bool isValidStringCode(char *str);
bool isValidStringModel(char *str);
bool isValidStringCompany(char *str);
bool isValidStringDate(char *str);
bool isValidStringTime(char *str);
bool isValidStringGate(char *str);
bool isValidStringStarting(char *str);
bool isValidStringDestination(char *str);

// 定义工具函数
int wcDisplayWidth(wchar_t wc);
int wcswidth(const wchar_t *wstr);
int visualWidth(const char *str);
void printAlign(const char *str, int totalWidth);
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
    char flights[MAX_USER_FLIGHT][MAX_CODE_LENGTH + MAX_DATE_LENGTH];
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
    int praise;
    int num;
    int curr;
} FLIGHT;
FLIGHT flights[MAX_FLIGHT_NUMBER];
int flightsCount = 0;

int main()
{
    setlocale(LC_ALL, ""); // 启用本地环境支持中文

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
        printf("请选择: ");

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
    strcpy(u1.flights[0], "CZ6546@2025-06-18");
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
    f1.praise = 1000;
    f1.num = 200;
    f1.curr = 100;
    flights[flightsCount++] = f1;

    saveUsers();
    saveFlights();
}
/**
 * 加载用户信息
 */
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

/**
 * 保存用户信息
 */
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

/**
 * 加载航班信息
 */
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

/**
 * 保存航班信息
 */
void saveFlights()
{
    FILE *fp = fopen(FLIGHTS_FILE, "wb");
    if (fp == NULL)
    {
        printf("保存航班时文件打开失败！\n");
        return;
    }

    fwrite(&flightsCount, sizeof(int), 1, fp);
    fwrite(flights, sizeof(FLIGHT), flightsCount, fp);

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

    while (1)
    {
        printf("UUID(3-20位字母和数字): ");
        fgets(u.UUID, MAX_UUID_LENGTH, stdin);

        // 清除多余输入
        if (strchr(u.UUID, '\n') == NULL)
        {
            clearInputBuffer();
        }
        u.UUID[strcspn(u.UUID, "\n")] = '\0'; // 去除换行符

        // 检查格式合法性
        if (!isValidStringUUID(u.UUID))
        {
            printf("UUID 不符合规范 请重新输入\n\n");
            continue;
        }

        // 检查是否已存在
        if ((findUserIndexByUUID(u.UUID) >= 0) ||
            (findAdminIndexByUUID(u.UUID) >= 0) ||
            (findEnterIndexByUUID(u.UUID) >= 0))
        {
            printf("该用户名已存在\n\n");
            pressEnterToContinue();
            return;
        }

        // 合法且未存在，退出循环
        break;
    }

    while (1)
    {
        printf("NAME(3-20个字符): ");
        fgets(u.NAME, MAX_NAME_LENGTH, stdin);

        if (strchr(u.NAME, '\n') == NULL)
        {
            clearInputBuffer();
        }
        u.NAME[strcspn(u.NAME, "\n")] = '\0';

        if (!isValidStringNAME(u.NAME))
        {
            printf("NAME 不符合规范 请重新输入\n\n");
            continue;
        }

        break;
    }

    while (1)
    {
        printf("PASSWORD(3-20位字母和数字): ");
        fgets(u.PASSWORD, MAX_PASSWORD_LENGTH, stdin);

        if (strchr(u.PASSWORD, '\n') == NULL)
        {
            clearInputBuffer();
        }
        u.PASSWORD[strcspn(u.PASSWORD, "\n")] = '\0';

        if (!isValidStringPASSWORD(u.PASSWORD))
        {
            printf("PASSWORD 不符合规范 请重新输入\n\n");
            continue;
        }

        break;
    }

    while (1)
    {
        printf("PHONE(3-20位字母和数字): ");
        fgets(u.PHONE, MAX_PHONE_LENGTH, stdin);

        if (strchr(u.PHONE, '\n') == NULL)
        {
            clearInputBuffer();
        }
        u.PHONE[strcspn(u.PHONE, "\n")] = '\0';

        if (!isValidStringPHONE(u.PHONE))
        {
            printf("PHONE 不符合规范 请重新输入\n\n");
            continue;
        }

        break;
    }

    int choice;
    char c;
    printf("是否立即补充其他信息?\n");
    printf("0否 1是\n");
    printf("选择: ");
    while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice != 0 && choice != 1)
    {
        printf("无效输入 请输入一个有效的数字选项\n");
        clearInputBuffer();
        printf("选择: ");
    }

    if (choice == 1)
    {
        while (1)
        {
            printf("请选择性别:\n");
            printf("0 默认\n");
            printf("1 男\n");
            printf("2 女\n");
            printf("gender:");

            if (scanf("%d%c", &u.gender, &c) == 2 && c == '\n' && isValidGender(u.gender))
            {
                break;
            }
            printf("输入不符合规范 请重新输入\n");
        }

        while (1)
        {
            printf("请输入年龄(0 - 150):\n");
            printf("age(0-150):");

            if (scanf("%d%c", &u.age, &c) == 2 && c == '\n' && isValidAge(u.age))
            {
                break;
            }
            clearInputBuffer();
            printf("输入不符合规范\n");
        }
    }

    users[usersCount++] = u;
    printf("注册成功\n");
    pressEnterToContinue();
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
                    clearInputBuffer();
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
            fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);
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
                while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || (choice != 0 && choice != 1))
                {
                    printf("无效输入 请输入一个有效的数字选项\n");
                    clearInputBuffer();
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
                    clearInputBuffer();
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
        printf("1 查询全部航班\n");
        printf("2 订购航班\n");
        printf("3 查询已订航班\n");
        printf("4 退订航班\n");
        printf("0 注销并返回上级菜单\n");
        printf("-----------------\n");
        printf("请选择功能: ");

        if (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice < 0 || choice > 4)
        {
            printf("无效输入 请输入一个有效的数字选项\n");
            pressEnterToContinue();
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
            listUserBookedFlights(index);
            break;
        case 4:
            cancleFlight(index);
            break;
        case 0:
            printf("已注销\n");
            pressEnterToContinue();
            return;
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

            if (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice < 0 || choice > 4)
            {
                printf("无效输入 请输入一个有效的数字选项\n");
                pressEnterToContinue();
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

            if (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice < 0 || choice > 4)
            {
                printf("无效输入 请输入一个有效的数字选项\n");
                pressEnterToContinue();
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
        printf("请选择功能: ");

        if (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice < 0 || choice > 4)
        {
            printf("无效输入 请输入一个有效的数字选项\n");
            pressEnterToContinue();
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
        }
    } while (choice != 0);
}

void listFlight(const char *name)
{
    system("cls");
    printf("当前航班数量: %d\n", flightsCount);
    printf("----------航班列表----------\n");
    printAlign("航班号", 10);
    printAlign("机型", 10);
    printAlign("承办公司", 20);
    printAlign("日期", 12);
    printAlign("出发时间", 12);
    printAlign("到达时间", 12);
    printAlign("始发地", 20);
    printAlign("目的地", 20);
    printAlign("价格", 8);
    printAlign("剩余", 8);
    printAlign("状态", 8);
    printf("\n");

    char tempStr[64];
    if (strlen(name) == 0)
    {
        for (int i = 0; i < flightsCount; ++i)
        {
            printAlign(flights[i].CODE, 10);
            printAlign(flights[i].MODEL, 10);
            printAlign(flights[i].COMPANY, 20);
            printAlign(flights[i].date, 12);
            printAlign(departureTime(i), 12);
            printAlign(arrivalTime(i), 12);
            printAlign(flights[i].STARTING, 20);
            printAlign(flights[i].DESTINATION, 20);
            char priceStr[16], remainStr[16];
            sprintf(priceStr, "%d", flights[i].praise);
            sprintf(remainStr, "%d", countFlightRemain(i));
            printAlign(priceStr, 8);
            printAlign(remainStr, 8);
            printAlign(calStatus(i), 8);
            printf("\n");
        }
    }
    else
    {
        for (int i = 0; i < flightsCount; ++i)
        {
            if (strcmp(flights[i].COMPANY, name) == 0)
            {
                printAlign(flights[i].CODE, 10);
                printAlign(flights[i].MODEL, 10);
                printAlign(flights[i].COMPANY, 20);
                printAlign(flights[i].date, 12);
                printAlign(departureTime(i), 12);
                printAlign(arrivalTime(i), 12);
                printAlign(flights[i].STARTING, 20);
                printAlign(flights[i].DESTINATION, 20);
                char priceStr[16], remainStr[16];
                sprintf(priceStr, "%d", flights[i].praise);
                sprintf(remainStr, "%d", countFlightRemain(i));
                printAlign(priceStr, 8);
                printAlign(remainStr, 8);
                printAlign(calStatus(i), 8);
                printf("\n");
            }
        }
    }

    pressEnterToContinue();
}

char *departureTime(int index)
{
    static char buffer[6];
    struct tm *timeinfo = localtime(&(flights[index].time));
    sprintf(buffer, "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
    return buffer;
}

char *arrivalTime(int index)
{
    static char buffer[6];
    time_t arrivalTime = flights[index].time + flights[index].duration;
    struct tm *timeinfo = localtime(&arrivalTime);
    sprintf(buffer, "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
    return buffer;
}

int countFlightRemain(int index)
{
    return (flights[index].num - flights[index].curr);
}

char *calStatus(int index)
{
    static char buffer[10];
    time_t curr = time(NULL);
    if (curr < flights[index].time)
    {
        strcpy(buffer, "未起飞");
    }
    else if ((curr >= flights[index].time) && (curr < flights[index].time + flights[index].duration))
    {
        strcpy(buffer, "飞行中");
    }
    else
    {
        strcpy(buffer, "已到达");
    }

    return buffer;
}

void bookFlight(int index)
{
    if (users[index].count >= MAX_USER_FLIGHT)
    {
        printf("超过可订购航班数量上限\n");
        pressEnterToContinue();
        return;
    }

    // 展示当前航班
    printf("当前航班数量: %d\n", flightsCount);
    printf("----------航班列表----------\n");
    printAlign("航班号", MAX_CODE_LENGTH);
    printf("日期", MAX_DATE_LENGTH);
    printf("\n");
    for (int i = 0; i < flightsCount; ++i)
    {
        printAlign(flights[i].CODE, MAX_CODE_LENGTH);
        printf(flights[i].date, MAX_DATE_LENGTH);
        printf("\n");
    }

    char inputCode[MAX_CODE_LENGTH];
    int findFlightIndex[MAX_FLIGHT_NUMBER] = {0};
    int p = 0;

    // 循环输入航班号直到找到结果
    while (1)
    {
        printf("请输入你想要订购的航班号(CODE): ");
        fgets(inputCode, sizeof(inputCode), stdin);
        if (strchr(inputCode, '\n') == NULL)
        {
            clearInputBuffer();
        }
        inputCode[strcspn(inputCode, "\n")] = '\0';

        p = 0;
        for (int i = 0; i < flightsCount; ++i)
        {
            if (strcmp(flights[i].CODE, inputCode) == 0)
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
        else
        {
            break;
        }
    }

    printf("共找到 %d 个航班号为 %s 的航班\n", p, inputCode);

    // 打印表头
    printAlign("序号", 6);
    printAlign("日期", MAX_DATE_LENGTH);
    printAlign("起点", MAX_NAME_LENGTH);
    printAlign("终点", MAX_NAME_LENGTH);
    printAlign("价格(元)", 10);
    printf("\n");

    // 打印分隔线
    printAlign("----", 6);
    printAlign("--------", MAX_DATE_LENGTH);
    printAlign("--------", MAX_NAME_LENGTH);
    printAlign("--------", MAX_NAME_LENGTH);
    printAlign("--------", 10);
    printf("\n");

    for (int i = 0; i < p; ++i)
    {
        int index = findFlightIndex[i];

        char numStr[8];
        snprintf(numStr, sizeof(numStr), "%d", i + 1);
        char priceStr[16];
        snprintf(priceStr, sizeof(priceStr), "%d", flights[index].praise);

        printAlign(numStr, 6);
        printAlign(flights[index].date, MAX_DATE_LENGTH);
        printAlign(flights[index].STARTING, MAX_NAME_LENGTH);
        printAlign(flights[index].DESTINATION, MAX_NAME_LENGTH);
        printAlign(priceStr, 10);
        printf("\n");
    }

    int inputBookFlight = 0;
    char c;

    printf("请输入想要订购的航班序号(1 - %d): ", p);
    while (scanf("%d%c", &inputBookFlight, &c) != 2 || c != '\n' || (inputBookFlight < 1 || inputBookFlight > p))
    {
        printf("输入错误 请输入一个有效的数字序号\n\n");
        printf("请输入想要订购的航班序号(1 - %d): ", p);

        clearInputBuffer();
    }

    int selected = findFlightIndex[inputBookFlight - 1];
    printf("请支付金额: %d元\n", flights[selected].praise);

    int payRes = 0;
    printf("是否成功支付(0失败 1成功): ");
    while (scanf("%d%c", &payRes, &c) != 2 || c != '\n' || (payRes != 0 && payRes != 1))
    {
        printf("输入错误 请输入一个有效的数字选项\n\n");
        printf("是否成功支付(0失败 1成功): ");
        clearInputBuffer();
    }
    if (!payRes)
    {
        printf("支付失败 预订未完成\n");
        pressEnterToContinue();
        return;
    }

    // 保存为 航班号@日期
    char flightRecord[MAX_CODE_LENGTH + MAX_DATE_LENGTH];
    snprintf(flightRecord, sizeof(flightRecord), "%s@%s", flights[selected].CODE, flights[selected].date);
    strcpy(users[index].flights[users[index].count++], flightRecord);

    printf("预订成功\n");
    saveUsers();
    pressEnterToContinue();
}

void listUserBookedFlights(int index)
{
    if (users[index].count == 0)
    {
        printf("还未订购任何航班\n");
        pressEnterToContinue();
        return;
    }

    printf("已订购的航班如下\n");

    // 打印表头
    printAlign("序号", 6);
    printAlign("航班号", MAX_CODE_LENGTH);
    printAlign("出发日期", MAX_DATE_LENGTH);
    printf("\n");

    // 打印分隔线
    printAlign("----", 6);
    printAlign("--------", MAX_CODE_LENGTH);
    printAlign("--------", MAX_DATE_LENGTH);
    printf("\n");

    for (int i = 0; i < users[index].count; ++i)
    {
        char *record = users[index].flights[i];
        char code[MAX_CODE_LENGTH];
        char date[MAX_DATE_LENGTH];

        // 用 @ 分割航班号和日期
        char *atPos = strchr(record, '@');
        if (!atPos)
        {
            // 数据格式错误，跳过此项
            continue;
        }

        size_t codeLen = atPos - record;
        if (codeLen >= MAX_CODE_LENGTH)
            codeLen = MAX_CODE_LENGTH - 1;
        strncpy(code, record, codeLen);
        code[codeLen] = '\0';

        strncpy(date, atPos + 1, MAX_DATE_LENGTH - 1);
        date[MAX_DATE_LENGTH - 1] = '\0';

        // 打印每一行
        char numStr[8];
        snprintf(numStr, sizeof(numStr), "%d", i + 1);
        printAlign(numStr, 6);
        printAlign(code, MAX_CODE_LENGTH);
        printAlign(date, MAX_DATE_LENGTH);
        printf("\n");
    }

    pressEnterToContinue();
}

void cancleFlight(int index)
{
    if (users[index].count == 0)
    {
        printf("您当前没有已订购的航班，无法取消。\n");
        pressEnterToContinue();
        return;
    }

    printf("已订购的航班\n");

    // 表头
    printAlign("序号", 6);
    printAlign("航班号", MAX_CODE_LENGTH);
    printAlign("出发日期", MAX_DATE_LENGTH);
    printf("\n");

    // 分隔线
    printAlign("----", 6);
    printAlign("--------", MAX_CODE_LENGTH);
    printAlign("--------", MAX_DATE_LENGTH);
    printf("\n");

    // 显示用户所有航班记录
    for (int i = 0; i < users[index].count; ++i)
    {
        char *record = users[index].flights[i];
        char code[MAX_CODE_LENGTH];
        char date[MAX_DATE_LENGTH];

        char *atPos = strchr(record, '@');
        if (!atPos)
            continue;

        size_t codeLen = atPos - record;
        if (codeLen >= MAX_CODE_LENGTH)
            codeLen = MAX_CODE_LENGTH - 1;
        strncpy(code, record, codeLen);
        code[codeLen] = '\0';

        strncpy(date, atPos + 1, MAX_DATE_LENGTH - 1);
        date[MAX_DATE_LENGTH - 1] = '\0';

        char numStr[8];
        snprintf(numStr, sizeof(numStr), "%d", i + 1);
        printAlign(numStr, 6);
        printAlign(code, MAX_CODE_LENGTH);
        printAlign(date, MAX_DATE_LENGTH);
        printf("\n");
    }

    // 获取用户要取消的航班序号
    int choice = 0;
    char c;
    printf("请输入要取消的航班序号(1 - %d): ", users[index].count);
    while (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice < 1 || choice > users[index].count)
    {
        printf("输入错误，请重新输入有效的航班序号(1 - %d): ", users[index].count);
        clearInputBuffer();
    }

    // 删除选中的航班记录
    int pos = choice - 1;
    for (int i = pos; i < users[index].count - 1; ++i)
    {
        strcpy(users[index].flights[i], users[index].flights[i + 1]);
    }
    users[index].count--;

    printf("航班取消成功！\n");
    saveUsers();
    pressEnterToContinue();
}

void addUser()
{
    system("cls");
    printf("-----增加用户-----\n");
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
        clearInputBuffer();
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
            clearInputBuffer();
        }

        while (1)
        {
            printf("age(0-150):");

            if (scanf("%d%c", &u.age, &c) == 2 && c == '\n' && isValidAge(u.age))
            {
                break;
            }
            printf("输入不符合规范\n");
            clearInputBuffer();
        }
    }

    users[usersCount++] = u;
    printf("用户添加成功\n");
    pressEnterToContinue();
    saveUsers();
}

void deleteUser()
{
    system("cls");
    printf("-----删除用户-----\n");
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
    if (!isValidStringUUID(inputUUID))
    {
        printf("UUID 不符合规范\n");
        pressEnterToContinue();
        return;
    }

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
    printf("用户删除成功\n");
    pressEnterToContinue();
}

void modifyUser()
{
    system("cls");
    printf("-----修改用户-----\n");
    if (usersCount == 0)
    {
        printf("暂无用户\n");
        pressEnterToContinue();
        return;
    }

    char inputUUID[MAX_UUID_LENGTH];
    printf("UUID(3-20位字母和数字): ");
    fgets(inputUUID, sizeof(inputUUID), stdin);
    if (strchr(inputUUID, '\n') == NULL)
        clearInputBuffer();
    inputUUID[strcspn(inputUUID, "\n")] = '\0';

    if (!isValidStringUUID(inputUUID))
    {
        printf("UUID 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    int index = findUserIndexByUUID(inputUUID);
    if (index == -1)
    {
        printf("该用户不存在\n");
        pressEnterToContinue();
        return;
    }

    int choice;
    char c;

    while (1)
    {
        system("cls");
        printf("-----修改用户信息[%s]-----\n", users[index].NAME);
        printf("1 UUID\n");
        printf("2 NAME\n");
        printf("3 PASSWORD\n");
        printf("4 PHONE\n");
        printf("5 Gender\n");
        printf("6 Age\n");
        printf("0 退出修改\n");
        printf("请输入选项: ");

        if (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice < 0 || choice > 6)
        {
            printf("无效输入 请输入 0-6 的数字\n");
            pressEnterToContinue();
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            char newUUID[MAX_UUID_LENGTH];
            printf("新 UUID(3-20位字母和数字): ");
            fgets(newUUID, sizeof(newUUID), stdin);
            if (strchr(newUUID, '\n') == NULL)
            {
                clearInputBuffer();
            }
            newUUID[strcspn(newUUID, "\n")] = '\0';

            if (!isValidStringUUID(newUUID))
            {
                printf("UUID 不符合规范\n");
                break;
            }

            if (findUserIndexByUUID(newUUID) >= 0 || findAdminIndexByUUID(newUUID) >= 0 || findEnterIndexByUUID(newUUID) >= 0)
            {
                printf("UUID 已存在\n");
                break;
            }

            strcpy(users[index].UUID, newUUID);
            saveUsers();
            printf("UUID 修改成功\n");
            break;
        }

        case 2:
        {
            char newName[MAX_NAME_LENGTH];
            printf("新名称(3-20字符): ");
            fgets(newName, sizeof(newName), stdin);
            if (strchr(newName, '\n') == NULL)
            {
                clearInputBuffer();
            }
            newName[strcspn(newName, "\n")] = '\0';

            if (!isValidStringNAME(newName))
            {
                printf("名称不符合规范\n");
                break;
            }

            strcpy(users[index].NAME, newName);
            saveUsers();
            printf("名称修改成功\n");
            break;
        }

        case 3:
        {
            char newPassword[MAX_PASSWORD_LENGTH];
            printf("新密码(3-20位字母和数字): ");
            fgets(newPassword, sizeof(newPassword), stdin);
            if (strchr(newPassword, '\n') == NULL)
            {
                clearInputBuffer();
            }
            newPassword[strcspn(newPassword, "\n")] = '\0';

            if (!isValidStringPASSWORD(newPassword))
            {
                printf("密码不符合规范\n");
                break;
            }

            strcpy(users[index].PASSWORD, newPassword);
            saveUsers();
            printf("密码修改成功\n");
            break;
        }

        case 4:
        {
            char newPhone[MAX_PHONE_LENGTH];
            printf("新手机号(11位数字): ");
            fgets(newPhone, sizeof(newPhone), stdin);
            if (strchr(newPhone, '\n') == NULL)
            {
                clearInputBuffer();
            }
            newPhone[strcspn(newPhone, "\n")] = '\0';

            if (!isValidStringPHONE(newPhone))
            {
                printf("手机号不符合规范\n");
                break;
            }

            strcpy(users[index].PHONE, newPhone);
            saveUsers();
            printf("手机号修改成功\n");
            break;
        }

        case 5:
        {
            int gender;
            printf("新性别(0未知 1男 2女): ");
            while (scanf("%d%c", &gender, &c) != 2 || c != '\n' || gender < 0 || gender > 2)
            {
                printf("请输入有效的数字(0-2): ");
                clearInputBuffer();
            }

            if (!isValidGender(gender))
            {
                printf("性别不符合规范。\n");
                break;
            }

            users[index].gender = gender;
            saveUsers();
            printf("性别修改成功\n");
            break;
        }

        case 6:
        {
            int age;
            printf("新年龄(0-150): ");
            while (scanf("%d%c", &age, &c) != 2 || c != '\n' || age < 0 || age > 150)
            {
                printf("请输入有效的年龄(0-150): ");
                clearInputBuffer();
            }

            if (!isValidAge(age))
            {
                printf("年龄不符合规范\n");
                break;
            }

            users[index].age = age;
            saveUsers();
            printf("年龄修改成功\n");
            break;
        }

        case 0:
        {
            printf("退出用户修改\n");
            pressEnterToContinue();
            return;
        }

        default:
        {
            break;
        }
        }

        pressEnterToContinue();
    }
}

void searchUser()
{
    system("cls");
    printf("-----查询用户-----\n");
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
    printf("-----增加航班-----\n");

    if (flightsCount >= MAX_FLIGHT_NUMBER)
    {
        printf("航班数量已达上限 无法继续添加\n");
        pressEnterToContinue();
        return;
    }

    FLIGHT f = {0}; // 初始化所有字段
    char c;

    // 航班编号
    printf("CODE(3-20位字母和数字): ");
    fgets(f.CODE, MAX_CODE_LENGTH, stdin);
    if (strchr(f.CODE, '\n') == NULL)
    {
        clearInputBuffer();
    }
    f.CODE[strcspn(f.CODE, "\n")] = '\0';
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

    // 机型
    printf("MODEL(2-30位字母与数字): ");
    fgets(f.MODEL, MAX_NAME_LENGTH, stdin);
    if (strchr(f.MODEL, '\n') == NULL)
    {
        clearInputBuffer();
    }
    f.MODEL[strcspn(f.MODEL, "\n")] = '\0';
    if (!isValidStringModel(f.MODEL))
    {
        printf("MODEL 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    // 公司
    printf("COMPANY(2-10个汉字): ");
    fgets(f.COMPANY, MAX_NAME_LENGTH, stdin);
    if (strchr(f.COMPANY, '\n') == NULL)
    {
        clearInputBuffer();
    }
    f.COMPANY[strcspn(f.COMPANY, "\n")] = '\0';
    if (!isValidStringCompany(f.COMPANY))
    {
        printf("COMPANY 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    // 出发日期
    printf("DATE(YYYY-MM-DD): ");
    fgets(f.date, MAX_DATE_LENGTH, stdin);
    if (strchr(f.date, '\n') == NULL)
    {
        clearInputBuffer();
    }
    f.date[strcspn(f.date, "\n")] = '\0';
    if (!isValidStringDate(f.date))
    {
        printf("DATE 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    // 出发时间
    char inputTime[MAX_TIME_LENGTH];
    int hour, minute;
    printf("TIME(HH:MM): ");
    fgets(inputTime, MAX_TIME_LENGTH, stdin);
    if (strchr(inputTime, '\n') == NULL)
    {
        clearInputBuffer();
    }
    inputTime[strcspn(inputTime, "\n")] = '\0';
    if (!isValidStringTime(inputTime))
    {
        printf("TIME 不符合规范\n");
        pressEnterToContinue();
        return;
    }
    sscanf(inputTime, "%d:%d", &hour, &minute);
    f.time = dateTotime(f.date, hour, minute);

    // 航程时长(分钟)
    printf("DURATION(MM)(总计分钟): ");
    while (scanf("%d%c", &minute, &c) != 2 || c != '\n' || minute < 0 || minute > 1440)
    {
        printf("无效输入 请输入 0~1440 范围的分钟数: ");
        clearInputBuffer();
    }
    f.duration = minute * 60;

    // 登机口
    printf("GATE(2-30位字母与数字): ");
    fgets(f.GATE, MAX_NAME_LENGTH, stdin);
    if (strchr(f.GATE, '\n') == NULL)
    {
        clearInputBuffer();
    }
    f.GATE[strcspn(f.GATE, "\n")] = '\0';
    if (!isValidStringGate(f.GATE))
    {
        printf("GATE 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    // 出发地
    printf("STARTING(2-10个汉字): ");
    fgets(f.STARTING, MAX_NAME_LENGTH, stdin);
    if (strchr(f.STARTING, '\n') == NULL)
    {
        clearInputBuffer();
    }
    f.STARTING[strcspn(f.STARTING, "\n")] = '\0';
    if (!isValidStringStarting(f.STARTING))
    {
        printf("STARTING 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    // 目的地
    printf("DESTINATION(2-10个汉字): ");
    fgets(f.DESTINATION, MAX_NAME_LENGTH, stdin);
    if (strchr(f.DESTINATION, '\n') == NULL)
    {
        clearInputBuffer();
    }
    f.DESTINATION[strcspn(f.DESTINATION, "\n")] = '\0';
    if (!isValidStringDestination(f.DESTINATION))
    {
        printf("DESTINATION 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    // 票价
    printf("PRICE(1-10000): ");
    while (scanf("%d%c", &f.praise, &c) != 2 || c != '\n' || f.praise < 1 || f.praise > 10000)
    {
        printf("无效输入 请输入 1~10000 范围内的票价: ");
        clearInputBuffer();
    }

    // 乘客上限
    printf("最大乘客数量(10-500): ");
    while (scanf("%d%c", &f.num, &c) != 2 || c != '\n' || f.num < 10 || f.num > 500)
    {
        printf("无效输入 请输入 10~500 范围内的乘客数量: ");
        clearInputBuffer();
    }

    f.curr = 0; // 当前人数默认为 0
    flights[flightsCount++] = f;
    saveFlights();

    printf("航班添加成功\n");
    pressEnterToContinue();
}

void deleteflight()
{
    system("cls");
    printf("-----删除航班-----\n");

    if (flightsCount == 0)
    {
        printf("当前无任何航班信息 无法删除\n");
        pressEnterToContinue();
        return;
    }

    char inputCode[MAX_CODE_LENGTH];
    printf("请输入要删除的航班编号(3-20位字母和数字): ");
    fgets(inputCode, MAX_CODE_LENGTH, stdin);
    if (strchr(inputCode, '\n') == NULL)
    {
        clearInputBuffer();
    }
    inputCode[strcspn(inputCode, "\n")] = '\0';

    int index = findFlightIndexByCode(inputCode);
    if (index == -1)
    {
        printf("未找到航班编号为 \"%s\" 的航班\n", inputCode);
        pressEnterToContinue();
        return;
    }

    // 显示航班信息
    printf("\n即将删除航班信息如下:\n");
    printf("航班号: %s\n", flights[index].CODE);
    printf("公司: %s\n", flights[index].COMPANY);
    printf("出发地 → 目的地: %s → %s\n", flights[index].STARTING, flights[index].DESTINATION);
    printf("出发日期: %s\n", flights[index].date);
    printf("票价: %d 元\n", flights[index].praise);

    // 删除确认
    char confirm;
    printf("\n是否确认删除该航班?(Y/N): ");
    scanf(" %c", &confirm);
    clearInputBuffer();
    if (confirm != 'Y' && confirm != 'y')
    {
        printf("已取消删除\n");
        pressEnterToContinue();
        return;
    }

    // 删除航班(覆盖并减少数量)
    for (int i = index; i < flightsCount - 1; ++i)
    {
        flights[i] = flights[i + 1];
    }
    flightsCount--;

    saveFlights(); // 保存更改

    printf("航班删除成功\n");
    pressEnterToContinue();
}

void modifyFlight()
{
    system("cls");
    printf("-----修改航班-----\n");

    if (flightsCount == 0)
    {
        printf("暂无航班\n");
        pressEnterToContinue();
        return;
    }

    char inputCode[MAX_CODE_LENGTH];
    printf("请输入要修改的航班编号(CODE): ");
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
        printf("请选择想要修改的内容:\n");
        printf("1  CODE\n");
        printf("2  MODEL\n");
        printf("3  COMPANY\n");
        printf("4  DATE\n");
        printf("5  TIME\n");
        printf("6  DURATION\n");
        printf("7  GATE\n");
        printf("8  STARTING\n");
        printf("9  DESTINATION\n");
        printf("10 PRISE\n");
        printf("11 NUM\n");
        printf("0  退出\n");
        printf("输入选项编号: ");

        if (scanf("%d%c", &choice, &c) != 2 || c != '\n' || choice < 0 || choice > 11)
        {
            printf("无效输入 请输入 0~11 的数字\n");
            clearInputBuffer();
            pressEnterToContinue();
            continue;
        }

        switch (choice)
        {
        case 0:
            return;

        case 1: // 修改 CODE
        {
            char newCode[MAX_CODE_LENGTH];
            printf("新航班编号(3-20位字母和数字): ");
            fgets(newCode, MAX_CODE_LENGTH, stdin);
            if (strchr(newCode, '\n') == NULL)
            {
                clearInputBuffer();
            }
            newCode[strcspn(newCode, "\n")] = '\0';

            if (!isValidStringCode(newCode))
            {
                printf("CODE 不符合规范\n");
            }
            else if (strcmp(newCode, flights[index].CODE) != 0 &&
                     findFlightIndexByCode(newCode) >= 0)
            {
                printf("该航班编号已存在\n");
            }
            else
            {
                strcpy(flights[index].CODE, newCode);
                saveFlights();
                printf("航班编号修改成功\n");
            }
            pressEnterToContinue();
            break;
        }

        case 2:
        {
            char input[MAX_NAME_LENGTH];
            printf("新机型(2-30位字母和数字): ");
            fgets(input, MAX_NAME_LENGTH, stdin);
            if (strchr(input, '\n') == NULL)
            {
                clearInputBuffer();
            }
            input[strcspn(input, "\n")] = '\0';

            if (!isValidStringModel(input))
                printf("MODEL 不符合规范\n");
            else
            {
                strcpy(flights[index].MODEL, input);
                saveFlights();
                printf("机型修改成功\n");
            }
            pressEnterToContinue();
            break;
        }

        case 3:
        {
            char input[MAX_NAME_LENGTH];
            printf("新航空公司(2-10个汉字): ");
            fgets(input, MAX_NAME_LENGTH, stdin);
            if (strchr(input, '\n') == NULL)
            {
                clearInputBuffer();
            }
            input[strcspn(input, "\n")] = '\0';

            if (!isValidStringCompany(input))
                printf("COMPANY 不符合规范\n");
            else
            {
                strcpy(flights[index].COMPANY, input);
                saveFlights();
                printf("公司修改成功\n");
            }
            pressEnterToContinue();
            break;
        }

        case 4:
        {
            char input[MAX_DATE_LENGTH];
            printf("新出发日期(YYYY-MM-DD): ");
            fgets(input, MAX_DATE_LENGTH, stdin);
            if (strchr(input, '\n') == NULL)
            {
                clearInputBuffer();
            }
            input[strcspn(input, "\n")] = '\0';

            if (!isValidStringDate(input))
                printf("DATE 不符合规范\n");
            else
            {
                strcpy(flights[index].date, input);
                saveFlights();
                printf("日期修改成功\n");
            }
            pressEnterToContinue();
            break;
        }

        case 5:
        {
            char input[MAX_TIME_LENGTH];
            int hour, minute;
            printf("新出发时间(HH:MM): ");
            fgets(input, MAX_TIME_LENGTH, stdin);
            if (strchr(input, '\n') == NULL)
            {
                clearInputBuffer();
            }
            input[strcspn(input, "\n")] = '\0';

            if (!isValidStringTime(input))
            {
                printf("TIME 不符合规范\n");
            }
            else
            {
                sscanf(input, "%d:%d", &hour, &minute);
                flights[index].time = dateTotime(flights[index].date, hour, minute);
                saveFlights();
                printf("时间修改成功\n");
            }
            pressEnterToContinue();
            break;
        }

        case 6:
        {
            int dur;
            printf("新航程时长(分钟 0-1440): ");
            while (scanf("%d%c", &dur, &c) != 2 || c != '\n' || dur < 0 || dur > 1440)
            {
                printf("无效输入 请重新输入: ");
                clearInputBuffer();
            }
            flights[index].duration = dur * 60;
            saveFlights();
            printf("航程时长修改成功\n");
            pressEnterToContinue();
            break;
        }

        case 7:
        {
            char input[MAX_NAME_LENGTH];
            printf("新登机口(2-30字母): ");
            fgets(input, MAX_NAME_LENGTH, stdin);
            if (strchr(input, '\n') == NULL)
            {
                clearInputBuffer();
            }
            input[strcspn(input, "\n")] = '\0';

            if (!isValidStringGate(input))
                printf("GATE 不符合规范\n");
            else
            {
                strcpy(flights[index].GATE, input);
                saveFlights();
                printf("登机口修改成功\n");
            }
            pressEnterToContinue();
            break;
        }

        case 8:
        {
            char input[MAX_NAME_LENGTH];
            printf("新出发地(2-10个汉字): ");
            fgets(input, MAX_NAME_LENGTH, stdin);
            if (strchr(input, '\n') == NULL)
            {
                clearInputBuffer();
            }
            input[strcspn(input, "\n")] = '\0';

            if (!isValidStringStarting(input))
                printf("STARTING 不符合规范\n");
            else
            {
                strcpy(flights[index].STARTING, input);
                saveFlights();
                printf("出发地修改成功\n");
            }
            pressEnterToContinue();
            break;
        }

        case 9:
        {
            char input[MAX_NAME_LENGTH];
            printf("新目的地(2-10个汉字): ");
            fgets(input, MAX_NAME_LENGTH, stdin);
            if (strchr(input, '\n') == NULL)
            {
                clearInputBuffer();
            }
            input[strcspn(input, "\n")] = '\0';

            if (!isValidStringDestination(input))
                printf("DESTINATION 不符合规范\n");
            else
            {
                strcpy(flights[index].DESTINATION, input);
                saveFlights();
                printf("目的地修改成功\n");
            }
            pressEnterToContinue();
            break;
        }

        case 10:
        {
            int price;
            printf("新票价(1-10000): ");
            while (scanf("%d%c", &price, &c) != 2 || c != '\n' || price < 1 || price > 10000)
            {
                printf("无效输入 请重新输入: ");
                clearInputBuffer();
            }
            flights[index].praise = price;
            saveFlights();
            printf("票价修改成功\n");
            pressEnterToContinue();
            break;
        }

        case 11:
        {
            int num;
            printf("新乘客上限(10-500): ");
            while (scanf("%d%c", &num, &c) != 2 || c != '\n' || num < 10 || num > 500)
            {
                printf("无效输入 请重新输入: ");
                clearInputBuffer();
            }
            flights[index].num = num;
            saveFlights();
            printf("乘客上限修改成功\n");
            pressEnterToContinue();
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
    else if (age > 150)
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
    wchar_t wstr[32];
    size_t wchar_count = mbstowcs(wstr, str, sizeof(wstr) / sizeof(wstr[0]));

    if (wchar_count == (size_t)-1)
    {
        printf("字符串包含无效字符，无法转换为宽字符。\n");
        pressEnterToContinue();
        return false;
    }

    if (wchar_count < 2)
    {
        printf("COMPANY 过短，至少为 2 个汉字。\n");
        pressEnterToContinue();
        return false;
    }

    if (wchar_count > 10)
    {
        printf("COMPANY 过长，最多为 10 个汉字。\n");
        pressEnterToContinue();
        return false;
    }

    for (size_t i = 0; i < wchar_count; ++i)
    {
        if (!(wstr[i] >= 0x4E00 && wstr[i] <= 0x9FFF))
        {
            printf("COMPANY 只能包含汉字。\n");
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
 * printf("GATE(2-30位字母与数字): ");
 */
bool isValidStringGate(char *str)
{
    int len = strlen(str);

    if (len < 2)
    {
        printf("GATE 过短，至少为 2 位。\n");
        pressEnterToContinue();
        return false;
    }
    if (len > 30)
    {
        printf("GATE 过长，最多为 30 位。\n");
        pressEnterToContinue();
        return false;
    }

    for (int i = 0; i < len; ++i)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9')))
        {
            printf("GATE 只能包含字母与数字。\n");
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
    wchar_t wstr[32];
    size_t wchar_count = mbstowcs(wstr, str, sizeof(wstr) / sizeof(wstr[0]));

    if (wchar_count == (size_t)-1)
    {
        printf("字符串包含无效字符，无法转换为宽字符。\n");
        pressEnterToContinue();
        return false;
    }

    if (wchar_count < 2)
    {
        printf("COMPANY 过短，至少为 2 个汉字。\n");
        pressEnterToContinue();
        return false;
    }

    if (wchar_count > 10)
    {
        printf("COMPANY 过长，最多为 10 个汉字。\n");
        pressEnterToContinue();
        return false;
    }

    for (size_t i = 0; i < wchar_count; ++i)
    {
        if (!(wstr[i] >= 0x4E00 && wstr[i] <= 0x9FFF))
        {
            printf("COMPANY 只能包含汉字。\n");
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
    wchar_t wstr[32];
    size_t wchar_count = mbstowcs(wstr, str, sizeof(wstr) / sizeof(wstr[0]));

    if (wchar_count == (size_t)-1)
    {
        printf("字符串包含无效字符，无法转换为宽字符。\n");
        pressEnterToContinue();
        return false;
    }

    if (wchar_count < 2)
    {
        printf("COMPANY 过短，至少为 2 个汉字。\n");
        pressEnterToContinue();
        return false;
    }

    if (wchar_count > 10)
    {
        printf("COMPANY 过长，最多为 10 个汉字。\n");
        pressEnterToContinue();
        return false;
    }

    for (size_t i = 0; i < wchar_count; ++i)
    {
        if (!(wstr[i] >= 0x4E00 && wstr[i] <= 0x9FFF))
        {
            printf("COMPANY 只能包含汉字。\n");
            pressEnterToContinue();
            return false;
        }
    }

    return true;
}

/**
 * 判断一个宽字符是否为宽字符(中日韩/全角字符)
 */
int wcDisplayWidth(wchar_t wc)
{
    // 简化: 中日韩统一表意文字范围
    if ((wc >= 0x4E00 && wc <= 0x9FFF) || // CJK Unified Ideographs
        (wc >= 0x3400 && wc <= 0x4DBF) || // CJK Extension A
        (wc >= 0xF900 && wc <= 0xFAFF) || // CJK Compatibility Ideographs
        (wc >= 0x3000 && wc <= 0x303F) || // CJK 标点符号(如全角逗号)
        (wc >= 0xFF00 && wc <= 0xFFEF))
    {
        // 全角 ASCII、符号
        return 2;
    }
    return 1; // 英文、数字、空格等
}

/**
 * 自定义 wcswidth(): 计算整个宽字符串的可视宽度
 */
int wcswidth(const wchar_t *wstr)
{
    int width = 0;
    while (*wstr)
    {
        width += wcDisplayWidth(*wstr);
        wstr++;
    }
    return width;
}

int visualWidth(const char *str)
{
    // 设置地区为 UTF-8，保证中文识别
    setlocale(LC_ALL, "");

    // 转换为宽字符字符串
    wchar_t wstr[256];
    mbstowcs(wstr, str, sizeof(wstr) / sizeof(wchar_t));

    // 返回显示宽度(中文=2，英文=1)
    return wcswidth(wstr);
}

/**
 * 打印字符串并按宽度对齐(右侧补空格)
 * 例如 printAlign("航班号", 10); 会打印两字+6空格
 */
void printAlign(const char *str, int totalWidth)
{
    int strWidth = visualWidth(str);
    printf("%s", str);
    for (int i = strWidth; i < totalWidth; i++)
    {
        printf(" ");
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
