#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <string.h>

/*Q. "I am a boy. I am Happy!" 문자열이 있는데

이 중 boy 의 위치 주소를 출력하고

boy 를 girl 로 바꾸어 출력하도록 하는 코드를

작성하라.

​

출력결과)

boy 위치 주소 : 0FF2 C400

바뀐 문자열 : "I am a girl. I am Happy!"
*/

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
