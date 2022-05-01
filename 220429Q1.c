#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*행렬 전환
  다음과 같은 A행렬을 B행렬과 같은 형태가 되도록 하라.
  
  A				B			A		B
  1 2 3 4		5 1			1 2 3   7 4 1
  5 6 7 8		6 2			4 5 6   8 5 2
				7 3			7 8 9   9 6 3
				8 4
  */

int main(void)
{
	int A[2][4] = { {1, 2, 3, 4}, {5, 6, 7, 8} };
	int B[4][2];

	int cnt1 = sizeof(A) / sizeof(A[0]);
	int cnt2 = sizeof(A[0]) / sizeof(A[0][1]);

	for (int i = 0; i < cnt1; i++) // A행렬의 행
	{
		for (int j = 0; j < cnt2; j++) // B행렬의 행
		{
			B[j][i] = A[i][j];
		}
	}

	for (int i = 0; i < cnt2; i++)
	{
		for (int j = cnt1 - 1; j >= 0; j--)
		{
			printf("%d\t", B[i][j]);
		}
		printf("\n");
	}

}