#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[100];
    int i = 0;
    do
    {
        scanf("%d", &a[i]);
        i++;
    } while (getchar() != '\n'); //输入回车跳出循环输入
    i = 0;
    while (a[i] != '\0')
    {
        printf("%d ", a[i]);
        i++;
    }
}