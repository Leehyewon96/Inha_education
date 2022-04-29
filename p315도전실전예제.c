#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	char c1, c2, c3;
	char ch = getchar();
	c1 = getchar();
	c2 = getchar();
	c3 = getchar();

	printf("%c %c %c", c1, c2, c3);
	printf("----");
	return 0;

	/*
	char ch;
	int size = 0, maxSize = 0;

	while (1)
	{
		size = 1;
		ch = getchar();

		if (ch == EOF)
		{
			break;
		}

		while(getchar() != '\n')
		{
			size++;
		}


		if (size >= maxSize)
		{
			maxSize = size;
		}

	}

	printf("%d", maxSize);

	return 0;
	*/

}