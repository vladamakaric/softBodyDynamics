#pragma once
#include "Vector.h"
#include "f_misc.h"

class CSquare
{
public:
	CSquare(const CVector &_downLeft, const CVector &_upRight, bool _sort=false)
	{
		if(!_sort)
		{
			upRight = _upRight;
			downLeft = _downLeft;
			return;
		}

		double x1,x2,y1,y2;

		x1 = _upRight.x;
		x2 = _downLeft.x;
		y1 = _upRight.y;
		y2 = _downLeft.y;

		upRight.Set(F::MISC::Max(x1,x2), F::MISC::Max(y1,y2));
		downLeft.Set(F::MISC::Min(x1,x2), F::MISC::Min(y1,y2));
	}

	CVector upRight,downLeft;
};