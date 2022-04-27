#include <stdio.h>

int main()
{
    int a = 10, b;
    int* pa; // aÀÇ ÁÖ¼Ò

    pa = &a;

    printf("a : %d, pa : %d\n", a, *pa);

    pa = &b;
    *pa = 20;
    printf("b : %d, pa : %d\n", b, *pa);
    printf("&b : %d, pa : %d\n", &b, pa);

    return 0;
}
