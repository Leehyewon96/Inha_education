#include <stdio.h>

/*Q.배열에 숫자를 다음과 같은 방법으로 채워지도록
	프로그램을 작성하라.
	시계 방향으로 m x m 의 2차원 배열에 숫자가 채워지도록 한다.
	ex >
			1 2 3
			8 9 4
			7 6 5
  */


int main()
{
	int M[4][4];
	int x = 0, y = -1; // 행x, 열y
	int n = sizeof(M) / sizeof(M[0]); // 행열수
	int num = n; //while 안에서 n값 손실
	int cnt = 0;//대입되는 숫자
	int u = 1; // 증감연산

	while (n > 0)
	{
		for (int i = 0; i < n; i++) // 열증가,열감소
		{
			y += u;
			M[x][y] = ++cnt;
		}
		n--;
		for (int i = 0; i < n; i++)//행증가
		{
			x += u;
			M[x][y] = ++cnt;
		}
		u *= -1;
	}

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			printf("%4d", M[i][j]);
		}
		printf("\n");
	}
}