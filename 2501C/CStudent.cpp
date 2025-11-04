#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20
#define MAX_USERS 100
#define MAX_GRADES 1000
#define MAX_SUBJECT_LENGTH 50

// 身份角色常量
#define ROLE_STUDENT 0
#define ROLE_TEACHER 1
#define ROLE_ADMIN 2

typedef struct
{
    int identify;                       // 身份标识符，由系统自动顺序分配(唯一)
    char id[MAX_NAME_LENGTH];           // 登录账号
    char name[MAX_NAME_LENGTH];         // 姓名
    char password[MAX_PASSWORD_LENGTH]; // 密码
    int role;                           // 0: 学生, 1: 教师, 2: 管理员
} User;

typedef struct
{
    char student_id[MAX_NAME_LENGTH]; // 学生账号，用于关联 User.id
    char subject[MAX_SUBJECT_LENGTH]; // 科目名称
    float score;                      // 分数
} Grade;

// 全局变量：用户和成绩信息
User users[MAX_USERS];
int user_count = 0;

Grade grades[MAX_GRADES];
int grade_count = 0;

// 文件名常量
const char *USER_FILE = "users.dat";
const char *GRADE_FILE = "grades.dat";

// 函数声明
void initialize_data(); // 140
void load_users();
void save_users();
void load_grades();
void save_grades();

int login(int role); // 265
void student_menu(int user_index);
void teacher_menu(int user_index);
void admin_menu(int user_index);

void student_query_grades(int user_index); // 330
void student_change_password(int user_index);

void teacher_add_grade(); // 416
void teacher_delete_grade();
void teacher_modify_grade();
void teacher_query_grades();
int find_grade_index(const char *student_id, const char *subject);

void admin_add_user(); // 666
void admin_delete_user();
void admin_modify_user();
void admin_query_users();
int find_user_index_by_id(const char *id, int role);

void press_enter_to_continue(); // 896

// 程序入口
int main()
{
    int choice_role;
    int login_index;

    // 仅初次使用进行初始化
    initialize_data();

    // 主循环：角色选择 -> 登录 -> 菜单操作
    while (1)
    {
        // 在标准 C 语言中，fflush(stdin) 的行为是未定义的，
        // 不过有些编译器（像 Microsoft Visual C）支持这种用法。
        // 但为了保证代码的可移植性，最好不要使用它。
        setbuf(stdin, NULL); // 忽略输入缓冲区中的数据

        system("cls"); // Linux/Unix 下清屏。Windows 下可改为 system("cls");
        printf("========= 学生成绩管理系统 =========\n");
        printf("请选择身份:\n");
        printf("1. 学生\n");
        printf("2. 教师\n");
        printf("3. 管理员\n");
        printf("0. 退出系统\n");
        printf("输入选项: ");
        scanf("%d", &choice_role);
        getchar(); // 吃掉换行

        if (choice_role == 0)
        {
            printf("退出系统，感谢使用！\n");
            break;
        }

        if (choice_role < 1 || choice_role > 3)
        {
            printf("无效选项，请重试。\n");
            press_enter_to_continue();
            continue;
        }

        // 登录
        login_index = login(choice_role - 1);
        if (login_index >= 0)
        {
            // 登录成功，根据身份进入对应菜单
            if (choice_role - 1 == ROLE_STUDENT)
            {
                student_menu(login_index);
            }
            else if (choice_role - 1 == ROLE_TEACHER)
            {
                teacher_menu(login_index);
            }
            else if (choice_role - 1 == ROLE_ADMIN)
            {
                admin_menu(login_index);
            }
        }
        else
        {
            // 登录失败
            printf("登录失败，用户名或密码错误。\n");
            press_enter_to_continue();
        }
    }

    return 0;
}

/**
 * 初始化数据：初始化时添加一个示例学生、教师、管理员，
 * 并保存到文件中。示例账户：
 *   学生：账号 072440600, 密码 072440600
 *   教师：账号 JS001, 密码 JS001
 *   管理员：账号 admin, 密码 admin
 */
void initialize_data()
{
    // 如果文件已经存在，跳过初始化
    FILE *fp = fopen(USER_FILE, "rb");
    if (fp)
    {
        fclose(fp);
        return;
    }

    // 清空全局数组
    user_count = 0;
    grade_count = 0;

    // 添加示例学生
    User u;
    u.identify = 1;
    strcpy(u.id, "072440600");
    strcpy(u.name, "示例学生");
    strcpy(u.password, "072440600");
    u.role = ROLE_STUDENT;
    users[user_count++] = u;

    // 添加示例教师
    u.identify = 2;
    strcpy(u.id, "JS001");
    strcpy(u.name, "示例教师");
    strcpy(u.password, "JS001");
    u.role = ROLE_TEACHER;
    users[user_count++] = u;

    // 添加示例管理员
    u.identify = 3;
    strcpy(u.id, "admin");
    strcpy(u.name, "示例管理员");
    strcpy(u.password, "admin");
    u.role = ROLE_ADMIN;
    users[user_count++] = u;

    // 将示例用户写入文件
    save_users();

    // 成绩文件初始为空
    save_grades();
}

/**
 * 从文件加载用户数据
 */
void load_users()
{
    FILE *fp = fopen(USER_FILE, "rb");
    if (!fp)
    {
        // 文件不存在或打开失败，初始化为空
        printf("无法打开用户文件进行读取！\n");
        user_count = 0;
        return;
    }
    fread(&user_count, sizeof(int), 1, fp);
    fread(users, sizeof(User), user_count, fp);
    fclose(fp);
}

/**
 * 将用户数据保存到文件
 */
void save_users()
{
    FILE *fp = fopen(USER_FILE, "wb");
    if (!fp)
    {
        printf("无法打开用户文件进行写入！\n");
        return;
    }
    fwrite(&user_count, sizeof(int), 1, fp);
    fwrite(users, sizeof(User), user_count, fp);
    fclose(fp);
}

/**
 * 从文件加载成绩数据
 */
void load_grades()
{
    FILE *fp = fopen(GRADE_FILE, "rb");
    if (!fp)
    {
        printf("无法打开成绩文件进行读取！\n");
        grade_count = 0;
        return;
    }
    fread(&grade_count, sizeof(int), 1, fp);
    fread(grades, sizeof(Grade), grade_count, fp);
    fclose(fp);
}

/**
 * 将成绩数据保存到文件
 */
void save_grades()
{
    FILE *fp = fopen(GRADE_FILE, "wb");
    if (!fp)
    {
        printf("无法打开成绩文件进行写入！\n");
        return;
    }
    fwrite(&grade_count, sizeof(int), 1, fp);
    fwrite(grades, sizeof(Grade), grade_count, fp);
    fclose(fp);
}

/**
 * 登录函数：根据 role(0/1/2)登录，成功返回用户数组索引，否则返回 -1
 */
int login(int role)
{
    char input_id[MAX_NAME_LENGTH];
    char input_pwd[MAX_PASSWORD_LENGTH];

    printf("请输入账号: ");
    fgets(input_id, MAX_NAME_LENGTH, stdin);
    input_id[strcspn(input_id, "\n")] = '\0';

    printf("请输入密码: ");
    fgets(input_pwd, MAX_PASSWORD_LENGTH, stdin);
    input_pwd[strcspn(input_pwd, "\n")] = '\0';

    // 先加载最新用户数据
    load_users();

    for (int i = 0; i < user_count; i++)
    {
        if (users[i].role == role &&
            strcmp(users[i].id, input_id) == 0 &&
            strcmp(users[i].password, input_pwd) == 0)
        {
            return i;
        }
    }
    return -1;
}

/**
 * 学生菜单
 */
void student_menu(int user_index)
{
    int choice;
    while (1)
    {
        system("cls");
        printf("------ 学生菜单 (%s) ------\n", users[user_index].name);
        printf("1. 查询成绩\n");
        printf("2. 修改密码\n");
        printf("0. 注销并返回上级\n");
        printf("输入选项: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            student_query_grades(user_index);
            break;
        case 2:
            student_change_password(user_index);
            break;
        case 0:
            return;
        default:
            printf("无效选项，请重试。\n");
            press_enter_to_continue();
        }
    }
}

/**
 * 学生查询成绩：显示当前登录学生的所有科目成绩
 */
void student_query_grades(int user_index)
{
    load_grades();
    char *stu_id = users[user_index].id;
    int found = 0;
    printf("\n[%s] 的成绩列表：\n", users[user_index].name);
    printf("---------------------------------\n");
    printf("%-20s %-10s\n", "科目", "分数");
    printf("---------------------------------\n");
    for (int i = 0; i < grade_count; i++)
    {
        if (strcmp(grades[i].student_id, stu_id) == 0)
        {
            printf("%-20s %-10.2f\n", grades[i].subject, grades[i].score);
            found = 1;
        }
    }
    if (!found)
    {
        printf("暂无成绩信息。\n");
    }
    printf("---------------------------------\n");
    press_enter_to_continue();
}

/**
 * 学生修改密码
 */
void student_change_password(int user_index)
{
    char new_pwd[MAX_PASSWORD_LENGTH];
    printf("\n请输入新密码: ");
    fgets(new_pwd, MAX_PASSWORD_LENGTH, stdin);
    new_pwd[strcspn(new_pwd, "\n")] = '\0';

    strcpy(users[user_index].password, new_pwd);
    save_users();
    printf("密码修改成功！\n");
    press_enter_to_continue();
}

/**
 * 教师菜单
 */
void teacher_menu(int user_index)
{
    int choice;
    while (1)
    {
        system("cls");
        printf("------ 教师菜单 (%s) ------\n", users[user_index].name);
        printf("1. 添加学生成绩\n");
        printf("2. 删除学生成绩\n");
        printf("3. 修改学生成绩\n");
        printf("4. 查询学生成绩\n");
        printf("0. 注销并返回上级\n");
        printf("输入选项: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            teacher_add_grade();
            break;
        case 2:
            teacher_delete_grade();
            break;
        case 3:
            teacher_modify_grade();
            break;
        case 4:
            teacher_query_grades();
            break;
        case 0:
            return;
        default:
            printf("无效选项，请重试。\n");
            press_enter_to_continue();
        }
    }
}

/**
 * 教师添加学生成绩
 */
void teacher_add_grade()
{
    load_grades();
    load_users();

    Grade g;
    char stu_id[MAX_NAME_LENGTH];
    char subject[MAX_SUBJECT_LENGTH];
    float score;

    printf("\n请输入学生账号: ");
    fgets(stu_id, MAX_NAME_LENGTH, stdin);
    stu_id[strcspn(stu_id, "\n")] = '\0';

    // 检查学生是否存在
    int stu_idx = find_user_index_by_id(stu_id, ROLE_STUDENT);
    if (stu_idx < 0)
    {
        printf("未找到该学生账号。\n");
        press_enter_to_continue();
        return;
    }

    printf("请输入科目名称: ");
    fgets(subject, MAX_SUBJECT_LENGTH, stdin);
    subject[strcspn(subject, "\n")] = '\0';

    // 检查该学生在该科目是否已有成绩
    if (find_grade_index(stu_id, subject) >= 0)
    {
        printf("该学生在此科目已有成绩，若要修改请使用“修改学生成绩”功能。\n");
        press_enter_to_continue();
        return;
    }

    printf("请输入分数: ");
    scanf("%f", &score);
    getchar();

    strcpy(g.student_id, stu_id);
    strcpy(g.subject, subject);
    g.score = score;
    grades[grade_count++] = g;
    save_grades();

    printf("成绩添加成功！\n");
    press_enter_to_continue();
}

/**
 * 教师删除学生成绩
 */
void teacher_delete_grade()
{
    load_grades();

    char stu_id[MAX_NAME_LENGTH];
    char subject[MAX_SUBJECT_LENGTH];

    printf("\n请输入学生账号: ");
    fgets(stu_id, MAX_NAME_LENGTH, stdin);
    stu_id[strcspn(stu_id, "\n")] = '\0';

    printf("请输入科目名称: ");
    fgets(subject, MAX_SUBJECT_LENGTH, stdin);
    subject[strcspn(subject, "\n")] = '\0';

    int idx = find_grade_index(stu_id, subject);
    if (idx < 0)
    {
        printf("未找到该学生该科目成绩。\n");
        press_enter_to_continue();
        return;
    }

    // 将最后一个元素覆盖到当前索引，然后计数减一
    grades[idx] = grades[grade_count - 1];
    grade_count--;
    save_grades();

    printf("成绩删除成功！\n");
    press_enter_to_continue();
}

/**
 * 教师修改学生成绩
 */
void teacher_modify_grade()
{
    load_grades();

    char stu_id[MAX_NAME_LENGTH];
    char subject[MAX_SUBJECT_LENGTH];
    float new_score;

    printf("\n请输入学生账号: ");
    fgets(stu_id, MAX_NAME_LENGTH, stdin);
    stu_id[strcspn(stu_id, "\n")] = '\0';

    printf("请输入科目名称: ");
    fgets(subject, MAX_SUBJECT_LENGTH, stdin);
    subject[strcspn(subject, "\n")] = '\0';

    int idx = find_grade_index(stu_id, subject);
    if (idx < 0)
    {
        printf("未找到该学生该科目成绩。\n");
        press_enter_to_continue();
        return;
    }

    printf("当前分数: %.2f\n", grades[idx].score);
    printf("请输入新分数: ");
    scanf("%f", &new_score);
    getchar();

    grades[idx].score = new_score;
    save_grades();

    printf("成绩修改成功！\n");
    press_enter_to_continue();
}

/**
 * 教师查询学生成绩：可按学生账号或查看所有成绩
 */
void teacher_query_grades()
{
    load_grades();

    int choice;
    printf("\n1. 查询指定学生成绩\n");
    printf("2. 查询所有学生成绩\n");
    printf("输入选项: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1)
    {
        char stu_id[MAX_NAME_LENGTH];
        printf("请输入学生账号: ");
        fgets(stu_id, MAX_NAME_LENGTH, stdin);
        stu_id[strcspn(stu_id, "\n")] = '\0';

        int found = 0;
        printf("\n[%s] 的成绩列表：\n", stu_id);
        printf("---------------------------------\n");
        printf("%-20s %-10s\n", "科目", "分数");
        printf("---------------------------------\n");
        for (int i = 0; i < grade_count; i++)
        {
            if (strcmp(grades[i].student_id, stu_id) == 0)
            {
                printf("%-20s %-10.2f\n", grades[i].subject, grades[i].score);
                found = 1;
            }
        }
        if (!found)
        {
            printf("暂无该学生成绩信息。\n");
        }
        printf("---------------------------------\n");
    }
    else if (choice == 2)
    {
        if (grade_count == 0)
        {
            printf("暂无任何成绩信息。\n");
        }
        else
        {
            printf("\n所有学生成绩列表：\n");
            printf("------------------------------------------------------\n");
            printf("%-15s %-20s %-10s\n", "学生账号", "科目", "分数");
            printf("------------------------------------------------------\n");
            for (int i = 0; i < grade_count; i++)
            {
                printf("%-15s %-20s %-10.2f\n", grades[i].student_id, grades[i].subject, grades[i].score);
            }
            printf("------------------------------------------------------\n");
        }
    }
    else
    {
        printf("无效选项。\n");
    }
    press_enter_to_continue();
}

/**
 * 根据学生账号和科目名称查找成绩在数组中的索引，找不到返回 -1
 */
int find_grade_index(const char *student_id, const char *subject)
{
    for (int i = 0; i < grade_count; i++)
    {
        if (strcmp(grades[i].student_id, student_id) == 0 &&
            strcmp(grades[i].subject, subject) == 0)
        {
            return i;
        }
    }
    return -1;
}

/**
 * 管理员菜单
 */
void admin_menu(int user_index)
{
    int choice;
    while (1)
    {
        system("cls");
        printf("------ 管理员菜单 (%s) ------\n", users[user_index].name);
        printf("1. 添加用户（学生/教师）\n");
        printf("2. 删除用户（学生/教师）\n");
        printf("3. 修改用户（学生/教师）\n");
        printf("4. 查询用户（学生/教师）\n");
        printf("0. 注销并返回上级\n");
        printf("输入选项: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            admin_add_user();
            break;
        case 2:
            admin_delete_user();
            break;
        case 3:
            admin_modify_user();
            break;
        case 4:
            admin_query_users();
            break;
        case 0:
            return;
        default:
            printf("无效选项，请重试。\n");
            press_enter_to_continue();
        }
    }
}

/**
 * 管理员添加用户（学生或教师）
 */
void admin_add_user()
{
    load_users();

    if (user_count >= MAX_USERS)
    {
        printf("用户数量已达上限，无法添加新用户。\n");
        press_enter_to_continue();
        return;
    }

    User u;
    char role_str[10];
    int role_input;

    printf("\n请选择要添加的角色: 0-学生, 1-教师: ");
    scanf("%d", &role_input);
    getchar();
    if (role_input != ROLE_STUDENT && role_input != ROLE_TEACHER)
    {
        printf("无效角色。\n");
        press_enter_to_continue();
        return;
    }

    u.role = role_input;
    u.identify = (user_count > 0 ? users[user_count - 1].identify + 1 : 1);

    printf("请输入账号: ");
    fgets(u.id, MAX_NAME_LENGTH, stdin);
    u.id[strcspn(u.id, "\n")] = '\0';

    // 检查账号是否已存在（不区分角色也不允许重复）
    if (find_user_index_by_id(u.id, ROLE_STUDENT) >= 0 || find_user_index_by_id(u.id, ROLE_TEACHER) >= 0 || find_user_index_by_id(u.id, ROLE_ADMIN) >= 0)
    {
        printf("该账号已存在，无法添加。\n");
        press_enter_to_continue();
        return;
    }

    printf("请输入姓名: ");
    fgets(u.name, MAX_NAME_LENGTH, stdin);
    u.name[strcspn(u.name, "\n")] = '\0';

    printf("请输入密码: ");
    fgets(u.password, MAX_PASSWORD_LENGTH, stdin);
    u.password[strcspn(u.password, "\n")] = '\0';

    users[user_count++] = u;
    save_users();

    printf("用户添加成功！\n");
    press_enter_to_continue();
}

/**
 * 管理员删除用户（学生或教师）
 */
void admin_delete_user()
{
    load_users();

    char del_id[MAX_NAME_LENGTH];
    printf("\n请输入要删除的用户账号: ");
    fgets(del_id, MAX_NAME_LENGTH, stdin);
    del_id[strcspn(del_id, "\n")] = '\0';

    // 尝试在学生和教师中查找
    int idx = find_user_index_by_id(del_id, ROLE_STUDENT);
    if (idx < 0)
    {
        idx = find_user_index_by_id(del_id, ROLE_TEACHER);
    }
    if (idx < 0)
    {
        printf("未找到该用户或该用户为管理员，无法删除。\n");
        press_enter_to_continue();
        return;
    }

    // 删除用户
    users[idx] = users[user_count - 1];
    user_count--;
    save_users();

    printf("用户删除成功！\n");
    press_enter_to_continue();
}

/**
 * 管理员修改用户（学生或教师）信息
 */
void admin_modify_user()
{
    load_users();

    char mod_id[MAX_NAME_LENGTH];
    printf("\n请输入要修改的用户账号: ");
    fgets(mod_id, MAX_NAME_LENGTH, stdin);
    mod_id[strcspn(mod_id, "\n")] = '\0';

    int idx = find_user_index_by_id(mod_id, ROLE_STUDENT);
    if (idx < 0)
    {
        idx = find_user_index_by_id(mod_id, ROLE_TEACHER);
    }
    if (idx < 0)
    {
        printf("未找到该用户或该用户为管理员，无法修改。\n");
        press_enter_to_continue();
        return;
    }

    printf("当前姓名: %s\n", users[idx].name);
    printf("请输入新姓名(回车保留原值): ");
    char new_name[MAX_NAME_LENGTH];
    fgets(new_name, MAX_NAME_LENGTH, stdin);
    new_name[strcspn(new_name, "\n")] = '\0';
    if (strlen(new_name) > 0)
    {
        strcpy(users[idx].name, new_name);
    }

    printf("当前密码: %s\n", users[idx].password);
    printf("请输入新密码(回车保留原值): ");
    char new_pwd[MAX_PASSWORD_LENGTH];
    fgets(new_pwd, MAX_PASSWORD_LENGTH, stdin);
    new_pwd[strcspn(new_pwd, "\n")] = '\0';
    if (strlen(new_pwd) > 0)
    {
        strcpy(users[idx].password, new_pwd);
    }

    save_users();
    printf("用户信息修改成功！\n");
    press_enter_to_continue();
}

/**
 * 管理员查询用户（学生或教师）
 */
void admin_query_users()
{
    load_users();

    int choice;
    printf("\n1. 查询所有学生\n");
    printf("2. 查询所有教师\n");
    printf("3. 查询指定账号用户\n");
    printf("输入选项: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1)
    {
        printf("\n所有学生列表：\n");
        printf("---------------------------------------------\n");
        printf("%-10s %-20s %-10s\n", "账号", "姓名", "ID");
        printf("---------------------------------------------\n");
        for (int i = 0; i < user_count; i++)
        {
            if (users[i].role == ROLE_STUDENT)
            {
                printf("%-10s %-20s %-10d\n", users[i].id, users[i].name, users[i].identify);
            }
        }
        printf("---------------------------------------------\n");
    }
    else if (choice == 2)
    {
        printf("\n所有教师列表：\n");
        printf("---------------------------------------------\n");
        printf("%-10s %-20s %-10s\n", "账号", "姓名", "ID");
        printf("---------------------------------------------\n");
        for (int i = 0; i < user_count; i++)
        {
            if (users[i].role == ROLE_TEACHER)
            {
                printf("%-10s %-20s %-10d\n", users[i].id, users[i].name, users[i].identify);
            }
        }
        printf("---------------------------------------------\n");
    }
    else if (choice == 3)
    {
        char query_id[MAX_NAME_LENGTH];
        printf("请输入要查询的用户账号: ");
        fgets(query_id, MAX_NAME_LENGTH, stdin);
        query_id[strcspn(query_id, "\n")] = '\0';

        int idx = find_user_index_by_id(query_id, ROLE_STUDENT);
        if (idx < 0)
        {
            idx = find_user_index_by_id(query_id, ROLE_TEACHER);
        }
        if (idx < 0)
        {
            printf("未找到该用户。\n");
        }
        else
        {
            printf("\n用户信息：\n");
            printf("账号: %s\n", users[idx].id);
            printf("姓名: %s\n", users[idx].name);
            printf("ID: %d\n", users[idx].identify);
            printf("角色: %s\n", users[idx].role == ROLE_STUDENT ? "学生" : "教师");
        }
    }
    else
    {
        printf("无效选项。\n");
    }
    press_enter_to_continue();
}

/**
 * 根据账号和角色查找用户在数组中的索引，找不到返回 -1
 */
int find_user_index_by_id(const char *id, int role)
{
    for (int i = 0; i < user_count; i++)
    {
        if (users[i].role == role && strcmp(users[i].id, id) == 0)
        {
            return i;
        }
    }
    return -1;
}

/**
 * 按回车键继续
 */
void press_enter_to_continue()
{
    printf("\n按回车键继续...");
    getchar();
}
