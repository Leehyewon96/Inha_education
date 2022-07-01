#pragma once
#define __TURRET_H__
#include "object.h"

class Turret : public Object
{
private:
	double width, height, LookX, LookY;
public:
	Turret();
	Turret(double X, double Y);
	~Turret();
	double getLookX() { return LookX; }
	double getLookY() { return LookY; }
	double getWidth() { return width; }
	double getHeight() { return height; }
	double getAngle() { return angle; }
	void setAngle(double A) { angle = A; }
	void setWidth(double W) { width = W; }
	void setHeight(double H) { height = H; }
	void Draw(HDC hdc);
	
};