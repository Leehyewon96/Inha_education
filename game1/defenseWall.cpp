#include "defenseWall.h"

DefenseWall::DefenseWall()
{
}

DefenseWall::DefenseWall(double X, double Y, double W, double H)
{
	x = X;
	y = Y;
	width = W;
	height = H;
	color = "black";
	Object::type = "defense";
	Object::conflict = 0;
}
DefenseWall::~DefenseWall()
{

}

void DefenseWall::Draw(HDC hdc)
{
	Rectangle(hdc, x - width / 2.0, y - height / 2.0, x + width / 2.0, y + height / 2.0);
}

void DefenseWall::ColorDraw(HDC hdc, int r, int g, int b)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(r, g, b));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, x - width / 2.0, y - height / 2.0, x + width / 2.0, y + height / 2.0);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}




