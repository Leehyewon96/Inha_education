#pragma once
#include <Windows.h>

class Circle
{
private:
	double x, y, r;
public:
	Circle();
	Circle(double X, double Y, double R);
	~Circle();
	double getX() { return x; }
	double getY() { return y; }
	double getR() { return r; }
};