#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	printf("apple�� ����� ���� �ּ� �� : %p\n", "apple");
	printf("�� ��° ������ �ּ� �� : %p\n", "apple" + 1);
	printf("ù ��° ���� : %c\n", *"apple");
	printf("�� ��° ���� : %c\n", *("apple" + 1));
	printf("�迭�� ǥ���� �� ��° ���� : %c\n", "apple"[3]);

	return 0;
}