/**
 * 第3章 栈和队列
 * 3-4 队列的循环顺序实现
 * 2020-09-30 */


#include <stdio.h>
#include <stdlib.h>
#define MAXQSIZE 100    //最大队列长度
#define OVERFLOW 1 //宏定义:失败


typedef struct
{
    char name[15]; 
    int age;
    char sex;
    float score;
}QElemType;
typedef struct
{
    QElemType *base;
    int front;
    int rear;
}SqQueue;


bool InitQueue(SqQueue &Q)
{
    Q.base = (QElemType *)malloc(MAXQSIZE *sizeof(QElemType));
    if(!Q.base)
        exit(OVERFLOW);
    Q.front = Q.rear = 0;   //队首和队尾都指向第一个元素
    return true;
}
bool DestroyQueue(SqQueue &Q)
{
    free(Q.base);
    Q.base = NULL;
    return true;
}
bool ClearQueue(SqQueue &Q)
{
    Q.front = Q.rear = 0;
    return true;
}
bool QueueEmpty(SqQueue Q)
{
    if(Q.front == Q.rear)
        return true;
    else 
        return false;
}
int QueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}
bool GetHead(SqQueue Q, QElemType &e)
{
    if(QueueEmpty(Q))
        return false;
    e = Q.base[Q.front];
    return true;
}
bool EnQueue(SqQueue &Q, QElemType e)     //插入元素e为Q的新的队尾元素
{
    if((Q.rear+1) % MAXQSIZE == Q.front)
        return false;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear+1) % MAXQSIZE;
    return true;
}
bool DeQueue(SqQueue &Q, QElemType &e)    //取出Q的队首元素e
{
    if(QueueEmpty(Q))
        return false;
    e = Q.base[Q.front];
    Q.front = (Q.front+1) % MAXQSIZE;
    return true;
}