#pragma once
#include <ctime>
#include "star2D.h"

Star2D::Star2D()
{
}

Star2D::Star2D(int X, int Y)
{
	x = X;
	y = Y;
	n = rand() % 3 + 5;
	angle = (double)(rand() % 360) / 180.0 * 3.14159;
	//angle = (360.0 / n) / 180 * 3.14159;
	rotAngle = (360.0 / n) / 180 * 3.14159;
	moveSpeed = rand() % 10 + 5;
	d = (rand() % 50) + 20;
	distance = d;
	lookX = moveSpeed * cos(angle);
	lookY = moveSpeed * sin(angle);
	//lookX = (rand() % 81 + 20) / 100.0;
	//lookY = (rand() % 81 + 20) / 100.0;


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

	Object::type = "star";
}

Star2D::~Star2D()
{
}


void Star2D::Draw(HDC hdc)
{
	double temp_size = d * cos(rotAngle);
	double half_angle = rotAngle / 2.0;
	double size = temp_size / cos(half_angle);

	POINT* starAry = new POINT[2 * n];
	for (int i = 0; i < 2 * n; i++)
	{
		if (i % 2 == 0)
		{
			starAry[i] = { (LONG)(x + d * cos(i * half_angle + rotVelAngle)), (LONG)(y + d * sin(i * half_angle + rotVelAngle)) };
		}
		else
		{
			starAry[i] = { (LONG)(x + size * cos(i * half_angle + rotVelAngle)), (LONG)(y + size * sin(i * half_angle + rotVelAngle)) };
		}
	}

	Polygon(hdc, starAry, 2 * n);

	delete[] starAry;
}