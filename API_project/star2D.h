#pragma once

#ifndef __Star2D_H__
#define __Star2D_H__

#include "object.h"
//#include <windef.h>

class Star2D : public Object
{
private:
	double n, distance; // �߽���ǥ, n��, �ܰ��������� �Ÿ�
	double lookX, lookY; //���⺤��
	double rotAngle; //ȸ����
	double rotVelAngle; //ȸ�����ӵ�
public:
	Star2D();
	Star2D(int X, int Y);
	~Star2D();

	double getLookX() { return lookX; }
	double getLookY() { return lookY; }
	double getAngle() { return angle; }
	double getRotAngle() { return rotAngle; }
	double getRotVelAngle() { return rotVelAngle; }
	double getDistance() { return distance; }
	double getN() { return n; }
	double getPerimeter();

	void setDistance(double d) { distance = d; }
	void setRotAngle(double angle) { rotAngle = angle; }
	void setRotVelAngle(double angle) { rotVelAngle = angle; }
	void Draw(HDC hdc);
};

#endif