/**
 * 第4章 串
 * 4-1 串的模式匹配-朴素算法
 * 2020-10-05 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRLEN 255

typedef unsigned char Sstring[MAXSTRLEN + 1]; //0号单元存放串的长度
void CreateString(Sstring &S, char *s)
{
    int i = 1;
    S[0] = strlen(s); //0号单元存放串的长度
    while (*s != '\0')
    {
        S[i] = *s;
        s++;
        i++;
    }
}
int Index(Sstring S, Sstring T, int pos) //串的模式匹配-简单算法
{
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0])
    {
        if (S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > T[0])
        return i - T[0];
    else
        return 0;
}

int main()
{
    Sstring S, T;
    char s[MAXSTRLEN], t[MAXSTRLEN];
    int pos, res;
    printf("字符串匹配\n");
    printf("请输入主字符串：\n");
    scanf("%s", s);
    CreateString(S, s);
    printf("请输入子字符串：\n");
    scanf("%s", t);
    CreateString(T, t);
    printf("请输入从主串第几个位置开始匹配：\n");
    scanf("%d", &pos);
    if (pos <= 0)
    {
        printf("位置输入错误\n");
        exit(0);
    }
    res = Index(S, T, pos);
    if (res == 0)
        printf("未查询到目标位置，匹配失败\n");
    else
        printf("匹配成功，目标首字符位于主串中第%d个位置\n", res);
    return 0;
}