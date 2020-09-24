/**
 * 第2章 线性表 
 * 2-1 线性表的顺序实现
 * 2020-09-21*/

#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100  //线性表存储空间的初始分配量
#define LISTINCREASEMENT 10 //线性表存储空间的分配增量
#define OVERFLOW 1 //宏定义:失败

typedef struct
{
    char name[15]; 
    int age;
    char sex;
    float score;
}ElemType;
typedef struct
{
    ElemType *elem; //存储空间基址
    int length; //当前长度
    int listsize;// 当前分配的存储容量
}SqList;

bool InitList(SqList &L) //构造一个空线性表L
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem) //申请内存失败，L.elem为NULL
    {
        printf("内存申请失败，程序异常终止\n");
        exit(OVERFLOW);
    }
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return true;
}
bool ClearList(SqList &L) //清空线性表L
{
    L.length = 0;
    return true;
}
bool DestroyList(SqList &L) //销毁线性表L
{
    L.length = 0;
    free(L.elem);
    L.elem = NULL;
    return true;
}
bool ListEmpty(SqList L) //判断线性表L是否为空
{
    //也可以写成 return (L.length == 0);
    if(L.length == 0)
        return true;
    else 
        return false;
}
int ListLength(SqList L)   //求线性表L的长度
{
    return L.length;
}
void DisplayList(SqList L)
{
    for(int i = 0; i < L.length; i++)
    printf("%s %d %c %.2f\n", L.elem[i].name, L.elem[i].age, L.elem[i].sex, L.elem[i].score);
}
bool PriorElem(SqList L, int cur_e, ElemType &pre_e)    //求前驱的值
{
    if(cur_e <= 1 || cur_e >= L.length+2 || L.length == 0 )    //可输入位置2~L.length+1
        return false;
    else 
    {
        pre_e = L.elem[cur_e-2];
        return true;
    }       
}
bool NextElem(SqList L, int cur_e, ElemType &next_e)    //求后继的值
{
    if(cur_e <= -1 || cur_e >= L.length || L.length == 0 ) //可输入位置0~L.length-1
        return false;
    else 
    {
        next_e = L.elem[cur_e];
        return true;
    }       
}
bool GetElem(SqList L, int i, ElemType &e)  //取第i个位置的值
{
    if(i < 0 || i > L.length || L.length == 0)     //可输入位置1~L.length
        return false;
    else
    {
        e = L.elem[i-1];
        return true;
    }
}
bool ListInsert(SqList &L, int i, ElemType e)   //在第i个位置前插入元素e，时间复杂度O(ListLength(L))
{
    if(i<1||i>L.length+1)
        return false;
    if(L.length >= L.listsize)
    {
        ElemType * newbase = (ElemType *)realloc(L.elem, (L.listsize+LISTINCREASEMENT)*sizeof(ElemType));  //重新分配内存
        if(!newbase)
            exit(OVERFLOW);
        L.elem = newbase;   //新基址
        L.listsize += LISTINCREASEMENT; //增加存储容量
    }
    for(int j = L.length-1; j >= i-1; j--)
        L.elem[j+1] = L.elem[j];
    L.elem[i-1] = e;
    L.length++;
    return true;
    /*  //以上5行语句也可以使用指针实现
    q = &(L.elem[i-1]);
    for(ElemType *p = &(L.elem[L.length-1]); p >= q; p--)
        *(p+1) = *p;
    *q = e;
    L.length++;
    return true;
    */
}
bool ListDelete(SqList &L, int i, ElemType &e)  //删除第i个位置的元素，时间复杂度O(ListLength(L))
{
    if( i < 1 || i > L.length)
        return false;
    else
    {
        e = L.elem[i-1];
        for(int j = i-1; j < L.length; j++)
            L.elem[j] = L.elem[j+1];
        L.length--;
        return true;
        /* //以上5行语句也可以使用指针实现
        p = &(L.elem[i-1]);
        e = *p;
        q = L.elem + L.length - 1;
        for(++p; p <= q; p++)
            *(p-1) = *p;
        L.length--;
        return true;
        */
    }
}

int main()
{
    char iscreate ;
    int num, oper;
    printf("是否创建一个空的线性表？y/n \n");
    scanf("%c", &iscreate);
    if (iscreate != 'y'&& iscreate != 'Y')
    {
        printf("程序结束\n");
        exit(0);
    }
    else
    {
        SqList L;
        if(InitList(L))
        {
            printf("线性表创建成功,请输入数据条数\n");
            scanf("%d", &num);
            L.length = num;
            printf("请依次录入各数据的信息\n");
            for(int i = 0; i < num; i++)
                scanf("%s %d %c %f", &L.elem[i].name, &L.elem[i].age, &L.elem[i].sex, &L.elem[i].score);
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
                            printf("%s %d %c %.2f\n", element.name, element.age, element.sex, element.score);
                        }
                        else 
                        {
                            printf("查找失败\n");
                        }
                        break;}
                    case 4: {
                        ElemType element;
                        int cur_i;
                        printf("请输入要查找的数据位置\n");
                        scanf("%d", &cur_i);
                        if(NextElem(L, cur_i, element))
                        {
                            printf("查找成功，数据信息如下：\n");
                            printf("%s %d %c %.2f\n", element.name, element.age, element.sex, element.score);
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
                            printf("%s %d %c %.2f\n", element.name, element.age, element.sex, element.score);
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
                            printf("%s %d %c %.2f\n", element.name, element.age, element.sex, element.score);
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