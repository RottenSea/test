#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

/* 找到 parent=0 的两个最小节点 */
void Select(HuffmanTree HT, int n, int *s1, int *s2)
{
    int i;
    *s1 = *s2 = 0;

    for (i = 1; i <= n; i++)
    {
        if (HT[i].parent == 0)
        {
            if (*s1 == 0 || HT[i].weight < HT[*s1].weight)
                *s1 = i;
        }
    }

    for (i = 1; i <= n; i++)
    {
        if (HT[i].parent == 0 && i != *s1)
        {
            if (*s2 == 0 || HT[i].weight < HT[*s2].weight)
                *s2 = i;
        }
    }
}

/* 构造哈夫曼树 */
void CreateHuffmanTree(HuffmanTree *HT, int w[], int n)
{
    int m = 2 * n - 1;
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));

    for (int i = 1; i <= m; i++)
    {
        (*HT)[i].parent = (*HT)[i].lchild = (*HT)[i].rchild = 0;
        if (i <= n)
            (*HT)[i].weight = w[i];
        else
            (*HT)[i].weight = 0;
    }

    for (int i = n + 1; i <= m; i++)
    {
        int s1, s2;
        Select(*HT, i - 1, &s1, &s2);
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}

/* 生成哈夫曼编码 */
void GenerateCodes(HuffmanTree HT, char *codes[], int n, char ch[])
{
    char temp[100];
    int start, c, p;

    for (int i = 1; i <= n; i++)
    {
        start = 99;
        temp[start] = '\0';
        c = i;
        p = HT[c].parent;

        while (p != 0)
        {
            if (HT[p].lchild == c)
                temp[--start] = '0';
            else
                temp[--start] = '1';

            c = p;
            p = HT[p].parent;
        }

        codes[i] = (char *)malloc(100 - start);
        strcpy(codes[i], &temp[start]);
    }

    printf("哈夫曼编码：\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%c : %s\n", ch[i], codes[i]);
    }
}

/* 解码 */
void Decode(HuffmanTree HT, int root, const char *code, char ch[])
{
    printf("\n解码结果：");
    int p = root;

    for (int i = 0; code[i]; i++)
    {
        if (code[i] == '0')
            p = HT[p].lchild;
        else
            p = HT[p].rchild;

        if (HT[p].lchild == 0 && HT[p].rchild == 0)
        {
            printf("%c ", ch[p]);
            p = root;
        }
    }
    printf("\n");
}

int main()
{
    /* 示例：A:5 B:9 C:12 D:13 E:16 F:45 */
    int n = 6;
    int w[7] = {0, 5, 9, 12, 13, 16, 45};
    char ch[7] = {0, 'A', 'B', 'C', 'D', 'E', 'F'};

    HuffmanTree HT;
    CreateHuffmanTree(&HT, w, n);

    char *codes[7];
    GenerateCodes(HT, codes, n, ch);

    /* 测试解码 */
    const char *test = "1001011"; // 示例
    printf("\n输入编码：%s\n", test);
    Decode(HT, 2 * n - 1, test, ch);

    return 0;
}
