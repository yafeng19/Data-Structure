/**
 * 2020-12-11
 * 数据结构课设
 * 核心算法：利用二叉树和栈求解表达式
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <cstring>
#define N 10000
#define operand 1
#define operator 2
using namespace std;

class BiTNode
{
public:
    BiTNode *lchild, *rchild;
    int op;      //区分当前节点是操作符还是操作数
    double optd; //操作数
    char optr;   //操作符
};
typedef BiTNode *BiTree;

class LSNode
{
public:
    double optd; //存放操作数
    LSNode *next;
};
typedef LSNode *LinkStack;

bool InitStack(LinkStack &S)
{
    S = (LSNode *)malloc(sizeof(LSNode));
    if (!S)
    {
        printf("内存申请失败，程序异常终止\n");
        exit(-1);
    }
    S->next = NULL;
    return true;
}
bool Push(LinkStack &S, double e) //与单链表的头插法操作方式一致
{
    LinkStack p = (LSNode *)malloc(sizeof(LSNode));
    p->optd = e;
    p->next = S->next;
    S->next = p;
    return true;
}
bool Pop(LinkStack &S, double &e)
{
    if (S->next == NULL)
        return false;
    else
    {
        LinkStack p = (LSNode *)malloc(sizeof(LSNode));
        p = S->next;
        e = p->optd;
        S->next = p->next;
        free(p);
        return true;
    }
}
bool StackEmpty(LinkStack S)
{
    if (S == NULL || S->next == NULL)
        return true;
    else
        return false;
}
bool Top(LinkStack S, double &e)
{
    if (!StackEmpty(S))
        return false;
    else
    {
        e = S->next->optd;
        return true;
    }
}

void traverse(char formula[]) //格式化表达式，均化成二元运算的形式
{
    for (int i = strlen(formula) - 1; i >= 0; i--)
        if (formula[i] == '-' && formula[i - 1] == '(')
        {
            formula[strlen(formula) + 1] = '\0';
            for (int j = strlen(formula); j > i; j--)
                formula[j] = formula[j - 1];
            formula[i] = '0'; //(-a)的情况转化为(0-a)
        }
}

//由原表达式建立表达式二叉树，lpos和rpos分别代表遍历起止位置
void buildTree(BiTree &T, char formula[], int lpos, int rpos)
{
    int i;
    for (i = lpos; i < rpos; ++i)
        if (!isdigit(formula[i]) && formula[i] != '.')
            break;
    if (i >= rpos) //仅为数字
    {
        T = new BiTNode(); //生成一个新结点存放操作数
        T->op = operand;   //表示操作数
        //将相对于表达式数组首地址偏移量+lpos位置开始的运算数（有可能是浮点数），赋值给optd
        sscanf(formula + lpos, "%lf", &T->optd);
        return;
    }
    int pAS = -1, pMD = -1, pSR = -1; //分别表示加减号、乘除号、平方及求余号所在的位置
    int bracket = 0;                  //记录左括弧相对于右括弧出现的数目
    for (i = lpos; i < rpos; ++i)
    {
        switch (formula[i])
        {
        case '(':
            bracket++;
            break;
        case ')':
            bracket--;
            break;

        //最后计算的运算符一定是在括弧的外边，不会包含在括弧里边
        case '+':
        case '-':
            if (bracket == 0)
                pAS = i;
            break;
        case '*':
        case '/':
            if (bracket == 0)
                pMD = i;
            break;
        case '^':
        case '%':
            if (bracket == 0)
                pSR = i;
            break;
        }
    }
    if (pAS < 0)
        pAS = pMD;
    if (pAS < 0)
        pAS = pSR;
    if (pAS < 0) //说明没有找到括弧外边的运算符，则去掉一对括弧重新寻找
        return buildTree(T, formula, lpos + 1, rpos - 1);
    T = new BiTNode(); //生成一个新结点存放操作符
    T->op = operator;  //表示操作符
    T->optr = formula[pAS];
    buildTree(T->lchild, formula, lpos, pAS);
    buildTree(T->rchild, formula, pAS + 1, rpos);
}

void print_tree(BiTree t, int n) //凹入法打印二叉树
{
    if (t == NULL)
        return;
    print_tree(t->rchild, n + 1);
    for (int i = 0; i < n - 1; i++)
        cout << "      ";
    if (n > 0)
    {
        cout << "$$$";
        if (t->op == operand)
            cout << t->optd << endl;
        else
            cout << t->optr << endl;
    }
    print_tree(t->lchild, n + 1);
}

bool SuffixOrder(BiTree T, LinkStack S) //后序遍历表达式二叉树并进行运算，返回值为false代表出现除零操作
{
    if (T) //非空树，即非叶子结点的左右子树
    {
        bool lzflag = SuffixOrder(T->lchild, S); //遍历左子树
        bool rzflag = SuffixOrder(T->rchild, S); //遍历右子树
        if (lzflag && rzflag)                    //子树的任何一支都不出现false才可以继续操作
        {
            if (T->op == operand) //读取到操作数则入栈
            {
                Push(S, T->optd);
                return true;
            }
            else //读取到操作符则进行运算
            {
                double a, b, c; //两个操作数和结果
                Pop(S, b);      //第二个操作数先出栈
                Pop(S, a);
                switch (T->optr)
                {
                case '+':
                {
                    c = a + b;
                    Push(S, c);
                    break;
                }
                case '-':
                {
                    c = a - b;
                    Push(S, c);
                    break;
                }
                case '*':
                {
                    c = a * b;
                    Push(S, c);
                    break;
                }
                case '/':
                {
                    if (b == 0)
                        return false;
                    c = a / b;
                    Push(S, c);
                    break;
                }
                case '^':
                {
                    c = pow(a, b);
                    Push(S, c);
                    break;
                }
                case '%':
                {
                    if (b == 0)
                        return false;
                    c = fmod(a, b);
                    Push(S, c);
                    break;
                }
                }
            }
            return true; //其他正常情况返回true
        }
        else //若左右子树出现过false，直接层层返回false，直到最外面一层递归函数返回false
        {
            return false;
        }
    }
    else //为空树，即叶子结点的左右子树情况，直接返回true
    {
        return true;
    }
}

int main()
{
    char formula[1000];
    cin >> formula;
    BiTNode *T = NULL;
    traverse(formula);
    cout << formula;
    buildTree(T, formula, 0, strlen(formula));
    print_tree(T, strlen(formula));
    LinkStack S; //操作数辅助栈
    InitStack(S);
    bool zflag = SuffixOrder(T, S); //若zflag为false则出现除零操作
    if (zflag == false)
        cout << "被除数或者被模数为0" << endl;
    else
    {
        double result;
        Pop(S, result);
        cout << result << endl;
    }
    return 0;
}