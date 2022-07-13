#pragma once
#include <vector>
#include "Windows.h"
using namespace std;

class Object
{
protected:
	POINT p;
	bool Right = false;
	bool Left = false;
	bool Up = false;
	bool Down = false;
	bool Space = false;

public:
	Object();
	~Object();
	POINT getP() { return p; }
	bool getRight() { return Right; }
	bool getLeft() { return Left; }
	bool getUp() { return Up; }
	bool getDown() { return Down; }
	bool getSpace() { return Space; }

	void setP(POINT P) { p = P; }
	void setRight(bool b) { Right = b; }
	void setLeft(bool b) { Left = b; }
	void setUp(bool b) { Up = b; }
	void setDown(bool b) { Down = b; }
	void setSpace(bool b) { Space = b; }
};