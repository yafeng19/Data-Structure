/**
 * 第6章 树和二叉树
 * 6-4 线索二叉树
 * 2020-10-19
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TElemType
{
    char name;
};
typedef enum
{
    Link,
    Thread
} PointerThr;
//Link==0:指针；Thread==1:线索
typedef struct BiThrNod
{
    TElemType data;
    struct BiThrNod *lchild, *rchild; //左右指针
    PointerThr LTag, RTag;            //左右标志
} BiThrNod, *BiThrTree;

void visit(TElemType e)
{
    printf("%c", e.name);
}

BiThrTree pre;
//对以p为根的非空二叉树进行中序线索化
void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild); //左子树线索化
        if (!p->lchild)
        {
            p->LTag = Thread;
            p->lchild = pre;
        }
        if (!p->rchild)
        {
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;
        InThreading(p->rchild); //右子树线索化
    }
}
//构建中序线索链表
bool InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
    if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNod))))
        exit(1);
    Thrt->LTag = Link; //添加头结点，其左子树指针指向二叉树，右子树指针先指向自己
    Thrt->RTag = Thread;
    Thrt->rchild = Thrt;
    if (!T) //如果二叉树为空，则头结点指向自己
        Thrt->lchild = Thrt;
    else
    {
        Thrt->lchild = T;
        pre = Thrt;
        InThreading(T);
        pre->RTag = Thread; //处理最后一个结点
        pre->rchild = Thrt;
        Thrt->rchild = pre; //头结点右子树指针指向最后访问的结点
    }
    return true;
}
//对中序线索化链表的遍历算法
bool InOrderTraverse_Thr(BiThrTree T, void (*visit)(TElemType e))
{
    BiThrTree p = T->lchild; //p指向根节点
    while (p != T)           //空树或者遍历结束时，p==T
    {
        while (p->LTag == Link)
            p = p->lchild;                          //第一个结点
        while (p->RTag == Thread && p->rchild != T) //找到第一个结点开始沿线索遍历
        {
            p = p->rchild;
            visit(p->data);
        }
        p = p->rchild; //最后一个结点指回头结点
    }
    return true;
}
