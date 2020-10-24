/**
 * 实验1 一元多项式的求导
 * 2020-10-24
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int coef; //系数
    int expn; //指数
} ElemType;
typedef struct LNode
{
    ElemType data;      //数据域
    struct LNode *next; //指针域
} LNode, *Polynomial;

bool InitPolyn(Polynomial &P) //构造一个带有头结点的空线性表L
{
    P = (LNode *)malloc(sizeof(LNode));
    if (!P) //申请内存失败，L为NULL
    {
        printf("内存申请失败，程序异常终止\n");
        exit(1);
    }
    P->next = NULL;
    return true;
}
void CreatePolyn(Polynomial &P) //尾插法，顺序输入
{
    InitPolyn(P); //先建立一个带头结点的空链表
    Polynomial r = P;
    do
    {
        Polynomial p = (LNode *)malloc(sizeof(LNode));
        scanf("%d %d", &(p->data.coef), &(p->data.expn));
        r->next = p;
        r = p;
        r->next = NULL; //保证尾结点指针域为空
    } while (getchar() != '\n');
}
void Derivative(Polynomial &P) //求导函数
{
    Polynomial p = P->next;
    while (p->next)
    {
        p->data.coef *= p->data.expn;
        p->data.expn == 0 ? p->data.expn = 0 : p->data.expn -= 1; //常数项求导为0
        p = p->next;
    }
    //最后一项
    p->data.coef *= p->data.expn;
    p->data.expn == 0 ? p->data.expn = 0 : p->data.expn -= 1; //常数项求导为0
}
void DisplayPolyn(Polynomial P)
{
    Polynomial p = P->next;
    if (P->next->data.expn) //如果输入的多项式不是一项常数项
    {
        while (p->next)
        {
            if (p->data.coef) //如果系数等于0就不显示
                printf("%d %d ", p->data.coef, p->data.expn);
            p = p->next;
        }
        if (p->data.coef)                                  //如果系数等于0就不显示
            printf("%d %d\n", p->data.coef, p->data.expn); //最后一项
    }
    else
    {
        printf("%d %d\n", p->data.coef, p->data.expn); //如果只有一项常数项，求导后输出0 0
    }
}
int main()
{
    Polynomial P;
    CreatePolyn(P);
    Derivative(P);
    DisplayPolyn(P);
    return 0;
}