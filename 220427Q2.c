#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*���̰� 6�� int�� �迭 Arr �� �����ϰ� 1,2,3,4,5,6���� �ʱ�ȭ �� ������
�迭�� ����� ���� ������ 6,5,4,3,2,1�� �ǵ��� �����ϴ� ���α׷��� �ۼ��϶�.
��, �迭�� �Ǿհ� �ǵڸ� ����Ű�� ������ ���� �ΰ��� �����ؼ� �̸� Ȱ���Ͽ� ����� ���� ������ �ڹٲ���Ѵ�.*/

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