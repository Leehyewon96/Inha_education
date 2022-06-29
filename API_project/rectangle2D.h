#pragma once

#ifndef __Rectangle2D_H__
#define __Rectangle2D_H__

#include "object.h"
//#include <windef.h>

class Rectangle2D : public Object
{
private:
	double width, height; // �߽���ǥ, ����, ����
	double lookX, lookY; //���⺤��
	double rotAngle; //ȸ����
	double rotVelAngle; //ȸ�����ӵ�
public:
	Rectangle2D();
	Rectangle2D(int X, int Y);
	~Rectangle2D();
	double getWidth();
	double getHeight();
	double getLookX() { return lookX; }
	double getLookY() { return lookY; }
	double getRotAngle() { return rotAngle; }
	double getRotVelAngle() { return rotVelAngle; }
	double getArea();
	double getPerimeter();

	void setRotAngle(double angle) { rotAngle = angle; }
	void setPoint();
	void setRotVelAngle(double angle) { rotVelAngle = angle; }
	bool contains(double x, double y);
	bool contains(Rectangle2D& r);
	bool overlaps(Rectangle2D& r);
	void Draw(HDC hdc);
};

#endif