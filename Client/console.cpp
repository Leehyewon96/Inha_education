// console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//client
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define Buf_Size 1024
char strServerIP[] = "172.30.1.7";// "172.30.1.9";주한
char strClientIP[] = "127.0.0.1"; //127.0.0.1 -> 자기자신
char strPort[] = "12345"; // 1024 이하는 사용금지 (이미 컴퓨터에서 쓰고 있음)


void Error(const char* msg);
void Log(const char* msg);
void Client_Code();

int main()
{
    Client_Code();
    return 0;
}


void Error(const char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
void Log(const char* msg)
{
    fputs(msg, stdout);
    fputc('\n', stdout);
}

void Client_Code()
{
    WSADATA wsaData;
    SOCKET serverSocket;
    char msg[Buf_Size];
    int strlength, i;

    SOCKADDR_IN serverAddr;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        Error("WSAStartup() Error");

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
        Error("Socket() Error");

    Log("Socket OK");

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.S_un.S_addr = inet_addr(strServerIP);
    serverAddr.sin_port = htons(atoi(strPort));
    
    if (connect(serverSocket, (SOCKADDR *) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        Error("connect() Error");

    puts("Connected....");

    while (1)
    {
        fputs("Input message(Q to quit):", stdout);
        fgets(msg, Buf_Size, stdin);
        if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
            break;

        send(serverSocket, msg, strlen(msg), 0);
        strlength = recv(serverSocket, msg, Buf_Size - 1, 0);
        msg[strlength] = 0;
        printf("Message from server : %s\n", msg);
    }

    closesocket(serverSocket);
    WSACleanup();
}









// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
