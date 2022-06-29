// API_project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "framework.h"
#include "API_project.h"
#include "object.h"
#include "resource.h"
#include "rectangle2D.h"
#include "star2D.h"
#include "circle.h"

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
void DrawLine_Test(HDC hdc);
void DrawGrid(HDC hdc, POINT LeftTop, POINT RightBottom, LONG nWidth, LONG nHeight, LONG num);
void DrawCircle_Test(HDC hdc);
void Rectangle_Test(HDC hdc);
void DrawCircle(HDC hdc, POINT center, int radius);
void DrawPolygon_Test(HDC hdc);
void SunFlower(HDC hdc, POINT center, double radius, double circle_num);
void Star(HDC hdc, POINT center, double distance, double n);
void direction(HDC hdc);

void DrawMove_Star2D(HDC hdc, Star2D& star);
void DrawMove_Ellipse(HDC hdc, Circle& curPos);
void DrawMove_Rectangle(HDC hdc, Rectangle2D& curPos);
void Reflect_Conflict();
void Crash_Conflict();
void Reflect_Conflict_Circle(int mode, HWND hWnd, RECT windowRect);
void Reflect_Conflict_Star(int mode, HWND hWnd, RECT windowRect);

vector<Circle> circleArr;
vector<Rectangle2D> recArr;
vector<Star2D> starArr;

vector<Object*> objectArr;


static TCHAR str[256];
static int count = 0, yPos;
static SIZE size;
void TextOut_TEST(HDC hdc);
static POINT mouse;
//HWND hWnd;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    srand(clock());

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_APIPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APIPROJECT));

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
ATOM MyRegisterClass(HINSTANCE hInstance) // 윈도우 설정 알려줌
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QUESTION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_IBEAM);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);//윈도우색 
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_APIPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_QUESTION));

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

   HWND hWnd = CreateWindowW(szWindowClass, _T("이혜원의 첫 윈도우"), WS_OVERLAPPEDWINDOW,
      200, 300, 1280, 1000, nullptr, nullptr, hInstance, nullptr);
     //X  //Y   //가로 //세로
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, SW_SHOW);
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
    static HDC hdc = GetDC(hWnd);
    static RECT windowRect;
    static bool keydown = false;
    static bool key_Right = false;
    static bool key_Left = false;
    static bool key_Up = false;
    static bool key_Down = false;
    static bool LeftMouseDown = false;
    static bool includeMouse = false;
    static bool makeNew = false;
    static int move_direction = 0;
    static int speed = 15;
    static int size = 110;
    static double LbuttonX, LbuttonY;
    static bool bDrag = false;
    static int figure = 0;
    static int mode = 1;
    
    static POINT curPos;
    static POINT startPos;
    //static RECT windowRect;
    static Circle circle1;
    switch (message)
    {
    case WM_CREATE: // 생성자
        //count = 0;
        yPos = 120;
        SetTimer(hWnd, 1, 30, NULL);
        SetTimer(hWnd, 2, 30, NULL);
        SetTimer(hWnd, 3, 30, NULL);
        SetTimer(hWnd, 4, 30, NULL);
        SetTimer(hWnd, 5, 30, NULL);
        //SetTimer(hWnd, 6, 30, NULL);
        GetClientRect(hWnd, &windowRect);
        CreateCaret(hWnd, NULL, 3, 20);
        ShowCaret(hWnd);
        startPos.x = 0;
        startPos.y = 0;
        break;
    case WM_TIMER:
        GetClientRect(hWnd, &windowRect);

        if (wParam == 1) // 자유이동 및 벽충돌체크 타이머
        {
            //object배열로 체크
            for (int i = 0; i < objectArr.size(); i++)
            {
                if (objectArr[i]->getType() == "circle")
                {
                    Circle* circle_temp = dynamic_cast<Circle*>(objectArr[i]);
                    circle_temp->setX(circle_temp->getX() + circle_temp->getMoveSpeed() * cos(circle_temp->getAngle()));
                    circle_temp->setY(circle_temp->getY() + circle_temp->getMoveSpeed() * sin(circle_temp->getAngle()));

                    //벽충돌
                    if (circle_temp->getX() - circle_temp->getRadius() <= windowRect.left) // 왼오 충돌
                    {
                        if (circle_temp->getAngle() < 3.14159 && circle_temp->getAngle() >= 0) // 위방향 이동이면
                        {
                            circle_temp->setAngle(3.14159 - circle_temp->getAngle());
                        }
                        else // 아래방향이동이면
                        {
                            circle_temp->setAngle(3.14159 * 3 - circle_temp->getAngle());
                        }
                        circle_temp->setX(circle_temp->getX() + circle_temp->getRadius() - circle_temp->getX());
                    }
                    if (circle_temp->getX() + circle_temp->getRadius() >= windowRect.right)
                    {

                        if (circle_temp->getAngle() < 3.14159 && circle_temp->getAngle() >= 0) // 위방향 이동이면
                        {
                            circle_temp->setAngle(3.14159 - circle_temp->getAngle());
                        }
                        else // 아래방향이동이면
                        {
                            circle_temp->setAngle(3.14159 * 3 - circle_temp->getAngle());
                        }
                        circle_temp->setX(circle_temp->getX() - (circle_temp->getRadius() - (windowRect.right - circle_temp->getX())));
                    }
                    if (circle_temp->getY() - circle_temp->getRadius() <= windowRect.top) // 위아래 충돌
                    {

                        circle_temp->setAngle(2 * 3.14159 - circle_temp->getAngle());
                        circle_temp->setY(circle_temp->getY() + circle_temp->getRadius() - circle_temp->getY());
                    }
                    if (circle_temp->getY() + circle_temp->getRadius() >= windowRect.bottom)
                    {

                        circle_temp->setAngle(2 * 3.14159 - circle_temp->getAngle());
                        circle_temp->setY(circle_temp->getY() - (circle_temp->getRadius() - (windowRect.bottom - circle_temp->getY())));
                    }
                }
                else if (objectArr[i]->getType() == "star")
                {
                    Star2D* star_temp = dynamic_cast<Star2D*>(objectArr[i]);
                    star_temp->setX(star_temp->getX() + star_temp->getMoveSpeed() * cos(star_temp->getAngle()));
                    star_temp->setY(star_temp->getY() + star_temp->getMoveSpeed() * sin(star_temp->getAngle()));
                    star_temp->setRotVelAngle(star_temp->getRotVelAngle() + star_temp->getRotAngle() / 10.0);

                    //벽충돌
                    if (star_temp->getX() - star_temp->getDistance() <= windowRect.left) // 왼쪽 충돌
                    {
                        if (star_temp->getAngle() < 3.14159 && star_temp->getAngle() >= 0) // 위방향 이동이면
                        {
                            star_temp->setAngle(3.14159 - star_temp->getAngle());
                        }
                        else // 아래방향이동이면
                        {
                            star_temp->setAngle(3.14159 * 3 - star_temp->getAngle());
                        }
                        star_temp->setX(star_temp->getX() + star_temp->getDistance() - star_temp->getX());
                        //
                        //회전방향바꾸기
                        star_temp->setRotAngle(star_temp->getRotAngle() * (-1));
                    }
                    if (star_temp->getX() + star_temp->getDistance() >= windowRect.right) // 오른쪽 충돌
                    {
                        if (star_temp->getAngle() < 3.14159 && star_temp->getAngle() >= 0) // 위방향 이동이면
                        {
                            star_temp->setAngle(3.14159 - star_temp->getAngle());
                        }
                        else // 아래방향이동이면
                        {
                            star_temp->setAngle(3.14159 * 3 - star_temp->getAngle());
                        }
                        star_temp->setX(star_temp->getX() - (star_temp->getDistance() - (windowRect.right - star_temp->getX())));
                        
                        //회전방향바꾸기
                        star_temp->setRotAngle(star_temp->getRotAngle() * (-1));
                    }
                    if (star_temp->getY() - star_temp->getDistance() <= windowRect.top) // 위아래 충돌
                    {

                        star_temp->setAngle(2 * 3.14159 - star_temp->getAngle());
                        star_temp->setY(star_temp->getY() + star_temp->getDistance() - star_temp->getY());

                        //회전방향바꾸기
                        star_temp->setRotAngle(star_temp->getRotAngle() * (-1));
                    }
                    if (star_temp->getY() + star_temp->getDistance() >= windowRect.bottom)
                    {

                        star_temp->setAngle(2 * 3.14159 - star_temp->getAngle());
                        star_temp->setY(star_temp->getY() - (star_temp->getDistance() - (windowRect.bottom - star_temp->getY())));

                        //회전방향바꾸기
                        star_temp->setRotAngle(star_temp->getRotAngle() * (-1));
                    }
                }
                else if (objectArr[i]->getType() == "rectangle")
                {
                    Rectangle2D* rec_temp = dynamic_cast<Rectangle2D*>(objectArr[i]);
                    rec_temp->setX(rec_temp->getX() + rec_temp->getMoveSpeed() * cos(rec_temp->getAngle()));
                    rec_temp->setY(rec_temp->getY() + rec_temp->getMoveSpeed() * sin(rec_temp->getAngle()));
                    rec_temp->setRotAngle(rec_temp->getRotAngle() + rec_temp->getRotVelAngle());

                    double dia = sqrt(pow(rec_temp->getHeight() / 2, 2) + pow(rec_temp->getWidth() / 2, 2));

                    //벽충돌
                    if (rec_temp->getX() - dia <= windowRect.left) // 왼쪽 충돌
                    {
                        if (rec_temp->getAngle() < 3.14159 && rec_temp->getAngle() >= 0) // 위방향 이동이면
                        {
                            rec_temp->setAngle(3.14159 - rec_temp->getAngle());
                        }
                        else // 아래방향이동이면
                        {
                            rec_temp->setAngle(3.14159 * 3 - rec_temp->getAngle());
                        }
                        rec_temp->setX(rec_temp->getX() + dia - rec_temp->getX());

                        //회전방향바꾸기
                        rec_temp->setRotVelAngle(rec_temp->getRotVelAngle() * (-1));
                    }
                    if (rec_temp->getX() + dia >= windowRect.right) // 오른쪽 충돌
                    {
                        if (rec_temp->getAngle() < 3.14159 && rec_temp->getAngle() >= 0) // 위방향 이동이면
                        {
                            rec_temp->setAngle(3.14159 - rec_temp->getAngle());
                        }
                        else // 아래방향이동이면
                        {
                            rec_temp->setAngle(3.14159 * 3 - rec_temp->getAngle());
                        }
                        rec_temp->setX(rec_temp->getX() - (dia - (windowRect.right - rec_temp->getX())));

                        //회전방향바꾸기
                        rec_temp->setRotVelAngle(rec_temp->getRotVelAngle() * (-1));
                    }
                    if (rec_temp->getY() - dia <= windowRect.top) // 위아래 충돌
                    {

                        rec_temp->setAngle(2 * 3.14159 - rec_temp->getAngle());
                        rec_temp->setY(rec_temp->getY() + dia - rec_temp->getY());

                        //회전방향바꾸기
                        rec_temp->setRotVelAngle(rec_temp->getRotVelAngle() * (-1));
                    }
                    if (rec_temp->getY() + dia >= windowRect.bottom)
                    {

                        rec_temp->setAngle(2 * 3.14159 - rec_temp->getAngle());
                        rec_temp->setY(rec_temp->getY() - (dia - (windowRect.bottom - rec_temp->getY())));

                        //회전방향바꾸기
                        rec_temp->setRotVelAngle(rec_temp->getRotVelAngle() * (-1));
                    }
                }
            }
        }
        if (wParam == 2) // 충돌체크 타이머
        {
            Reflect_Conflict_Circle(mode, hWnd, windowRect);
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
            break;
        }
    case WM_PAINT: // 글, 그림
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            //클래스 그리기
            for (int i = 0; i < objectArr.size(); i++)
            {
                if (objectArr[i]->getType() == "circle")
                {
                    Circle* circle_temp = dynamic_cast<Circle*>(objectArr[i]);
                    circle_temp->Draw(hdc);
                }
                else if (objectArr[i]->getType() == "star")
                {
                    Star2D* star_temp = dynamic_cast<Star2D*>(objectArr[i]);
                    star_temp->Draw(hdc);
                }
                else if (objectArr[i]->getType() == "rectangle")
                {
                    Rectangle2D* rec_temp = dynamic_cast<Rectangle2D*>(objectArr[i]);
                    rec_temp->Draw(hdc);
                }
            }
            EndPaint(hWnd, &ps);
            break;
        }
    case WM_DESTROY:// 소멸자
        HideCaret(hWnd);
        DestroyCaret();
        PostQuitMessage(0);
        KillTimer(hWnd, 1); // 타이머 죽이기
        KillTimer(hWnd, 2); // 타이머 죽이기
        KillTimer(hWnd, 3); // 타이머 죽이기
        KillTimer(hWnd, 4); // 타이머 죽이기
        break;
    case WM_LBUTTONDOWN:
    {
        //bDrag = true;
        figure = rand() % 3;
        if (figure == 0)
        {            
            //부모배열에 넣기
            objectArr.push_back(new Circle(LOWORD(lParam), HIWORD(lParam)));
            //objectArr.back()->setType("circle");
        }
        else if (figure == 1)
        {

            //부모배열에 넣기
            objectArr.push_back(new Rectangle2D(LOWORD(lParam), HIWORD(lParam)));
        }
        else if (figure == 2)
        {
            //부모배열에 넣기
            objectArr.push_back(new Star2D(LOWORD(lParam), HIWORD(lParam)));
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_KEYDOWN:
    {
        switch(wParam)
        {
        case VK_F1:
            mode = 1;
            break;
        case VK_F2:
            mode = 2;
            break;
        case VK_F3:
            mode = 3;
            break;
        default:
            break;
        }
        break;
    }
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

void DrawLine_Test(HDC hdc)
{
    MoveToEx(hdc, 250, 250, NULL);
    LineTo(hdc, 500, 500);
}

void DrawGrid(HDC hdc, POINT LeftTop, POINT RightBottom, LONG nWidth, LONG nHeight, LONG num)
{
    MoveToEx(hdc, LeftTop.x, LeftTop.y, NULL);
    LineTo(hdc, RightBottom.x , LeftTop.y);
    LineTo(hdc, RightBottom.x, RightBottom.y);
    LineTo(hdc, LeftTop.x, RightBottom.y); 
    LineTo(hdc, LeftTop.x, LeftTop.y);

    MoveToEx(hdc, LeftTop.x, LeftTop.y + nHeight, NULL);

    for (int i = 1; i <= (RightBottom.y - LeftTop.y) / nHeight; i++)
    {
        LineTo(hdc, RightBottom.x, LeftTop.y + nHeight*i);
        MoveToEx(hdc, LeftTop.x, LeftTop.y + nHeight*(i+1), NULL);
    }

    MoveToEx(hdc, LeftTop.x + nWidth, LeftTop.y, NULL);
    for (int i = 1; i <= (RightBottom.x - LeftTop.x) / nWidth; i++)
    {
        LineTo(hdc, LeftTop.x + nWidth * i, RightBottom.y);
        MoveToEx(hdc, LeftTop.x + nHeight*(i+1), LeftTop.y, NULL);
    }

}
void DrawCircle_Test(HDC hdc)
{
    Ellipse(hdc, 300, 300, 400, 400);
}

void Rectangle_Test(HDC hdc)
{
    Rectangle(hdc, 500, 300, 700, 500);
}


void Star(HDC hdc, POINT center, double distance, double n)
{
    double angle = 2 * 3.14159 / n;
    double temp_size = distance * cos(angle);
    double half_Angle = angle / 2.0;
    double size = temp_size / cos(half_Angle);
    double temp = 3.14159 / 2;
    
    POINT* point = new POINT[2*n];

    for (int i = 0; i < 2*n; i++)
    {
        if (i % 2 == 0)
        {
            point[i] = { (LONG)(center.x + distance*cos(i*half_Angle-temp)), (LONG)((center.y) + distance * sin(i* half_Angle-temp)) };
        }
        else
        {
            point[i] = { (LONG)(center.x + size * cos(i * half_Angle-temp)), (LONG)((center.y) + size * sin(i*half_Angle-temp)) };
        }
    }
    
    Polygon(hdc, point, 2*n);

    delete[] point;
}

void direction(HDC hdc)
{
    Rectangle(hdc, 500, 300, 700, 500);//위
    Rectangle(hdc, 500, 700, 700, 900);//아래
    Rectangle(hdc, 300, 500, 500, 700);//왼
    Rectangle(hdc, 700, 500, 900, 700);//오
    WPARAM wParam = NULL;

    if (wParam == VK_LEFT)
    {
        HBRUSH hBrush, oldBrush;
        hBrush = CreateSolidBrush(RGB(0, 255, 0));
        oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        Rectangle(hdc, 300, 500, 500, 700);//왼
        SelectObject(hdc, oldBrush);
        DeleteObject(hBrush);
    }
}

void DrawMove_Star2D(HDC hdc, Star2D& star)
{
    double temp_size = star.getDistance() * cos(star.getRotAngle());
    double half_angle = star.getRotAngle() / 2.0;
    double size = temp_size / cos(half_angle);

    POINT* starAry = new POINT[2 * star.getN()];
    for (int i = 0; i < 2 * star.getN(); i++)
    {
        if (i % 2 == 0)
        {
            starAry[i] = { (LONG)(star.getX() + star.getDistance() * cos(i * half_angle + star.getRotVelAngle())), (LONG)((star.getY()) + star.getDistance() * sin(i * half_angle + star.getRotVelAngle())) };
        }
        else
        {
            starAry[i] = { (LONG)(star.getX() + size * cos(i * half_angle + star.getRotVelAngle())), (LONG)(star.getY() + size * sin(i * half_angle + star.getRotVelAngle())) };
        }
    }

    Polygon(hdc, starAry, 2 * star.getN());

    delete[] starAry;
}

void DrawMove_Ellipse(HDC hdc, Circle& curPos)
{
    Ellipse(hdc, curPos.getX() - curPos.getRadius(), curPos.getY() - curPos.getRadius(), curPos.getX() + curPos.getRadius(), curPos.getY() + curPos.getRadius());
}

void DrawMove_Rectangle(HDC hdc, Rectangle2D& curPos)
{
    POINT rec[4]; // 4개 꼭짓점
    double dia = sqrt(pow(curPos.getHeight() / 2, 2) + pow(curPos.getWidth() / 2, 2));
    for (int i = 0; i < 4; i++)
    {
        rec[i] = { (LONG)(curPos.getX()
            + dia * cos(curPos.getRotAngle() + (3.14159 / 2 * i))), (LONG)(curPos.getY() + dia * sin(curPos.getRotAngle() + (3.14159 / 2 * i))) };
    }
    Polygon(hdc, rec, 4);
}

void Reflect_Conflict_Circle(int mode, HWND hWnd, RECT windowRect)
{
    
    //GetWindowRect(hWnd, &windowRect);
    for (int i = 0; i < objectArr.size(); i++)
    {
        for (int j = 0; j < objectArr.size(); j++)
        {
            if (i == j || i >= objectArr.size())
                break;
            else
            {
                if (conflict(objectArr[i], objectArr[j]) == true)
                {
                    double radius_overlap = objectArr[i]->getD() + objectArr[j]->getD() - sqrt(pow(objectArr[i]->getX() - objectArr[j]->getX(), 2) + pow(objectArr[j]->getY() - objectArr[i]->getY(), 2));

                    if (radius_overlap > 0)
                    {
                        if (objectArr[i]->getAngle() >= 0 && objectArr[i]->getAngle() < 3.14159 / 2.0) // 1사분면일때
                        {
                            objectArr[i]->setX(objectArr[i]->getX() - radius_overlap / sqrt(2));
                            objectArr[i]->setY(objectArr[i]->getY() - radius_overlap / sqrt(2));
                        }
                        else if (objectArr[i]->getAngle() < 3.14159 && objectArr[i]->getAngle() >= 3.14159 / 2.0) // 2사분면일때
                        {
                            objectArr[i]->setX(objectArr[i]->getX() + radius_overlap / sqrt(2));
                            objectArr[i]->setY(objectArr[i]->getY() - radius_overlap / sqrt(2));
                        }
                        else if (objectArr[i]->getAngle() >= 3.14159 && objectArr[i]->getAngle() < 3 * 3.14159 / 2.0) // 3사분면일때
                        {
                            objectArr[i]->setX(objectArr[i]->getX() + radius_overlap / sqrt(2));
                            objectArr[i]->setY(objectArr[i]->getY() + radius_overlap / sqrt(2));
                        }
                        else if (objectArr[i]->getAngle() < 2 * 3.14159 && objectArr[i]->getAngle() >= 3 * 3.14159 / 2.0) // 4사분면일때
                        {
                            objectArr[i]->setX(objectArr[i]->getX() - radius_overlap / sqrt(2));
                            objectArr[i]->setY(objectArr[i]->getY() + radius_overlap / sqrt(2));
                        }
                    }

                    if (mode == 2)
                    {
                        ////합치기
                        if (objectArr[i]->getD() <= objectArr[j]->getD())
                        {
                            objectArr[j]->setD(objectArr[j]->getD() + objectArr[i]->getD());
                            objectArr.erase(objectArr.begin() + i);
                            int j_temp = j > i ? j - 1 : j;
                            if (objectArr[j_temp]->getD() >= windowRect.bottom / 2)
                            {
                                objectArr.erase(objectArr.begin() + j_temp);
                            }
                        }
                        else
                        {
                            objectArr[i]->setD(objectArr[i]->getD() + objectArr[j]->getD());
                            objectArr.erase(objectArr.begin() + j);

                            int i_temp = i > j ? i - 1 : i;
                            if (objectArr[i_temp]->getD() >= windowRect.bottom / 2)
                            {
                                objectArr.erase(objectArr.begin() + i_temp);
                            }
                        }

                        break;
                    }
                    else if (mode == 3)
                    {
                        //파티클
                        double particleX = 0, particleY = 0;
                        if (objectArr[i]->getAngle() >= 0 && objectArr[i]->getAngle() < 3.14159 / 2.0) // 1사분면일때
                        {
                            particleX = -30;
                            particleY = -30;
                        }
                        else if (objectArr[i]->getAngle() < 3.14159 && objectArr[i]->getAngle() >= 3.14159 / 2.0) // 2사분면일때
                        {
                            particleX = 30;
                            particleY = -30;
                        }
                        else if (objectArr[i]->getAngle() >= 3.14159 && objectArr[i]->getAngle() < 3 * 3.14159 / 2.0) // 3사분면일때
                        {
                            particleX = 30;
                            particleY = 30;
                        }
                        else if (objectArr[i]->getAngle() < 2 * 3.14159 && objectArr[i]->getAngle() >= 3 * 3.14159 / 2.0) // 4사분면일때
                        {
                            particleX = -30;
                            particleY = 30;
                        }
                        if (objectArr[i]->getType() == "circle")
                        {
                            objectArr.push_back(new Circle(objectArr[i]->getX(), objectArr[i]->getY()));
                        }          
                        else if (objectArr[i]->getType() == "star")
                        {
                            objectArr.push_back(new Star2D(objectArr[i]->getX(), objectArr[i]->getY()));
                        }
                        else
                        {
                            objectArr.push_back(new Rectangle2D(objectArr[i]->getX(), objectArr[i]->getY()));
                        }
                        objectArr.back()->setD(objectArr[i]->getD() / 5.0 * 4.0);
                        if (objectArr.back()->getD() <= 8)
                        {
                            objectArr.pop_back();
                        }

                        //==============================================

                        if (objectArr[i]->getType() == "circle")
                        {
                            objectArr.push_back(new Circle(objectArr[i]->getX() + particleX, objectArr[i]->getY() + particleY));
                        }
                        else if (objectArr[i]->getType() == "star")
                        {
                            objectArr.push_back(new Star2D(objectArr[i]->getX() + particleX, objectArr[i]->getY() + particleY));
                        }
                        else
                        {
                            objectArr.push_back(new Rectangle2D(objectArr[i]->getX() + particleX, objectArr[i]->getY() + particleY));
                        }
                        objectArr.back()->setD(objectArr[i]->getD() / 5.0 * 4.0);
                        if (objectArr.back()->getD() <= 8)
                        {
                            objectArr.pop_back();
                        }
                        
                        //============================================

                        if (objectArr[j]->getAngle() >= 0 && objectArr[j]->getAngle() < 3.14159 / 2.0) // 1사분면일때
                        {
                            particleX = -30;
                            particleY = -30;
                        }
                        else if (objectArr[j]->getAngle() < 3.14159 && objectArr[j]->getAngle() >= 3.14159 / 2.0) // 2사분면일때
                        {
                            particleX = 30;
                            particleY = -30;
                        }
                        else if (objectArr[j]->getAngle() >= 3.14159 && objectArr[j]->getAngle() < 3 * 3.14159 / 2.0) // 3사분면일때
                        {
                            particleX = 30;
                            particleY = 30;
                        }
                        else if (objectArr[j]->getAngle() < 2 * 3.14159 && objectArr[j]->getAngle() >= 3 * 3.14159 / 2.0) // 4사분면일때
                        {
                            particleX = -30;
                            particleY = 30;
                        }

                        if (objectArr[j]->getType() == "circle")
                        {
                            objectArr.push_back(new Circle(objectArr[j]->getX(), objectArr[j]->getY()));
                        }
                        else if (objectArr[j]->getType() == "star")
                        {
                            objectArr.push_back(new Star2D(objectArr[j]->getX(), objectArr[j]->getY()));
                        }
                        else
                        {
                            objectArr.push_back(new Rectangle2D(objectArr[j]->getX(), objectArr[j]->getY()));
                        }
                        objectArr.back()->setD(objectArr[j]->getD() / 5.0 * 4.0);
                        if (objectArr.back()->getD() <= 8)
                        {
                            objectArr.pop_back();
                        }

                        //==============================================

                        if (objectArr[j]->getType() == "circle")
                        {
                            objectArr.push_back(new Circle(objectArr[j]->getX() + particleX, objectArr[j]->getY() + particleY));
                        }
                        else if (objectArr[j]->getType() == "star")
                        {
                            objectArr.push_back(new Star2D(objectArr[j]->getX() + particleX, objectArr[j]->getY() + particleY));
                        }
                        else
                        {
                            objectArr.push_back(new Rectangle2D(objectArr[j]->getX() + particleX, objectArr[j]->getY() + particleY));
                        }
                        objectArr.back()->setD(objectArr[j]->getD() / 5.0 * 4.0);
                        if (objectArr.back()->getD() <= 8)
                        {
                            objectArr.pop_back();
                        }


                        if (i <= j)
                        {
                            objectArr.erase(objectArr.begin() + i);
                            objectArr.erase(objectArr.begin() + j - 1);
                        }
                        else
                        {
                            objectArr.erase(objectArr.begin() + i);
                            objectArr.erase(objectArr.begin() + j);
                        }
                        break;
                    }
                    else if (mode == 1)
                    {
                        //튕기기
                        double Itemp_Angle = objectArr[i]->getAngle();
                        objectArr[i]->setAngle(objectArr[j]->getAngle());
                        objectArr[j]->setAngle(Itemp_Angle);

                        double Itemp_Speed = objectArr[i]->getMoveSpeed();
                        objectArr[i]->setMoveSpeed(objectArr[j]->getMoveSpeed());
                        objectArr[j]->setMoveSpeed(Itemp_Speed);
                    }
                }
            }
        }
    }
}
/*
클라이언트 영역에 마우스 클릭하면 
현재 마우스 위치에 원,사각형,별이 랜덤하게 생성
생성된 도형은 임의의 방향으로 이동, 
클라이언트 영역을 넘어서지 ㅇ낳게 외곽에서 반사
옵션은 1, 2, 3키로 설정
1.1 다른 오브젝트와 부딪히면 서로 튕기기
1.2 다른 오브젝트와 부딪히면 하나로 합체해서 커지게 하기
1.3 다른 오브젝트와 부딪히면 분열해서 작아지게 하기
*/