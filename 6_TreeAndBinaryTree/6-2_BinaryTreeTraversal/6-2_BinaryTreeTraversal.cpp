/**
 * 第6章 树和二叉树
 * 6-2 二叉树的遍历
 * 2020-10-14
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct ElemType //结点数据域
{
    char TreeName;
};
//二叉链表存储表示
typedef struct BiTNode //二叉链表结点结构
{
    ElemType data;
    struct BiTNode *lchild, *rchild; //左右孩子结点
} BiTNode, *BiTree;
typedef struct SNode //链栈结点结构
{
    BiTree data;        //数据域存储子树
    struct SNode *next; //链域
} SNode, *Stack;
bool StackEmpty(Stack S)
{
    if (S == NULL || S->next == NULL)
        return true;
    else
        return false;
}
bool Push(Stack &S, BiTree T) //入栈操作
{
    Stack p = (SNode *)malloc(sizeof(SNode));
    p->data = T;
    p->next = S->next;
    S->next = p;
    return true;
}
BiTNode *Pop(Stack &S) //出栈操作
{
    BiTNode *t;
    Stack p = (SNode *)malloc(sizeof(SNode));
    p = S->next;
    t = p->data;
    S->next = p->next;
    free(p);
    return t;
}
void PrintStack(Stack &S)
{
    Stack p = S->next;
    while (p->next)
    {
        printf("%c ", p->data->data.TreeName);
    }
    printf("%c", p->data->data.TreeName);
}
//先序遍历算法的递归描述
void Preorder(BiTree T, void (*visit)(ElemType &e))
{
    if (T)
    {
        visit(T->data);             //访问节点
        Preorder(T->lchild, visit); //遍历左子树
        Preorder(T->rchild, visit); //遍历右子树
    }
}

//中序遍历算法的非递归描述
BiTNode *GoFarLeft(BiTree T, Stack &S) //寻找最左下结点
{
    if (!T)
        return NULL;
    while (T->lchild)
    {
        Push(S, T);
        T = T->lchild;
    }
    return T;
}
void Inorder_I(BiTree T, void (*visit)(ElemType &e))
{
    Stack S;
    BiTNode *t;
    ElemType e;
    t = GoFarLeft(T, S);
    while (t)
    {
        visit(t->data);
        if (t->rchild)
            t = GoFarLeft(t->rchild, S);
        else if (!StackEmpty(S))
            t = Pop(S);
        else
            t = NULL;
    }
}

//统计二叉树中叶子结点的个数（先序遍历）
void CountLeaf(BiTree T, int &count)
{
    if (T)
    {
        if (!(T->lchild) && !(T->rchild)) //对叶子结点计数
            count++;
        CountLeaf(T->lchild, count);
        CountLeaf(T->rchild, count);
    }
}

//计算二叉树的深度（后序遍历）
int depthval = 0, depthLeft = 0, depthRight = 0;
int Depth(BiTree T)
{
    if (!T)
        depthval = 0;
    else
    {
        depthLeft = Depth(T->lchild);
        depthRight = Depth(T->rchild);
        depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
    }
    return depthval;
}

//复制二叉树（后序遍历）
BiTNode *GetTreeNode(ElemType item, BiTNode *lptr, BiTNode *rptr) //生成一个二叉树节点
{
    BiTNode *T = (BiTNode *)malloc(sizeof(BiTNode));
    if (!T)
        exit(1);
    T->data = item;
    T->lchild = lptr;
    T->rchild = rptr;
    return T;
}
BiTNode *newlptr, *newrptr, *newT;
BiTNode *CopyTree(BiTNode *T)
{
    if (!T)
        return NULL;
    if (T->lchild)
        newlptr = CopyTree(T->lchild);
    else
        newlptr = NULL;
    if (T->rchild)
        newrptr = CopyTree(T->rchild);
    else
        newrptr = NULL;
    newT = GetTreeNode(T->data, newlptr, newrptr);
    return newT;
}

//以字符串的形式定义一棵二叉树（根 左子树 右子树）
void CreateBiTree(BiTree &T)
{
    char ch;
    scanf(&ch);
    if (ch == ' ')
        T = NULL;
    else
    {
        if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
            exit(1);
        T->data.TreeName = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}
//建立叶子结点
void CrtNode(BiTree &T, char ch)
{
    Stack S;
    T = (BiTNode *)malloc(sizeof(BiTNode));
    T->data.TreeName = ch;
    T->lchild = T->rchild = NULL;
    Push(S, T);
}
//建立子树
void CrtSubtree(BiTree &T, char c)
{
    Stack S;
    BiTNode *rc, *lc;
    T = (BiTNode *)malloc(sizeof(BiTNode)),
    T->data.TreeName = c;
    Pop(S);
    T->rchild = rc;
    Pop(S);
    T->lchild = lc;
    Push(S, T);
}

//输出二叉树上所有从根到叶子结点的路径
void AllPath(BiTree T, Stack &S)
{
    if (T)
    {
        Push(S, T);
        if (!T->lchild && !T->rchild)
            PrintStack(S);
        else
        {
            AllPath(T->lchild, S);
            AllPath(T->rchild, S);
        }
    }
}