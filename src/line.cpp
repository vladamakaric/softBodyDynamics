#include "Line.h"
#include "draw.h"
#include "f_misc.h"

void CLine::Draw()
{
	if(b)
		Draw::Line(CVector(0, GetY(0)), CVector(1000, GetY(1000)));
	else
		Draw::Line(CVector(GetX(0), 0), CVector(GetX(1000), 1000));
}

void CLine::Translate( const CVector &_t )
{
	CVector axisIntersect = GetIntersectionOnXorYAxis();
	ThroughPoint(axisIntersect+_t);
}

double CLine::GetX( double _y ) const
{
	return (-b*_y - c)/a;
}

double CLine::GetY( double _x ) const
{
	return (-a*_x - c)/b;
}

CVector CLine::GetIntersectionOnXorYAxis()
{
	if(b)
		return CVector(0, GetY(0));
	else
		return CVector(GetX(0), 0);
}

void CLine::Perp()
{
	F::MISC::Swap(a,b);
	if(abs(a) && abs(b)) a=-a;
}

void CLine::ThroughPoint( const CVector &_p )
{
	c = -a*_p.x - b*_p.y;
}

CLine::CLine( const CLine &_l, const CVector &_p )
{
	a = _l.a;
	b = _l.b;
	ThroughPoint(_p);
}

CLine::CLine( const CVector &_a,const CVector &_b )
{
	Set(_a,_b);
}

CLine::CLine( const CVector &_v )
{
	a = -_v.y;
	b = _v.x ;
	c = 0;
}

CLine::CLine( const CLineSegment &ls )
{
	Set(ls.b, ls.a);
}

void CLine::Set( const CVector &_a, const CVector &_b )
{
	a = _a.y - _b.y;
	b = _b.x - _a.x;
	c = _a.x*_b.y - _b.x*_a.y;
}
