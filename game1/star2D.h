#pragma once

#ifndef __Star_H__
#define __Star_H__

#include "object.h"

class Star2D : public Object
{
private:
	double n; // 중심좌표, n별, 외곽점까지의 거리
	double lookX, lookY; //방향벡터
	double rotAngle; //회전각
	double rotVelAngle; //회전각속도
public:
	Star2D();
	Star2D(int X, int Y);
	~Star2D();

	double getLookX() { return lookX; }
	double getLookY() { return lookY; }
	double getAngle() { return angle; }
	double getRotAngle() { return rotAngle; }
	double getRotVelAngle() { return rotVelAngle; }
	double getN() { return n; }
	double getPerimeter();

	void setRotAngle(double angle) { rotAngle = angle; }
	void setRotVelAngle(double angle) { rotVelAngle = angle; }
	void Draw(HDC hdc);
	void ColorDraw(HDC hdc);
};

#endif