/**
 * 实验2 二叉树的深度
 * 2020-10-17
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#define MAXSIZE 10000
using namespace std;

char preExp[MAXSIZE], inExp[MAXSIZE]; //前序序列，中序序列
int length;                           //二叉树结点的个数
typedef struct BiTNode
{
    char name;
    struct BiTNode *leftchild;
    struct BiTNode *rightchild;
} BiTNode, *BiTree;
//初始化
void init(BiTNode *&root)
{
    root = (BiTNode *)malloc(sizeof(BiTNode));
    root->leftchild = NULL;
    root->rightchild = NULL;
}

//创建左子树
BiTNode *build_ltree(BiTNode *h, char name)
{
    BiTNode *p, *t;
    if (h == NULL)
        return NULL;
    t = h->leftchild;
    p = (BiTNode *)malloc(sizeof(BiTNode));
    p->name = name;
    p->leftchild = t;
    p->rightchild = NULL;
    h->leftchild = p;
    return h->leftchild;
}

//创建右子树
BiTNode *build_rtree(BiTNode *h, char name)
{
    BiTNode *p, *t;
    if (h == NULL)
        return NULL;
    t = h->rightchild;
    p = (BiTNode *)malloc(sizeof(BiTNode));
    p->name = name;
    p->leftchild = NULL;
    p->rightchild = t;
    h->rightchild = p;
    return h->rightchild;
}

//凹入法打印二叉树
void print_tree(BiTNode *t, int n)
{
    if (t == NULL)
        return;
    print_tree(t->rightchild, n + 1);
    for (int i = 0; i < n - 1; i++)
        printf("      ");
    if (n > 0)
    {
        printf("***");
        printf("%c\n", t->name);
    }
    print_tree(t->leftchild, n + 1);
}
//寻找对应中序序列中和前序序列相对应的结点的位置
int findPosition(char ch[], char name)
{
    int i(0);
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
int Depth(BiTNode *T)
{
    int depthval, depthLeft, depthRight; //二叉树的深度、左子树深度、右子树深度
    if (!T)
        depthval = 0;
    else
    {
        depthLeft = Depth(T->leftchild);
        depthRight = Depth(T->rightchild);
        depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
    }
    return depthval;
}
/*
9
ABDFGHIEC
FDHGIBEAC
10
ABDFHGIJEC
HFDGJIBEAC
15
ABDHIEJKCFLMGNO
HDIBJEKALFMCNGO
*/

int main()
{
    BiTNode *root; //定义根节点
    init(root);    //创建根节点
    scanf("%d", &length);
    BiTNode *nodeTree[MAXSIZE]; //二叉树结点
    int flag[MAXSIZE];          //标记数组
    int left, right;
    memset(flag, 0, sizeof(flag)); //标记数组全部赋值为0
    //printf("请输入前序序列：");
    scanf("%s", preExp);
    //printf("请输入中序序列：");
    scanf("%s", inExp);
    char node_pre; //前序序列中的结点
    int num;       //中序序列中对应前序序列结点的位置
    for (int i = 0; i < length; ++i)
    {
        node_pre = preExp[i];
        num = findPosition(inExp, node_pre);
        left = seek_left(flag, num);   //找到左子树位置
        right = seek_right(flag, num); //找到右子树位置
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
    //printf("二叉树结构为：\n");
    print_tree(root, 0);
    printf("%d", Depth(root->leftchild));
    return 0;
}