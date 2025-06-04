#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_COURSES 50
#define MAX_STUDENTS 100
#define MAX_TEACHERS 50
#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_COURSE_NAME_LENGTH 50
#define MAX_GRADES 20

// 用户类型枚举
typedef enum
{
    ADMIN,
    TEACHER,
    STUDENT
} UserType;

// 用户结构体
typedef struct
{
    char id[MAX_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char name[MAX_NAME_LENGTH];
    UserType type;
    int active; // 1表示活跃，0表示禁用
} User;

// 课程结构体
typedef struct
{
    char courseId[MAX_ID_LENGTH];
    char courseName[MAX_COURSE_NAME_LENGTH];
    char teacherId[MAX_ID_LENGTH]; // 授课教师ID
    int maxStudents;
    int currentStudents;
    char studentIds[MAX_STUDENTS][MAX_ID_LENGTH]; // 选课学生ID
    float grades[MAX_STUDENTS][MAX_GRADES];       // 每个学生的成绩
    int gradeCount[MAX_STUDENTS];                 // 每个学生的成绩数量
} Course;

// 系统数据结构
typedef struct
{
    User users[MAX_USERS];
    int userCount;
    Course courses[MAX_COURSES];
    int courseCount;
} SystemData;

// 全局数据
SystemData systemData;
User currentUser;

// 函数声明
void initializeSystem();
int login();
void adminMenu();
void teacherMenu();
void studentMenu();
void addUser();
void manageUsers();
void viewUserList();
void addCourse();
void manageCourses();
void viewCourseList();
void viewStudentCourses();
void selectCourse();
void dropCourse();
void inputGrades();
void viewGrades();
void viewStudentInfo();
void backupData();
void restoreData();
int findUserIndex(const char *id);
int findCourseIndex(const char *courseId);
int findStudentInCourse(const char *courseId, const char *studentId);
void generateReport();
void changePassword();
void printSystemInfo();
void clearInputBuffer();
void waitForEnter();
void showWelcomeScreen();
void showMenuHeader(const char *title);

// 初始化系统
void initializeSystem()
{
    systemData.userCount = 0;
    systemData.courseCount = 0;

    // 添加默认管理员
    User admin = {
        .type = ADMIN,
        .active = 1};
    strcpy(admin.id, "admin");
    strcpy(admin.password, "admin123");
    strcpy(admin.name, "系统管理员");

    systemData.users[systemData.userCount++] = admin;

    // 尝试从文件恢复数据
    restoreData();

    printf("系统初始化完成...\n");
    waitForEnter();
}

// 登录函数
int login()
{
    char id[MAX_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int attempts = 3;

    showWelcomeScreen();

    while (attempts > 0)
    {
        printf("\n请输入账号: ");
        scanf("%s", id);
        clearInputBuffer();

        printf("请输入密码: ");
        scanf("%s", password);
        clearInputBuffer();

        int index = findUserIndex(id);
        if (index != -1 && strcmp(systemData.users[index].password, password) == 0)
        {
            if (!systemData.users[index].active)
            {
                printf("账号已被禁用，请联系管理员!\n");
                waitForEnter();
                return 0;
            }

            currentUser = systemData.users[index];
            printf("\n欢迎回来，%s！\n", currentUser.name);
            waitForEnter();
            return 1;
        }

        attempts--;
        printf("账号或密码错误！你还有%d次尝试机会。\n", attempts);
    }

    printf("登录尝试次数过多，程序退出。\n");
    waitForEnter();
    return 0;
}

// 管理员菜单
void adminMenu()
{
    int choice;

    do
    {
        showMenuHeader("管理员菜单");
        printf("1. 添加用户\n");
        printf("2. 管理用户\n");
        printf("3. 添加课程\n");
        printf("4. 管理课程\n");
        printf("5. 查看用户列表\n");
        printf("6. 查看课程列表\n");
        printf("7. 生成报表\n");
        printf("8. 修改密码\n");
        printf("9. 系统信息\n");
        printf("0. 退出登录\n");
        printf("请输入你的选择: ");

        if (scanf("%d", &choice) != 1)
        {
            choice = -1;
            clearInputBuffer();
        }
        else
        {
            clearInputBuffer();
        }

        switch (choice)
        {
        case 1:
            addUser();
            break;
        case 2:
            manageUsers();
            break;
        case 3:
            addCourse();
            break;
        case 4:
            manageCourses();
            break;
        case 5:
            viewUserList();
            break;
        case 6:
            viewCourseList();
            break;
        case 7:
            generateReport();
            break;
        case 8:
            changePassword();
            break;
        case 9:
            printSystemInfo();
            break;
        case 0:
            printf("退出登录成功！\n");
            waitForEnter();
            break;
        default:
            printf("无效的选择，请重新输入！\n");
            waitForEnter();
        }
    } while (choice != 0);
}

// 教师菜单
void teacherMenu()
{
    int choice;

    do
    {
        showMenuHeader("教师菜单");
        printf("1. 查看课程列表\n");
        printf("2. 录入成绩\n");
        printf("3. 查看学生信息\n");
        printf("4. 修改密码\n");
        printf("0. 退出登录\n");
        printf("请输入你的选择: ");

        if (scanf("%d", &choice) != 1)
        {
            choice = -1;
            clearInputBuffer();
        }
        else
        {
            clearInputBuffer();
        }

        switch (choice)
        {
        case 1:
            viewCourseList();
            break;
        case 2:
            inputGrades();
            break;
        case 3:
            viewStudentInfo();
            break;
        case 4:
            changePassword();
            break;
        case 0:
            printf("退出登录成功！\n");
            waitForEnter();
            break;
        default:
            printf("无效的选择，请重新输入！\n");
            waitForEnter();
        }
    } while (choice != 0);
}

// 学生菜单
void studentMenu()
{
    int choice;

    do
    {
        showMenuHeader("学生菜单");
        printf("1. 查看可选课程\n");
        printf("2. 选课\n");
        printf("3. 退课\n");
        printf("4. 查看已选课程\n");
        printf("5. 查看成绩\n");
        printf("6. 修改密码\n");
        printf("0. 退出登录\n");
        printf("请输入你的选择: ");

        if (scanf("%d", &choice) != 1)
        {
            choice = -1;
            clearInputBuffer();
        }
        else
        {
            clearInputBuffer();
        }

        switch (choice)
        {
        case 1:
            viewCourseList();
            break;
        case 2:
            selectCourse();
            break;
        case 3:
            dropCourse();
            break;
        case 4:
            viewStudentCourses();
            break;
        case 5:
            viewGrades();
            break;
        case 6:
            changePassword();
            break;
        case 0:
            printf("退出登录成功！\n");
            waitForEnter();
            break;
        default:
            printf("无效的选择，请重新输入！\n");
            waitForEnter();
        }
    } while (choice != 0);
}

// 添加用户
void addUser()
{
    User newUser;
    int type;

    showMenuHeader("添加用户");

    if (systemData.userCount >= MAX_USERS)
    {
        printf("用户数量已达到上限，无法添加新用户！\n");
        waitForEnter();
        return;
    }

    printf("请输入用户ID: ");
    scanf("%s", newUser.id);
    clearInputBuffer();

    if (findUserIndex(newUser.id) != -1)
    {
        printf("该用户ID已存在！\n");
        waitForEnter();
        return;
    }

    printf("请输入用户名: ");
    scanf("%s", newUser.name);
    clearInputBuffer();

    printf("请输入密码: ");
    scanf("%s", newUser.password);
    clearInputBuffer();

    do
    {
        printf("请选择用户类型 (0-管理员, 1-教师, 2-学生): ");
        if (scanf("%d", &type) != 1)
        {
            type = -1;
            clearInputBuffer();
        }
        else
        {
            clearInputBuffer();
        }

        if (type < 0 || type > 2)
        {
            printf("无效的用户类型，请重新输入！\n");
        }
    } while (type < 0 || type > 2);

    newUser.type = (UserType)type;
    newUser.active = 1;

    systemData.users[systemData.userCount++] = newUser;
    backupData();

    printf("用户添加成功！\n");
    waitForEnter();
}

// 管理用户
void manageUsers()
{
    char id[MAX_ID_LENGTH];
    int choice, index;

    showMenuHeader("管理用户");

    printf("请输入要管理的用户ID: ");
    scanf("%s", id);
    clearInputBuffer();

    index = findUserIndex(id);
    if (index == -1)
    {
        printf("未找到该用户！\n");
        waitForEnter();
        return;
    }

    if (strcmp(systemData.users[index].id, "admin") == 0)
    {
        printf("不能管理默认管理员账号！\n");
        waitForEnter();
        return;
    }

    do
    {
        printf("\n管理用户: %s (%s)\n", systemData.users[index].name,
               systemData.users[index].type == ADMIN ? "管理员" : systemData.users[index].type == TEACHER ? "教师"
                                                                                                          : "学生");
        printf("1. 修改用户名\n");
        printf("2. 修改密码\n");
        printf("3. %s用户账号\n", systemData.users[index].active ? "禁用" : "启用");
        printf("4. 删除用户\n");
        printf("0. 返回\n");
        printf("请输入你的选择: ");

        if (scanf("%d", &choice) != 1)
        {
            choice = -1;
            clearInputBuffer();
        }
        else
        {
            clearInputBuffer();
        }

        switch (choice)
        {
        case 1:
            printf("请输入新的用户名: ");
            scanf("%s", systemData.users[index].name);
            clearInputBuffer();
            backupData();
            printf("用户名修改成功！\n");
            break;
        case 2:
            printf("请输入新的密码: ");
            scanf("%s", systemData.users[index].password);
            clearInputBuffer();
            backupData();
            printf("密码修改成功！\n");
            break;
        case 3:
            systemData.users[index].active = !systemData.users[index].active;
            backupData();
            printf("用户账号已%s！\n", systemData.users[index].active ? "启用" : "禁用");
            break;
        case 4:
            if (strcmp(systemData.users[index].id, currentUser.id) == 0)
            {
                printf("不能删除当前登录的用户！\n");
            }
            else
            {
                // 将后面的用户前移
                for (int i = index; i < systemData.userCount - 1; i++)
                {
                    systemData.users[i] = systemData.users[i + 1];
                }
                systemData.userCount--;
                backupData();
                printf("用户删除成功！\n");
                choice = 0; // 返回
            }
            break;
        case 0:
            break;
        default:
            printf("无效的选择，请重新输入！\n");
        }

        if (choice != 0)
            waitForEnter();
    } while (choice != 0);
}

// 查看用户列表
void viewUserList()
{
    showMenuHeader("用户列表");

    printf("%-15s %-20s %-10s %-8s\n", "用户ID", "用户名", "用户类型", "状态");
    printf("---------------------------------------------\n");

    for (int i = 0; i < systemData.userCount; i++)
    {
        printf("%-15s %-20s %-10s %-8s\n",
               systemData.users[i].id,
               systemData.users[i].name,
               systemData.users[i].type == ADMIN ? "管理员" : systemData.users[i].type == TEACHER ? "教师"
                                                                                                  : "学生",
               systemData.users[i].active ? "活跃" : "禁用");
    }

    waitForEnter();
}

// 添加课程
void addCourse()
{
    Course newCourse;

    showMenuHeader("添加课程");

    if (systemData.courseCount >= MAX_COURSES)
    {
        printf("课程数量已达到上限，无法添加新课程！\n");
        waitForEnter();
        return;
    }

    printf("请输入课程ID: ");
    scanf("%s", newCourse.courseId);
    clearInputBuffer();

    if (findCourseIndex(newCourse.courseId) != -1)
    {
        printf("该课程ID已存在！\n");
        waitForEnter();
        return;
    }

    printf("请输入课程名称: ");
    scanf("%s", newCourse.courseName);
    clearInputBuffer();

    // 验证教师ID是否存在
    char teacherId[MAX_ID_LENGTH];
    int teacherFound = 0;

    do
    {
        printf("请输入授课教师ID: ");
        scanf("%s", teacherId);
        clearInputBuffer();

        int teacherIndex = findUserIndex(teacherId);
        if (teacherIndex != -1 && systemData.users[teacherIndex].type == TEACHER)
        {
            strcpy(newCourse.teacherId, teacherId);
            teacherFound = 1;
        }
        else
        {
            printf("未找到该教师ID，请重新输入！\n");
        }
    } while (!teacherFound);

    do
    {
        printf("请输入课程最大容量: ");
        if (scanf("%d", &newCourse.maxStudents) != 1 || newCourse.maxStudents <= 0)
        {
            printf("无效的容量，请输入正整数！\n");
            clearInputBuffer();
            newCourse.maxStudents = -1;
        }
        else
        {
            clearInputBuffer();
        }
    } while (newCourse.maxStudents <= 0);

    newCourse.currentStudents = 0;
    // 初始化成绩数组
    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        newCourse.gradeCount[i] = 0;
        for (int j = 0; j < MAX_GRADES; j++)
        {
            newCourse.grades[i][j] = 0;
        }
    }

    systemData.courses[systemData.courseCount++] = newCourse;
    backupData();

    printf("课程添加成功！\n");
    waitForEnter();
}

// 管理课程
void manageCourses()
{
    char courseId[MAX_ID_LENGTH];
    int choice, index;

    showMenuHeader("管理课程");

    printf("请输入要管理的课程ID: ");
    scanf("%s", courseId);
    clearInputBuffer();

    index = findCourseIndex(courseId);
    if (index == -1)
    {
        printf("未找到该课程！\n");
        waitForEnter();
        return;
    }

    do
    {
        printf("\n管理课程: %s (%s)\n", systemData.courses[index].courseName, systemData.courses[index].courseId);
        printf("授课教师: %s\n", systemData.courses[index].teacherId);
        printf("当前选课人数: %d/%d\n", systemData.courses[index].currentStudents, systemData.courses[index].maxStudents);
        printf("1. 修改课程名称\n");
        printf("2. 修改授课教师\n");
        printf("3. 修改课程容量\n");
        printf("4. 删除课程\n");
        printf("0. 返回\n");
        printf("请输入你的选择: ");

        if (scanf("%d", &choice) != 1)
        {
            choice = -1;
            clearInputBuffer();
        }
        else
        {
            clearInputBuffer();
        }

        switch (choice)
        {
        case 1:
            printf("请输入新的课程名称: ");
            scanf("%s", systemData.courses[index].courseName);
            clearInputBuffer();
            backupData();
            printf("课程名称修改成功！\n");
            break;
        case 2:
        {
            // 验证教师ID是否存在
            char teacherId[MAX_ID_LENGTH];
            int teacherFound = 0;

            do
            {
                printf("请输入新的授课教师ID: ");
                scanf("%s", teacherId);
                clearInputBuffer();

                int teacherIndex = findUserIndex(teacherId);
                if (teacherIndex != -1 && systemData.users[teacherIndex].type == TEACHER)
                {
                    strcpy(systemData.courses[index].teacherId, teacherId);
                    teacherFound = 1;
                }
                else
                {
                    printf("未找到该教师ID，请重新输入！\n");
                }
            } while (!teacherFound);

            backupData();
            printf("授课教师修改成功！\n");
            break;
        }
        case 3:
            do
            {
                printf("请输入新的课程容量: ");
                if (scanf("%d", &systemData.courses[index].maxStudents) != 1 ||
                    systemData.courses[index].maxStudents < systemData.courses[index].currentStudents)
                {
                    printf("无效的容量，请输入大于等于当前选课人数的正整数！\n");
                    clearInputBuffer();
                    systemData.courses[index].maxStudents = -1;
                }
                else
                {
                    clearInputBuffer();
                }
            } while (systemData.courses[index].maxStudents < systemData.courses[index].currentStudents);

            backupData();
            printf("课程容量修改成功！\n");
            break;
        case 4:
            // 将后面的课程前移
            for (int i = index; i < systemData.courseCount - 1; i++)
            {
                systemData.courses[i] = systemData.courses[i + 1];
            }
            systemData.courseCount--;
            backupData();
            printf("课程删除成功！\n");
            choice = 0; // 返回
            break;
        case 0:
            break;
        default:
            printf("无效的选择，请重新输入！\n");
        }

        if (choice != 0)
            waitForEnter();
    } while (choice != 0);
}

// 查看课程列表
void viewCourseList()
{
    showMenuHeader("课程列表");

    printf("%-15s %-25s %-15s %-10s %-10s\n", "课程ID", "课程名称", "授课教师", "当前人数", "最大容量");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < systemData.courseCount; i++)
    {
        printf("%-15s %-25s %-15s %-10d %-10d\n",
               systemData.courses[i].courseId,
               systemData.courses[i].courseName,
               systemData.courses[i].teacherId,
               systemData.courses[i].currentStudents,
               systemData.courses[i].maxStudents);
    }

    waitForEnter();
}

// 查看学生已选课程
void viewStudentCourses()
{
    showMenuHeader("我的课程");

    int courseCount = 0;
    printf("%-15s %-25s %-15s\n", "课程ID", "课程名称", "授课教师");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < systemData.courseCount; i++)
    {
        for (int j = 0; j < systemData.courses[i].currentStudents; j++)
        {
            if (strcmp(systemData.courses[i].studentIds[j], currentUser.id) == 0)
            {
                printf("%-15s %-25s %-15s\n",
                       systemData.courses[i].courseId,
                       systemData.courses[i].courseName,
                       systemData.courses[i].teacherId);
                courseCount++;
                break;
            }
        }
    }

    if (courseCount == 0)
    {
        printf("你还没有选择任何课程！\n");
    }

    waitForEnter();
}

// 选课
void selectCourse()
{
    char courseId[MAX_ID_LENGTH];
    int courseIndex;

    showMenuHeader("选课");

    printf("请输入要选择的课程ID: ");
    scanf("%s", courseId);
    clearInputBuffer();

    courseIndex = findCourseIndex(courseId);
    if (courseIndex == -1)
    {
        printf("未找到该课程！\n");
        waitForEnter();
        return;
    }

    // 检查是否已选该课程
    for (int i = 0; i < systemData.courses[courseIndex].currentStudents; i++)
    {
        if (strcmp(systemData.courses[courseIndex].studentIds[i], currentUser.id) == 0)
        {
            printf("你已经选择了该课程！\n");
            waitForEnter();
            return;
        }
    }

    // 检查课程是否已满
    if (systemData.courses[courseIndex].currentStudents >= systemData.courses[courseIndex].maxStudents)
    {
        printf("该课程已选满！\n");
        waitForEnter();
        return;
    }

    // 添加学生到课程
    strcpy(systemData.courses[courseIndex].studentIds[systemData.courses[courseIndex].currentStudents], currentUser.id);
    systemData.courses[courseIndex].currentStudents++;
    backupData();

    printf("选课成功！\n");
    waitForEnter();
}

// 退课
void dropCourse()
{
    char courseId[MAX_ID_LENGTH];
    int courseIndex, studentIndex;

    showMenuHeader("退课");

    printf("请输入要退选的课程ID: ");
    scanf("%s", courseId);
    clearInputBuffer();

    courseIndex = findCourseIndex(courseId);
    if (courseIndex == -1)
    {
        printf("未找到该课程！\n");
        waitForEnter();
        return;
    }

    // 检查是否已选该课程
    studentIndex = findStudentInCourse(courseId, currentUser.id);
    if (studentIndex == -1)
    {
        printf("你没有选择该课程！\n");
        waitForEnter();
        return;
    }

    // 从课程中移除学生
    for (int i = studentIndex; i < systemData.courses[courseIndex].currentStudents - 1; i++)
    {
        strcpy(systemData.courses[courseIndex].studentIds[i], systemData.courses[courseIndex].studentIds[i + 1]);
        // 移动成绩
        systemData.courses[courseIndex].gradeCount[i] = systemData.courses[courseIndex].gradeCount[i + 1];
        for (int j = 0; j < systemData.courses[courseIndex].gradeCount[i]; j++)
        {
            systemData.courses[courseIndex].grades[i][j] = systemData.courses[courseIndex].grades[i + 1][j];
        }
    }
    systemData.courses[courseIndex].currentStudents--;
    backupData();

    printf("退课成功！\n");
    waitForEnter();
}

// 录入成绩
void inputGrades()
{
    char courseId[MAX_ID_LENGTH];
    int courseIndex;

    showMenuHeader("录入成绩");

    // 检查教师是否有课程
    int hasCourse = 0;
    for (int i = 0; i < systemData.courseCount; i++)
    {
        if (strcmp(systemData.courses[i].teacherId, currentUser.id) == 0)
        {
            hasCourse = 1;
            break;
        }
    }

    if (!hasCourse)
    {
        printf("你没有教授任何课程！\n");
        waitForEnter();
        return;
    }

    printf("请输入要录入成绩的课程ID: ");
    scanf("%s", courseId);
    clearInputBuffer();

    courseIndex = findCourseIndex(courseId);
    if (courseIndex == -1)
    {
        printf("未找到该课程！\n");
        waitForEnter();
        return;
    }

    // 检查是否是该课程的教师
    if (strcmp(systemData.courses[courseIndex].teacherId, currentUser.id) != 0)
    {
        printf("你不是该课程的授课教师！\n");
        waitForEnter();
        return;
    }

    // 检查课程是否有学生
    if (systemData.courses[courseIndex].currentStudents == 0)
    {
        printf("该课程没有学生！\n");
        waitForEnter();
        return;
    }

    printf("课程: %s (%s)\n", systemData.courses[courseIndex].courseName, systemData.courses[courseIndex].courseId);
    printf("当前选课人数: %d\n", systemData.courses[courseIndex].currentStudents);

    int studentIndex;
    char studentId[MAX_ID_LENGTH];

    do
    {
        printf("\n请输入学生ID (输入0返回): ");
        scanf("%s", studentId);
        clearInputBuffer();

        if (strcmp(studentId, "0") == 0)
            break;

        studentIndex = findStudentInCourse(courseId, studentId);
        if (studentIndex == -1)
        {
            printf("该学生没有选择此课程！\n");
            continue;
        }

        // 录入成绩
        float grade;
        int gradeIndex = systemData.courses[courseIndex].gradeCount[studentIndex];

        printf("请输入第%d次成绩 (输入负数结束): ", gradeIndex + 1);
        if (scanf("%f", &grade) != 1)
        {
            printf("输入无效！\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (grade < 0)
            continue;

        if (gradeIndex < MAX_GRADES)
        {
            systemData.courses[courseIndex].grades[studentIndex][gradeIndex] = grade;
            systemData.courses[courseIndex].gradeCount[studentIndex]++;
            backupData();
            printf("成绩录入成功！\n");
        }
        else
        {
            printf("成绩数量已达到上限！\n");
        }
    } while (1);
}

// 查看成绩
void viewGrades()
{
    showMenuHeader("我的成绩");

    int hasGrades = 0;

    for (int i = 0; i < systemData.courseCount; i++)
    {
        for (int j = 0; j < systemData.courses[i].currentStudents; j++)
        {
            if (strcmp(systemData.courses[i].studentIds[j], currentUser.id) == 0)
            {
                if (systemData.courses[i].gradeCount[j] > 0)
                {
                    printf("\n课程: %s (%s)\n", systemData.courses[i].courseName, systemData.courses[i].courseId);
                    printf("授课教师: %s\n", systemData.courses[i].teacherId);
                    printf("成绩列表:\n");

                    float total = 0;
                    for (int k = 0; k < systemData.courses[i].gradeCount[j]; k++)
                    {
                        printf("  第%d次成绩: %.2f\n", k + 1, systemData.courses[i].grades[j][k]);
                        total += systemData.courses[i].grades[j][k];
                    }

                    if (systemData.courses[i].gradeCount[j] > 0)
                    {
                        printf("  平均成绩: %.2f\n", total / systemData.courses[i].gradeCount[j]);
                    }

                    hasGrades = 1;
                }
                break;
            }
        }
    }

    if (!hasGrades)
    {
        printf("你还没有任何成绩记录！\n");
    }

    waitForEnter();
}

// 查看学生信息
void viewStudentInfo()
{
    char courseId[MAX_ID_LENGTH];
    int courseIndex;

    showMenuHeader("查看学生信息");

    // 检查教师是否有课程
    int hasCourse = 0;
    for (int i = 0; i < systemData.courseCount; i++)
    {
        if (strcmp(systemData.courses[i].teacherId, currentUser.id) == 0)
        {
            hasCourse = 1;
            break;
        }
    }

    if (!hasCourse)
    {
        printf("你没有教授任何课程！\n");
        waitForEnter();
        return;
    }

    printf("请输入要查看学生信息的课程ID: ");
    scanf("%s", courseId);
    clearInputBuffer();

    courseIndex = findCourseIndex(courseId);
    if (courseIndex == -1)
    {
        printf("未找到该课程！\n");
        waitForEnter();
        return;
    }

    // 检查是否是该课程的教师
    if (strcmp(systemData.courses[courseIndex].teacherId, currentUser.id) != 0)
    {
        printf("你不是该课程的授课教师！\n");
        waitForEnter();
        return;
    }

    // 检查课程是否有学生
    if (systemData.courses[courseIndex].currentStudents == 0)
    {
        printf("该课程没有学生！\n");
        waitForEnter();
        return;
    }

    printf("课程: %s (%s)\n", systemData.courses[courseIndex].courseName, systemData.courses[courseIndex].courseId);
    printf("学生列表:\n");
    printf("%-15s %-20s %-15s\n", "学生ID", "姓名", "成绩记录");
    printf("---------------------------------------------\n");

    for (int i = 0; i < systemData.courses[courseIndex].currentStudents; i++)
    {
        int userIndex = findUserIndex(systemData.courses[courseIndex].studentIds[i]);
        if (userIndex != -1)
        {
            printf("%-15s %-20s %-15d\n",
                   systemData.courses[courseIndex].studentIds[i],
                   systemData.users[userIndex].name,
                   systemData.courses[courseIndex].gradeCount[i]);
        }
    }

    waitForEnter();
}

// 备份数据
void backupData()
{
    FILE *file = fopen("system_data.dat", "wb");
    if (file == NULL)
    {
        printf("警告: 无法保存数据！\n");
        return;
    }

    fwrite(&systemData, sizeof(SystemData), 1, file);
    fclose(file);
}

// 恢复数据
void restoreData()
{
    FILE *file = fopen("system_data.dat", "rb");
    if (file == NULL)
    {
        printf("警告: 无法加载数据！\n");
        return;
    }

    if (fread(&systemData, sizeof(SystemData), 1, file) != 1)
    {
        printf("警告: 数据加载失败！\n");
    }

    fclose(file);
}

// 查找用户索引
int findUserIndex(const char *id)
{
    for (int i = 0; i < systemData.userCount; i++)
    {
        if (strcmp(systemData.users[i].id, id) == 0)
        {
            return i;
        }
    }
    return -1;
}

// 查找课程索引
int findCourseIndex(const char *courseId)
{
    for (int i = 0; i < systemData.courseCount; i++)
    {
        if (strcmp(systemData.courses[i].courseId, courseId) == 0)
        {
            return i;
        }
    }
    return -1;
}

// 在课程中查找学生
int findStudentInCourse(const char *courseId, const char *studentId)
{
    int courseIndex = findCourseIndex(courseId);
    if (courseIndex == -1)
        return -1;

    for (int i = 0; i < systemData.courses[courseIndex].currentStudents; i++)
    {
        if (strcmp(systemData.courses[courseIndex].studentIds[i], studentId) == 0)
        {
            return i;
        }
    }

    return -1;
}

// 生成报表
void generateReport()
{
    showMenuHeader("系统报表");

    printf("用户统计:\n");
    printf("  总用户数: %d\n", systemData.userCount);
    int adminCount = 0, teacherCount = 0, studentCount = 0;

    for (int i = 0; i < systemData.userCount; i++)
    {
        if (systemData.users[i].type == ADMIN)
            adminCount++;
        else if (systemData.users[i].type == TEACHER)
            teacherCount++;
        else
            studentCount++;
    }

    printf("  管理员: %d\n", adminCount);
    printf("  教师: %d\n", teacherCount);
    printf("  学生: %d\n\n", studentCount);

    printf("课程统计:\n");
    printf("  总课程数: %d\n", systemData.courseCount);

    int totalStudents = 0;
    for (int i = 0; i < systemData.courseCount; i++)
    {
        totalStudents += systemData.courses[i].currentStudents;
    }

    printf("  总选课人次: %d\n", totalStudents);
    printf("  平均每门课程选课人数: %.2f\n\n",
           systemData.courseCount > 0 ? (float)totalStudents / systemData.courseCount : 0);

    printf("课程容量利用率:\n");
    for (int i = 0; i < systemData.courseCount; i++)
    {
        float utilization = (float)systemData.courses[i].currentStudents / systemData.courses[i].maxStudents * 100;
        printf("  %s (%s): %.2f%%\n",
               systemData.courses[i].courseName,
               systemData.courses[i].courseId,
               utilization);
    }

    waitForEnter();
}

// 修改密码
void changePassword()
{
    char oldPassword[MAX_PASSWORD_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    showMenuHeader("修改密码");

    printf("请输入当前密码: ");
    scanf("%s", oldPassword);
    clearInputBuffer();

    if (strcmp(oldPassword, currentUser.password) != 0)
    {
        printf("当前密码错误！\n");
        waitForEnter();
        return;
    }

    do
    {
        printf("请输入新密码: ");
        scanf("%s", newPassword);
        clearInputBuffer();

        printf("请再次输入新密码以确认: ");
        scanf("%s", confirmPassword);
        clearInputBuffer();

        if (strcmp(newPassword, confirmPassword) != 0)
        {
            printf("两次输入的密码不一致，请重新输入！\n");
        }
    } while (strcmp(newPassword, confirmPassword) != 0);

    // 找到当前用户并修改密码
    int userIndex = findUserIndex(currentUser.id);
    if (userIndex != -1)
    {
        strcpy(systemData.users[userIndex].password, newPassword);
        strcpy(currentUser.password, newPassword);
        backupData();
        printf("密码修改成功！\n");
    }
    else
    {
        printf("修改密码失败，未找到用户！\n");
    }

    waitForEnter();
}

// 打印系统信息
void printSystemInfo()
{
    showMenuHeader("系统信息");

    printf("学生教务管理系统 v1.0\n");
    printf("开发日期: 2025年6月\n");
    printf("当前用户: %s (%s)\n", currentUser.name,
           currentUser.type == ADMIN ? "管理员" : currentUser.type == TEACHER ? "教师"
                                                                              : "学生");
    printf("用户总数: %d\n", systemData.userCount);
    printf("课程总数: %d\n", systemData.courseCount);

    time_t now = time(NULL);
    char *timeStr = ctime(&now);
    printf("当前时间: %s", timeStr);

    waitForEnter();
}

// 清除输入缓冲区
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// 等待用户按下Enter键
void waitForEnter()
{
    printf("\n按Enter键继续...");
    clearInputBuffer();
}

// 显示欢迎屏幕
void showWelcomeScreen()
{
    system("clear"); // 清屏，Windows系统使用system("cls")
    printf("========================================\n");
    printf("          学生教务管理系统 v1.0\n");
    printf("========================================\n");
}

// 显示菜单头部
void showMenuHeader(const char *title)
{
    system("clear"); // 清屏，Windows系统使用system("cls")
    printf("========================================\n");
    printf("               %s\n", title);
    printf("========================================\n");
}

// 主函数
int main()
{
    initializeSystem();

    while (1)
    {
        if (!login())
            break;

        switch (currentUser.type)
        {
        case ADMIN:
            adminMenu();
            break;
        case TEACHER:
            teacherMenu();
            break;
        case STUDENT:
            studentMenu();
            break;
        }
    }

    printf("\n感谢使用学生教务管理系统，再见！\n");
    return 0;
}
