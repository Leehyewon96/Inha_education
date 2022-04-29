#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*"I am a boy. I am Happy!" 문자열이 있는데 이중 boy의 위치 주소를 출력하고
boy를 girl로 바꾸어 출력하도록 하는 코드를 작성하라.

출력결과 >
	Boy 위치 주소 : 0FF2 C400
	바뀐 후 문자열 :"I am a girl. I am Happy"
*/

int main()
{
	char str1[25] = "I am a boy. I am Happy!";
	char str2[25];
	char str3[5] = "girl";
	char str4[4] = "boy";

	int cnt = 0;
	int count = 0;
	
	int i = 0;
	while (str1[i] == str4[0] && str2[i + 1] == str4[1] && str3[i + 2] == str4[2])
	{
		
	}
	return 0;
}