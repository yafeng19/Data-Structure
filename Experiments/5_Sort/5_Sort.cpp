/**
 * 实验5 模拟EXCEL排序
 * 快速排序
 * 2020-11-21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct info
{
    char stuNo[7];
    char name[9];
    int score;
} Info;

int compareByStuNo(const void *elem1, const void *elem2)
{
    Info *p1, *p2;
    p1 = (Info *)elem1;
    p2 = (Info *)elem2;
    return strcmp((*p1).stuNo, (*p2).stuNo);
}
int compareByName(const void *elem1, const void *elem2)
{
    Info *p1, *p2;
    p1 = (Info *)elem1;
    p2 = (Info *)elem2;
    if (strcmp((*p1).name, (*p2).name)) //姓名不相同
        return strcmp((*p1).name, (*p2).name);
    else //姓名相同，则按照学号递增
        return strcmp((*p1).stuNo, (*p2).stuNo);
}
int compareByScore(const void *elem1, const void *elem2)
{
    Info *p1, *p2;
    p1 = (Info *)elem1;
    p2 = (Info *)elem2;
    if ((*p1).score != (*p2).score) //分数不相等
        return (*p1).score < (*p2).score ? -1 : 1;
    else //分数相同，则按照学号递增
        return strcmp((*p1).stuNo, (*p2).stuNo);
}
int main()
{
    int num;
    int order;
    scanf("%d", &num);
    scanf("%d", &order);
    Info *stuList = (Info *)malloc(sizeof(Info) * num);
    for (int i = 0; i < num; i++)
        scanf("%s %s %d", stuList[i].stuNo, stuList[i].name, &stuList[i].score);
    switch (order)
    {
    case 1:
        qsort(stuList, num, sizeof(Info), compareByStuNo);
        break;
    case 2:
        qsort(stuList, num, sizeof(Info), compareByName);
        break;
    case 3:
        qsort(stuList, num, sizeof(Info), compareByScore);
        break;
    }
    printf("\n");
    for (int i = 0; i < num; i++)
        printf("%s %s %d\n", stuList[i].stuNo, stuList[i].name, stuList[i].score);
    return 0;
}

/*
3 1
000007 James 85
000010 Amy 90
000001 Zoe 60

4 2
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 98

1 2
999999 Williams 100
*/