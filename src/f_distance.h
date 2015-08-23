#pragma  once
#include "LineSegment.h"
#include "Vector.h"
#include "Line.h"

namespace F
{
	namespace DISTANCE
	{
		double GetLineSegmentPointDistance(const CLineSegment &_ls,const CVector &_p);
		double GetLineSegmentPointDistanceSq(const CLineSegment &_ls,const CVector &_p);
		double GetLinePointDistance(const CLine &_l, const CVector &_p);
		double GetDistance(const CVector &_v1, const CVector &_v2); 
		double GetDistanceSq(const CVector &_v1, const CVector &_v2); 
		bool DistBetweenVecsBiggerThan(const CVector &_a,const CVector &_b, double _dist);
	}
}

