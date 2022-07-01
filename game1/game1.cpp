// game1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "framework.h"
#include "game1.h"
#include "turret.h"
#include "object.h"
#include "circle.h"
#include "star2D.h"
#include "DefenseWall.h"
using namespace std;

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

//
TCHAR word[128];
vector<Object*> objectArr;
vector<int> score;
static int timer = 0;
static RECT rcClient;
Turret turret1(720, 720); 
static int playing = 0;
static int pause = 0;
static int defense_num = 15;
static int top_score = 0;
static int cur_score = 0;
static int big = 5;
static int mid = 3;
static int small = 1;
static int restart = 0;
static int launch_delay = 0; // 발사 딜레이

//Turret turret1(rcClient.right / 2.0, rcClient.bottom - 60);

//함수선언
BOOL CALLBACK Dlg_Proc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void DrawRectText(HDC hdc);
// ===============이혜원의 게임========================

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
    LoadStringW(hInstance, IDC_GAME1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAME1);
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

   //HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      //CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      200, 200, 1410, 840, nullptr, nullptr, hInstance, nullptr);
   //HWND hWnd = CreateWindowW(szWindowClass, _T("정찬우의 첫 윈도우"), WS_OVERLAPPEDWINDOW,
       //200, 300, 1000, 400, nullptr, nullptr, hInstance, nullptr);

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
    GetClientRect(hWnd, &rcClient);

    //memset(&conflict, false, sizeof(bool));
    switch (message)
    {
    case WM_CREATE:
        {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ENTER_ID), hWnd, Dlg_Proc);
            
            //디펜스월 생성
            double temp_width = 14;
            for (int i = 0; i < temp_width; i++)
            {
                objectArr.push_back(new DefenseWall((turret1.getWidth()) * i + turret1.getWidth() / 2.0, rcClient.bottom - 5.0, turret1.getWidth(), 10));
            }
            SetTimer(hWnd, 1, 50, NULL);
            SetTimer(hWnd, 2, 1500, NULL);
            SetTimer(hWnd, 3, 50, NULL);
            SetTimer(hWnd, 4, 1000, NULL);

            
        }
        break;
    case WM_TIMER:
        if (wParam == 1 && playing == 1) // 1번 타이머
        {
            for (int i = 0; i < objectArr.size(); i++)
            {
                if (objectArr[i]->getType() == "star")
                {
                    Star2D* star_temp = dynamic_cast<Star2D*>(objectArr[i]);
                    star_temp->setX(objectArr[i]->getX());
                    star_temp->setY(objectArr[i]->getY() + objectArr[i]->getSpeed());

                    if (star_temp->getY() >= rcClient.bottom)
                    {
                        playing = 2;
                        objectArr.clear();
                        break;
                    }
                }

                if (objectArr[i]->getType() == "circle")
                {
                    Circle* circle_temp = dynamic_cast<Circle*>(objectArr[i]);
                    circle_temp->setX(objectArr[i]->getX() + objectArr[i]->getSpeed() * turret1.getLookX());
                    circle_temp->setY(objectArr[i]->getY() + objectArr[i]->getSpeed() * turret1.getLookY());

                    //장애물 조준판정
                    if (objectArr[i]->getType() == "circle")
                    {
                        //Circle* circle_temp = dynamic_cast<Circle*>(objectArr[i]);
                        for (int j = 0; j < objectArr.size(); j++)
                        {
                            if (objectArr[j]->getType() == "star")
                            {
                                //Star2D* star_temp = dynamic_cast<Star2D*>(objectArr[i]);
                                double d = sqrt(pow(objectArr[i]->getX() - objectArr[j]->getX(), 2) + pow(objectArr[i]->getY() - objectArr[j]->getY(), 2));
                                double radius_d = objectArr[i]->getRadius() + objectArr[j]->getRadius();
                                if (d <= radius_d)
                                {
                                    if (objectArr[i]->getRadius() >= 10 && objectArr[i]->getRadius() < 16)
                                        cur_score += 5;
                                    else if(objectArr[i]->getRadius() >= 16 && objectArr[i]->getRadius() < 26)
                                        cur_score += 3;
                                    else
                                        cur_score += 1;

                                    objectArr.erase(objectArr.begin() + i);
                                    if (i < j)
                                    {
                                        objectArr.erase(objectArr.begin() + j - 1);
                                    }
                                    else
                                    {
                                        objectArr.erase(objectArr.begin() + j);
                                    }
                                    break;
                                }
                            }
                        }
                    }

                    
                }
            }
        }
        if (wParam == 2 && playing == 1) // 1번 타이머
        {
            objectArr.push_back(new Star2D(rand() % rcClient.right, 10));
        }
        if (wParam == 3 && playing == 1) // 1번 타이머
        {
            
            for (int i = 0; i < objectArr.size(); i++)
            {
                //디펜스월 장애물 충돌판정
                if (objectArr[i]->getType() == "defense")
                {
                    DefenseWall* defense_temp = dynamic_cast<DefenseWall*>(objectArr[i]);

                    for (int j = 0; j < objectArr.size(); j++)
                    {
                        if (objectArr[j]->getType() != "defense")
                        {
                            double distance = defense_temp->getY() - objectArr[j]->getY();
                            double limit = objectArr[j]->getRadius() + defense_temp->getHeight() / 2.0;
                            if (distance <= limit && defense_temp->getX() - defense_temp->getWidth()/2.0 <= objectArr[j]->getX() && defense_temp->getX() + defense_temp->getWidth() / 2.0 >= objectArr[j]->getX())
                            {
                                objectArr.erase(objectArr.begin() + i);
                                if (i < j)
                                {
                                    objectArr.erase(objectArr.begin() + j - 1);
                                }
                                else
                                {
                                    objectArr.erase(objectArr.begin() + j);
                                }
                                defense_num--;
                                if (defense_num == 0)
                                {
                                    playing = 2;
                                    objectArr.clear();




                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (wParam == 4 && timer == 1)
        {
            launch_delay = 0;
            timer = 0;
        }
        InvalidateRect(hWnd, NULL, TRUE);
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
            GetClientRect(hWnd, &rcClient);
            if (playing == 1) //게임화면
            {
                turret1.Draw(hdc);
                DrawRectText(hdc);
                TCHAR str[50];
                wsprintf(str, TEXT("현재 점수 : %d"), cur_score);
                TextOut(hdc, 150, 0, str, lstrlen(str));
                for (int i = 0; i < objectArr.size(); i++)
                {
                    if (objectArr[i]->getType() == "circle")
                    {
                        Circle* circle_temp = dynamic_cast<Circle*>(objectArr[i]);
                        circle_temp->Draw(hdc);
                    }
                    if (objectArr[i]->getType() == "star")
                    {
                        Star2D* star_temp = dynamic_cast<Star2D*>(objectArr[i]);
                        //star_temp->Draw(hdc);
                        if (objectArr[i]->getConflict() == true)
                        {
                            star_temp->ColorDraw(hdc);
                        }
                        else
                        {
                            star_temp->Draw(hdc);
                        }
                    }
                    if (objectArr[i]->getType() == "defense")
                    {
                        DefenseWall* defense_temp = dynamic_cast<DefenseWall*>(objectArr[i]);
                        defense_temp->Draw(hdc);
                    }
                }
            }
            else if(playing == 2)// 게임끝
            {
                TCHAR str1[50];
                wsprintf(str1, TEXT("Top Score : %d"), top_score);
                TextOut(hdc, 630, 500, str1, lstrlen(str1));

                score.push_back(cur_score);

                for (int i = 0; i < score.size(); i++)
                {
                    if (top_score <= score[i])
                    {
                        top_score = score[i];
                    }
                }

                HPEN MyPen, OldPen;
                MyPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
                OldPen = (HPEN)SelectObject(hdc, MyPen);
                Rectangle(hdc, 550, 280, 850, 320);
                TCHAR str2[50];
                wsprintf(str2, TEXT("현재 점수 : %d"), cur_score);
                TextOut(hdc, 630, 300, str2, lstrlen(str2));
                SelectObject(hdc, OldPen);
                DeleteObject(MyPen);

                
                /*HBRUSH hBrush, oldBrush;
                hBrush = CreateSolidBrush(RGB(0, 255, 0));
                oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                Rectangle(hdc, 200, 500, 500, 800);
                TCHAR str2[50];
                wsprintf(str2, TEXT("현재 점수 : %d"), top_score);
                TextOut(hdc, 350, 650, str2, lstrlen(str2));
                SelectObject(hdc, oldBrush);
                DeleteObject(hBrush);*/

                

            }
            
            //circle1.Draw(hdc);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_LBUTTONDOWN:
        
        /*DeleteBitmap();
        PostQuitMessage(0);
        KillTimer(hWnd, TIMER_IDI);*/
        break;
    case WM_KEYDOWN:
        {
            switch (wParam)
            {
            case VK_LEFT:
                if (turret1.getAngle() - turret1.getSpeed() / 180.0 * 3.14159 >= 180.0 / 180.0 * 3.14159)
                {
                    turret1.setAngle(turret1.getAngle() - turret1.getSpeed() / 180.0 * 3.14159);
                }
                break;
            case VK_RIGHT:
                if (turret1.getAngle() + turret1.getSpeed() / 180.0 * 3.14159 <= 360.0 / 180.0 * 3.14159)
                {
                    turret1.setAngle(turret1.getAngle() + turret1.getSpeed() / 180.0 * 3.14159);
                }
                break;
            case VK_SPACE:// 포 발사
                {
                    if (launch_delay <= 5)
                    {
                        objectArr.push_back(new Circle(turret1.getX() + 100.0 * turret1.getLookX(), turret1.getY() + 100.0 * turret1.getLookY()));
                        launch_delay++;
                    }
                    else
                        timer = 1;
                }
                break;
            case VK_ESCAPE:
                {
                    playing = 2; // 일시정지
                    pause = 1;
                }
                break;
            case VK_RETURN:
            {
                if ((pause == 0 && playing == 2) || restart == 1)
                {
                    cur_score = 0;
                    restart = 0;
                    turret1.setAngle(270.0 / 180.0 * 3.14159);
                    double temp_width = 14;
                    for (int i = 0; i < temp_width; i++)
                    {
                        objectArr.push_back(new DefenseWall((turret1.getWidth()) * i + turret1.getWidth() / 2.0, rcClient.bottom - 5.0, turret1.getWidth(), 10));
                    }
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ENTER_ID), hWnd, Dlg_Proc);
                }
                else
                {
                    pause = 0;
                    playing = 1;
                }
            }
            break;
            default:
                break;
            }
        }

        
        /*DeleteBitmap();
        PostQuitMessage(0);
        KillTimer(hWnd, TIMER_IDI);*/
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        HideCaret(hWnd);
        DestroyCaret();
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

BOOL CALLBACK Dlg_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

    UNREFERENCED_PARAMETER(lParam);
    switch (iMsg)
    {
    case WM_INITDIALOG:
    {
        HWND hBtn = GetDlgItem(hDlg, IDD_ENTER_ID);
        EnableWindow(hBtn, FALSE);

    }
    return TRUE;

    case WM_COMMAND:
        
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_ENTER_ID:
            {
                GetDlgItemText(hDlg, IDC_EDIT_ID, word, 128);
                SetDlgItemText(hDlg, IDC_EDIT_ID, word);
                //대화상자 종료함수
                //EndDialog(hDlg, LOWORD(wParam));
                //return TRUE;

                SetDlgItemText(hDlg, IDC_STATIC_CREATE_ID, _T("아이디가 생성되었습니다."));
            }
            break;
        case IDC_BUTTON_START:
        {
            if (word[0] == '\0')
            {
                SetDlgItemText(hDlg, IDC_STATIC_CREATE_ID, _T("아이디를 입력하세요."));
                break;
            }
            playing = 1;
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
        }
       
    }
    return (INT_PTR)FALSE;
}

void DrawRectText(HDC hdc)
{
    static int yPos = 0;
    TCHAR strTest[] = _T("아이디 : ");
    TextOut(hdc, 10, yPos, strTest, _tcslen(strTest));
    TextOut(hdc, 70, yPos, word, _tcslen(word));
}

//void sort_Top3(vector<int> vec)
//{
//    for (int i = 0; i < vec.size(); i++)
//    {
//        for (int j = 0; j < vec.size(); j++)
//        {
//            if (i == j)
//                break;
//
//            if (vec[i] <= vec[j])
//            {
//                int temp = vec[i];
//                vec[i] = vec[j];
//                vec[j] = temp;
//            }
//
//        }
//    }
//}

//void DrawRectScore(HDC hdc, int defense_num, int cur_score)
//{
//    static int yPos = 0;
//    TCHAR strTest[] = _T("현재 점수 : ");
//    string cur_s = "";
//    int tmp_cur = cur_score;
//    
//
//    TextOut(hdc, 150, yPos, strTest, _tcslen(strTest));
//    TextOut(hdc, 210, yPos, strTest, _tcslen(word));
//}



//void ColorChange(HDC Hdc)
//{
//    HBRUSH hBrush, oldBrush;
//    hBrush = CreateSolidBrush(RGB(0, 255, 0));
//    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
//    Rectangle(hdc, 300, 500, 500, 700);//왼
//    SelectObject(hdc, oldBrush);
//    DeleteObject(hBrush);
//    TextOut(hdc, 400, 600, TEXT("LEFT"), 4);
//}
