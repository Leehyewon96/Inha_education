#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*���̰� 6�� int�� �迭 Arr �� �����ϰ� 1,2,3,4,5,6���� �ʱ�ȭ �� ������ 
�迭�� ����� ���� ������ 6,5,4,3,2,1�� �ǵ��� �����ϴ� ���α׷��� �ۼ��϶�.
��, �迭�� �Ǿհ� �ǵڸ� ����Ű�� ������ ���� �ΰ��� �����ؼ� �̸� Ȱ���Ͽ� ����� ���� ������ �ڹٲ���Ѵ�.*/

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
