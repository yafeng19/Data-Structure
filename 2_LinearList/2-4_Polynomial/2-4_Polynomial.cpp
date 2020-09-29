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
}LNode, *Polynomial;


bool InitPolyn(Polynomial &P) //构造一个带有头结点的空线性表L
{
    P = (LNode *)malloc(sizeof(LNode));
    if(!P) //申请内存失败，L为NULL
    {
        printf("内存申请失败，程序异常终止\n");
        exit(OVERFLOW);
    }
    P->next = NULL;
    return true;
}
void CreatePolyn(Polynomial &P, int n) //尾插法，顺序输入
{
    InitPolyn(P);    //先建立一个带头结点的空链表
    Polynomial r = P;
    for(int i = n; i > 0; i--)
    {
        Polynomial p = (LNode *)malloc(sizeof(LNode));
        scanf("%f %d", &(p->data.coef), &(p->data.expn));
        fflush(stdin);  //避免指数输入错误
        r->next = p;
        r = p;
        r->next = NULL; //保证尾结点指针域为空
    }
}
bool PolynEmpty(Polynomial P) //判断线性表L是否为空
{
    if(P->next == NULL)    //多项式为空
        return true;
    else 
        return false;
}
int PolynLength(Polynomial P)   //求多项式的项数
{
    int length = 0;
    if(P == NULL)   //被销毁
        return 0;
    LNode *p = P->next;
    while(p)
    {
        length++;
        p = p->next;
    }
    return length;
}
void SortPolyn(Polynomial &P)    //链表的冒泡排序
{
    LNode *p = NULL, *q = NULL, *temp = NULL;
    if(!PolynEmpty(P))
    {
        LNode *temp = (LNode *)malloc(sizeof(LNode));   //要为暂存结点开辟空间
        for(p = P->next; p != NULL; p = p->next)
        {
            for(q = P->next; q->next != NULL; q = q->next)
            {
                if(q->data.expn < q->next->data.expn)
                {
                    temp->data = q->data;
                    q->data = q->next->data;
                    q->next->data = temp->data;
                }
                else if(q->data.expn == q->next->data.expn)
                {
                    LNode *t = q->next;
                    q->data.coef += t->data.coef;
                    q->next = t->next;
                    free(t); 
                    if(q->next == NULL)     //当最后两项可以合并的时候注意跳出循环
                        return ;
                }
            }
        }
        free(temp);
    }
}
void AddPolyn(Polynomial Pa, Polynomial Pb, Polynomial &Pc)
{
    LNode *r = Pc, *pa = Pa->next, *pb = Pb->next;
    if(!PolynEmpty(Pa) && !PolynEmpty(Pb))
    {
        while(pa->next && pb->next)
        {
            LNode *p = (LNode *)malloc(sizeof(LNode));
            if(pa->data.expn > pb->data.expn)
            {
                p->data = pa->data;
                r->next = p;
                r = p;
                r->next = NULL;
                pa = pa->next;
            }
            else if(pa->data.expn < pb->data.expn)
            {
                p->data = pb->data;
                r->next = p;
                r = p;
                r->next = NULL;
                pb = pb->next;
            }
            else
            {
                p->data.coef = pa->data.coef + pb->data.coef;
                p->data.expn = pa->data.expn;
                r->next = p;
                r = p;
                r->next = NULL;
                pa = pa->next;
                pb = pb->next;
            }
        }
        if(!(pa->next)) //Pa链表遍历完毕，则需将Pb链表直接加在Pc之后
        {
            LNode *p = (LNode *)malloc(sizeof(LNode));
            p->data = pa->data;
            r->next = p;
            r = p;
            r->next = NULL;
            while(pb->next)
            {
                LNode *p = (LNode *)malloc(sizeof(LNode));
                p->data = pb->data;
                r->next = p;
                r = p;
                r->next = NULL;
                pb = pb->next;
            }
            LNode *pl = (LNode *)malloc(sizeof(LNode));
            pl->data = pb->data;
            r->next = pl;
            r = pl;
            r->next = NULL;
        }
        else if(!(pb->next))    //Pb链表遍历完毕，则需将Pa链表直接加在Pc之后
        {
            LNode *p = (LNode *)malloc(sizeof(LNode));
            p->data = pb->data;
            r->next = p;
            r = p;
            r->next = NULL;
            while(pa->next)
            {
                LNode *p = (LNode *)malloc(sizeof(LNode));
                p->data = pa->data;
                r->next = p;
                r = p;
                r->next = NULL;
                pa = pa->next;
            }
            LNode *pl = (LNode *)malloc(sizeof(LNode));
            pl->data = pa->data;
            r->next = pl;
            r = pl;
            r->next = NULL;
        }
    }
}
void DisplayPolyn(Polynomial P)
{
    if(!PolynEmpty(P))
    {
        SortPolyn(P);
        Polynomial p = P->next;
        printf("f(x) = ");
        
        while(p->next)
        {
            printf("%gx^%d + ", p->data.coef, p->data.expn);    //%g 表示省略浮点数最后无意义的0
            p = p->next;
        }
        if(p->data.expn) //最后一项指数不为0
            printf("%gx^%d\n", p->data.coef, p->data.expn);   //最后一项的输出格式
        else        //最后一项指数为0
            printf("%g\n", p->data.coef);   //最后一项的输出格式
    }
    else
        printf("多项式为空\n");
}
void CreateAndDisplay(Polynomial &P, int i)
{
    int num;
    printf("请输入第%d个多项式的项数\n", i);
    scanf("%d", &num);
    printf("请依次输入第%d个多项式的项的系数与指数\n", i);
    CreatePolyn(P, num);
    printf("第%d个多项式为：\n", i);
    DisplayPolyn(P);
}

int main()
{
    char iscreate ;
    int numa, numb;
    printf("是否创建一元多项式？y/n \n");
    scanf("%c", &iscreate);
    if (iscreate != 'y'&& iscreate != 'Y')
    {
        printf("程序结束\n");
        exit(0);
    }
    else
    {
        Polynomial Pa, Pb, Pc;
        CreateAndDisplay(Pa, 1);
        CreateAndDisplay(Pb, 2);

        printf("两个多项式相加结果为：\n");
        InitPolyn(Pc);
        AddPolyn(Pa, Pb, Pc);
        DisplayPolyn(Pc);
    }
    return 0;
}