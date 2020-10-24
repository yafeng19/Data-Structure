/**
 * 实验2 二叉树的深度
 * 非建树方法
 * 2020-10-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#define MAXSIZE 50

char preExp[MAXSIZE], inExp[MAXSIZE]; //前序序列，中序序列
int length;
int findPosition(char ch[], char name)
{
    int i = 0;
    while (ch[i] != name)
        ++i;
    return i;
}
void leftLevelAdd(int flag[], int level[], int pos, int pos0)
{
    if (pos != 0) //如果不是首位元素，则还需要遍历根节点左侧
    {
        for (int i = pos - 1; i >= 0; i--)
        {
            if (flag[i] == 0)
                level[i]++;
            else
                break;
        }
    }
    for (int i = pos + 1; i <= pos0; i++)
    {
        if (flag[i] == 0)
            level[i]++;
        else
            break;
    }
}
void rightLevelAdd(int flag[], int level[], int pos, int pos0)
{
    if (pos != length - 1) //如果不是末位元素，则还需要遍历根节点右侧
    {
        for (int i = pos + 1; i <= length - 1; i++)
        {
            if (flag[i] == 0)
                level[i]++;
            else
                break;
        }
    }
    for (int i = pos - 1; i >= pos0; i--)
    {
        if (flag[i] == 0)
            level[i]++;
        else
            break;
    }
}
int maxLevel(int level[])
{
    int max = level[0];
    for (int i = 1; i <= length - 1; i++)

        max = max > level[i] ? max : level[i];
    return max + 1;
}
int depth(char *pre, char *in, int flag[], int level[], int length)
{
    char node_pre; //前序表达式的遍历字符
    int pos, pos0; //pos为中序表达式中的根节点位置,pos0为上一次的中根结点位置
    for (int i = 0; i < length; ++i)
    {
        node_pre = preExp[i];
        pos = findPosition(inExp, node_pre);
        if (i == 1) //第一次的时候肯定会执行这个条件后面的语句
        {
            leftLevelAdd(flag, level, pos, length - 1); //首次执行方式
        }
        else
        {
            if (pos < pos0)                           //新的根结点位置在上一次根节点位置的左侧
                leftLevelAdd(flag, level, pos, pos0); //在上一次根节点的左侧实现层数+1
            else
                rightLevelAdd(flag, level, pos, pos0); //在上一次根节点的右侧实现层数+1
        }
        flag[pos] = 1; //已经遍历过的结点设置标记变量为1
        pos0 = pos;    //用pos0记录上一次的根节点
    }
    return maxLevel(level); //返回层数的最大值
}
int main()
{
    int flag[MAXSIZE];  //标记数组
    int level[MAXSIZE]; //记录层数数组
    int depthval = 0;
    memset(flag, 0, sizeof(flag)); //标记数组全部赋值为0
    int depthVal = 0;
    scanf("%d", &length);
    memset(flag, 0, sizeof(int) * length);  //标记数组全部赋值为0
    memset(level, 0, sizeof(int) * length); //层数数组全部赋值为0
    scanf("%s", preExp);
    scanf("%s", inExp);
    depthVal = depth(preExp, inExp, flag, level, length);
    printf("%d\n", depthVal);
    return 0;
}
/*
测试用例
9
ABDFGHIEC
FDHGIBEAC
>>>5

10
ABDFHGIJEC
HFDGJIBEAC
>>>6

15
ABDHIEJKCFLMGNO
HDIBJEKALFMCNGO
>>>4

7
ABCDEFG
GFEDCBA
>>>7
*/