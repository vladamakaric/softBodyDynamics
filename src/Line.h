#pragma once
#include "Vector.h"
#include "LineSegment.h"

class CLine
{
public:
	double a,b,c;
	CLine(){}
	CLine(const CLineSegment &ls);

	CLine(const CVector &_v);

	CLine(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

	CLine(const CVector &_a,const CVector &_b);

	void Set(const CVector &_a, const CVector &_b);

	//Line through point
	CLine(const CLine &_l, const CVector &_p);

	void Perp();

	//Adjust line to go through point
	void ThroughPoint( const CVector &_p);
	

	CVector GetIntersectionOnXorYAxis();
	
	void Translate(const CVector &_t);

	double GetX(double _y) const;

	double GetY(double _x) const;

	void Draw();
};

