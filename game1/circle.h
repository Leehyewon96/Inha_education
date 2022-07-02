#pragma once
#include  "object.h"

class Circle : public Object
{
private:
	double LookX;
	double LookY;
public:
	Circle();
	Circle(double X, double Y, double lX, double lY);
	~Circle();
	double getLookX() { return LookX; }
	double getLookY() { return LookY; }
	string getType() { return type; }
	void Draw(HDC hdc);
	void ColorDraw(HDC hdc);
	void setLookX(double x) { LookX = x; }
	void setLookY(double y) { LookX = y; }
};