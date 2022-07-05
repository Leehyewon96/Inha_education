#define __CIRCLE_H__
#include "circle.h"

Circle::Circle()
{

}
Circle::Circle(double X, double Y, double lX, double lY)
{
	x = X;
	y = Y;
	radius = 5;
	speed = 20;
	LookX = lX;
	LookY = lY;
	Object::type = "circle";
	Object::conflict = 0;
}
Circle::~Circle()
{
}
void Circle::Draw(HDC hdc)
{
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
}

void Circle::ColorDraw(HDC hdc)
{
    HBRUSH hBrush, oldBrush;
    hBrush = CreateSolidBrush(RGB(0, 255, 0));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);
    TextOut(hdc, 400, 600, TEXT("LEFT"), 4);
}