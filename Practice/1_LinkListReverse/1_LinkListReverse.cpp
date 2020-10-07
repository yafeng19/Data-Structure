/**
 * 练习1 
 * 链表的就地逆置 
 */

#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW 1

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode;
typedef LNode *LinkList;

bool InitList(LinkList &L) //构造一个带有头结点的空线性表L
{
    L = (LNode *)malloc(sizeof(LNode));
    if (!L) //申请内存失败，L为NULL
    {
        printf("内存申请失败，程序异常终止\n");
        exit(OVERFLOW);
    }
    L->next == NULL;
    return true;
}
void CreateList(LinkList &L, int n) //尾插法，顺序输入
{
    InitList(L); //先建立一个带头结点的空链表
    LNode *r = L;
    printf("请依次输入值：\n");
    for (int i = n; i > 0; i--)
    {
        LinkList p = (LNode *)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        r->next = p;
        r = p;
        r->next = NULL; //保证尾结点指针域为空
    }
}
void ReverseList(LinkList &L)
{
    LNode *p = L->next->next;
    LNode *q = NULL;
    L->next->next = NULL;
    while (p)
    {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}
void DisplayList(LinkList L)
{
    LNode *p = L->next;
    while (p->next)
    {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("%d\n", p->data); //最后一个元素的输出格式
}

int main()
{
    LinkList L;
    int num;
    printf("请输入链表中元素的个数：\n");
    scanf("%d", &num);
    CreateList(L, num);
    printf("创建链表为：\n");
    DisplayList(L);
    ReverseList(L);
    printf("转置后的链表为：\n");
    DisplayList(L);
    return 0;
}