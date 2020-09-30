/**
 * 第3章 栈和队列
 * 3-2 栈的链式实现
 * 2020-09-30 */

#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW 1 //宏定义:失败

typedef struct
{
    char name[15]; 
    int age;
    char sex;
    float score;
}SElemType;
typedef struct SNode
{
    SElemType data;     //数据域
    struct SNode *next; //链域
}SNode, *LinkStack;


bool InitStack(LinkStack &S){
    S = (SNode *)malloc(sizeof(SNode));
    if(!S)
    {
        printf("内存申请失败，程序异常终止\n");
        exit(OVERFLOW);
    }
    S->next = NULL;
    return true;
}
bool Push(LinkStack &S, SElemType e)    //与单链表的头插法操作方式一致
{
    LinkStack p = (SNode *)malloc(sizeof(SNode));
    p->data = e;
    p->next = S->next;
    S->next = p;
    return true;
}
bool Pop(LinkStack &S, SElemType &e)
{
    if(S->next == NULL)
        return false;
    else
    {
        LinkStack p = (SNode *)malloc(sizeof(SNode));
        p = S->next;
        e = p->data;
        S->next = p->next;
        free(p);
        return true;
    }
}
bool DestroyStack(LinkStack &S)
{
    free(S);
    S = NULL;
    return true;
}
bool ClearStack(LinkStack &S)
{
    while(!StackEmpty(S))
    {
        SElemType e ;
        Pop(S, e);
    }
    return true;
}
bool StackEmpty(LinkStack S)
{
    if(S == NULL || S->next == NULL)
        return true;
    else 
        return false;
}
int StackLength(LinkStack S)
{
    int length = 0;
    if(S == NULL)   //被销毁
        return false;
    LinkStack p = S->next;
    while(p)
    {
        length++;
        p = p->next;
    }
    return length;
}
bool GetTop(LinkStack S, SElemType &e)
{
    if(!StackEmpty(S))
        return false;
    else
    {
        e = S->next->data;
        return true;
    }
}


int main()
{
    return 0;
}