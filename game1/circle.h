#pragma once
#include  "object.h"

class Circle : public Object
{
private:
public:
	Circle();
	Circle(double x, double y);
	~Circle();
	string getType() { return type; }
	void Draw(HDC hdc);
	void ColorDraw(HDC hdc);
};