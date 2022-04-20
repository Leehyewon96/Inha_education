#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{

    int m, n, i = 1;
    int keep = 99;
    printf("두 정수 m, n을 입력하세요.");
    scanf("%d %d", &m, &n);
    //2,3 입력 -> max = 3, min = 2, maxKeep = 3, keep = 98 //4 6
    // test
    do
    {
        int max = (m * i > n * i) ? m * i : n * i; // 현재 계산 최댓값
        int min = (m * i < n* i) ? m * i : n * i; // 현재 계산 최솟값

        max < keep ? printf("%d %d ", min, max) : printf("%d %d", min, keep);
        keep = max;

        i++;
    } while (m * i < 99);

    return 0;

    // 나머지 정리 % 
    // 2 4 6 8 10
    // 
    // 3 6 9 12 15
    // 2 3 


/*
    for (int i = 1; n * i < 99 && m * i < 99; i++)
    {

        int max = (m * i > n * i) ? m * i : n * i; // 현재 계산 최댓값
        int min = (m * i < n* i) ? m * i : n * i; // 현재 계산 최솟값 

        max < keep ? printf("%d %d ", min, max) : printf("%d %d", min, keep);

        keep = max;


        return 0;

    }
}
*/




    /*Q7. 1이상 100미만인 정수 m과 n의 배수를 출력하는 프로그램을 작성하라.
    단, m의 배수이면서 n의 배수인 정수는 한번만 출력해야 한다.
    
    ex) 7 9
    7 9 14 18 21 27 28 35 36

    2 3 4 6
    */

    /*Q9.
    int n;
    printf("n행과 n열을 만들 때, 정수 n을 입력하세요.");
    scanf("%d", &n);

    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < n - i + 1; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i; k++)
        {
            printf("*");
        }
        printf("\n");
    }

    return 0;
    */

    /*Q8.

    int n;
    printf("n행과 n열을 만들 때, 정수 n을 입력하세요.");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i+1; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    return 0;

    */

    /*Q7. 1이상 100미만인 정수 m과 n의 배수를 출력하는 프로그램을 작성하라.
    단, m의 배수이면서 n의 배수인 정수는 한번만 출력해야 한다.
    ex) 7 9
    7 9 14 18 21 27 28 35 36

    2 3 4 6 
    

    
    int m, n, mMul, nMul, keep1, keep2, keep3 = 0, i = 1;

    printf("정수 m, n을 입력하세요.");
    scanf("%d %d", &m, &n);

    do
    {
        mMul = m * i;
        nMul = n * i;
        
        keep1 = mMul > nMul ? nMul : mMul; // keep1에 작은 수 저장
        keep2 = mMul > nMul ? mMul : nMul; // keep2에 큰 수 저장
        //keep3 = keep1;

        printf("%d ", keep1); // 작은 수 출력
        printf("%d ", keep2 < keep3 ? keep2 : keep3);


        keep3 = keep2;
        i++;

    } while ((mMul >= 1 && mMul < 99) && (mMul >= 1 && nMul < 99));

    return 0;
    
    */


    /*
    int number = 0;
    for (int i = 1; i <= 100; i++)
    {
        if ((i % 3) == 0)
        {
            continue;//그 이하의 문장을 무시하고 맨 앞으로간다. / break : 반복문을 탈출한다.
        }
        number += i;
    }

    printf("number : %d\n", number);

    return 0;
    */

    /*
    int number = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j <= 5; j++)
        {
            if (j > 3) break;
            printf("*");
        }
        printf("\n");
    }
    */

    /*
    for (int i = 2; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            printf("%d * %d = %d\n", i, j, i * j);
        }
        printf("\n");
    }

    return 0;
    */

    /*Q6.사용자로부터 계속 정수를 입력받아 그 값을 계속 더해 나간다. 
    사용자가 0을 입력할때까지 계속 되어야하며, 0이 입력되면 입력된 모든 정수의 합을 출력한다.

    int a, sum = 0;


    do
    {
        printf("정수를 입력하세요(0을 입력하면 종료됩니다.) : ");
        scanf("%d", &a);

        sum += a;

    } while (a != 0);

    printf("입력한 수의 합은 %d입니다.", sum);

    return 0;
    */


    /*
    int a;

    do
    {
        printf("정수를 입력하세요 (continue : 양수 / break : 0 또는 음수): ");
        scanf("%d", &a);
    } while (a < 0);

    printf("%d은 음수가 아니므로 종료되었습니다.", a);

    return 0;
    */


    /*
    int a;
    printf("정수를 입력하세요 : ");
    scanf("%d", &a);
    printf("입력받은 값은 %d\n", a);

    while (1)
    {

        do
        {
            printf("원하는 메뉴를 선택하시오: ");
            printf("덧셈 1, 뺄셈 2, 그만두기: -1");
            scanf("%d\n", &a);
        } while (a > 0);
        if (a < 0) break;

        switch (a)
        {
        case 1 :
            break;
        }
    }
    */
    /*Q5.사용자로부터 양의 정수 m과 n을 입력받아
    n개만큼 m의 배수를 출력하는 프로그램을 작성
    ex) 3  4
    3 6 9 12

    int m, n;
    printf("정수 m, n을 입력하세요.");
    scanf("%d %d", &m, &n);
    
    int a;

    for (int i = 1; i <= n; i++)
    {
        a = m * i;

        printf("%d ", a);
    }

    return 0;
    */


    /*
    int num1, num2, startNum, endNum;
    printf("두개의 정수를 입력하세요.");
    scanf("%d %d", &num1, &num2);

    int sum = 0;

    startNum = (num2 < num1) ? num2 : num1;
    endNum = (num2 > num1) ? num2 : num1;

    for (int i = startNum; i <= endNum; i++)
    {
        sum += i;
    }
    
    printf("%d + %d = %d\n", startNum, endNum, sum);

    return 0;

    */

    /*Q4 두 수를 입력받아 두 수 사이에 존재하는 정수의 합을 구하는 프로그램을 작성하라.*/

    /*
    int num1, num2, sum, maxNum, minNum;
    printf("두개의 정수를 입력하세요.");
    scanf("%d %d", &num1, &num2);

    if (num1 > num2)
    {
        maxNum = num1;
        minNum = num2;
    }
    else
    {
        maxNum = num2;
        minNum = num1;
    }

    for (int i = num1; i <= num2; i++)
    {
        sum = num1 + i;
    }

    printf("%d + %d = %d\n", minNum, maxNum, sum);
    
    return 0;
    */

    /*
    int a;
    printf("정수 a를 입력하세요.");
    scanf("%d", &a);

    int b = a;
    int i = 1;

    if (a > 0)
    {
        while (i<a)
        {
            i *= b;
            b--;
        }
    }
    else 
        printf("자연수가 아닙니다.");

    printf("%d\n", a);
    

    return 0;
    */



    /*Q3.어떤 자연수를 입력받아 팩토리얼을 구하는 프로그램을 작성하라.
    int a = 1;

    printf("정수 a를 입력하세요.");

    scanf("%d", &a);

    if (a > 0)
    {
        int b = a;
        for (int i = 1; i < b; i++)
        {
            a *= i;
        }
    }

    else
        printf("자연수가 아닙니다.");


    printf("%d\n", a);

    return 0;
    */


    /*
    int a = 1;
    int i;

    for (int i = 0; i < 3; i++)
    {
        a = a * 2;
    }

    printf("a : %d\n", a);

    return 0;
    */

    /*
    int a = 6;

    while (a < 10) // 조건식이 참인 동안 while문 내부 동작실행
    {
        a = a * 2;
    }

    printf("a: %d\n", a);

    return 0;
    */

    /*Q2. 학생의 전체 평균 점수에 대한 학점을 출력하는 프로그램 작성.
    성적이 90점 이상 A
    성적이 80점 이상 B
    성적이 70점 이상 C
    성적이 60점 이상 D
    그 미만은 F로 처리.
    프로그램 실행시 국, 영, 수 점수를 입력 받는다.
    그 평균을 구하고, 위를 참고하여 적절한 학점을 출력하라.
    

    int K, E, M;
    char grade;
    printf("국어, 영어, 수학 점수를 모두 입력하세요.");
    scanf("%d %d %d", &K, &E, &M);

    double mScore = (K + E + M) / 3;

    if (mScore >= 90)
    {
        grade = 'A';
    }
    else if (mScore < 90 && mScore >= 80)
    {
        grade = 'B';
    }
    else if (mScore < 80 && mScore >= 90)
    {
        grade = 'C';
    }
    else if (mScore < 70 && mScore >= 80)
    {
        grade = 'D';
    }
    else
    {
        grade = 'F';
    }

    printf("학점은 %c입니다.", grade);

    return 0;
    */
    


    /*
    int rank =3, m = 0;


    switch (rank)
    {
    case 1 :
        m = 300;
        break;//case마다 break없으면 다음 default까지 자동으로 넘어감.
    case 2 :
        m = 200;
        break;
    case 3:
        m = 100;
        break;
    default : //case에 없는 경우에 실행되는 동작
        m = 10;
        break;
    }

    printf("%d\n", m);

    return 0;
    */


    /* Q1. 두개의 정수를 입력받아 두 수의 차를 출력하는 프로그램을 작성하라.
    단, 무조건 큰 수에서 작은 수를 빼야 한다.
    

    int a, b;

    printf("정수 a와 b를 입력하세요.");

    scanf("%d %d", &a, &b);

    (a > b) ? printf("%d - %d = %d\n", a, b, a - b) : printf("%d - %d = %d\n", b, a, b - a);

    return 0;
    */

    /*
    int a, b;

    printf("정수 a와 b를 입력하세요.");

    scanf("%d %d", &a, &b);

    if (a > b)
    {
        printf("%d - %d = %d\n", a, b, a - b);
    }
    else
    {
        printf("%d - %d = %d\n", b, a, b - a);
    }

    return 0;
    */


    /*
    int a = 0;
    scanf("%d", &a);

    if (a % 2)
    {
        printf("입력된 수 %d 홀수입니다.\n", a)        ;
    }
    
    else if (!(a % 2))
    {
        printf("입력된 수 %d 짝수입니다.\n", a);
    }
    */


    /*
    int a = 20;
    int b = 0;

    if (a > 10)
    {
        b = a;
    }

    printf("a : %d, b :%d\n", a, b);

    return 0;
    */
