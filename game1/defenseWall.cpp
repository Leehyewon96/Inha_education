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
	Object::type = "defense";
}
DefenseWall::~DefenseWall()
{

}

void DefenseWall::Draw(HDC hdc)
{
	Rectangle(hdc, x - width / 2.0, y - height / 2.0, x + width / 2.0, y + height / 2.0);
}




