#include <stdio.h>
#include <stdlib.h>

#define MAXV 20 // 最大顶点数
#define INF 0   // 无权图，0 表示无边

typedef struct
{
    char vertex[MAXV];   // 顶点名称，如 A B C D
    int adj[MAXV][MAXV]; // 邻接矩阵
    int n;               // 顶点数
    int e;               // 边数
} MGraph;

/* 队列结构 */
typedef struct
{
    int data[MAXV];
    int front, rear;
} Queue;

void InitQueue(Queue *q)
{
    q->front = q->rear = 0;
}
int Empty(Queue *q)
{
    return q->front == q->rear;
}
void EnQueue(Queue *q, int x)
{
    q->data[q->rear++] = x;
}
int DeQueue(Queue *q)
{
    return q->data[q->front++];
}

/* —— 构造无向图：邻接矩阵 —— */
void CreateGraph(MGraph *G)
{
    int i, j, k;
    printf("请输入顶点数量 n：");
    scanf("%d", &G->n);

    printf("请输入边数量 e：");
    scanf("%d", &G->e);

    printf("请输入 %d 个顶点名称（例如 A B C D）:\n", G->n);
    for (i = 0; i < G->n; i++)
    {
        scanf(" %c", &G->vertex[i]);
    }

    /* 初始化邻接矩阵为 0（无边） */
    for (i = 0; i < G->n; i++)
        for (j = 0; j < G->n; j++)
            G->adj[i][j] = INF;

    printf("请输入每条边 (格式：i j  表示顶点 i 与顶点 j 相连)：\n");
    for (k = 0; k < G->e; k++)
    {
        scanf("%d %d", &i, &j);
        G->adj[i][j] = 1;
        G->adj[j][i] = 1; // 无向图对称
    }
}

/* —— BFS 遍历 —— */
void BFS(MGraph *G, int start)
{
    int visited[MAXV] = {0};
    Queue q;
    InitQueue(&q);

    printf("BFS 遍历顺序：");

    /* 从 start 开始 */
    visited[start] = 1;
    printf("%c ", G->vertex[start]);
    EnQueue(&q, start);

    while (!Empty(&q))
    {
        int v = DeQueue(&q);

        /* 遍历所有邻接顶点 */
        for (int i = 0; i < G->n; i++)
        {
            if (G->adj[v][i] != INF && visited[i] == 0)
            {
                visited[i] = 1;
                printf("%c ", G->vertex[i]);
                EnQueue(&q, i);
            }
        }
    }
    printf("\n");
}

/* —— 示例图：A-B-C-D —— */
void ExampleRun()
{
    /*
        示例图结构（无向图）：

        A -- B
             |
             C -- D

        顶点: A B C D
        边: (A,B) (B,C) (C,D)
    */

    printf("======= 示例自动运行 =======\n");

    MGraph G;
    G.n = 4;
    G.e = 3;

    G.vertex[0] = 'A';
    G.vertex[1] = 'B';
    G.vertex[2] = 'C';
    G.vertex[3] = 'D';

    /* 初始化邻接矩阵 */
    for (int i = 0; i < G.n; i++)
        for (int j = 0; j < G.n; j++)
            G.adj[i][j] = INF;

    G.adj[0][1] = G.adj[1][0] = 1; // A-B
    G.adj[1][2] = G.adj[2][1] = 1; // B-C
    G.adj[2][3] = G.adj[3][2] = 1; // C-D

    BFS(&G, 0); // 从 A 开始 BFS
}

/* —— 主程序 —— */
int main()
{
    MGraph G;
    CreateGraph(&G);

    int start;
    printf("请输入 BFS 起始顶点编号（0 ~ %d）:", G.n - 1);
    scanf("%d", &start);

    BFS(&G, start);

    return 0;
}
