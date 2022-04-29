#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <string.h>


int main()
{
	char s[100] = "I am a boy. I am Happy!";
	char find[10];
	printf("I am a boy. I am Happy!\n");
	printf("위 문장에서 수정하고 싶은 문자열을 입력하세요");
	gets(find);
	printf("새로운 문자열을 입력하세요.");
	char news[10];
	gets(news);
	char temp1[10];
	int slen = strlen(s);
	int findlen = strlen(find);
	int newslen = strlen(news);
	int error = newslen - findlen;
	int cnt = 0;

	while(1)
	{
		for (int j = cnt; j < cnt + findlen; j++)
		{
			temp1[j - cnt] = s[j];
		}
		if (strncmp(temp1, find, 3) == 0)
		{
			break;
		}
		cnt++;
	}

	printf("%p\n", s[cnt]); // boy주소값 반환

	if (error >= 0)
	{
		for (int i = slen - 1; i >= cnt + findlen; i--) // 오차만큼 인덱스 이동
		{
			*(s + i + error) = *(s + i);
		}
	}
	else
	{
		for (int i = cnt + findlen; i < slen - 1; i++) // 오차만큼 인덱스 이동
		{
			*(s + i + error) = *(s + i);
		}
	}

	for (int i = cnt; i < cnt + newslen; i++) // 바꿀단어 교체
	{
		*(s + i) = *(news + i - cnt);
	}

	printf("%s\n", s);

	return 0;
}
