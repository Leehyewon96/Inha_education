#include "turret.h"

Turret::Turret()
{

}
Turret::Turret(double X, double Y)
{
	width = 100;
	height = 100;
	x = X;
	y = Y + height / 2.0;
	
	angle = 270.0 / 180.0 * 3.14159;
	speed = 5.0;
}
Turret::~Turret()
{

}
void Turret::Draw(HDC hdc)
{
	LookX = cos(angle);
	LookY = sin(angle);
	Ellipse(hdc, x - width / 2.0, y - height / 2.0, x + width / 2.0, y + height / 2.0);
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + 100.0 * LookX, y + 100.0 * LookY);
}