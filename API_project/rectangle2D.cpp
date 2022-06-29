#pragma once
#include <ctime>
#include "rectangle2D.h"

Rectangle2D::Rectangle2D()
{	
}

Rectangle2D::Rectangle2D(int X, int Y)
{
	x = X;
	y = Y;

	width = rand() % 80 + 20;
	height = rand() % 60 + 20;
	lookX = (rand() % 81 + 20) / 100.0;
	lookY = (rand() % 81 + 20) / 100.0;

	angle = (double)(rand() % 360) / 180.0 * 3.14159;

	moveSpeed = rand() % 10 + 5;

	d = sqrt(pow(width / 2.0, 2) + pow(height / 2.0, 2));

	double vecX = width / 2.0;
	double vecY = height / 2.0;
	rotAngle = asin(vecY / sqrt(pow(vecX, 2) + pow(vecY, 2)));

	double temp_angle = rand() % 360;
	rotVelAngle = temp_angle / 180 * 3.14159;

	int direction = rand() % 2;
	if (direction == 0)
	{
		lookX *= -1;
		temp_angle *= -1;
	}
	direction = rand() % 2;
	if (direction == 0)
	{
		lookY *= -1;
	}

	Object::type = "rectangle";
}

Rectangle2D::~Rectangle2D()
{
}
double Rectangle2D::getWidth()
{
	return width;
}
double Rectangle2D::getHeight()
{
	return height;
}
double Rectangle2D::getArea()
{
	return width * height;
}
double Rectangle2D::getPerimeter()
{
	return 2.0 * (width + height);
}
bool Rectangle2D::contains(double X, double Y)
{
	double halfD = sqrt(pow(width / 2.0, 2) + pow(height / 2.0, 2));
	double distance = sqrt(pow(x - X, 2) + pow(y - Y, 2));
	if (distance <= halfD)
		return true;
	else
		return false;
}
bool Rectangle2D::contains(Rectangle2D& r)
{
	double halfD = sqrt(pow((width / 2.0 - r.getWidth() / 2.0), 2) + pow((height / 2.0 - r.getHeight() / 2.0), 2));
	double distance = sqrt(pow(x - r.getX(), 2) + pow(y - r.getY(), 2));
	if (distance <= halfD)
		return true;
	else
		return false;
}
bool Rectangle2D::overlaps(Rectangle2D& r)
{
	double halfD = sqrt(pow((width / 2.0 + r.getWidth() / 2.0), 2) + pow((height / 2.0 + r.getHeight() / 2.0), 2));
	double distance = sqrt(pow(x - r.getX(), 2) + pow(y - r.getY(), 2));
	if (distance <= halfD)
	{
		if (!(abs(x - r.getX()) > (width + r.getWidth()) / 2 || abs(y - r.getY()) > (height + r.getHeight()) / 2))
			return true;
		else return false;
	}
	else
		return false;
}

void Rectangle2D::Draw(HDC hdc)
{
	POINT rec[4]; // 4°³ ²ÀÁþÁ¡
	//double dia = sqrt(pow(height / 2, 2) + pow(width/ 2, 2));
	for (int i = 0; i < 4; i++)
	{
		rec[i] = { (LONG)(x + d * cos(rotAngle + (3.14159 / 2 * i))), (LONG)(y + d * sin(rotAngle + (3.14159 / 2 * i))) };
	}
	Polygon(hdc, rec, 4);
}