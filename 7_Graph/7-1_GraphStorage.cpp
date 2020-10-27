/**
 * 第7章 图
 * 7-1 图的存储结构
 * 2020-10-27
 */

#include <stdio.h>
#include <stdlib.h>

/*邻接矩阵的存储实现*/
#define INFINITY INT_MAX   //最大值，表示无穷大
#define MAX_VERTEX_NUM 100 //最大顶点个数
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
typedef struct ArcCell //弧的定义
{
    VRType adj;     //VRType是顶点关系类型
                    //对无权图，用1或0表示是否相邻
                    //对带权图，则为权值类型
    InfoType *info; //该弧相关信息的指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct MGraph //图的类型定义
{
    VertexType vexs[MAX_VERTEX_NUM]; //顶点信息
    AdjMatrix arcs;                  //弧的信息
    int vexnum, arcnum;              //顶点数，弧数
    GraphKind kind;                  //图的种类标志
} MGraph;
MGraph G;

//建立无向网络（边带全图）G的算法详解
void Creategraph(MGraph &G)
{
    int i, j, k;
    float w;
    scanf("%d,%d,%d", G.vexnum, G.arcnum, G.kind);
    for (i = 1; i <= G.vexnum; i++)
        scanf("%c", &G.vexs[i]);
    for (i = 1; i <= G.vexnum; i++)
        for (j = 1; j <= G.vexnum; j++)
        {
            G.arcs[i][j].adj = INFINITY;
            G.arcs[i][j].info = NULL;
        }
    for (k = 1; k <= G.arcnum; k++)
    {
        scanf("%d %d %f", &i, &j, &w);
        G.arcs[i][j].adj = w;
        G.arcs[j][i].adj = w;
    }
}

/*邻接表的存储实现*/
#define MAX_VERTEX_NUM 20
//边表的存储类型：
typedef struct ArcNode
{
    int adjvex;              //该弧所指向的顶点的位置
    struct ArcNode *nextarc; //指向下一条弧的指针
    InfoType *info;          //该弧相关信息的指针
} ArcNode;
//顶点表的存储类型：
typedef struct vnode
{
    VertexType data;   //顶点信息
    ArcNode *firstarc; //指向第一条依附该顶点的弧
} vnode, adjlist[MAX_VERTEX_NUM];
typedef struct
{
    adjlist vertices;
    int vexnum, arcnum;
    int kind; //图的种类标志
} ALGraph;
ALGraph G;

void Creatadilist(ALGraph &G)
{
    int i, j, k;
    ArcNode *s;
    scanf("%d %d %d", G.vexnum, G.arcnum, G.kind);
    for (i = 1; i <= G.vexnum; i++)
    {
        scanf("%d", &G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    for (k = 0; k < G.arcnum; k++)
    {
        scanf("%d %d", &i, &j);
        s = (ArcNode *)malloc(sizeof(ArcNode));
        s->adjvex = j;
        s->info = NULL;
        s->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = s;
    }
}

/*十字链表的存储实现*/
#define MAX_VERTEX_NUM 20
//边表的存储类型：
typedef struct structArcBox
{
    int tailvex, headvex; // 该 该 弧的尾和头位置
    structArcBox *hlink, *tlink;
    //  分别为弧头相同和弧尾相同的弧的链域
    InfoType *info; //  该弧相关信息的指针
} ArcBox;
//顶点表的存储类型：
typedef struct Vexnode
{
    VertexType data; //  顶点信息
    ArcBox *firstin, *firstout;
    //  分别指向下一个入边和出边
} Vexnode;
//图的十字链表存储类型：
typedef struct
{
    Vexnode xlist[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    //  节点个数，边个数
} OLGraph;
OLGraph G;