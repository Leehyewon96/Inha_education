#pragma once
#include "framework.h"
#include "cVector3.h"
#include "cMatrix.h"

class cVector3;

class cMainGame
{
private :
	HDC					m_MemDC = NULL;
	HBITMAP				m_hOldBitmap, m_hBitmap;

	vector<cVector3>	m_vecVertex;
	vector<cVector3>	m_vecLineVertex; // �ؿ� �࿡ ���� ����
	vector<DWORD>		m_vecIndex;
	

	cMatrix				m_matWorld;
	cMatrix				m_matView;
	cMatrix				m_matProj;
	cMatrix				m_matViewPort;

	cVector3			m_vEye;			// ���� ī�޶� ��ġ
	cVector3			m_vLookAt;		// ī�޶� ���� �ִ� ��ġ
	cVector3			m_vUp;			// ī�޶��� ����
	cVector3			m_vPosition;
	cVector3			m_vBoxDirection;
	cVector3			m_vAxisXTextPosition;
	cVector3			m_vAxisZTextPosition;

	POINT				m_ptPrevMouse;
	bool				m_isLButtonDown;
	float				m_fCameraDistance;
	cVector3			m_vCamRotAngle;
	float				m_fScale;

	float				m_fBoxRotX; // X�࿡ ���� ȸ��
	float				m_fBoxRotY; // Y�࿡ ���� ȸ��

public :
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//
	void SetGrid();
	void DrawGrid();
	bool IsBackFace(cVector3& v1, cVector3& v2, cVector3& v3);
	void Update_Rotation();
	void Update_Move();
	void Update_Scale();
};

