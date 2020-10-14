/**
 * 第6章 树和二叉树
 * 5-1 二叉树的存储
 * 2020-10-12 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TElemType //结点数据域
{
};

//二叉树的顺序存储表示
#define MAX_TREE_SIZE 100                  //二叉树的最大结点数
typedef TElemType SqBiTree[MAX_TREE_SIZE]; //0号单元存储根节点
SqBiTree bt;

//二叉链表存储表示
typedef struct BiTNode //结点结构
{
    TElemType data;
    struct BiTNode *lchild, *rchild; //左右孩子结点
} BiTNode, *BiTree;

//三叉链表存储表示
typedef struct BiTNode //结点结构
{
    TElemType data;
    struct TriTNode *lchild, *rchild; //左右孩子结点
    struct TriTNode *parent;          //双亲结点
} TriTNode, *TriTree;

//双亲链表存储表示
typedef struct BPTNode //结点结构
{
    TElemType data;
    int *parent; //指向双亲的指针
    char LRTag;  //左右孩子标志域
} BPTNode;
typedef struct BPTree //树结构
{
    BPTNode nodes[MAX_TREE_SIZE];
    int num_node; //结点数目
    int root;     //根节点的位置
} BPTree;