#pragma once
#include "object.h"

class Sigong : public Object
{
private:
public:
	Sigong();
	Sigong(POINT P);
	~Sigong();
	char moveConfirm();
};
