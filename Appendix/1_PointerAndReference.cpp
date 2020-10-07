/**
 * 附录1
 * 指针和引用比较 
 */

#include <stdio.h>
#include <stdlib.h>

void change_pointer(int *m, int *n)
{
    int temp;
    temp = *m;
    *m = *n;
    *n = temp;
}
void change_reference(int &m, int &n)
{
    int temp;
    temp = m;
    m = n;
    n = temp;
}
int main()
{
    int a = 3, b = 5;
    int c = 2, d = 4;
    change_pointer(&a, &b);
    printf("change_pointer: a=%d, b=%d\n", a, b);
    change_reference(c, d);
    printf("change_reference: c=%d, d=%d\n", c, d);
    return 0;
}