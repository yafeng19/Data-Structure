/**
 * 第6章 树和二叉树
 * 6-3 由先缀表达式建树
 * 2020-10-14
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct SNode //链栈结点结构
{
    union
    {
        char data;
        BiTree tree; //数据域存储子树
    };
    struct SNode *next; //链域
} SNode, *Stack;
bool InitStack(Stack &S)
{
    S = (SNode *)malloc(sizeof(SNode));
    if (!S)
    {
        printf("内存申请失败，程序异常终止\n");
        exit(1);
    }
    S->next = NULL;
    return true;
}
bool StackEmpty(Stack S)
{
    if (S == NULL || S->next == NULL)
        return true;
    else
        return false;
}
char GetTop(Stack S)
{
    if (StackEmpty(S))
        return S->next->data;
}
typedef struct BiTNode //二叉链表结点结构
{
    char data;
    struct BiTNode *lchild, *rchild; //左右孩子结点
} BiTNode, *BiTree;
bool Push(Stack &S, char t) //入栈操作
{
    Stack p = (SNode *)malloc(sizeof(SNode));
    p->data = t;
    p->next = S->next;
    S->next = p;
    return true;
}
void Pop(Stack &S, BiTree &T) //出栈操作
{
    Stack p = (SNode *)malloc(sizeof(SNode));
    p = S->next;
    T = p->tree;
    S->next = p->next;
    free(p);
}
bool precede(char c, char ch)
{
}
bool IN(char ch, Stack S)
{
}

Stack PTR;
//建立叶子结点
void CrtNode(BiTree &T, char ch)
{
    BiTNode *T = (BiTNode *)malloc(sizeof(BiTNode));
    T->data = ch;
    T->lchild = T->rchild = NULL;
    Push(PTR, T->data);
}
//建立子树的算法
void CrtSubtree(BiTree &T, char c)
{
    BiTree rc, lc;
    BiTNode *T = (BiTNode *)malloc(sizeof(BiTNode));
    T->data = c;
    Pop(PTR, rc);
    T->rchild = rc;
    Pop(PTR, lc);
    T->lchild = lc;
}
void CrtExptree(BiTree &T, char exp[])
{
    Stack S, OP;
    BiTree t;
    InitStack(S);
    Push(S, '#');
    InitStack(PTR);
    char *p = exp;
    char ch = *p, c;
    while (!(GetTop(S) == '#' && ch == '#'))
    {
        if (!IN(ch, OP))
            CrtNode(t, ch);
        else
        {
            switch (ch)
            {
            case '(':
                Push(S, ch);
                break;
            case ')':
            {
                Pop(S, t);
                while (c != '(')
                {
                    CrtSubtree(t, c); //建立二叉树并入栈
                    Pop(S, t);
                }
                break;
            }
            default:
            {
                while (GetTop(S) && (precede(c, ch)))
                {
                    CrtSubtree(t, c);
                    Pop(S, t);
                    if (ch != '#')
                        Push(S, ch);
                    break;
                }
            }
            }
        }
        if (ch != '#')
        {
            p++;
            ch = *p;
        }
        Pop(PTR, T);
    }
}

typedef struct QNode
{
    char data;          //数据域
    struct QNode *next; //链域
} QNode, *QueuePtr;
typedef struct
{
    QueuePtr front; //队头指针
    QueuePtr rear;  //队尾指针
} Queue;

bool InitQueue(Queue &Q)
{
    Q.front = Q.rear = (QNode *)malloc(sizeof(QNode));
    if (!Q.front)
        exit(1);
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
bool EnQueue(Queue &Q, char e) //插入元素e为Q的新的队尾元素
{
    QueuePtr p = (QNode *)malloc(sizeof(QNode));
    if (!p)
        exit(1);
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return true;
}
bool DeQueue(Queue &Q, char &e) //取出Q的队首元素e
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
void visit(char name)
{
    printf("%c", name);
}
//利用队列对二叉树进行层次遍历
bool LevelOrderTraverse(BiTree T)
{
    Queue Q;
    BiTree E;
    InitQueue(Q);
    if (T)
        EnQueue(Q, T->data);
    while (!(QueueEmpty(Q)))
    {
        DeQueue(Q, E->data);
        visit(E->data);
        if (E->lchild)
            EnQueue(Q, E->lchild->data);
        if (E->rchild)
            EnQueue(Q, E->rchild->data);
    }
}