#pragma once
#include "object.h"

class DefenseWall : public Object
{
private:
	double width, height;
	string color;
public:
	DefenseWall();
	DefenseWall(double X, double Y, double W, double H);
	~DefenseWall();
	double getWidth() { return width; }
	double getHeight() { return height; }
	string getColor() { return color; }
	void setColor(string w) { color = w; }
	void setWidth(double w) { width = w; }
	void setHeight(double h) { height = h; }
	void Draw(HDC hdc);
	void ColorDraw(HDC hdc, int r, int g, int b);
};