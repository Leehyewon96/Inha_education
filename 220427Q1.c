#include <stdio.h>

/* int형 num1, num2를 선언과 동시에 10과 20으로 초기화 해주고, 
int형 포인터 ptr1, ptr2를 선언, 각 num1과 num2를 가리키게 한다.
ptr1과 ptr2를 이용해서 num1은 10 증가, num2는 10 감소하게 한다.
이후 ptr1과 ptr2가 가리키는 대상을 서로 바꾼다.
마지막으로 ptr1과 ptr2가 가리키는 변수의 내용을 출력한다.
그리고 각 변수에 저장된 값도 출력해서 확인한다.
*/

int main()
{
	int num1 = 10, num2 = 20;
	int  * ptr1, * ptr2;
	ptr1 = &num1;
	ptr2 = &num2;

	*ptr1 += 10;
	*ptr2 -= 10;

	int* temp;
	temp = ptr2;
	ptr2 = ptr1;
	ptr1 = temp;

	printf("ptr1이 가리키는 변수 : %d\n", *ptr1);
	printf("ptr2이 가리키는 변수 : %d\n", *ptr2);
	printf("num1 : %d\n", num1);
	printf("num2 : %d\n", num2);

	return 0;
}
