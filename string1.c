#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int a = 10;
	int b = 20;

	char c[10] = "apple";
	char d[10] = "pie";

	printf("%d\n", a + b);
	printf("%s\n", c + d); // c와 d는 주소값이기때문에 string으로 출력 불가능.

	return 0;
}