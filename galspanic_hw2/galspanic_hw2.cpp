// galspanic_hw2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Resource.h"
#include "framework.h"
#include "galspanic_hw2.h"
#include "Object.h"
#include "Sigong.h"

#pragma comment (lib, "msimg32.lib")

// >> GDI
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;
ULONG_PTR g_GdiToken;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
static RECT rcClient;
int Run_Frame_Max = 0;
int Run_Frame_Min = 0;
int curFrame = 0;
HDC hdc;

//격자배열
static bool check[81][81] = {0};
static bool draw[81][81] = { 0 };
static bool space = false;

//비트맵 이미지
HBITMAP hDoubleBufferImage;
HBITMAP hBackImage;
BITMAP bitBack;
HBITMAP hSigongImage;
BITMAP bitSigong;

//객체 생성
Sigong sigong({0,0});
//sigong.setP({ 450 - bx / 2, 500 - by / 2 });


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void Update();
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
void CoverDrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
void CreateBitmap();
VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void UpdateFrame(HWND hWnd);
void DeleteBitmap();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GALSPANICHW2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GALSPANICHW2));

    MSG msg;

    //check[0][0] = true;
    // 
    // << 테두리 1로 바꾸기
    /*for (int i = 0; i <= 80; i++)
    {
        check[i][0] = true;
        check[i][80] = true;
    }
    for (int j = 0; j <= 80; j++)
    {
        check[0][j] = true;
        check[80][j] = true;
    }*/
    
    // >>

    // 기본 메시지 루프입니다:
    /*while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/
    while (true)
    {
        //메시지가 발생했을때
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } //메시지가 발생하지 않았을때
        else
        {
            Update();
        }
    }
    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GALSPANICHW2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GALSPANICHW2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //double Wwidth = bitSigong.bmWidth * (int)(900 / bitSigong.bmWidth);
   //double Wheight = bitSigong.bmHeight * (int)(1000 / bitSigong.bmHeight);


   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       50, 50, 816, 859, nullptr, nullptr, hInstance, nullptr);

   

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int TIMER_IDI = 1;
    static POINT mousePos;

    for (int i = 0; i <= 80; i++)
    {
        check[i][0] = true;
        check[i][80] = true;
    }
    for (int j = 0; j <= 80; j++)
    {
        check[0][j] = true;
        check[80][j] = true;
    }

    switch (message)
    {
    case WM_CREATE:
        
        GetClientRect(hWnd, &rcClient);
        SetTimer(hWnd, TIMER_IDI, 100, TimerProc);
        CreateBitmap();
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		DrawBitmapDoubleBuffering(hWnd, hdc);

        //CoverDrawBitmapDoubleBuffering(hWnd, hdc);

        
        if (sigong.getSpace() == true && sigong.getPvec().size() != 0)
        {
            HPEN MyPen, OldPen;
            MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
            OldPen = (HPEN)SelectObject(hdc, MyPen);
            sigong.drawLine(hdc, sigong.getPvec());
            SelectObject(hdc, OldPen);
            DeleteObject(MyPen);
        }

        /*TCHAR str[50];
        wsprintf(str, TEXT("%d %d"), mousePos.x, mousePos.y);
        TextOut(hdc, 10, 10, str, lstrlen(str));*/


		//TextOut(hdc, 100, 100, str, _tcslen(str));
		//DrawText(hdc, 100, 100, _T("%d %d"), _tcslen());
		EndPaint(hWnd, &ps);
	}
	break;
    case WM_MOUSEMOVE:
        mousePos.x = LOWORD(lParam);
        mousePos.y = HIWORD(lParam);
        //InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        DeleteBitmap();
        PostQuitMessage(0);
        KillTimer(hWnd, TIMER_IDI);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void CreateBitmap()
{
    hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/수지.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hBackImage, sizeof(BITMAP), &bitBack);

    hSigongImage = (HBITMAP)LoadImage(NULL, TEXT("images/m_sigong1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hSigongImage, sizeof(BITMAP), &bitSigong);
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    //>>
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx, by;
    bx = rcClient.right;
    by = rcClient.bottom;
    //<<

    HDC hMemDC2;
    HBITMAP hOldBitmap2;

    hMemDC = CreateCompatibleDC(hdc);

    //BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);
    if (hDoubleBufferImage == NULL)
        hDoubleBufferImage = CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom);

    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

    hMemDC2 = CreateCompatibleDC(hMemDC);
    //TransparentBlt(hMemDC2, 0, 0, bx, by, hMemDC, 0, 0, bx, by, RGB(100, 200, 0));
    //hMemDC3 = CreateCompatibleDC(hMemDC);
    hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);

    TransparentBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 0));
    //BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);

    //TransparentBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, bx, by, RGB(100, 200, 0));
    SelectObject(hMemDC2, hOldBitmap2);
    DeleteDC(hMemDC2);

    //수지
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // hMemDC를 복사해서 hMemDC2에 넣어주기
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom)); // 시공 이미지를 hMemDC2에 그려주기

        //TransparentBlt(hMemDC2, 0, 0, bx, by, hMemDC, 0, 0, bx, by, RGB(100, 200, 0));
        
        //BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);
        //BitBlt(hMemDC, 0, 0, bx, by, hMemDC3, 0, 0, SRCCOPY);
        //        시작위치    어디까지 출력할건지     사진에서 출력할 위치
        
        for (int i = 0; i <= 79; i++)
        {
            for (int j = 0; j <= 79; j++)
            {
                if (((check[i][j] == false) && (check[i + 1][j] == false) && (check[i][j + 1] == false) && (check[i + 1][j + 1] == false)))
                {
                    HBRUSH MyBrush, OldBrush;
                    MyBrush = CreateSolidBrush(RGB(100, 200, 0));
                    OldBrush = (HBRUSH)SelectObject(hMemDC2, MyBrush);
                    HPEN MyPen, OldPen;
                    MyPen = CreatePen(PS_SOLID, 5, RGB(100, 200, 0));
                    OldPen = (HPEN)SelectObject(hMemDC2, MyPen);
                    Rectangle(hMemDC2, i * 10, j * 10, (i + 1) * 10, (j + 1) * 10);
                    SelectObject(hMemDC2, OldPen);
                    DeleteObject(MyPen);
                    SelectObject(hMemDC2, OldBrush);
                    DeleteObject(MyBrush);
                }
            }
        }

        TransparentBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, bx, by, RGB(0, 0, 0));
        //BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);

        //TransparentBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, bx, by, RGB(100, 200, 0));
        DeleteObject(SelectObject(hMemDC2, hOldBitmap2));
        DeleteDC(hMemDC2);

        //DeleteDC(hMemDC3);
    }

    {
        //sigong
        hMemDC2 = CreateCompatibleDC(hMemDC); // hMemDC를 복사해서 hMemDC2에 넣어주기
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hSigongImage); // 시공 이미지를 hMemDC2에 그려주기
        bx = bitSigong.bmWidth;
        by = bitSigong.bmHeight;

        //sigong.setP({ 0 - bx / 2, 0 - by / 2 });
        TransparentBlt(hMemDC, sigong.getP().x - bx / 2, sigong.getP().y - by / 2, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255)| RGB(255, 0, 0));
        
            
        //BitBlt(hdc, sigong.getP().x, sigong.getP().y, bx, by, hMemDC, 0, 0, SRCCOPY);
        //        시작위치               사진에서 출력할 위치
        //StretchBlt(hdc, 700, 0, 200, 200, hMemDC, 0, 0, bx, by, SRCCOPY);

        SelectObject(hMemDC2, hOldBitmap2);

        DeleteDC(hMemDC2);
    }

    //Gdi_Draw(hMemDC);
    BitBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, hMemDC, 0, 0, SRCCOPY);
    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}



void CoverDrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    /** 더블버퍼링 시작처리입니다. **/
    //static HDC hdc, MemDC;
    static HDC MemDC;
    static HBITMAP BackBit, oldBackBit;
    static RECT bufferRT;
    //MemDC = BeginPaint(hWnd, &ps);

    GetClientRect(hWnd, &bufferRT);
    hdc = CreateCompatibleDC(MemDC);
    BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
    oldBackBit = (HBITMAP)SelectObject(hdc, BackBit);
    PatBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

    // TODO: 여기에 그리기 코드를 추가합니다.
    for (int i = 0; i <= 79; i++)
    {
        for (int j = 0; j <= 79; j++)
        {
            if ((check[i][j] == false) && (check[i + 1][j] == false) && (check[i][j + 1] == false) && (check[i + 1][j + 1] == false))
            {
                HBRUSH MyBrush, OldBrush;
                MyBrush = CreateSolidBrush(RGB(100, 200, 0));
                OldBrush = (HBRUSH)SelectObject(MemDC, MyBrush);
                HPEN MyPen, OldPen;
                MyPen = CreatePen(PS_SOLID, 5, RGB(100, 200, 0));
                OldPen = (HPEN)SelectObject(MemDC, MyPen);
                Rectangle(MemDC, i * 10, j * 10, (i + 1) * 10, (j + 1) * 10);
                SelectObject(MemDC, OldPen);
                DeleteObject(MyPen);
                SelectObject(MemDC, OldBrush);
                DeleteObject(MyBrush);
            }
        }
    }

    /*for (int i = 0; i < 10; i++) {
        Rectangle(hdc, rand() % bufferRT.right, rand() % bufferRT.bottom, rand() % bufferRT.right, rand() % bufferRT.bottom);
        Sleep(30);
    }*/

    /** 더블버퍼링 끝처리 입니다. **/
    GetClientRect(hWnd, &bufferRT);
    BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hdc, 0, 0, SRCCOPY);
    SelectObject(hdc, oldBackBit);
    DeleteObject(BackBit);
    //DeleteDC(hdc);
    //EndPaint(hWnd, &ps);
}

VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    UpdateFrame(hWnd);
    InvalidateRect(hWnd, NULL, false);
}

void UpdateFrame(HWND hWnd)
{
    curFrame++;
    if (curFrame > Run_Frame_Max)
        curFrame = Run_Frame_Min;
}

void Update()
{
    DWORD newTime = GetTickCount();
    static DWORD oldTime = newTime;
    if (newTime - oldTime < 100)
        return;
    oldTime = newTime;

    //Async의 경우 비동기적인 흐름이다. 그러므로 메시지의 큐를 거치지 않는다.
    
    // << 지나간 면적 true로 바꾸기
    for (int i = 1; i <= 80; i++)
    {
        int j = 1;

        while (j != 80)
        {
            if (check[i][j] == true)
            {
                for (int k = 1; k < j; k++)
                {
                    check[i][k] = true;
                }

                break;
            }
            j++;
        }
    }
    // >>

    //keydown
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        sigong.setSpace(true);
    }
    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && (sigong.moveConfirm() == 'R' || sigong.moveConfirm() == 'A'))
    {
        sigong.setRight(true);
        if (sigong.getSpace() == true && (sigong.getP().x + 10 <= rcClient.right) && draw[(sigong.getP().x + 10) / 10][sigong.getP().y / 10] == false)
        {
            sigong.pushPvec({ sigong.getP().x , sigong.getP().y });
            sigong.setP({ sigong.getP().x + 10, sigong.getP().y });
        }
        else if ((sigong.getP().x + 10 <= rcClient.right) && (check[(sigong.getP().x + 10) / 10][sigong.getP().y / 10] == true))
            sigong.setP({ sigong.getP().x + 10, sigong.getP().y });
    }
    else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && (sigong.moveConfirm() == 'L' || sigong.moveConfirm() == 'A'))
    {
        sigong.setLeft(true);
        if (sigong.getSpace() == true && (sigong.getP().x - 10 >= rcClient.left) && draw[(sigong.getP().x - 10) / 10][sigong.getP().y / 10] == false)
        {
            sigong.pushPvec({ sigong.getP().x , sigong.getP().y });
            sigong.setP({ sigong.getP().x - 10, sigong.getP().y });
        }
        else if ((sigong.getP().x - 10 >= rcClient.left) && (check[(sigong.getP().x - 10) / 10][sigong.getP().y / 10] == true))
            sigong.setP({ sigong.getP().x - 10, sigong.getP().y });
    }
    else if ((GetAsyncKeyState(VK_UP) & 0x8000) && (sigong.moveConfirm() == 'U' || sigong.moveConfirm() == 'A'))
    {
        sigong.setUp(true);
        if (sigong.getSpace() == true && (sigong.getP().y - 10 >= rcClient.top) && draw[(sigong.getP().x) / 10][(sigong.getP().y - 10) / 10] == false)
        {
            sigong.pushPvec({ sigong.getP().x , sigong.getP().y });
            sigong.setP({ sigong.getP().x, sigong.getP().y - 10 });
        }
        else if ((sigong.getP().y - 10 >= rcClient.top) && check[sigong.getP().x / 10][(sigong.getP().y - 10) / 10] == true)
            sigong.setP({ sigong.getP().x, sigong.getP().y - 10 });
    }
    else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && (sigong.moveConfirm() == 'D' || sigong.moveConfirm() == 'A'))
    {
        sigong.setDown(true);
        if (sigong.getSpace() == true && (sigong.getP().y + 5 <= rcClient.bottom) && draw[(sigong.getP().x) / 10][(sigong.getP().y + 10) / 10] == false)
        {
            sigong.pushPvec({ sigong.getP().x , sigong.getP().y });
            sigong.setP({ sigong.getP().x, sigong.getP().y + 10 });
        }
        else if ((sigong.getP().y + 5 <= rcClient.bottom) && check[sigong.getP().x / 10][(sigong.getP().y + 10) / 10] == true)
            sigong.setP({ sigong.getP().x, sigong.getP().y + 10 });
    }
    
    //keyup
    if (!(GetAsyncKeyState(VK_SPACE) & 0x8000))
    {
        sigong.setSpace(false);
        if (sigong.getPvec().size() != 0)
        {
            if (check[sigong.getP().x / 10][sigong.getP().y / 10] == false)
                sigong.setP(sigong.getPvec().front());
            else
            {
                // << 마지막 좌표 저장
                int cnt = 0;
                for (int i = 0; i < sigong.getPvec().size(); i++)
                {
                    check[sigong.getPvec()[i].x / 10][sigong.getPvec()[i].y / 10] = true; // 간 경로 true로 바꾸기

                    if (sigong.getPvec()[i].x == sigong.getP().x && sigong.getPvec()[i].y == sigong.getP().y)
                    {
                        cnt++;
                    }
                }
                if (cnt == 0)
                {
                    sigong.pushPvec(sigong.getP());
                    cnt = 0;
                }
                //>>

                // << 지나간 면적 true로 바꾸기
                /*for (int i = 0; i <= 80; i++)
                {
                    int j = 1;
                    
                    while (j != 80)
                    {
                        if (check[i][j] == true)
                        {
                            for (int k = 0; k <= j; k++)
                            {
                                check[i][k] == true;
                            }
                            break;
                        }
                        j++;
                    }
                }*/
                // >>
            }
            sigong.clearPvec();
        }
        
        
    }
    if (!(GetAsyncKeyState(VK_RIGHT) & 0x8000))
    {
        sigong.setRight(false);
    }
    if (!(GetAsyncKeyState(VK_LEFT) & 0x8000))
    {
        sigong.setLeft(false);
    }
    if (!(GetAsyncKeyState(VK_UP) & 0x8000))
    {
        sigong.setUp(false);
    }
    if (!(GetAsyncKeyState(VK_DOWN) & 0x8000))
    {
        sigong.setDown(false);
    }
}

void DeleteBitmap()
{
    DeleteObject(hBackImage);
    DeleteObject(hSigongImage);
}


//폴리곤 좌표 알고리즘
//    else
//    {
//        int cnt = 0;
//        for (int i = 0; i < sigong.getPvec().size(); i++)
//        {
//            check[sigong.getPvec()[i].x / 10][sigong.getPvec()[i].y / 10] = true;
//
//            if (sigong.getPvec()[i].x == sigong.getP().x && sigong.getPvec()[i].y == sigong.getP().y)
//            {
//                cnt++;
//            }
//        }
//        if (cnt == 0)
//        {
//            sigong.pushPvec(sigong.getP());
//            cnt = 0;
//        }
//
//
//
//        double bigX = sigong.getPvec().front().x >= sigong.getPvec().back().x ? sigong.getPvec().front().x : sigong.getPvec().back().x;
//        double smallX = sigong.getPvec().front().x <= sigong.getPvec().back().x ? sigong.getPvec().front().x : sigong.getPvec().back().x;
//        double bigY = sigong.getPvec().front().y >= sigong.getPvec().back().y ? sigong.getPvec().front().y : sigong.getPvec().back().y;
//        double smallY = sigong.getPvec().front().y <= sigong.getPvec().back().y ? sigong.getPvec().front().y : sigong.getPvec().back().y;
//
//        vector<POINT> temp;
//        temp = sigong.getPolyvec();
//        sigong.clearPolyvec();
//
//        sigong.pushPolyvec(sigong.getPvec().front());
//        for (int i = 0; i < temp.size(); i++)
//        {
//            if (temp[i].x >= smallX && temp[i].x <= bigX && temp[i].y >= smallY && temp[i].y <= bigY)
//            {
//                temp.erase(temp.begin() + i);
//            }
//        }
//
//        for (int i = 0; i < temp.size(); i++)
//        {
//            sigong.pushPolyvec(temp[i]);
//        }
//
//        for (int i = sigong.getPvec().size() - 1; i >= 1; i--)
//        {
//            sigong.pushPolyvec(sigong.getPvec()[i]);
//        }
//
//        //sigong.pushPolyvec(sigong.getPvec().back());
//    }
//}
//sigong.clearPvec();