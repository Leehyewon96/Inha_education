#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#define max(a,b)  (((a) > (b)) ? (a) : (b))

void comp3(char* a, char* b, char* c); // 사전에서 첫번째 단어 찾기i
int comp2(char *a, char *b); // 사전에서 두번째, 세번째 단어 찾기

int main()
{
	char ch1[20], ch2[20], ch3[20];
	printf("세 단어 입력 : ");
	scanf("%s %s %s", ch1, ch2, ch3);

	comp3(ch1, ch2, ch3);

	return 0;
}

void comp3(char* a, char* b, char* c)
{
	char a1[20], a2[20], a3[20];
	int i = 0;
	while (1)
	{
		if (*a != *b || *b != *c)
		{
			break;
		}
		else
		{
			i++;
			comp2(*a == *b);
		}
	}

	if (*a != *b && *a != *c && *b != *c)
	{
		if (*a < min(*b, *c))
		{
			strcpy(a1, a);

			(comp2(b, c) == b) ? strcpy(a2, b), strcpy(a3, c) : strcpy(a2, c), strcpy(a3, b);
		}
		else if (*a > max(*b, *c))
		{
			strcpy(a3, a);

			(comp2(b, c) == b) ? strcpy(a1, b), strcpy(a2, c) : strcpy(a1, c), strcpy(a2, b);
		}
		else
		{
			strcpy(a2, a);

			(comp2(b, c) == b) ? strcpy(a1, b), strcpy(a3, c) : strcpy(a1, c), strcpy(a3, b);
		}
	}
	
	printf("%s %s %s", a1, a2, a3);
}

int comp2(char *a, char *b) 
{
	int min;
	if (*a == *b)
	{
		int i = 0;
		while (1)
		{
			if (*(a + i) == *(b + i))
			{
				i++;
				min = comp2((a + i), (b + i));
				break;
			}
		}
	}
	else
	{
		min = (*a < *b ? a : b);
	}

	return min;
}