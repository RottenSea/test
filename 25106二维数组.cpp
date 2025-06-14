#include <stdio.h>
#include <math.h>

#define NUM_STUDENTS 5
#define NUM_COURSES 4

// 定义一个结构体来存储学生的学号和总成绩
typedef struct
{
    int id;
    int total_score;
} Student;

// 比较函数，用于 qsort 降序排序
int compare(const void *a, const void *b)
{
    return ((Student *)b)->total_score - ((Student *)a)->total_score;
}

int main()
{
    int scores[NUM_STUDENTS][NUM_COURSES];
    Student students[NUM_STUDENTS];

    // 输入每个学生的 4 门课程成绩
    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        students[i].id = i + 1;
        students[i].total_score = 0;
        printf("请输入第 %d 个学生的 %d 门课程成绩：\n", i + 1, NUM_COURSES);
        for (int j = 0; j < NUM_COURSES; j++)
        {
            scanf("%d", &scores[i][j]);
            students[i].total_score += scores[i][j];
        }
    }

    // 对学生按总成绩降序排序
    qsort(students, NUM_STUDENTS, sizeof(Student), compare);

    // 输出排序后的学号和总成绩
    printf("\n奖学金评定依据（按总成绩降序排列）：\n");
    printf("学号\t总成绩\n");
    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        printf("%d\t%d\n", students[i].id, students[i].total_score);
    }

    return 0;
}