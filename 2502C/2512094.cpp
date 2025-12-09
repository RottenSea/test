#include <stdio.h>
#include <stdlib.h>

#define MAXV 20 // 最大顶点数

/* —— 邻接表结点 —— */
typedef struct ArcNode
{
    int adjvex;           // 指向的邻接点下标
    struct ArcNode *next; // 指向下一条边
} ArcNode;

/* —— 顶点表结点 —— */
typedef struct
{
    char data;      // 顶点名称 (例如 A B C...)
    ArcNode *first; // 指向第一条邻接边
} VNode;

/* —— 图结构 —— */
typedef struct
{
    VNode adjlist[MAXV]; // 顶点链表
    int n, e;            // 顶点数、边数
} ALGraph;

/* —— 队列 —— */
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

/* —— 创建有向图的邻接表 —— */
void CreateALGraph(ALGraph *G)
{
    int i, j, k;
    printf("请输入顶点数量 n：");
    scanf("%d", &G->n);

    printf("请输入边数量 e：");
    scanf("%d", &G->e);

    printf("请输入 %d 个顶点名称（例如 A B C D）:\n", G->n);
    for (i = 0; i < G->n; i++)
    {
        scanf(" %c", &G->adjlist[i].data);
        G->adjlist[i].first = NULL;
    }

    printf("请输入每条边（格式：i j）表示 i → j：\n");
    for (k = 0; k < G->e; k++)
    {
        scanf("%d %d", &i, &j);

        // 创建边结点 (i → j)
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->next = G->adjlist[i].first;
        G->adjlist[i].first = p;
    }
}

/* —— 广度优先遍历 BFS —— */
void BFS(ALGraph *G, int start)
{
    int visited[MAXV] = {0};
    Queue q;
    InitQueue(&q);

    printf("BFS 遍历结果：");

    visited[start] = 1;
    printf("%c ", G->adjlist[start].data);
    EnQueue(&q, start);

    while (!Empty(&q))
    {
        int v = DeQueue(&q);

        ArcNode *p = G->adjlist[v].first;
        while (p)
        {
            int j = p->adjvex;
            if (!visited[j])
            {
                visited[j] = 1;
                printf("%c ", G->adjlist[j].data);
                EnQueue(&q, j);
            }
            p = p->next;
        }
    }
    printf("\n");
}

/* —— 示例运行：有向图 —— */
/*
    示例图（有向）：

        A → B → D
        ↓   ↓
        C → E

    顶点：A B C D E
    边：
        A→B  A→C
        B→D  B→E
        C→E
*/
void ExampleRun()
{
    ALGraph G;
    G.n = 5;
    G.e = 6;

    // 顶点
    G.adjlist[0].data = 'A';
    G.adjlist[1].data = 'B';
    G.adjlist[2].data = 'C';
    G.adjlist[3].data = 'D';
    G.adjlist[4].data = 'E';

    for (int i = 0; i < G.n; i++)
        G.adjlist[i].first = NULL;

    // 手动添加边：注意是头插法
    int edges[][2] = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 4}};

    for (int k = 0; k < 5; k++)
    {
        int i = edges[k][0], j = edges[k][1];
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->next = G.adjlist[i].first;
        G.adjlist[i].first = p;
    }

    printf("======= 示例图 BFS 从 A 开始 =======\n");
    BFS(&G, 0);
}

/* —— 主函数 —— */
int main()
{
    ALGraph G;
    CreateALGraph(&G);

    int start;
    printf("请输入 BFS 起点编号（0 ~ %d）：", G.n - 1);
    scanf("%d", &start);

    BFS(&G, start);

    return 0;
}
