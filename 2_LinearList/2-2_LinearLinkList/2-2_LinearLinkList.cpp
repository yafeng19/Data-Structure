/**
 * 第2章 线性表 
 * 2-2 线性表的链式实现
 * 2020-09-23*/


#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW 1 //宏定义:失败


typedef struct
{
    char name[15]; 
    int age;
    char sex;
    float score;
}ElemType;
typedef struct LNode
{
    ElemType data;  //数据域
    struct LNode *next; //指针域
}LNode, *LinkList;


bool InitList(LinkList &L) //构造一个带有头结点的空线性表L
{
    L = (LNode *)malloc(sizeof(LNode));
    if(!L) //申请内存失败，L为NULL
    {
        printf("内存申请失败，程序异常终止\n");
        exit(OVERFLOW);
    }
    L->next == NULL;
    return true;
}
void CreateList_head(LinkList &L, int n) //头插法，逆序输入
{
    InitList(L);    //先建立一个带头结点的空链表
    for(int i = n; i > 0; i--)
    {
        LinkList p = (LNode *)malloc(sizeof(LNode));
        scanf("%s %d %c %f", &((p->data).name), &((p->data).age), &((p->data).sex), &((p->data).score));
        p->next = L->next;
        L->next = p;
    }
}
void CreateList_tail(LinkList &L, int n) //尾插法，顺序输入
{
    InitList(L);    //先建立一个带头结点的空链表
    LinkList r = L;
    for(int i = n; i > 0; i--)
    {
        LinkList p = (LNode *)malloc(sizeof(LNode));
        scanf("%s %d %c %f", &((p->data).name), &((p->data).age), &((p->data).sex), &((p->data).score));
        r->next = p;
        r = p;
        r->next = NULL; //保证尾结点指针域为空
    }
}
bool ClearList(LinkList &L) //清空线性表L，即重置为空链表（只含有一个空结点）
{
    LinkList p;
    while(L->next)
    {
        p = L->next;
        L->next = p->next;
        free(p);
    }
    return true;
}
bool DestroyList(LinkList &L) //销毁线性表L，即不再保留空链表
{
    free(L);
    return true;
}
bool ListEmpty(LinkList L) //判断线性表L是否为空
{
    //也可以写成 return (L->next == NULL);
    if(L->next == NULL)
        return true;
    else 
        return false;
}
int ListLength(LinkList L)   //求线性表L的长度
{
    int length = 0;
    LinkList p = L->next;
    while(p)
    {
        length++;
        p = p->next;
    }
    return length;
}
void DisplayList(LinkList L)
{
    LinkList p = L->next;
    while(p)
    {
        printf("%s %d %c %.2f\n", (p->data).name, (p->data).age, (p->data).sex, (p->data).score);
        p = p->next;
    }
}
bool NextElem(LinkList L, int cur_e, ElemType &next_e)    //求后继的值，可输入位置0到length-1
{
    LinkList p = L;
    int j = 0;
    while(p->next && j < cur_e) //由于求后继，故要求p->next不空。j = cur_e时则取出在第0个结点（头结点）的后继元素e
    {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > cur_e)
        return false;
    next_e = p->next->data;
    return true;
}
bool GetElem(LinkList L, int i, ElemType &e)  //取第i个位置的值，时间复杂度O(ListLength(L))
{
    LinkList p = L->next;
    int j = 0;
    while(p && j < i-1) //j = i-1时则取出在第1个结点的元素e
    {
        p = p->next;
        j++;
    }
    if (!p || j > i-1)
        return false;
    e = p->data;
    return true;
}
bool ListInsert(LinkList &L, int i, ElemType e)   //在第i个位置前插入元素e，时间复杂度O(ListLength(L))
{
    LinkList p = L;
    int j = 0;
    while(p && j < i-1) //j = i-1时则在第1个结点前插入元素e
    {
        p = p->next;
        j++;
    }
    if (!p || j > i-1)
        return false;
    LinkList s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}
bool ListDelete(LinkList &L, int i, ElemType &e)  //删除第i个位置的元素，时间复杂度O(ListLength(L))
{
    LinkList p = L, q = NULL;
    int j = 0;
    while(p->next && j < i-1)   //p的后继代表要删除的元素，因此p->next不能为空。 j = i-1时则删除第1个结点
    {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i-1)
        return false;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return true;
}


int main()
{
    char iscreate ;
    int num, oper, order;
    printf("是否创建一个空的线性表？y/n \n");
    scanf("%c", &iscreate);
    if (iscreate != 'y'&& iscreate != 'Y')
    {
        printf("程序结束\n");
        exit(0);
    }
    else
    {
        LinkList L;
        printf("请输入选择顺序显示还是逆序显示：  1.顺序显示\t2.逆序显示\n");
        scanf("%d", &order);
        if(order == 1|| order == 2)
        {
            printf("请输入数据条数\n");
            scanf("%d", &num);
            printf("请依次录入各数据的信息\n");
            if(order == 1)
            {
                CreateList_tail(L, num);
            }
            else 
            {
                CreateList_head(L, num);
            }
            printf("信息录入完毕，请输入数字代码以选择操作：\n");
            while(oper != 0)
            {
                printf("\n 0.退出程序\n 1.判断线性表是否为空\n 2.求线性表的长度\n 3.求后继数据\n 4.取第i个数据\n");
                printf(" 5.在第i个数据前插入数据\n 6.删除第i个数据\n 7.清空线性表\n 8.销毁线性表\n 9.展示线性表\n");
                scanf("%d", &oper);
                switch(oper)
                {
                    case 0: {
                        printf("程序结束\n"); 
                        exit(0); 
                        break;}
                    case 1: {
                        if(ListEmpty(L))
                            printf("线性表为空\n");
                        else 
                            printf("线性表不为空\n");
                        break;}
                    case 2: {
                        printf("线性表的长度为%d\n", ListLength(L));
                        break;}
                    case 3: {
                        ElemType element;
                        int cur_i;
                        printf("请输入要查找的数据位置\n");
                        scanf("%d", &cur_i);
                        if(NextElem(L, cur_i, element))
                        {
                            printf("查找成功，数据信息如下：\n");
                            printf("%s %d %c %.2f", element.name, element.age, element.sex, element.score);
                        }
                        else 
                            printf("查找失败\n");
                        break;}
                    case 4: {
                        ElemType element;
                        int cur_i;
                        printf("请输入要查找的数据位置\n");
                        scanf("%d", &cur_i);
                        if(GetElem(L, cur_i, element))
                        {
                            printf("查找成功，数据信息如下：\n");
                            printf("%s %d %c %.2f", element.name, element.age, element.sex, element.score);
                        }
                        else 
                            printf("查找失败\n");
                        break;}
                    case 5: 
                    {
                        ElemType element;
                        int insert_i;
                        printf("请输入在第几个数据前插入新数据\n");
                        scanf("%d", &insert_i);
                        printf("请输入需要插入的数据信息\n");
                        scanf("%s %d %c %f", &element.name, &element.age, &element.sex, &element.score);
                        if(ListInsert(L, insert_i, element))
                            printf("插入成功\n");
                        else
                            printf("插入失败\n");
                        break;}
                    case 6: {
                        ElemType element;
                        int delete_i;
                        printf("请输入删除第几个数据\n");
                        scanf("%d", &delete_i);
                        if(ListDelete(L, delete_i, element))
                        {
                            printf("删除成功,被删除的数据为：\n"); 
                            printf("%s %d %c %.2f", element.name, element.age, element.sex, element.score);
                        }
                        else 
                            printf("删除失败\n");
                        break;}
                    case 7: {
                        ClearList(L);
                        printf("线性表清空成功\n");
                        break;}
                    case 8: {
                        DestroyList(L);
                        printf("线性表销毁成功\n");
                        break;}
                    case 9: {
                        if(ListEmpty(L))
                            printf("线性表为空\n");
                        else
                        {
                            printf("线性表展示如下：\n");
                            DisplayList(L);
                        }
                        break;
                    }
                    default: printf("无此选项\n");
                }
            }
        }
        else 
        {
            printf("线性表创建失败\n");
            exit(1);
        }
    }
    return 0;
}