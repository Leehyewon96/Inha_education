// game1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale.h>
#include <tchar.h>
#include <algorithm>
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
vector<DefenseWall> defenseWall;
vector<int> defense_conflict_num;
static int timer = 0;
static RECT rcClient;
Turret turret1(720, 720); 
static int playing = 0;
static int pause = 0;
static int defense_num = 14;
static int top_score = 0;
static int cur_score = 0;
static int big = 5;
static int mid = 3;
static int small = 1;
static int restart = -1;
static int launch_delay = 0; // 발사 딜레이

//Turret turret1(rcClient.right / 2.0, rcClient.bottom - 60);

//함수선언
BOOL CALLBACK Dlg_Proc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void DrawRectText(HDC hdc);
void Input_ID(TCHAR word[]);
bool compare(const pair<string, string>& a, const pair<string, string>& b);

vector <pair<string, string>> ID_SCORE_PAIR;

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
            SetTimer(hWnd, 5, 50, NULL);
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
                        DialogBox(hInst, MAKEINTRESOURCE(IDD_END), hWnd, Dlg_Proc);
                        break;
                    }
                    ////디펜스 없는곳으로 떨어지거나 디펜스가 다 사라지면 게임오버
                    //if (defense_num == 0 || star_temp->getY() == rcClient.bottom)
                    //{
                    //    playing = 2;
                    //    objectArr.clear();
                    //}
                }

                if (objectArr[i]->getType() == "circle") // 총알 발사
                {
                    Circle* circle_temp = dynamic_cast<Circle*>(objectArr[i]);
                    circle_temp->setX(objectArr[i]->getX() + objectArr[i]->getSpeed() * circle_temp->getLookX());
                    circle_temp->setY(objectArr[i]->getY() + objectArr[i]->getSpeed() * circle_temp->getLookY());

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
        if (wParam == 2 && playing == 1) // 별생성 타이머
        {
            objectArr.push_back(new Star2D(rand() % rcClient.right, 10));
        }
        if (wParam == 3 && playing == 1) // 디펜스 충돌판정 타이머
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
                            if (distance <= limit && defense_temp->getX() - defense_temp->getWidth() / 2.0 <= objectArr[j]->getX() && defense_temp->getX() + defense_temp->getWidth() / 2.0 >= objectArr[j]->getX())
                            {
                                //디펜스당 충돌 횟수 저장
                                defense_temp->setConflict(defense_temp->getConflict() + 1);

                                //1번 충돌하면 블루, 2번 그린, 3번 충돌시 레드
                                if (defense_temp->getConflict() == 3)
                                {
                                    objectArr.erase(objectArr.begin() + j);
                                    defense_temp->setColor("red");
                                }
                                else if (defense_temp->getConflict() == 2)
                                {
                                    objectArr.erase(objectArr.begin() + j);
                                    defense_temp->setColor("green");
                                }
                                else if (defense_temp->getConflict() == 1)
                                {
                                    objectArr.erase(objectArr.begin() + j);
                                    defense_temp->setColor("blue");
                                }
                                else if (defense_temp->getConflict() == 4)//4번 충돌시 해당 디펜스 삭제
                                {
                                    defense_num--;
                                    objectArr.erase(objectArr.begin() + i); //디펜스 삭제
                                    if (j < i) //해당 목표물 삭제
                                    {
                                        objectArr.erase(objectArr.begin() + j - 1);
                                    }
                                    else
                                    {
                                        objectArr.erase(objectArr.begin() + j);
                                    }
                                    break;
                                }

                                //디펜스 없는곳으로 떨어지거나 디펜스가 다 사라지면 게임오버
                                if (defense_num == 0 || objectArr[j]->getY() == rcClient.bottom)
                                {
                                    playing = 2;
                                    objectArr.clear();
                                    break;
                                }
                                
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
        if (wParam == 5 && restart == 0)
        {
            restart = -1;
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
                        star_temp->Draw(hdc);
                        /*if (objectArr[i]->getConflict() == true)
                        {
                            star_temp->ColorDraw(hdc);
                        }
                        else
                        {
                            star_temp->Draw(hdc);
                        }*/
                    }
                    if (objectArr[i]->getType() == "defense")
                    {
                        DefenseWall* defense_temp = dynamic_cast<DefenseWall*>(objectArr[i]);
                        if (defense_temp->getColor() == "red")
                        {
                            defense_temp->ColorDraw(hdc, 255, 0, 0);
                        }
                        else if (defense_temp->getColor() == "green")
                        {
                            defense_temp->ColorDraw(hdc, 0, 255, 0);
                        }
                        else if (defense_temp->getColor() == "blue")
                        {
                            defense_temp->ColorDraw(hdc, 0, 0, 255);
                        }
                        else
                        {
                            defense_temp->Draw(hdc);
                        }
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

                        objectArr.push_back(new Circle(turret1.getX() + 100.0 * turret1.getLookX(), turret1.getY() + 100.0 * turret1.getLookY(), turret1.getLookX(), turret1.getLookY()));
                        
                        launch_delay++;
                    }
                    else
                        timer = 1;
                }
                break;
            case VK_ESCAPE:
                {
                    playing = 2; // 일시정지
                    //pause = 1;
                    objectArr.clear();
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_END), hWnd, Dlg_Proc);
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
        if (playing == 0)
        {
            HWND hBtn = GetDlgItem(hDlg, IDD_ENTER_ID);
            EnableWindow(hBtn, FALSE);
        }
        else if (playing == 2)
        {
            HWND hBtn = GetDlgItem(hDlg, IDD_END);
            EnableWindow(hBtn, FALSE);
            Input_ID(word);



            wstring sc1 = to_wstring(cur_score);
            sc1 += _T("점");
            SetDlgItemText(hDlg, IDC_STATIC_CUR, sc1.c_str());

            //TCHAR str1[50];

            int size = ID_SCORE_PAIR.size() >= 3 ? 3 : ID_SCORE_PAIR.size();
            for (int i = 0; i < size; ++i)
            {
                wstring temp;
                temp.assign(ID_SCORE_PAIR[i].first.begin(), ID_SCORE_PAIR[i].first.end());
                SetDlgItemText(hDlg, IDC_STATIC_TOP_ID1 + i, temp.c_str());
                SetDlgItemText(hDlg, IDC_STATIC_TOP1+i, to_wstring(stoi(ID_SCORE_PAIR[i].second)).c_str());
            }

            playing = 0;
            ID_SCORE_PAIR.clear();
            /*

            wstring sc2 = to_wstring(top_score);
            sc2 += _T("점");
            SetDlgItemText(hDlg, IDC_STATIC_TOP1, sc2.c_str());
            */
        }

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
            if (playing == 0 || playing == 1)
            {
                if (word[0] == '\0')
                {
                    SetDlgItemText(hDlg, IDC_STATIC_CREATE_ID, _T("아이디를 입력하세요."));
                }
            }
            turret1.setAngle(270.0 / 180.0 * 3.14159);
            cur_score = 0;
            playing = 1;
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        case IDC_BUTTON_RESTART:
        {
            //playing = 1;
            restart = 0;
            EndDialog(hDlg, LOWORD(wParam));
            //word = _T("");
            return (INT_PTR)TRUE;
        }
        case IDC_BUTTON_END:
        {
            EndDialog(hDlg, LOWORD(wParam));
            PostQuitMessage(0);
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
/*
BOOL CALLBACK DEF_END_Proc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (iMsg)
    {
    case WM_INITDIALOG:
    {
        string Filename = "Rank.txt"; // 파일 이름
        fstream Fio; // 파일 열기 위한 변수

        wstring ID_ToConvert = ID; // TCHAR인 ID를 wstring으로 변환
        string ID_string(ID_ToConvert.begin(), ID_ToConvert.end()); // wstring에서 string으로 변환

        string SCORE_string = to_string(SCORE); // int형인 SCORE를 string 화

        Fio.open(Filename, ios_base::in | ios_base::binary);
        if (!Fio.is_open()) // 여는 데에 실패했을 때 파일 만들어주고 다시 열기
        {
            ofstream makeFile(Filename, ios_base::binary);
            makeFile << ID_string << '\n' << SCORE_string; // 현재 아이디 입력, 개행 후, 점수 입력.
            makeFile.close();
            Fio.close();
            Fio.open(Filename, ios_base::in | ios_base::binary); // 새로 열기
        }

        vector <pair<string, string>> RankID_Score; // 넣어줄 ID & SCORE 벡터

        int i = 0, j = 0;
        bool next_ID = false;

        string temp_ID_SCORE[2]; // 내부 파일의 아이디와 스코어를 담아둘 임시 벡터

        Fio.seekg(0); // 파일 커서 위치 처음으로.
        while (!Fio.eof()) // 내부 파일 열어서 한 글자 씩 저장하기
        {
            char temp_c = Fio.get();
            if (temp_c == '\r')
                continue;
            else if (temp_c == '\n' || temp_c == -1) // 개행 혹은 파일 끝에 다다르면
            {
                if (next_ID) // 점수까지 입력 다 받았으면 RankID_Score에 저장하고 임시 벡터 초기화
                {
                    ++i;
                    RankID_Score.push_back(make_pair(temp_ID_SCORE[0], temp_ID_SCORE[1]));
                    temp_ID_SCORE[0] = "";
                    temp_ID_SCORE[1] = "";
                    next_ID = false;
                }
                else
                    next_ID = true;
                continue;
            }
            if (!next_ID)
                temp_ID_SCORE[0] += temp_c; // 아이디 저장
            else
                temp_ID_SCORE[1] += temp_c; // 점수 저장
        }

        Fio.close(); // 파일은 다 읽었으니 닫아주기


        bool isChanged = false;
        for (int i = 0; i < RankID_Score.size(); ++i)
        {
            int score_temp = stoi(RankID_Score[i].second);
            if (RankID_Score.size() == 3) // 이미 3위까지 입력이 되어있었으면 기존 점수와 비교 후 교환
            {
                if (score_temp < SCORE)
                {
                    RankID_Score[i].first = ID_string;
                    RankID_Score[i].second = SCORE_string;
                    isChanged = true;
                    break;
                }
                else
                    continue;
            }
            else // 3위까지 다 입력이 되어 있는게 아니었다면
            {
                if (score_temp < SCORE) // 현재 플레이의 점수가 더 높다면
                {
                    RankID_Score.insert(RankID_Score.begin() + i, make_pair(ID_string, SCORE_string));
                    // 해당 인덱스에 삽입.
                    isChanged = true;
                    break;
                }
                else if (i == RankID_Score.size() - 1) // 마지막 인덱스면 중간 삽입이 아니라 push_back
                {
                    if (RankID_Score[i].first != ID_string || RankID_Score[i].second != SCORE_string)
                    {
                        RankID_Score.push_back(make_pair(ID_string, SCORE_string));
                        isChanged = true;
                    }
                    break;
                }
            }
        }

        if (isChanged) // 기존과 조금이라도 변한게 있으면
        {
            Fio.open(Filename, ios_base::out | ios_base::binary | ios_base::trunc);
            // 파일을 열되, 기존 파일 내용을 지우면서 열기
            for (int i = 0; i < RankID_Score.size(); ++i)
            {
                Fio << RankID_Score[i].first << '\n';
                if (i == RankID_Score.size() - 1) // 마지막
                    Fio << RankID_Score[i].second;
                else
                    Fio << RankID_Score[i].second << '\n';
            }
        }
        Fio.close();

        HWND hBtn = GetDlgItem(hWnd, IDC_PAUSE);
        SetDlgItemText(hWnd, IDC_EDIT_ID_INPUT_ME, ID); // 현재 내 아이디 입력

        TCHAR score[256];
        wsprintf(score, _T("%d"), SCORE);
        SetDlgItemText(hWnd, IDC_EDIT_SCORE_INPUT_ME, score); // 현재 내 점수 입력

        for (int i = 0; i < RankID_Score.size(); ++i) // 입력받은 아이디와 점수를 표기
        {
            TCHAR temp[256];
            RankID_Score[i].first += '\0'; // 기존에 종료문자가 없었으므로 종료문자를 끝에 넣어주기
            RankID_Score[i].second += '\0';
            copy(RankID_Score[i].first.begin(), RankID_Score[i].first.end(), temp);
            SetDlgItemText(hWnd, IDC_EDIT_ID_INPUT_RANK1 + i, temp);
            copy(RankID_Score[i].second.begin(), RankID_Score[i].second.end(), temp);
            SetDlgItemText(hWnd, IDC_EDIT_SCORE_INPUT_1 + i, temp);
        }


        EnableWindow(hBtn, FALSE);

        return TRUE;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CLOSE:
        case IDCANCEL:
        {
            EndDialog(hWnd, LOWORD(wParam));
            isExit = true;
            return TRUE;
        }
        break;
        }
    }
    return FALSE;
}
*/
void Input_ID(TCHAR word[])
{
    string OutputFile;

    wstring ID_ToConvert = word; // TCHAR인 word를 wstring으로 변환
    string ID_string(ID_ToConvert.begin(), ID_ToConvert.end()); // wstring에서 string으로 변환

    OutputFile = "id.txt";
    fstream ofile(OutputFile.c_str(), ios::binary | ios::app);
    ofile << ID_string;
    ofile << '\n' << cur_score << '\n';

    ofile.close();

    fstream ifile(OutputFile.c_str(), ios::in, ios::binary);
    //ifile.open(OutputFile.c_str(), ios::in | ios::binary);
    ifile.seekg(0);

    string ID_TEMP = "", SCORE_TEMP ="";
    bool Switch = false;
    while (!ifile.eof())
    {
        char ch = ifile.get();
        if (ch == '\n' || ch == -1)
        {
            if(Switch == true)
            {
                ID_TEMP += '\0';
                SCORE_TEMP += '\0';
                ID_SCORE_PAIR.push_back(make_pair(ID_TEMP, SCORE_TEMP));
                ID_TEMP = "";
                SCORE_TEMP = "";
            }
            Switch = !Switch;
            continue;
        }
        if (!Switch)
            ID_TEMP += ch;
        else
            SCORE_TEMP += ch;
    }
    ifile.close();

    //ID_SCORE_PAIR.push_back(make_pair(ID_string, to_string(cur_score)));

    sort(ID_SCORE_PAIR.begin(), ID_SCORE_PAIR.end(), compare);
}

bool compare(const pair<string, string>& a, const pair<string, string>& b)
{
    int a_score = stoi(a.second);
    int b_score = stoi(b.second);
    return a_score > b_score;
}







//int Input_Score(int score)
//{
//    string OutputFile;
//
//    OutputFile = "id.txt";
//
//    ofstream ofile(OutputFile.c_str(), ios::binary);
//
//    //마지막 글자까지 읽어서 커서 옮기기 필요
//    ofile << score;
//
//    ofile.close();
//}

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










//BOOL CALLBACK Dlg_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
//{
//
//    UNREFERENCED_PARAMETER(lParam);
//    switch (iMsg)
//    {
//    case WM_INITDIALOG:
//    {
//        HWND hBtn = GetDlgItem(hDlg, IDD_ENTER_ID);
//        EnableWindow(hBtn, FALSE);
//
//    }
//    return TRUE;
//
//    case WM_COMMAND:
//
//        switch (LOWORD(wParam))
//        {
//        case IDC_BUTTON_ENTER_ID:
//        {
//            GetDlgItemText(hDlg, IDC_EDIT_ID, word, 128);
//            SetDlgItemText(hDlg, IDC_EDIT_ID, word);
//            //대화상자 종료함수
//            //EndDialog(hDlg, LOWORD(wParam));
//            //return TRUE;
//            SetDlgItemText(hDlg, IDC_STATIC_CREATE_ID, _T("아이디가 생성되었습니다."));
//        }
//        break;
//        case IDC_BUTTON_START:
//        {
//            if (word[0] == '\0')
//            {
//                SetDlgItemText(hDlg, IDC_STATIC_CREATE_ID, _T("아이디를 입력하세요."));
//                break;
//            }
//            playing = 1;
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//        }
//
//    }
//    return (INT_PTR)FALSE;
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


//if (wParam == 3 && playing == 1) // 디펜스 충돌판정 타이머
//{
//    for (int i = 0; i < objectArr.size(); i++)
//    {
//        //디펜스월 장애물 충돌판정
//        if (objectArr[i]->getType() == "defense")
//        {
//            DefenseWall* defense_temp = dynamic_cast<DefenseWall*>(objectArr[i]);
//
//            for (int j = 0; j < objectArr.size(); j++)
//            {
//                if (objectArr[j]->getType() != "defense")
//                {
//                    double distance = defense_temp->getY() - objectArr[j]->getY();
//                    double limit = objectArr[j]->getRadius() + defense_temp->getHeight() / 2.0;
//                    if (distance <= limit && defense_temp->getX() - defense_temp->getWidth() / 2.0 <= objectArr[j]->getX() && defense_temp->getX() + defense_temp->getWidth() / 2.0 >= objectArr[j]->getX())
//                    {
//                        objectArr.erase(objectArr.begin() + i);
//                        if (i < j)
//                        {
//                            objectArr.erase(objectArr.begin() + j - 1);
//                        }
//                        else
//                        {
//                            objectArr.erase(objectArr.begin() + j);
//                        }
//                        defense_num--;
//                        if (defense_num == 0)
//                        {
//                            playing = 2;
//                            objectArr.clear();
//                        }
//                        break;
//                    }
//                }
//            }
//        }
//    }
//}