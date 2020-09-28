/**
 * 第2章 线性表 
 * 2-3 双向链表的应用
 * 2020-09-28*/


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
typedef struct DuLNode
{
    ElemType data;  //数据域
    struct DuLNode *prior;    //指针域，前驱指针
    struct DuLNode *next;     //指针域，后继指针
}DuLNode, *DuLinkList;


bool InitList(DuLinkList &L) //构造一个带有头结点的空线性表L
{
    L = (DuLNode *)malloc(sizeof(DuLNode));
    if(!L) //申请内存失败，L为NULL
    {
        printf("内存申请失败，程序异常终止\n");
        exit(OVERFLOW);
    }
    L->prior == NULL;
    L->next == NULL;
    return true;
}
void CreateList_head(DuLinkList &L, int n) //头插法，逆序输入
{
    InitList(L);    //先建立一个带头结点的空链表
    for(int i = n; i > 0; i--)
    {
        DuLinkList p = (DuLNode *)malloc(sizeof(DuLNode));
        scanf("%s %d %c %f", &((p->data).name), &((p->data).age), &((p->data).sex), &((p->data).score));
        p->next = L->next;
        p->prior = L;
        L->next->prior = p;
        L->next = p;
    }
}
void CreateList_tail(DuLinkList &L, int n) //尾插法，顺序输入
{
    InitList(L);    //先建立一个带头结点的空链表
    DuLinkList r = L;
    for(int i = n; i > 0; i--)
    {
        DuLinkList p = (DuLNode *)malloc(sizeof(DuLNode));
        scanf("%s %d %c %f", &((p->data).name), &((p->data).age), &((p->data).sex), &((p->data).score));
        r->next = p;
        p->prior = r;
        r = p;
        r->next = NULL; //保证尾结点指针域为空
    }
}
bool ClearList(DuLinkList &L) //清空线性表L，即重置为空链表（只含有一个空结点）
{
    DuLinkList p;
    while(L->next)
    {
        p = L->next;
        L->next = p->next;
        free(p);
    }
    return true;
}
bool DestroyList(DuLinkList &L) //销毁线性表L，即不再保留空链表
{
    free(L);
    return true;
}
bool ListEmpty(DuLinkList L) //判断线性表L是否为空
{
    //也可以写成 return (L == NULL || L->next == NULL);
    if(L == NULL || L->next == NULL)    //被销毁或者为空表
        return true;
    else 
        return false;
}
int ListLength(DuLinkList L)   //求线性表L的长度
{
    int length = 0;
    if(L == NULL)   //被销毁
        return false;
    DuLinkList p = L->next;
    while(p)
    {
        length++;
        p = p->next;
    }
    return length;
}
void DisplayList(DuLinkList L)
{
    DuLinkList p = L->next;
    while(p)
    {
        printf("%s %d %c %.2f\n", (p->data).name, (p->data).age, (p->data).sex, (p->data).score);
        p = p->next;
    }
}
bool PriorElem(DuLinkList L, int cur_e, ElemType &pre_e)    //求前驱的值，可输入位置2到length+1
{
    DuLinkList p = L->next;
    int j = 1;
    while(p->prior && p->next && j < cur_e) //由于求前驱，故要求p->prior不空。向后遍历要求p->next不空。j = cur_e时则取出在第i个结点的前驱e
    {
        p = p->next;
        j++;
    }
    if (!(p->prior) || j > cur_e || cur_e == 1) //位置为1时不能求其前驱
        return false;
    if(!(p->next)) //位置为length+1时
    {
        pre_e = p->data;
        return true;
    }
    else
    {
        pre_e = p->prior->data;
        return true;
    }
}
bool NextElem(DuLinkList L, int cur_e, ElemType &next_e)    //求后继的值，可输入位置0到length-1
{
    DuLinkList p = L;
    int j = 0;
    while(p->next && j < cur_e) //由于求后继，故要求p->next不空。j = cur_e时则取出在第i个结点的后继元素e
    {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > cur_e)
        return false;
    next_e = p->next->data;
    return true;
}
bool GetElem(DuLinkList L, int i, ElemType &e)  //取第i个位置的值，时间复杂度O(ListLength(L))
{
    DuLinkList p = L->next;
    int j = 0;
    while(p && j < i-1) //j = i-1时则取出在第i个结点的元素e
    {
        p = p->next;
        j++;
    }
    if (!p || j > i-1)
        return false;
    e = p->data;
    return true;
}
bool ListInsert(DuLinkList &L, int i, ElemType e)   //在第i个位置前插入元素e，时间复杂度O(ListLength(L))
{
    DuLinkList p = L;
    int j = 0;
    while(p && j < i) //j = i时则在第i个结点前插入元素e
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)
        return false;
    DuLinkList s = (DuLNode *)malloc(sizeof(DuLNode));
    s->data = e;
    s->prior = p->prior;
    s->next = p;
    p->prior->next = s;
    p->prior = s;
    return true;
}
bool ListDelete(DuLinkList &L, int i, ElemType &e)  //删除第i个位置的元素，时间复杂度O(ListLength(L))
{
    DuLinkList p = L;
    int j = 0;
    while(p->next && j < i)   //p的后继代表要删除的元素，因此p->next不能为空。 j = i时则删除第i个结点
    {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i)
        return false;
    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
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
        DuLinkList L;
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
                printf("\n 0.退出程序\n 1.判断线性表是否为空\n 2.求线性表的长度\n 3.求前驱数据\n 4.求后继数据\n 5.取第i个数据\n");
                printf(" 6.在第i个数据前插入数据\n 7.删除第i个数据\n 8.清空线性表\n 9.销毁线性表\n 10.展示线性表\n");
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
                        if(PriorElem(L, cur_i, element))
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
                        if(NextElem(L, cur_i, element))
                        {
                            printf("查找成功，数据信息如下：\n");
                            printf("%s %d %c %.2f", element.name, element.age, element.sex, element.score);
                        }
                        else 
                            printf("查找失败\n");
                        break;}
                    case 5: {
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
                    case 6: 
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
                    case 7: {
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
                    case 8: {
                        ClearList(L);
                        printf("线性表清空成功\n");
                        break;}
                    case 9: {
                        DestroyList(L);
                        printf("线性表销毁成功\n");
                        break;}
                    case 10: {
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