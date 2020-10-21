/**
 * 第6章 树和二叉树
 * 6-5 树和森林的遍历
 * 2020-10-21
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Elem
{
    char name;
} Elem;
typedef struct CSNode
{
    Elem data;
    struct CSNode *firstchild;
    struct CSNode *nextsibling;
} CSNode, *CSTree;
typedef struct SNode //链栈结点结构
{
    CSTree data;        //数据域存储子树
    struct SNode *next; //链域
} SNode, *Stack;
typedef struct QNode
{
    Elem data;          //数据域
    struct QNode *next; //链域
} QNode, *QueuePtr;
typedef struct
{
    QueuePtr front; //队头指针
    QueuePtr rear;  //队尾指针
} Queue;

bool Push(Stack &S, CSTree T) //入栈操作
{
    Stack p = (SNode *)malloc(sizeof(SNode));
    p->data = T;
    p->next = S->next;
    S->next = p;
    return true;
}
CSNode *Pop(Stack &S) //出栈操作
{
    CSNode *t;
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
        printf("%c ", p->data->data.name);
    }
    printf("%c", p->data->data.name);
}
CSNode *GetTreeNode(char ch)
{
}
void GetHead(Queue Q, CSTree s)
{
}
void EnQueue(Queue Q, CSTree p)
{
}
void DeQueue(Queue Q, CSTree p)
{
}

//求树的深度
int TreeDepth(CSTree T)
{
    if (!T)
        return 0;
    else
    {
        int h1 = TreeDepth(T->firstchild);
        int h2 = TreeDepth(T->nextsibling);
        return h1 + 1 > h2 ? h1 + 1 : h2;
    }
}

//输出森林中所有从根到叶子结点的路径
void OutPath(CSTree T, Stack &S)
{
    while (T)
    {
        Push(S, T);
        if (!T->firstchild)
            PrintStack(S);
        else
            OutPath(T->firstchild, S);
        Pop(S);
        T = T->nextsibling; //往右走前需要出栈，因为右链域为兄弟
    }
}

//建树的存储结构的算法
void CreatTree(CSTree &T)
{
    T = NULL;
    CSTree p, r, s;
    Queue Q;
    char fa, ch;
    for (scanf("%c %c", &fa, &ch); ch != '#'; scanf("%c %c", &fa, &ch))
    {
        p = GetTreeNode(ch);
        EnQueue(Q, p);
        if (fa == '#')
            T = p;
        else
        {
            GetHead(Q, s);
            while (s->data.name != fa)
            {
                DeQueue(Q, s);
                GetHead(Q, s);
            }
            if (!(s->firstchild))
            {
                s->firstchild = p;
                r = p;
            }
            else
            {
                r->nextsibling = p;
                r = p;
            }
        }
    }
}