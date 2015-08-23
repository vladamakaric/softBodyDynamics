#pragma once
#include "Vector.h"


class CLineSegment
{
public:
	CVector a,b;

	static int globalID;
	int ID;


	void init() { ID = globalID++; }
	CLineSegment(){init();}
	CLineSegment(const CVector &_a, const CVector &_b) : a(_a), b(_b) {init();}
	double Lenght() const;
	void Set(const CVector &_a, const CVector &_b){ a=_a; b=_b; }
	void Draw();
};