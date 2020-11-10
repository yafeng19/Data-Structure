#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp(void *a, void *b)
{
    return *(int *)a > *(int *)b;
}

void dfs(int A[], int ASize, int *count, int visited[], int result[], int index)
{

    if (index == ASize) // 得到一个排列
    {
        (*count)++;
        return;
    }

    for (int i = 0; i < ASize; i++)
    {
        if (visited[i] == 0)
        {
            if (i > 0 && A[i] == A[i - 1] && visited[i - 1] == 0)
            { //如果当前元素和前一个元素相同时，如果前一个元素没有选，那么当前元素也不选 【2，2，2】
                continue;
            }
            if (index > 0 && sqrt(result[index - 1] + A[i]) != (int)sqrt(result[index - 1] + A[i]))
            { //不是完全平方数
                continue;
            }

            result[index] = A[i];
            visited[i] = 1;
            dfs(A, ASize, count, visited, result, index + 1);
            visited[i] = 0;
        }
    }
}

int main()
{
    int A[4] = {1, 17, 8, 3};
    int ASize = sizeof(A) / sizeof(int);
    int count = 0;
    qsort(A, ASize, sizeof(int), cmp); //将数组元素进行从小到大的排序
    int *visited = (int *)malloc(ASize * sizeof(int));
    memset(visited, 0, sizeof(visited));
    int *result = (int *)malloc(ASize * sizeof(int));
    memset(result, 0, sizeof(result));
    dfs(A, ASize, &count, visited, result, 0);
    printf("%d", count);
}
