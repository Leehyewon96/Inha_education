#define __OBJECT_H__

#include "object.h"

bool conflict(Object *o1, Object *o2)
{
	double dis = sqrt(pow((o1->getX() - o2->getX()), 2) + pow((o1->getY() - o2->getY()), 2)); // �ο��� �߽ɻ����� �Ÿ�

	if (dis > o1->getD() + o2->getD())
		return false;
	else
		return true;
}