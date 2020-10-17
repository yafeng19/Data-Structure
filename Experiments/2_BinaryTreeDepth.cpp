/**
 * 实验2 二叉树的深度
 * 2020-10-17
 */

#include <stdio.h>
#include <stdlib.h>

int length;
bool findLeft(char preRoot, int pos, int &l_start, int &l_end)
{
    int l_start = 0;
    int l_end = pos - 1;
}
bool findRight(char preRoot, int pos, int &r_start, int &r_end)
{
    int r_start = pos + 1;
    int r_end = length;
}
void depth(int length, char *pre, char *in, int flag[], int &depthval)
{
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
}
int main()
{
    int depthVal = 0;
    scanf("%d", &length);
    int *flag = (int *)malloc(sizeof(int) * (length + 2));
    flag[0] = 1;
    flag[length + 1] = 1;
    for (int i = 1; i <= length; i++)
        flag[i] = 0;
    char *preExp = (char *)malloc(sizeof(char) * (length + 2));
    scanf("%s", preExp);
    char *inExp = (char *)malloc(sizeof(char) * (length + 2));
    scanf("%s", inExp);
    depth(length, preExp, inExp, flag, depthVal);
    printf("%d\n", depthVal);
    return 0;
}