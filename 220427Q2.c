#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*길이가 6인 int형 배열 Arr 을 선언하고 1,2,3,4,5,6으로 초기화 한 다음에
배열에 저장된 값의 순서가 6,5,4,3,2,1이 되도록 변경하는 프로그램을 작성하라.
단, 배열의 맨앞과 맨뒤를 가리키는 포인터 변수 두개를 선언해서 이를 활용하여 저장된 값의 순서를 뒤바꿔야한다.*/

void swap(int* pa, int* pb);

int main()
{
	int ary[6] = { 1, 2, 3, 4, 5, 6 };
	int* ps = ary;

	for (int i = 0; i < 3; i++)
	{
		swap(ps + i, ps + (5 - i));
	}

	for (int i = 0; i < 6; i++)
	{
		printf("%d", *(ps + i));
	}

	return 0;
}

void swap(int* pa, int* pb)
{
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}