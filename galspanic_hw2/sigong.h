#pragma once
#include "object.h"

class Sigong : public Object
{
private:
	vector<POINT> pArr;
public:
	Sigong();
	Sigong(POINT P);
	~Sigong();
	char moveConfirm();
	vector<POINT> getPvec() { return pArr; }

	void pushPvec(POINT point) { pArr.push_back(point); }
	void clearPvec() { pArr.clear(); }
	void drawLine(HDC hdc, vector<POINT> p);
};
