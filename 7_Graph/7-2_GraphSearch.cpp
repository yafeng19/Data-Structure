/**
 * 第7章 图
 * 7-2 图的搜索
 * 2020-10-26
 */

#include <stdio.h>
#include <stdlib.h>

/*深度优先搜索*/
#define INFINITY INT_MAX   // 最大值
#define MAX_VERTEX_NUM 100 // 最大顶点个数
typedef float VRType;
typedef struct InfoType
{
};
typedef struct VertexType
{
};
typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind;
typedef struct ArcCell
{                   //  弧的定义
    VRType adj;     // VRType 是顶点关系类型
    InfoType *info; //  该弧相关信息的指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{                                    //  图的类型定义
    VertexType vexs[MAX_VERTEX_NUM]; //  顶点信息
    AdjMatrix arcs;                  //  弧的信息
    int vexnum, arcnum;              //  顶点数，弧数
    GraphKind kind;                  //  图的种类标志
} MGraph;
MGraph G;
int w;
int visited[MAX_VERTEX_NUM];
void VisitFunc(int v)
{
}
int FirstAdjVex(MGraph G, int v)
{
}
int NextAdjvex(MGraph G, int v, int w)
{
}
void DFS(MGraph G, int v)
{
    // 从顶点v出发，深度优先搜索遍历连通图 G
    visited[v] = 1;
    VisitFunc(v); //访问v
    for (w = FirstAdjVex(G, v); w != 0; w = NextAdjvex(G, v, w))
        if (!visited[w]) // 对v的尚未访问的邻接顶点w
            DFS(G, w);   // 递归调用DFS
} // DFS
void DFS(MGraph G, int v)
{
    // 从顶点v出发，深度优先搜索遍历连通图 G
    visited[v] = 1;
    printf("%c", G.vexs[v]); //访问v
    for (w = 0; w < G.vexnum; w++)
        if (G.arcs[v][w].adj != 0 && !visited[w])
            // 对v的尚未访问的邻接顶点w
            DFS(G, w); // 递归调用DFS
} // DFS

/*广度优先搜索*/
int v, u;
int visited[MAX_VERTEX_NUM];
typedef struct ArcNode //边表存储类型
{
    int adjvex; //  该弧所指向的顶点的位置
    struct ArcNode *nextarc;
    //  指向下一条弧的指针
    InfoType *info; //  该弧相关信息的指针
} ArcNode;
typedef struct vnode
{                    //顶点表的存储类型
    VertexType data; //  顶点信息
    ArcNode *firstarc;
    //  指向第一条依附该顶点的弧
} vnode, adjlist[MAX_VERTEX_NUM];
typedef struct
{ //图的邻接表存储类型
    adjlist vertices;
    int vexnum, arcnum;
    int kind; //  图的种类标志
} ALGraph;
ALGraph G;
typedef struct Queue
{
};
Queue Q;
void InitQueue(Queue Q)
{
}
bool QueueEmpty(Queue Q)
{
}
void EnQueue(Queue Q, int u)
{
}
void DeQueue(Queue Q, int &u)
{
}
void BFSTraVErse(MGraph G, void (*Visit)(int v))
{
    for (v = 0; v < G.vexnum; ++v)
        visited[v] = 0; // 初始化访问标志
    InitQueue(Q);       //  置空的辅助队列Q
    for (v = 0; v < G.vexnum; ++v)
        if (!visited[v])
        { // v  尚未访问
            visited[v] = 1;
            Visit(v);      //  访问u
            EnQueue(Q, v); // v 入队列
            while (!QueueEmpty(Q))
            {
                DeQueue(Q, u); //  队头元素出队并置为u
                for (w = FirstAdjVex(G, u); w != 0; w = NextAdjvex(G, u, w))
                    if (!visited[w])
                    {
                        visited[w] = 1;
                        Visit(w);
                        EnQueue(Q, w); //  访问的顶点w 入队列
                    }
            }
        }
} // BFSTraVErse