#include "cMainGame.h"

cMainGame::cMainGame()
	: m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_vEye(0, 0, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vPosition(0, 0, 0)
	, m_fBoxRotY(0.f)
	, m_fBoxRotX(0.f)
	, m_vBoxDirection(0, 0, 1)
	, m_fCameraDistance(5.f)
	, m_isLButtonDown(false)
	, m_vCamRotAngle(0, 0, 0)
	, m_fScale(1.f)	
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}

cMainGame::~cMainGame()
{
	SelectObject(m_MemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDC);
}

void cMainGame::Setup()
{
	HDC hdc = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(hdc);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	m_hOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);

	ReleaseDC(g_hWnd, hdc);

	
	m_vecVertex.push_back(cVector3(-1.f, -1.f, -1.f)); // 인덱스 0번
	m_vecVertex.push_back(cVector3(-1.f,  1.f, -1.f)); // 인덱스 1번
	m_vecVertex.push_back(cVector3(1.f,   1.f, -1.f)); // 인덱스 2번
	m_vecVertex.push_back(cVector3(1.f,  -1.f, -1.f)); // 인덱스 3번

	m_vecVertex.push_back(cVector3(-1.f, -1.f,  1.f)); // 인덱스 4번
	m_vecVertex.push_back(cVector3(-1.f,  1.f,  1.f)); // 인덱스 5번
	m_vecVertex.push_back(cVector3(1.f,   1.f,  1.f)); // 인덱스 6번
	m_vecVertex.push_back(cVector3(1.f,  -1.f,  1.f)); // 인덱스 7번

	// Front ( 보이는 면 기준에서 시계방향으로 ) =================================================

	/*

	 1	2

	 0	3

	*/

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(2);

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);

	// Back ( 보이는 면 기준에서 시계방향으로 ) =================================================

	/*
	
	 6	5

	 7	4

	*/
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(5);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(6);

	// Left ( 보이는 면 기준에서 시계방향으로 ) =================================================

	/*

	 5	1

	 4	0

	*/
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(1);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(0);

	// right ( 보이는 면 기준에서 시계방향으로 ) =================================================

	/*

	 2	6

	 3	7

	*/
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(3);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(7);

	// top ( 보이는 면 기준에서 시계방향으로 ) =================================================

	/*

	 5	6

	 1	2

	*/
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(1);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(2);

	// bottom ( 보이는 면 기준에서 시계방향으로 ) =================================================

	/*

	 0	3

	 4	7

	*/
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(3);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(7);

	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewPort = cMatrix::Identity(4);

}

void cMainGame::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vLookAt = cVector3(0.f, 0.f, 0.f);
	m_vEye = cVector3(0.f, 4.f, -5.f);

	cMatrix matR = cMatrix::RotationY(m_fBoxRotY);
	cMatrix matT = cMatrix::Translation(m_vPosition);
	m_matWorld = matR * matT;
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 4.f,
									(float)rc.right / (float)rc.bottom,
									1.f, 1000.f);
	m_matViewPort = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);

	cMatrix matWVP = m_matWorld * m_matView * m_matProj;
	for (UINT i = 0; i < m_vecIndex.size(); i+=3)
	{
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 0]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecIndex[i + 2]];

		v1 = cVector3::TransformCoord(v1, matWVP);
		v2 = cVector3::TransformCoord(v2, matWVP);
		v3 = cVector3::TransformCoord(v3, matWVP);

		v1 = cVector3::TransformCoord(v1, m_matViewPort);
		v2 = cVector3::TransformCoord(v2, m_matViewPort);
		v3 = cVector3::TransformCoord(v3, m_matViewPort);

		MoveToEx(m_MemDC, v1.x, v1.y, NULL);
		LineTo(m_MemDC, v2.x, v2.y);
		LineTo(m_MemDC, v3.x, v3.y);
		LineTo(m_MemDC, v1.x, v1.y);
	}

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void cMainGame::SetGrid()
{
}

void cMainGame::DrawGrid()
{
}

bool cMainGame::IsBackFace(cVector3& v1, cVector3& v2, cVector3& v3)
{
    return false;
}

void cMainGame::Update_Rotation()
{
}

void cMainGame::Update_Move()
{
}

void cMainGame::Update_Scale()
{
}
