#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*길이가 6인 int형 배열 Arr 을 선언하고 1,2,3,4,5,6으로 초기화 한 다음에 
배열에 저장된 값의 순서가 6,5,4,3,2,1이 되도록 변경하는 프로그램을 작성하라.
단, 배열의 맨앞과 맨뒤를 가리키는 포인터 변수 두개를 선언해서 이를 활용하여 저장된 값의 순서를 뒤바꿔야한다.*/

void swap(char* pa, char* pb);

int main()
{
	char ary[100];
	gets(ary);

	int arySize = 0;
	for (int i = 0; ary[i] != '\0'; i++)
	{
		arySize++;
	}

	char *ps = ary;
	
	for (int i = 0; i < arySize / 2; i++)
	{
		swap(ps + i, ps + (arySize - i - 1));
	}

	puts(ps);

	return 0;
}

void swap(char* pa, char* pb)
{
	char temp = *pa;
	*pa = *pb;
	*pb = temp;
}
