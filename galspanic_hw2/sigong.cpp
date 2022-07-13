#include "sigong.h"

Sigong::Sigong()
{

}
Sigong::Sigong(POINT P)
{
	p.x = P.x;
	p.y = P.y;
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