/**
 * 第3章 栈和队列
 * 3-1 栈的顺序实现
 * 2020-09-30 
 */

#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100 //栈容量
#define STACKINCREMENT 10   //栈顶指针
#define OVERFLOW 1          //宏定义:失败

typedef struct
{
    char name[15];
    int age;
    char sex;
    float score;
} SElemType;
typedef struct
{
    SElemType *base; //基地址
    SElemType *top;  //栈顶指针
    int stacksize;   //栈容量
} SqStack;

bool InitStack(SqStack &S)
{
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base)
    {
        printf("内存申请失败，程序异常终止\n");
        exit(OVERFLOW);
    }
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return true;
}
bool Push(SqStack &S, SElemType e)
{
    if (S.top - S.base >= S.stacksize)
    {
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base)
        {
            printf("内存申请失败，程序异常终止\n");
            exit(OVERFLOW);
        }
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top = e; //以下两行可以写成 *S.top++ = e;
    S.top++;
    return true;
}
bool Pop(SqStack &S, SElemType &e)
{
    if (S.top == S.base)
        return false;
    else
    {
        e = *(S.top - 1);
        S.top--;
        return true;
    }
}
bool DestroyStack(SqStack &S)
{
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
    return true;
}
bool ClearStack(SqStack &S)
{
    S.top = S.base;
    return true;
}
bool StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return true;
    else
        return false;
}
int StackLength(SqStack S)
{
    return S.top - S.base;
}
bool GetTop(SqStack S, SElemType &e)
{
    if (S.top == S.base)
        return false;
    else
    {
        e = *(S.top - 1);
        return true;
    }
}

int main()
{
    return 0;
}