#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 定义图片和答案的结构体
typedef struct
{
    char *name;            // 答案
    char *description;     // 提示信息
    const char *image[20]; // 文本图像
    int image_height;      // 图像高度
} Picture;

// 图片数据库
Picture pictures[] = {
    {"cat",
     "一种常见的家养宠物，喜欢吃鱼和老鼠",
     {"  /\\_/\\  ",
      " ( o.o ) ",
      "  > ^ <  ",
      NULL},
     3},
    {"tree",
     "一种高大的植物，有树干和叶子",
     {"    ^    ",
      "   ^^^   ",
      "  ^^^^^  ",
      " ^^^^^^^ ",
      "    |    ",
      "    |    ",
      NULL},
     6},
    {"house",
     "人们居住的地方",
     {"  ^ ^  ",
      " ^   ^ ",
      "^     ^",
      "|     |",
      "|  |  |",
      "|__|__|",
      NULL},
     6},
    {"car",
     "一种交通工具",
     {"  ______",
      " /      \\",
      "|        |",
      "|  O  O  |",
      " \\______/",
      NULL},
     5},
    {"sun",
     "天空中发光发热的天体",
     {"  ***  ",
      " ***** ",
      "*******",
      " ***** ",
      "  ***  ",
      NULL},
     5}};

// 计算图片数量
#define NUM_PICTURES (sizeof(pictures) / sizeof(Picture))

// 显示文本图像
void display_image(const char *image[])
{
    printf("\n");
    for (int i = 0; image[i] != NULL; i++)
    {
        printf("  %s\n", image[i]);
    }
    printf("\n");
}

// 游戏主函数
int main()
{
    char guess[50];
    int score = 0;
    int rounds_played = 0;
    int used[NUM_PICTURES] = {0}; // 记录已使用的图片
    int remaining = NUM_PICTURES;

    srand(time(NULL)); // 初始化随机数生成器

    printf("=================================\n");
    printf("        猜图大挑战游戏           \n");
    printf("=================================\n");
    printf("游戏规则：\n");
    printf("1. 系统会显示一个用字符组成的图片\n");
    printf("2. 你需要猜出图片所代表的物品\n");
    printf("3. 输入答案（小写字母）并按回车\n");
    printf("4. 猜对得分，还可以获得提示哦！\n");
    printf("=================================\n\n");

    // 游戏循环，直到所有图片都被猜过
    while (remaining > 0)
    {
        rounds_played++;
        int index;

        // 随机选择一张未使用的图片
        do
        {
            index = rand() % NUM_PICTURES;
        } while (used[index]);

        used[index] = 1;
        remaining--;

        printf("第 %d 轮 - 得分: %d\n", rounds_played, score);
        printf("请看图片：\n");
        display_image(pictures[index].image);

        // 猜图过程
        int attempts = 3; // 每轮3次猜测机会
        int correct = 0;

        while (attempts > 0)
        {
            printf("请输入你的答案（还有 %d 次机会）: ", attempts);
            fflush(stdin);
            fgets(guess, sizeof(guess), stdin);
            // 移除换行符
            guess[strcspn(guess, "\n")] = '\0';

            if (strcmp(guess, pictures[index].name) == 0)
            {
                printf("恭喜你，猜对了！\n\n");
                score += attempts * 10; // 剩余次数越多，得分越高
                correct = 1;
                break;
            }
            else
            {
                attempts--;
                if (attempts > 0)
                {
                    // 最后一次机会时给出提示
                    if (attempts == 1)
                    {
                        printf("不对哦，给你一个提示：%s\n", pictures[index].description);
                    }
                    else
                    {
                        printf("不对哦，请再试一次！\n");
                    }
                }
            }
        }

        if (!correct)
        {
            printf("很遗憾，你没能猜对。正确答案是：%s\n\n", pictures[index].name);
        }
    }

    // 游戏结束，显示结果
    printf("=================================\n");
    printf("游戏结束！\n");
    printf("你一共完成了 %d 轮挑战\n", rounds_played);
    printf("你的最终得分是：%d\n", score);

    // 根据得分给出评价
    float percentage = (float)score / (NUM_PICTURES * 30) * 100;
    if (percentage >= 90)
    {
        printf("太棒了，你是猜图高手！\n");
    }
    else if (percentage >= 60)
    {
        printf("不错哦，继续努力！\n");
    }
    else
    {
        printf("加油，多练习就能提高啦！\n");
    }
    printf("=================================\n");

    return 0;
}