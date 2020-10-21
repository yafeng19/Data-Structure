/**
 * 实验2 二叉树的深度
 * 2020-10-17
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
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
//找到左子树的位置
int seek_left(int flag[], int t)
{
    int temp;
    temp = t;
    while (flag[temp] != 1 && temp >= 0)
        temp--;
    if (flag[temp] == 1)
        return temp;
    else
        return -1;
}
//找到右子树的位置
int seek_right(int flag[], int t)
{
    int temp;
    temp = t;
    while (flag[temp] != 1 && temp <= 10000)
        temp++;
    if (flag[temp] == 1)
        return temp;
    else
        return -1;
}
void depth(char *pre, char *in, int flag[], int level[], int length, int &depthval)
{
    char node_pre;
    int pos;         //pos为中序表达式中的根节点位置
    int left, right; //分别为左、右子树的位置
    for (int i = 0; i < length; ++i)
    {
        node_pre = preExp[i];
        pos = findPosition(inExp, node_pre);
        left = seek_left(flag, pos);   //找到左子树位置
        right = seek_right(flag, pos); //找到右子树位置
        if (left == -1 && right == -1)
        { //第一次的时候肯定会执行这个条件后面的语句
            nodeTree[num] = build_ltree(root, node_pre);
            flag[num] = 1;
        }
        else if (left != -1 && nodeTree[left]->rightchild == NULL)
        {
            nodeTree[num] = build_rtree(nodeTree[left], node_pre);
            flag[num] = 1;
        }
        else if (right != -1 && nodeTree[right]->leftchild == NULL)
        {
            nodeTree[num] = build_ltree(nodeTree[right], node_pre);
            flag[num] = 1;
        }
    }
    /*
    char preRoot, inRoot;
    int leftDepth = 0, rightDepth = 0, i, pos; //i为前序表达式的遍历元，pos为中序表达式中的根节点位置
    int l_start = 1, l_end, r_start, r_end = length;
    for (i = 1; i <= length; i++)
    {
        preRoot = pre[i];
        int j = 1; //j为中序表达式的遍历元，
        while (pre[i] != in[j])
        {
            j++;
        }
        pos = j;
        flag[pos] = 1;
        findLeft(preRoot, pos, l_start, l_end);
        findRight(preRoot, pos, r_start, r_end);
    }
    */
}
int main()
{
    int flag[MAXSIZE];  //标记数组
    int level[MAXSIZE]; //记录层数数组
    int left, right;
    memset(flag, 0, sizeof(flag)); //标记数组全部赋值为0
    int depthVal = 0;
    scanf("%d", &length);
    memset(flag, 0, sizeof(int) * length); //标记数组全部赋值为0
    scanf("%s", preExp);
    scanf("%s", inExp);
    printf("深度为：");
    depth(preExp, inExp, flag, level, length, depthVal);
    printf("%d\n", depthVal);
    return 0;
}