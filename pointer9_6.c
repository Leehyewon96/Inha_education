#include <stdio.h>

int main()
{
	int a = 10;
	int* p = &a;
	double* pd;

	pd = p;

	printf("������pd�� ���� a�� �� : %lf\n", *pd);
	printf("pd�� ����Ű�� �ּ� : %d\n", pd);
	printf("a�� �ּ� : %d\n", &a);
	printf("p�� ����Ű�� �ּ����� a�� �ּ� : %d\n", p);
	printf("���� a�� �� : %d\n", a);
	printf("������ p�� ���� a�� �� : %d\n", *p);

	return 0;
}
