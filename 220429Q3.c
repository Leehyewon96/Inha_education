#include <stdio.h>

/*
Q.	다음과 같이 배열에 숫자가 채워지도록 프로그램을
	작성하라. ( N x N 의 경우로만 작성할 것)
	ex >	3 x 3 의 경우
	
			1 2 6
			3 5 7
			4 8 9
*/

int main()
{
    int M[12][12];
    int size = sizeof(M) / sizeof(M[0]);
    int dia = (size * 2) - 1; // 대각선 개수
    int cnt; // 대각선마다 변수를 대입하는 횟수 
    int num = 0; // 대입되는 값
    int x = 0, y = 0; // 행, 열 값

    int i = 0; // 1번째 행 값

    for(int j = 0; j < dia; j++) //대각선의 개수만큼 반복
    {
        cnt = i + j + 1; // 대각선마다 최소 1개의 변수가 대입되므로 1을 더해줌

        if((i + j) % 2 == 0) // 행과 열의 합이 짝수일때 -> 아래에서부터 증가시키기 (행감소, 열증가)
        {
            if(cnt <= size)
            {
                x = cnt - 1;
                y = 0;
            }
            else
            {
                x = size - 1;
                y = cnt - size;
                cnt = size - y;
            }
            for(int k = 0; k < cnt; k++)
            {
                M[x][y] = ++num;
                x--;
                y++;
            }
        } 
        else // 행과 열의 합이 홀수일때 -> 위에서부터 증가시키기
        {
            if(cnt <= size)
            {
                x = 0;
                y = cnt - 1;
            }
            else
            {
                x = cnt - size;
                y = size - 1;
                cnt = size - x;
            }
            for(int k = 0; k < cnt; k++)
            {
                M[x][y] = ++num;
                x++;
                y--;
            }
        }
    }

    for(int i = 0; i < size; i++) // 출력
    {
        for(int j = 0; j < size; j++)
        {
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }
    return 0;
}