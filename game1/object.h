#pragma once
#define __OBJECT_H__
#include <cmath>
#include <string>
#include <Windows.h>

using namespace std;

class Object
{
protected:
	double x, y, radius, speed, angle;
	bool conflict = false;
	string type;
public:
	Object() {};
	~Object() {};
	double getX() { return x; }
	double getY() { return y; }
	bool getConflict() { return conflict; }
	double getSpeed() { return speed; }
	double getRadius() { return radius; }
	string getType() { return type; }
	void setX(double X) { x = X; }
	void setY(double Y) { y = Y; }
	void setConflict(bool Y) { conflict = Y; }
	void setSpeed(double S) { speed = S; }
	virtual void Draw(HDC hdc) = 0;
};

