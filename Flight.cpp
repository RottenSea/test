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
void cancleflight(int index);

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

int visualWidth(const wchar_t *str);
void wprintAlign(const wchar_t *str, int total_width);
time_t dateTotime(const char *str, int hour, int minute);
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
    char date[11];
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

        if (scanf("%d%c", &choice, &c) != 2 || c != '\n')
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
    fgets(u.NAME, MAX_NAME_LENGTH, stdin);
    u.NAME[strcspn(u.NAME, "\n")] = '\0';
    if (!isValidStringNAME(u.NAME))
    {
        printf("NAME 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    printf("PASSWORD(3-20位字母和数字): ");
    fgets(u.PASSWORD, MAX_PASSWORD_LENGTH, stdin);
    u.PASSWORD[strcspn(u.PASSWORD, "\n")] = '\0';
    if (!isValidStringPASSWORD(u.PASSWORD))
    {
        printf("PASSWORD 不符合规范\n");
        pressEnterToContinue();
        return;
    }

    printf("PHONE(3-20位字母和数字): ");
    fgets(u.PHONE, MAX_PHONE_LENGTH, stdin);
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
    while (scanf("%d%c", &choice, &c) != 2 || c != '\n')
    {
        printf("无效输入 请输入一个有效的数字选项\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    if (choice)
    {
        do
        {
            printf("0 默认");
            printf("1 男");
            printf("2 女");
            printf("gender(0-2):");
            if (scanf("%d%c", &u.gender, &c) != 2 || c != '\n')
            {
                printf("无效输入 请输入一个有效的数字选项\n");
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }
            else
                (!isValidGender(u.gender))
                {
                    printf("输入不符合规范\n");
                }
        } while (choice != 0)

            printf("age:");
        scanf("%d", &u.age);
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

    printf("-----登录-----");
    char inputUUID[MAX_UUID_LENGTH];
    printf("UUID: ");
    fgets(inputUUID, MAX_UUID_LENGTH, stdin);
    inputUUID[strcspn(inputUUID, "\n")] = '\0';

    int choice;
    int index = -1;

    // 在users中查找该用户
    index = findUserIndexByUUID(inputUUID);
    if (index >= 0)
    {
        do
        {
            char inputPassword[MAX_PASSWORD_LENGTH];
            printf("PASSWORD: ");
            fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);
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
                scanf("%d", &choice);
                getchar();
            }
        } while (choice);
        printf("返回上级目录\n");
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
                scanf("%d", &choice);
                getchar();
            }
        } while (choice);
        printf("返回上级目录\n");
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
            fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);
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
                scanf("%d", &choice);
                getchar();
            }
        } while (choice);
        printf("返回上级目录\n");
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

        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            listFlight("");
            break;
        case 2:
            bookFlight(index);
            break;
        case 3:
            cancleflight(index);
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

        scanf("%d", &choice);
        getchar();
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
    fgets(inputCode, MAX_CODE_LENGTH, stdin);
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
        printf("----------航班列表----------\n");
        wprintf(L"%-10ls%-10ls%-20ls%-8ls%-8ls%-8ls%-20ls%-20ls%-8ls%-8ls%-8ls\n", L"航班号", L"机型", L"承办公司", L"日期", L"出发时间", L"到达时间", L"始发地", L"目的地", L"价格", L"剩余", L"状态");
        wprintf(L"%-10ls%-10ls%-20ls%-8ls%-8ls%-8ls%-20ls%-20ls%-8d%-8d%-8ls\n", flights[findFlightIndex[i]].CODE, flights[findFlightIndex[i]].MODEL, flights[findFlightIndex[i]].COMPANY, flights[findFlightIndex[i]].date, departureTime(i), arrivalTime(i), flights[findFlightIndex[i]].STARTING, flights[findFlightIndex[i]].DESTINATION, flights[findFlightIndex[i]].prise, countFlightRemain(i), calStatus(i));
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

    printf("请支付金额: %d元\n", flights[inputBookFlight - 1].prise);
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

void cancleflight(int index)
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

/**
 * 按回车键继续
 */
void pressEnterToContinue()
{
    printf("\n按回车键继续...");
    getchar();
}
