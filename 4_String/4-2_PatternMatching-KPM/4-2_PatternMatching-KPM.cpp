/**
 * 第4章 串
 * 4-2 串的模式匹配-KMP算法
 * 2020-10-07 
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
void GetNext(Sstring T, int next[])
{
    int j = 1, k = 0;
    next[1] = 0;
    while (j < T[0])
    {
        if (k == 0 || T[j] == T[k])
        {
            j++;
            k++;
            next[j] = k;
        }    //可以简写成 next[++j] = ++k;
        else //T[j]!=T[k]时，k跳转至next[k]
            k = next[k];
    }
}
int Index(Sstring S, Sstring T, int pos, int next[]) //串的模式匹配-KMP算法
{
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0])
    {
        if (j == 0 || S[i] == T[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
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
    int next[MAXSTRLEN + 1];
    printf("字符串匹配\n");
    printf("请输入主字符串：\n");
    scanf("%s", s);
    CreateString(S, s);
    printf("请输入子字符串：\n");
    scanf("%s", t);
    CreateString(T, t);
    GetNext(T, next);
    printf("请输入从主串第几个位置开始匹配：\n");
    scanf("%d", &pos);
    if (pos <= 0)
    {
        printf("位置输入错误\n");
        exit(0);
    }
    res = Index(S, T, pos, next);
    if (res == 0)
        printf("未查询到目标位置，匹配失败\n");
    else
        printf("匹配成功，目标首字符位于主串中第%d个位置\n", res);
    printf("以下为子串的next值：\n");
    for (int i = 1; i <= T[0]; i++)
        printf("%d ", next[i]);
    return 0;
}