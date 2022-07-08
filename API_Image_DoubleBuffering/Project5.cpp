// Project5.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Project5.h"
#include <commctrl.h>
#include <commdlg.h>

#pragma comment (lib, "msimg32.lib")


// >> GDI
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;
ULONG_PTR g_GdiToken;
void Gdi_Init();
void Gdi_Draw(HDC hdc);
void Gdi_End();
//

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

//비트맵 이미지
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
//비트맵이미지

void CreateBitmap();
void DrawBitmap(HDC hdc);
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);

void DeleteBitmap();
void UpdateFrame(HWND hWnd);
void DrawRectText(HDC hdc);
void CALLBACK Keystateproc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
TCHAR sKeyState[128];
void Update();
POINT ptAni = { 200,400 };
VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

static RECT rcClient;
BOOL CALLBACK Dlg_Proc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg_Proc2(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg_Proc3(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

HWND g_DlgHwnd = NULL;




// >>list ctrl
void MakeColumn(HWND hDlg);
void InsertData(HWND hDlg);


// >> split window
HWND ChildHwnd[2];
LRESULT CALLBACK ChildWndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



////GDI
//ULONG_PTR g_GdiToken;
//void Gdi_Init();
//void Gdi_Draw(HDC hdc);
//void Gdi_End();
////


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
    /*while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/
    Gdi_Init();
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
    Gdi_End();
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

    RegisterClassExW(&wcex);


    // split window
    wcex.lpfnWndProc = ChildWndProc1;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _T("Child Window Class 1");
    RegisterClassExW(&wcex);

    wcex.lpfnWndProc = ChildWndProc2;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _T("Child Window Class 2");
    RegisterClassExW(&wcex);


    //


    return NULL;
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
    static int TIMER_IDI = 1;
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
        SetTimer(hWnd, TIMER_IDI, 100, TimerProc);
        CreateBitmap();

        //split window
        ChildHwnd[0] = CreateWindowEx(WS_EX_CLIENTEDGE, _T("Child Window Class 1"), 
            NULL, WS_CHILD | WS_VISIBLE, 0, 0, rcClient.right, rcClient.bottom / 2 - 10, 
            hWnd, NULL, hInst, NULL);

        ChildHwnd[1] = CreateWindowEx(WS_EX_CLIENTEDGE, _T("Child Window Class 2"),
            NULL, WS_CHILD | WS_VISIBLE, 0, rcClient.bottom / 2 + 10, rcClient.right, rcClient.bottom / 2 - 20,
            hWnd, NULL, hInst, NULL);
        //

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
        KillTimer(hWnd, TIMER_IDI);
        break;
    case WM_LBUTTONDOWN:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, Dlg_Proc3);
        /*DeleteBitmap();
        PostQuitMessage(0);
        KillTimer(hWnd, TIMER_IDI);*/
        break;
    case WM_RBUTTONDOWN:
        //DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Dlg_Proc2);
        if (!IsWindow(g_DlgHwnd))
        {
            g_DlgHwnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Dlg_Proc2);
            ShowWindow(g_DlgHwnd,SW_SHOW);
        }
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
    bx = bitBack.bmWidth/2;
    by = bitBack.bmHeight/2;

    //GDI
    //Gdi_Draw(hMemDC);

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
        //        시작위치    어디까지 출력할건지     사진에서 출력할 위치
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
        TransparentBlt(hMemDC, ptAni.x, ptAni.y, bx, by, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255));
        //BitBlt(hdc, 200, 200, bx, by, hMemDC, 0, 0, SRCCOPY);
        //        시작위치               사진에서 출력할 위치
        //StretchBlt(hdc, 700, 0, 200, 200, hMemDC, 0, 0, bx, by, SRCCOPY);

        TransparentBlt(hMemDC, 1000, 400, bx, by, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255));

        xStart = Run_Frame_Max*bx - xStart;
        yStart = by;
        TransparentBlt(hMemDC, ptAni.x, ptAni.y + 50, bx, by, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255));

        SelectObject(hMemDC2, hOldBitmap2);

        DeleteDC(hMemDC2);
    }
    
    Gdi_Draw(hMemDC);
    BitBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, hMemDC, 0, 0, SRCCOPY);
    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    UpdateFrame(hWnd);
    InvalidateRect(hWnd, NULL, false);
}


void Update()
{
    DWORD newTime = GetTickCount();
    static DWORD oldTime = newTime;
    if (newTime - oldTime < 100)
        return;
    oldTime = newTime;

    //Async의 경우 비동기적인 흐름이다. 그러므로 메시지의 큐를 거치지 않는다.
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        ptAni.x += 10;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        ptAni.x -= 10;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        ptAni.y -= 10;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        ptAni.y += 10;
    }
}

void CALLBACK Keystateproc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    if (GetKeyState('A') & 0x8000)
    {
        wsprintf(sKeyState, TEXT("%s"), _T("A-Key pressed"));
    }
    else if (GetKeyState('D') & 0x8000)
    {
        wsprintf(sKeyState, TEXT("%s"), _T("D-Key pressed"));
    }
    else
    {
        wsprintf(sKeyState, _T(""));
    }
}

BOOL CALLBACK Dlg_Proc3(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

    UNREFERENCED_PARAMETER(lParam);
    switch (iMsg)
    {
    
    case WM_INITDIALOG:
        MakeColumn(hDlg);
        return TRUE;

    case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case IDC_BUTTON_INSERT:
                InsertData(hDlg);
                break;
            case IDOK:
            case IDCANCEL:
            {
                //대화상자 종료함수
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
            }
            break;
            }
        break;

    }
    return (INT_PTR)FALSE;
}

BOOL CALLBACK Dlg_Proc2(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hCombo;
    static HWND hList;
    static int selection;
    TCHAR name[20];


    UNREFERENCED_PARAMETER(lParam);
    switch (iMsg)
    {
    case WM_INITDIALOG:
        hCombo = GetDlgItem(hDlg, IDC_COMBO_LIST);
        hList = GetDlgItem(hDlg, IDC_LIST_NAME);

        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_INSERT:
            GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
            if (_tcscmp(name, _T("")))
            {
                SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)name);
                SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)name);
            }
            return 0;

        case IDC_BUTTON_DELETE:
            SendMessage(hCombo, CB_DELETESTRING, selection, 0);
            SendMessage(hList, LB_DELETESTRING, selection, 0);
            return 0;
            break;
        case IDC_COMBO_LIST:
            if (HIWORD(wParam) == CBN_SELCHANGE)
                selection = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
            break;
        case IDC_LIST_NAME:
            if (HIWORD(wParam) == CBN_SELCHANGE)
                selection = SendMessage(hList, LB_GETCURSEL, 0, 0);
            break;
        case IDCLOSE:
        case IDOK:
        case IDCANCEL:
        {
            //대화상자 종료함수
            //EndDialog(hDlg, LOWORD(wParam));
            DestroyWindow(g_DlgHwnd);
            g_DlgHwnd = NULL;
            return TRUE;
        }
        break;
        }
        break;
        
    }
    return (INT_PTR)FALSE;
}

BOOL CALLBACK Dlg_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static int Check[3], Radio;
    TCHAR hobby[][30] = { _T("독서") , _T("음악감상"), _T("인터넷") };
    TCHAR sex[][30] = { _T("여자"), _T("남자") };
    TCHAR output[258];

    UNREFERENCED_PARAMETER(lParam);
    switch (iMsg)
    {
    case WM_INITDIALOG:
        {
            HWND hBtn = GetDlgItem(hDlg, IDC_PAUSE);
            EnableWindow(hBtn, FALSE);

            CheckRadioButton(hDlg, IDC_RADIO_FEMALE, IDC_RADIO_MALE, IDC_RADIO_FEMALE); // 선택지1, 선택지2, 먼저 체크되어있는 선택지


        }
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CHECK_READING:
            Check[0] = 1 - Check[0]; // ==/ Check[0] != Check[0];
            break;
        case IDC_CHECK_MUSIC:
            Check[1] = 1 - Check[1];
            break;
        case IDC_CHECK_INTERNET:
            
            Check[2] = 1 - Check[2];
            break;
        case IDC_RADIO_FEMALE:
            Radio = 0;
            
            break;
        case IDC_RADIO_MALE:
            Radio = 1;
            break;
        case IDC_BUTTON_OUTPUT:
            _stprintf_s(output, _T("선택한 취미는 %s %s %s 입니다.\r\n")
                _T("선택한 성별은 %s 입니다."),
                Check[0] ? hobby[0] : _T(""), Check[1] ? hobby[1] : _T(""), 
                Check[2] ? hobby[2] : _T(""), 
                sex[Radio]
            );
            SetDlgItemText(hDlg, IDC_EDIT_OUTPUT, output);
            break;
        case IDC_BUTTON_COPY:
            {
            TCHAR word[128];
                GetDlgItemText(hDlg, IDC_EDIT_SOURCE, word, 128);
                SetDlgItemText(hDlg, IDC_EDIT_COPY, word);
            }
            break;
        case IDC_BUTTON_CLEAR:
            SetDlgItemText(hDlg, IDC_EDIT_COPY, _T(""));
            SetDlgItemText(hDlg, IDC_EDIT_SOURCE, _T(""));
            break;
        case IDC_START:
            {
                HWND hBtn = GetDlgItem(hDlg, IDC_START);
                EnableWindow(hBtn, FALSE);

                hBtn = GetDlgItem(hDlg, IDC_PAUSE);
                EnableWindow(hBtn, TRUE);

                SetDlgItemText(hDlg, IDC_TEXT, _T("시작~"));
            }
            break;
        case IDC_PAUSE:
            {
                HWND hBtn = GetDlgItem(hDlg, IDC_START);
                EnableWindow(hBtn, TRUE);

                hBtn = GetDlgItem(hDlg, IDC_PAUSE);
                EnableWindow(hBtn, EnableWindow(hBtn, FALSE));

                SetDlgItemText(hDlg, IDC_TEXT, _T("중지~"));
            }
            break;
        case IDC_END:
            {
                HWND hBtn = GetDlgItem(hDlg, IDC_START);
                EnableWindow(hBtn, TRUE);

                hBtn = GetDlgItem(hDlg, IDC_PAUSE);
                EnableWindow(hBtn, FALSE);

                SetDlgItemText(hDlg, IDC_TEXT, _T("끝~"));
                return TRUE;
            }
            break;
        case IDC_BUTTON_PRINT:
            {
                HDC hdc = GetDC(hDlg);
                TextOut(hdc, 10, 10, _T("Hello Button!!"), 14);
                SetDlgItemText(hDlg, IDC_TEXT, _T("hello Button!!"));
                ReleaseDC(hDlg, hdc);
            }
            break;
        case IDOK:
        case IDCANCEL:
            {
                //대화상자 종료함수
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

void Gdi_Init()
{
    GdiplusStartupInput gpsi;
    GdiplusStartup(&g_GdiToken, &gpsi, NULL);
}
void Gdi_Draw(HDC hdc)
{
    Graphics graphics(hdc);

    //>>txt
    SolidBrush brush(Color(255, 0, 0));
    FontFamily fontFamily(L"Times New Roman");
    Font font(&fontFamily, 80, FontStyleRegular, UnitPixel);
    PointF pointF(10.0f, 20.0f);
    graphics.DrawString(L"Hello GDI+!", -1, &font, pointF, &brush);
    //

    Pen pen(Color(128, 0, 255, 255));
    graphics.DrawLine(&pen, 0, 0, 200, 200);

    //image
    Image img((WCHAR*)L"images/sigong.png");
    int w = img.GetWidth();
    int h = img.GetHeight();
    graphics.DrawImage(&img, 405, 265, w, h);
    //

    // ani
    Image img2((WCHAR*)L"images/zero_run.png");
    w = img2.GetWidth()/16;
    h = img2.GetHeight()/2;
    int xStart = curFrame * w;
    int yStart = 0;
    ImageAttributes ImgAttr;
    ImgAttr.SetColorKey(Color(245, 0, 245), Color(255, 0, 255));
    graphics.DrawImage(&img2, Rect(400, 100, w, h), xStart, yStart, w, h, UnitPixel, &ImgAttr);

    //alpha rect
    brush.SetColor(Color(128, 255, 0, 0));
    graphics.FillRectangle(&brush, 400, 100, w, h);

    // rotate image
    Image* pImg = nullptr;
    int xPos = 300;
    int yPos = 200;
    pImg = Image::FromFile((WCHAR*)L"images/sigong.png");
    if (pImg)
    {
        w = pImg->GetWidth();
        h = pImg->GetHeight();
        //w = img.GetWidth();
        //h = img.GetHeight();
        Gdiplus::Matrix mat;
        static int rot = 0;
        

        mat.RotateAt((rot % 360), Gdiplus::PointF((xPos + (float)(w / 2.0)), yPos + (float)(h / 2.0)));
        graphics.SetTransform(&mat);
        graphics.DrawImage(pImg, xPos, yPos, w, h);

        rot += 10;

        mat.Reset();
        graphics.SetTransform(&mat);
    }

    //alpha image
    if (pImg)
    {
        REAL transparency = 0.5f;
        ColorMatrix colorMatrix =
        {
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, transparency, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        };
        ImgAttr.SetColorMatrix(&colorMatrix);
        xPos = 400;
        graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &ImgAttr);


        //gray
        ColorMatrix graycolorMatrix =
        {
            0.0f, 0.3f, 0.3f, 0.3f, 0.3f,
            0.6f, 0.6f, 0.6f, 0.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        };
        ImgAttr.SetColorMatrix(&graycolorMatrix);
        xPos = 400;
        graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &ImgAttr);

        //좌우대칭
        xPos = 700;
        pImg->RotateFlip(RotateNoneFlipX);
        graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &ImgAttr);

        delete pImg;

    }
}
void Gdi_End()
{
    GdiplusShutdown(g_GdiToken);
}


void MakeColumn(HWND hDlg)
{
    LPCTSTR name[2] = { _T("이름"), _T("전화번호") };
    LVCOLUMN lvCol = { 0, };
    HWND hList;
    int i;
    hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);

    RECT rt;
    GetClientRect(hList, &rt);


    lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvCol.fmt = LVCFMT_LEFT;

    for (i = 0; i < 2; i++)
    {
        lvCol.cx = (int)rt.right / 2; // 90
        lvCol.iSubItem = i;
        lvCol.pszText = (LPWSTR)name[i];
        SendMessage(hList, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvCol);
    }
}

void InsertData(HWND hDlg)
{
    LVITEM item;
    HWND hList;
    TCHAR name[20];// = { _T("김철수"), _T("김영희") };
    TCHAR phone[20];// = { _T("010-1111-2222"), _T("010 - 2222 - 3333") };

    int count;

    GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
    SetDlgItemText(hDlg, IDC_EDIT_NAME, _T(""));
    if (_tcscmp(name, _T("")) == 0) return;

    GetDlgItemText(hDlg, IDC_EDIT_PHONE, phone, 20);
    SetDlgItemText(hDlg, IDC_EDIT_PHONE, _T(""));

    hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
    count = ListView_GetItemCount(hList);
    item.mask = LVIF_TEXT;
    item.iItem = count;
    item.iSubItem = 0;
    item.pszText = (LPWSTR)name;
    ListView_InsertItem(hList, &item);
    ListView_SetItemText(hList, count, 1, phone);

    /*hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
    for (int i = 0; i < 2; i++)
    {
        item.mask = LVIF_TEXT;
        item.iItem = i;
        item.iSubItem = 0;
        item.pszText = (LPWSTR)name[i];
        ListView_InsertItem(hList, &item);
        ListView_SetItemText(hList, i, 1, (LPWSTR)phone[i]);
    }*/
}

#define IDC_CHILD1_BTN 100

LRESULT CALLBACK ChildWndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawBitmapDoubleBuffering(hWnd, hdc);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        break;

    }
    return DefWindowProc(hWnd, message, wParam, lParam); // 처리 안된 메세지 되돌려줌-> 이해안됨
}

LRESULT CALLBACK ChildWndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hBtn;
    static POINT ptMOUSE;
    static bool bToggle = false;

    switch (message)
    {
    case WM_CREATE:
        hBtn = CreateWindow(_T("button"), _T("OK"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 100, 100, 30, hWnd,
            (HMENU)IDC_CHILD1_BTN, hInst, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            case IDC_CHILD1_BTN:
            {
                bToggle = !bToggle;
                break;
            }
        }
        break;
    case WM_MOUSEMOVE:
        ptMOUSE.x = LOWORD(lParam);
        ptMOUSE.y = HIWORD(lParam);
        //InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_PAINT:
    {
        GetCursorPos(&ptMOUSE);

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        TCHAR str[128];
        wsprintf(str, TEXT("World Position : (%04d, %04d)"), ptMOUSE.x, ptMOUSE.y);
        TextOut(hdc, 10, 30, str, lstrlen(str));

        ScreenToClient(hWnd, &ptMOUSE);
        wsprintf(str, TEXT("Local Position : (%04d, %04d)"), ptMOUSE.x, ptMOUSE.y);
        TextOut(hdc, 10, 50, str, lstrlen(str));

        if (bToggle)
            TextOut(hdc, 10, 80, _T("Button Clicked"), lstrlen(_T("Button Clicked")));

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        break;

    }

    return DefWindowProc(hWnd, message, wParam, lParam); // 처리 안된 메세지 되돌려줌-> 이해안됨
}