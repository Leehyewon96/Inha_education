#include "sigong.h"

Sigong::Sigong()
{

}
Sigong::Sigong(POINT P)
{
	p.x = P.x;
	p.y = P.y;
	polyArr.push_back({ 0,0 });
	polyArr.push_back({ 800,0 });
	polyArr.push_back({ 800,800 });
	polyArr.push_back({ 0,800 });

}
Sigong::~Sigong()
{

}

char Sigong::moveConfirm()
{
	if (Right == false && Left == false && Up == false && Down == false)
	{
		return 'A';
	}
	else if (Right == true && Left == false && Up == false && Down == false)
	{
		return 'R';
	}
	else if (Right == false && Left == true && Up == false && Down == false)
	{
		return 'L';
	}
	else if (Right == false && Left == false && Up == true && Down == false)
	{
		return 'U';
	}
	else if (Right == false && Left == false && Up == false && Down == true)
	{
		return 'D';
	}
}

void Sigong::drawLine(HDC hdc, vector<POINT> p)
{
	for (int i = 0; i < p.size() - 1; i++)
	{
		MoveToEx(hdc, p[i].x, p[i].y, NULL);
		LineTo(hdc, p[i+1].x , p[i+1].y);
	}
}

void Sigong::drawPoly(HDC hdc, vector<POINT> p)
{
	POINT* poly = new POINT[p.size()];
	for (int i = 0; i < p.size(); i++)
	{
		poly[i] = p[i];
	}

	Polygon(hdc, poly, p.size());

	delete[] poly;
}