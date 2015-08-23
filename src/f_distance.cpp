#include "f_distance.h"
#include "f_intersection.h"
#include "f_misc.h"

double F::DISTANCE::GetLineSegmentPointDistance(const CLineSegment &_ls, const CVector &_p )
{
	CLine ln(_ls);
	double dist = GetLinePointDistance(ln,_p);

	if(F::INTERSECTION::PointProjectionOnLineSegment(_p, _ls))
		return dist;

	return F::MISC::Min(GetDistance(_ls.a,_p), GetDistance(_ls.b,_p));
}

double F::DISTANCE::GetLineSegmentPointDistanceSq(const CLineSegment &_ls, const CVector &_p )
{
	CLine ln(_ls);
	double dist = GetLinePointDistance(ln,_p);

	if(F::INTERSECTION::PointProjectionOnLineSegment(_p, _ls))
		return dist*dist;

	return F::MISC::Min(GetDistanceSq(_ls.a,_p), GetDistanceSq(_ls.b,_p));
}

double F::DISTANCE::GetLinePointDistance( const CLine &_l, const CVector &_p )
{
	return fabs((_l.a*_p.x + _l.b*_p.y + _l.c))/sqrt(_l.a*_l.a + _l.b*_l.b);
}

bool F::DISTANCE::DistBetweenVecsBiggerThan(const CVector &_a,const CVector &_b, double _dist)
{
	return GetDistanceSq(_a, _b) >= _dist*_dist;
}

double F::DISTANCE::GetDistance(const CVector &_v1, const CVector &_v2) {return (_v1 - _v2).Length();}
double F::DISTANCE::GetDistanceSq(const CVector &_v1, const CVector &_v2) {return (_v1 - _v2).LengthSq();}