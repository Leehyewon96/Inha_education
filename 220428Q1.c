#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*"I am a boy. I am Happy!" ���ڿ��� �ִµ� ���� boy�� ��ġ �ּҸ� ����ϰ�
boy�� girl�� �ٲپ� ����ϵ��� �ϴ� �ڵ带 �ۼ��϶�.

��°�� >
	Boy ��ġ �ּ� : 0FF2 C400
	�ٲ� �� ���ڿ� :"I am a girl. I am Happy"
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