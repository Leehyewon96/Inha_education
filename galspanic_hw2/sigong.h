#pragma once
#include "object.h"

class Sigong : public Object
{
private:
	vector<POINT> pArr;
	vector<POINT> polyArr;
public:
	Sigong();
	Sigong(POINT P);
	~Sigong();
	char moveConfirm();
	vector<POINT> getPvec() { return pArr; }
	vector<POINT> getPolyvec() { return polyArr; }

	void pushPvec(POINT point) { pArr.push_back(point); }
	void clearPvec() { pArr.clear(); }
	void pushPolyvec(POINT point) { polyArr.push_back(point); }
	void clearPolyvec() { polyArr.clear(); }
	void drawLine(HDC hdc, vector<POINT> p);
	void drawPoly(HDC hdc, vector<POINT> p);
};
