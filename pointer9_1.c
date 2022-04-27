#include <stdio.h>

int main()
{
    int a = 10;
    double d = 99.99f;
    char c = 'c';
    printf("%d %lf %c\n", a, d, c);

    printf("%x %p %u\n", &a, &d, &c); // %x, ,%p, %u 모두 주소출력 / %x, %p는 16진수

    return 0;
}
