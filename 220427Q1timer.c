#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define ONE_SECOND 100
#define Max 7

/*광고판 문자열 출력프로그램을 포인터를 이용한 코드로 바꿔 재작성 하도록 한다.*/

int main()
{
	char str[Max];
	gets(str);

	char* s = str;

	while (1)
	{
		int temp = *(s + 0);
		for (int i = 0; i < Max -1; i++)
		{
			*(s + i) = *(s + (i + 1));
		}
		*(s + Max -2) = temp;
		system("cls");

		puts(str);

		Sleep(ONE_SECOND);
	}

	return 0;
}