/**
 * 第3章 栈和队列
 * 3-3 队列的链式实现
 * 2020-09-30 
 */

#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW 1 //宏定义:失败

typedef struct
{
    char name[15];
    int age;
    char sex;
    float score;
} QElemType;
typedef struct QNode
{
    QElemType data;     //数据域
    struct QNode *next; //链域
} QNode, *QueuePtr;
typedef struct
{
    QueuePtr front; //队头指针
    QueuePtr rear;  //队尾指针
} LinkQueue;

bool InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QNode *)malloc(sizeof(QNode));
    if (!Q.front)
        exit(OVERFLOW);
    Q.front->next = NULL;
    return true;
}
bool DestroyQueue(LinkQueue &Q)
{
    while (Q.front)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return true;
}
bool ClearQueue(LinkQueue &Q)
{
    QueuePtr p;
    while (Q.front->next)
    {
        p = Q.front->next;
        Q.front->next = p->next;
        free(p);
    }
    return true;
}
bool QueueEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}
int QueueLength(LinkQueue Q)
{
    return Q.rear - Q.front;
}
bool GetHead(LinkQueue Q, QElemType &e)
{
    if (QueueEmpty(Q))
        return false;
    QueuePtr p = (QNode *)malloc(sizeof(QNode));
    p = Q.front->next;
    e = p->data;
    return true;
}
bool EnQueue(LinkQueue &Q, QElemType e) //插入元素e为Q的新的队尾元素
{
    QueuePtr p = (QNode *)malloc(sizeof(QNode));
    if (!p)
        exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return true;
}
bool DeQueue(LinkQueue &Q, QElemType &e) //取出Q的队首元素e
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