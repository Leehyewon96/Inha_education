#pragma once
#include <ctime>
#include "circle.h"


Circle::Circle()
{
	////srand(time(NULL));
	//double temp_angle = rand() % 360;
	//angle = temp_angle / 180 * 3.14159;
	////radius = 60;
	//radius = (rand() % 50) + 20;
	//moveSpeed = (rand() % 20) + 10;
}

Circle::Circle(int X, int Y)
{
	//srand(time(NULL));
	double temp_angle = rand() % 360;
	angle = temp_angle / 180 * 3.14159;
	//radius = 60;
	d = (rand() % 50) + 20;
	moveSpeed = (rand() % 20) + 10;
	x = X;
	y = Y;
	radius=d;
	Object::type = "circle";
}

Circle::~Circle()
{
}


void Circle::Draw(HDC hdc)
{
	//Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	Ellipse(hdc, x - d, y - d, x + d, y + d);
}
