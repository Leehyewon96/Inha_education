// Project5.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Project5.h"

#pragma comment (lib, "msimg32.lib")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HBITMAP hBackImage;
BITMAP bitBack;
HBITMAP hSigongImage;
BITMAP bitSigong;
HBITMAP hAniImage;
BITMAP bitAni;
const int Sprite_Size_X = 57;
const int Sprite_Size_Y = 52;

int Run_Frame_Max = 0;
int Run_Frame_Min = 0;
int curFrame = 0;

HBITMAP hDoubleBufferImage;

void CreateBitmap();
void DrawBitmap(HDC hdc);
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);

void DeleteBitmap();
void UpdateFrame(HWND hWnd);
void DrawRectText(HDC hdc);
VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

static RECT rcClient;

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
    LoadStringW(hInstance, IDC_PROJECT5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT5));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT5);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
    switch (message)
    {
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

    case WM_CREATE:
        GetClientRect(hWnd, &rcClient);
        SetTimer(hWnd, 1, 0, TimerProc);
        CreateBitmap();
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            DrawBitmapDoubleBuffering(hWnd, hdc);
            //DrawBitmap(hdc);

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            DrawRectText(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        DeleteBitmap();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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

void CreateBitmap()
{
    hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/수지.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hBackImage, sizeof(BITMAP), &bitBack);

    hSigongImage = (HBITMAP)LoadImage(NULL, TEXT("images/sigong.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hSigongImage, sizeof(BITMAP), &bitSigong);

    hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/zero_run.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hAniImage, sizeof(BITMAP), &bitAni);
    Run_Frame_Max = bitAni.bmWidth / Sprite_Size_X - 1;
    Run_Frame_Min = 2;
    curFrame = Run_Frame_Min;
}
void DrawBitmap(HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx, by;

    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
    bx = bitBack.bmWidth;
    by = bitBack.bmHeight;

    BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);
    //        시작위치               사진에서 출력할 위치
    StretchBlt(hdc, 700, 0, 200, 200, hMemDC, 0, 0, bx, by, SRCCOPY);

    SelectObject(hMemDC, hOldBitmap);

    DeleteDC(hMemDC);

    //sigong

    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hSigongImage);
    bx = bitSigong.bmWidth;
    by = bitSigong.bmHeight;

    TransparentBlt(hdc, 200, 200, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));
    //BitBlt(hdc, 200, 200, bx, by, hMemDC, 0, 0, SRCCOPY);
    //        시작위치               사진에서 출력할 위치
    //StretchBlt(hdc, 700, 0, 200, 200, hMemDC, 0, 0, bx, by, SRCCOPY);

    SelectObject(hMemDC, hOldBitmap);

    DeleteDC(hMemDC);


    //ani

    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
    bx = bitAni.bmWidth / 16;
    by = bitAni.bmHeight / 2;

    int xStart = curFrame * bx;
    int yStart = 0;
    TransparentBlt(hdc, 200, 400, bx, by, hMemDC, xStart, yStart, bx, by, RGB(255, 0, 255));
    //BitBlt(hdc, 200, 200, bx, by, hMemDC, 0, 0, SRCCOPY);
    //        시작위치               사진에서 출력할 위치
    //StretchBlt(hdc, 700, 0, 200, 200, hMemDC, 0, 0, bx, by, SRCCOPY);

    SelectObject(hMemDC, hOldBitmap);

    DeleteDC(hMemDC);

}
void DeleteBitmap()
{
    DeleteObject(hBackImage);
    DeleteObject(hSigongImage);
    DeleteObject(hAniImage);
}

void UpdateFrame(HWND hWnd)
{
    curFrame++;
    if (curFrame > Run_Frame_Max)
        curFrame = Run_Frame_Min;
}

void DrawRectText(HDC hdc)
{
    static int yPos = 0;
    TCHAR strTest[] = _T("이미지 출력");
    TextOut(hdc, 10, yPos, strTest, _tcslen(strTest));
    yPos += 5;
    if (yPos > rcClient.bottom) yPos = 0;
}

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    //>>
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx, by;
    //<<
    HDC hMemDC2;
    HBITMAP hOldBitmap2;

    hMemDC = CreateCompatibleDC(hdc);
    if (hDoubleBufferImage == NULL)
        hDoubleBufferImage = CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom);

    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

    {
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
        bx = bitBack.bmWidth;
        by = bitBack.bmHeight;

        BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);
        //        시작위치               사진에서 출력할 위치
        StretchBlt(hMemDC, 700, 0, 200, 200, hMemDC2, 0, 0, bx, by, SRCCOPY);

        SelectObject(hMemDC2, hOldBitmap2);

        DeleteDC(hMemDC2);
    }

    {
        //sigong
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hSigongImage);
        bx = bitSigong.bmWidth;
        by = bitSigong.bmHeight;

        TransparentBlt(hMemDC, 200, 200, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));
        //BitBlt(hdc, 200, 200, bx, by, hMemDC, 0, 0, SRCCOPY);
        //        시작위치               사진에서 출력할 위치
        //StretchBlt(hdc, 700, 0, 200, 200, hMemDC, 0, 0, bx, by, SRCCOPY);

        SelectObject(hMemDC2, hOldBitmap2);

        DeleteDC(hMemDC2);
    }

    {
        //ani
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage);
        bx = bitAni.bmWidth / 16;
        by = bitAni.bmHeight / 2;

        int xStart = curFrame * bx;
        int yStart = 0;
        TransparentBlt(hMemDC, 200, 400, bx, by, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255));
        //BitBlt(hdc, 200, 200, bx, by, hMemDC, 0, 0, SRCCOPY);
        //        시작위치               사진에서 출력할 위치
        //StretchBlt(hdc, 700, 0, 200, 200, hMemDC, 0, 0, bx, by, SRCCOPY);

        SelectObject(hMemDC2, hOldBitmap2);

        DeleteDC(hMemDC2);
    }

    BitBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, hMemDC, 0, 0, SRCCOPY);
    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    UpdateFrame(hWnd);
    InvalidateRect(hWnd, NULL, false);
}