/**
 * 第5章 数组和广义表
 * 5-1 三元组顺序表转置
 * 2020-10-07 
 */

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 12500

typedef struct
{
    int i, j; //非零元的行下标和列下标，即第i行第j列
    //Elemtype e;   //非零元的值
    int val;
} Triple;
typedef struct
{
    Triple data[MAXSIZE + 1]; //data[0]未使用
    int row, col, num;        //分别为三元组的行数，列数，总元素个数
} TSMatrix;

void GetInfomation(TSMatrix &M)
{
    printf("请分别输入矩阵的行数、列数以及非零元素个数\n");
    scanf("%d %d %d", &M.row, &M.col, &M.num);
    for (int count = 1; count <= M.num; count++)
    {
        printf("请依次输入第%d个三元组所记录的元素的行下标、列下标以及元素值\n", count);
        scanf("%d %d %d", &M.data[count].i, &M.data[count].j, &M.data[count].val);
    }
}
void TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    int m, n, colomn;
    T.row = M.col;
    T.col = M.row;
    T.num = M.num;
    if (T.num)
    {
        n = 1;
        for (colomn = 1; colomn <= M.col; colomn++)
            for (m = 1; m <= M.num; m++)
                if (M.data[m].j == colomn)
                {
                    T.data[n].i = M.data[m].j;
                    T.data[n].j = M.data[m].i;
                    T.data[n].val = M.data[m].val;
                    n++;
                }
    }
}
void DisplayTriple(TSMatrix M)
{
    for (int count = 1; count <= M.num; count++)
    {
        printf("(%d, %d, %d)\n", M.data[count].i,
               M.data[count].j,
               M.data[count].val);
    }
}

int main()
{
    TSMatrix M, T;
    GetInfomation(M);
    TransposeSMatrix(M, T);
    printf("原三元组为：\n");
    DisplayTriple(M);
    printf("经转置且按列排序的三元组为：\n");
    DisplayTriple(T);
    return 0;
}