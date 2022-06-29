#pragma once
#include <string>
#include <Windows.h>
using namespace std;

class Object
{
protected:
	double x;
	double y;
	double d;
	double angle;
	string type = "object";
	double moveSpeed;

public:
	Object() {}
	virtual ~Object() {}
	double getX() { return x; };
	double getY() { return y; };
	double getD() { return d; };

	double getAngle() { return angle; };
	void setAngle(double ANGLE) { angle = ANGLE; };

	double getMoveSpeed() { return moveSpeed; };
	void setMoveSpeed(double SPEED) { moveSpeed = SPEED; };

	void setX(double X) { x = X; };
	void setY(double Y) { y = Y; };
	void setD(double D) { d = D; };
	string getType() { return type; }

	void setType(string str) { type = str; }
	friend bool conflict(Object *o1, Object *o2);
	
	//virtual void Draw(HDC hdc) {};
	//virtual bool conflict() { return false; }
};





//class Star
//{
//private:
//	double x;
//	double y;
//	double distance;
//	double n;
//	string type;
//public:
//	double getX() { return x; };
//	double getY() { return y; };
//	double getDistance() { return distance; };
//	double getX() { return x; };
//	double getY() { return y; };
//	void setX(int X) { x = X; };
//	void setY(int Y) { y = Y; };
//	void setDistance(int DIS) { distance = DIS; };
//	void setType() { type = "TRIANGLE"; };
//	static bool conflict(Star& s1, Star& s2);
//};