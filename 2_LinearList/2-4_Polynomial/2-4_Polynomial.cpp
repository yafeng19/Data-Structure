/**
 * 第2章 线性表 
 * 2-4 一元多项式的表示与相加
 * 2020-09-28*/


#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW 1 //宏定义:失败


typedef struct
{
    float coef; //系数
    int expn;   //指数
}ElemType;
typedef struct LNode
{
    ElemType data;  //数据域
    struct LNode *next;     //指针域
}LNode, *LinkList;
typedef LinkList Polynomial;


bool InitList(Polynomial &P) //构造一个带有头结点的空线性表L
{
    P = (LNode *)malloc(sizeof(LNode));
    if(!P) //申请内存失败，L为NULL
    {
        printf("内存申请失败，程序异常终止\n");
        exit(OVERFLOW);
    }
    P->next == NULL;
    return true;
}
void CreateList(Polynomial &P, int n) //尾插法，顺序输入
{
    InitList(P);    //先建立一个带头结点的空链表
    Polynomial r = P;
    for(int i = n; i > 0; i--)
    {
        Polynomial p = (LNode *)malloc(sizeof(LNode));
        scanf("%f %d", &((p->data).coef), &((p->data).expn));
        r->next = p;
        r = p;
        r->next = NULL; //保证尾结点指针域为空
    }
}
bool ListEmpty(Polynomial P) //判断线性表L是否为空
{
    if(P == NULL || P->next == NULL)    //被销毁或者为空表
        return true;
    else 
        return false;
}
void DisplayList(Polynomial P)
{
    Polynomial p = P->next;
    if(!ListEmpty(P))
    {
        printf("f(x) = ");
        while(p->next)
        {
            printf("%fx^%d + ", (p->data).coef, (p->data).expn);
            p = p->next;
        }
        printf("%fx^%d", (p->data).coef, (p->data).expn);   //最后一项的输出格式
    }
}

int main()
{
    char iscreate ;
    int num, oper;
    printf("是否创建一元多项式？y/n \n");
    scanf("%c", &iscreate);
    if (iscreate != 'y'&& iscreate != 'Y')
    {
        printf("程序结束\n");
        exit(0);
    }
    else
    {
        printf("请输入项数\n");
        scanf("%d", &num);
        Polynomial P;
        CreateList(P, num);
        DisplayList(P);
    }
}