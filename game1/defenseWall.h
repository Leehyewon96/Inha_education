#pragma once
#include "object.h"

class DefenseWall : public Object
{
private:
	double width, height;
public:
	DefenseWall();
	DefenseWall(double X, double Y, double W, double H);
	~DefenseWall();
	double getWidth() { return width; }
	double getHeight() { return height; }
	void setWidth(double w) { width = w; }
	void setHeight(double h) { height = h; }
	void Draw(HDC hdc);
};