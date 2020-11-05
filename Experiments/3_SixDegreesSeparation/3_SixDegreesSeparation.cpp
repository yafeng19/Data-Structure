/**
 * 实验3 六度空间的计算
 * 2020-11-07
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM 105

typedef struct QNode
{
    int data;           //数据域
    struct QNode *next; //链域
} QNode, *QueuePtr;
typedef struct
{
    QueuePtr front; //队头指针
    QueuePtr rear;  //队尾指针
} Queue;

typedef struct EdgeNode //边表存储类型
{
    int adjvertex;             //与顶点表中的顶点邻接的顶点序号
    struct EdgeNode *nextedge; //指向下一顶点的指针
} EdgeNode;
typedef struct VerNode //顶点表的存储类型
{
    int vertex;                 //顶点序号
    struct EdgeNode *firstedge; //指向第一个邻接结点的指针
} VerNode, adjlist;
typedef struct ALGraph
{
    adjlist vertices[MAX_NUM]; //顶点表与边表集
    int vertexnum;             //顶点数
    int edgenum;               //边数
} ALGraph;

bool InitQueue(Queue &Q)
{
    Q.front = Q.rear = (QNode *)malloc(sizeof(QNode));
    if (!Q.front)
        exit(-1);
    Q.front->next = NULL;
    return true;
}
bool QueueEmpty(Queue Q)
{
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}
bool EnQueue(Queue &Q, int e) //插入元素e为Q的新的队尾元素
{
    QueuePtr p = (QNode *)malloc(sizeof(QNode));
    if (!p)
        exit(-1);
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return true;
}
bool DeQueue(Queue &Q, int &e) //取出Q的队首元素e
{
    if (QueueEmpty(Q))
        return false;
    QueuePtr p = (QNode *)malloc(sizeof(QNode));
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) //防止删除p节点时尾指针变为野指针
        Q.rear = Q.front;
    free(p);
    return true;
}
int FirstAdjvex(ALGraph G, int u) //求第一个边表结点序号
{
    return G.vertices[u].firstedge->adjvertex;
}
int NextAdjvex(ALGraph G, int u, int w) //求下一个边表结点序号
{
    struct EdgeNode *p = (struct EdgeNode *)malloc(sizeof(struct EdgeNode));
    p = G.vertices[u].firstedge; //从u结点开始遍历
    while (p)                    //p结点不空
    {
        if (p->adjvertex != w) //找到w结点
            p = p->nextedge;
    }
    if (p->nextedge) //p的下一结点不空返回w结点的下一元素
        return p->nextedge->adjvertex;
    else //否则返回0
        return 0;
}
void ALGraphStorage(ALGraph &G, int first, int second) //图的构建
{
    //顶点表中顶点为0，说明未添加过该节点，需要更新顶点表
    if (!G.vertices[first].vertex)
    {
        G.vertices[first].vertex = first;
        G.vertices[first].firstedge->adjvertex = second;
    }
    //顶点表中顶点非0，说明已经添加过该节点，只需在其边表后添加新的邻接结点
    else
    {
        struct EdgeNode *p = (struct EdgeNode *)malloc(sizeof(struct EdgeNode));
        struct EdgeNode *q = (struct EdgeNode *)malloc(sizeof(struct EdgeNode));
        q->adjvertex = second;
        q->nextedge = NULL;
        p = G.vertices[G.vertices[first].vertex].firstedge; //从首个边表结点开始遍历
        while (p->nextedge)                                 //p结点不空
            p = p->nextedge;
        p->nextedge = q;
        p = q;
    }
}
float BFSTraverse(ALGraph G, int vertex) //广度优先遍历
{
    int visited[MAX_NUM];
    int v, u, w;      //v代表遍历结点序号，u代表当前结点序号
    int count = 0;    //记录广度优先遍历的扩展次数
    int visitsum = 0; //六次扩展内访问到的节点总数
    Queue Q;          //定义辅助队列
    for (v = 0; v <= G.vertexnum; v++)
        visited[v] = 0; //初始化访问标志
    InitQueue(Q);
    v = vertex;        //最初广度优先遍历结点为vertex,且0号结点不使用
    while (count <= 6) //要在六次扩展后结束
    {
        if (!visited[v]) //对于尚未访问的结点
        {
            visited[v] = 1;
            EnQueue(Q, v); //将该结点入队列
            while (!QueueEmpty(Q))
            {
                DeQueue(Q, u); //队头元素出队列并置为u
                for (w = FirstAdjvex(G, u); w != 0; w = NextAdjvex(G, u, w))
                    if (!visited[w])
                    {
                        visited[w] = 1;
                        EnQueue(Q, w); //  访问的顶点w入队列
                    }
                count++;
            }
        }
        v = (v + 1 <= G.vertexnum ? v + 1 : (v + 1) % G.vertexnum);
    }
    for (v = 1; v <= G.vertexnum; v++)
        if (visited[v] == 1)
            visitsum += 1;

    return visitsum / G.vertexnum;
}
int main()
{
    int vertex1, vertex2;
    ALGraph G;
    printf("请依次输入结点数与边数：\n");
    scanf("%d %d", &G.vertexnum, &G.edgenum);
    printf("请依次输入%d对邻接顶点：\n", G.edgenum);
    /*初始化操作*/
    for (int i = 0; i <= G.vertexnum; i++)
        G.vertices[i].vertex = 0; //顶点表均置为0
    /*图的构建操作*/
    for (int i = 1; i <= G.edgenum; i++) //遍历次数为边数
    {
        scanf("%d %d", &vertex1, &vertex2);
        ALGraphStorage(G, vertex1, vertex2); //以vertex1为第一节点进行存储
        ALGraphStorage(G, vertex2, vertex1); //以vertex2为第一节点进行存储
    }
    /*对每个结点进行广度优先遍历，并求解距离小于等于6的结点数占比*/
    for (int i = 1; i <= G.edgenum; i++) //遍历次数为边数
        printf("%.2f%%\n", BFSTraverse(G, G.vertices[i].vertex) * 100);
    return 0;
}
