#include <stdio.h>

int main()
{
	int a = 10;
	int* p = &a;
	double* pd;

	pd = p;

	printf("포인터pd에 의한 a의 값 : %lf\n", *pd);
	printf("pd가 가리키는 주소 : %d\n", pd);
	printf("a의 주소 : %d\n", &a);
	printf("p가 가리키는 주소이자 a의 주소 : %d\n", p);
	printf("직접 a의 값 : %d\n", a);
	printf("포인터 p를 통한 a의 값 : %d\n", *p);

	return 0;
}
