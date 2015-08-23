#pragma once
#include "Vector.h"
#include "LineSegment.h"

class CCircle
{
public:
	CCircle(){}
	CCircle(CVector _p, double _r) : r(_r), position(_p) {}

	CCircle(const CLineSegment &_ls) : position((_ls.a + _ls.b)/2), r(_ls.Lenght()) {}
	void Set(const CVector &_pos, double _r) { position = _pos; r=_r; }
	void Set(CLineSegment &_ls) {position=(_ls.a + _ls.b)/2; r=_ls.Lenght();}
	double r;
	CVector position;
};