#define __CIRCLE_H__
#include "object.h"

class Circle : public Object
{
private:
	double radius;
	int cnt;
public:
	Circle();
	Circle(int X, int Y);
	~Circle();
	
	double getRadius() { return radius; };
	string getType() { return type; }
	void setRadius(int RADIUS) { radius = RADIUS; };
	virtual double Area() { return (getRadius() * getRadius() * 3.14159); };
	//void setType() { type = "CIRCLE"; };
	void Move_Random();
	void Draw(HDC hdc);
};