#include "f_geometry.h"
#include "f_misc.h"
#include "f_vector.h"
#include "f_angle.h"
#include "f_intersection.h"


#define _USE_MATH_DEFINES
#include <math.h>



double F::GEOMETRY::GetBaseOfIsoscelesTriangle( double side, double angleOppositeTheBase )
{
	return 2*side*sin(angleOppositeTheBase/2);
}


static int GetNextConvexPointIndex(CVector leftHandToPrevious, int currentIndx, int prevIndx, const vector<CVector> &_vecArr)
{
	double maxAngle = 0;
	int maxAngleIndx = -1;
	CVector rightHandToNext;
	double curAngle;

	
	for(int i=0; i<_vecArr.size(); i++)
	{
		if(currentIndx == i || prevIndx == i)
			continue;

		rightHandToNext = F::VECTOR::GetVectorFromAToB(_vecArr[currentIndx], _vecArr[i]);
		rightHandToNext.Normalise();
		curAngle = F::ANGLE::GetCWAFromV1toV2(leftHandToPrevious,rightHandToNext);

		if(curAngle>maxAngle)
		{
			maxAngleIndx = i;
			maxAngle = curAngle;
		}
	}

	return maxAngleIndx;
}
	 
void F::GEOMETRY::GetConvexHullFromVectorArray( const vector<CVector> &_vecArr, vector<CVector> &_convexArr )
{
	int vecArrSize = _vecArr.size();
	int firstIndx = F::MISC::GetLowestPointIndx(_vecArr);
	int currIndx = firstIndx;

	_convexArr.push_back(_vecArr[currIndx]);

	CVector leftHand(-1, 0);
	int prevIndx = -1;
	while (1)
	{  
		int nextIndx = GetNextConvexPointIndex(leftHand, currIndx, prevIndx, _vecArr);

		if(nextIndx == firstIndx)
			break;

		prevIndx = currIndx;
		currIndx = nextIndx;

		CVector previousPoint = _convexArr[_convexArr.size()-1];
		CVector currentPoint = _vecArr[currIndx];
		_convexArr.push_back(currentPoint);
		
		leftHand = F::VECTOR::GetVectorFromAToB(currentPoint,previousPoint);
		leftHand.Normalise();
	}
}

double F::GEOMETRY::GetAngleOppositeBaseOfIsescelesTriangle( double base, double side )
{
	double sinOfAngle = (base/2)/side;
	double asinoFAngle = asin(sinOfAngle);
	return 2*asinoFAngle;
}

bool F::GEOMETRY::PolygonClockwise( const vector<CVector> &poly )
{
	const CVector &second = poly[1]; 
	const CVector &first = poly[0]; 
	const CVector &third = poly[2];

	CVector toFirst = F::VECTOR::GetVectorFromAToB(second, first);
	CVector toThird = F::VECTOR::GetVectorFromAToB(second, third);

	CVector bisector = F::VECTOR::GetNormalisedVectorBisector(toThird, toFirst);

	double clockWiseAngleFromFirstToSecondLS = F::ANGLE::GetCWAFromV1toV2(toFirst, toThird);

	bool reflexAngle = clockWiseAngleFromFirstToSecondLS > M_PI;
	bool bisectorInPolygon = F::INTERSECTION::PointInPolygon(second + bisector, poly);

	return (reflexAngle && bisectorInPolygon) || (!reflexAngle && !bisectorInPolygon);
}

double F::GEOMETRY::PolygonArea( const vector<CVector> &poly )
{
	double area = 0;

	int i, j = poly.size()-1;

	for(i=0; i<poly.size(); i++)
	{
		area += (poly[i].x + poly[j].x)*(poly[j].y - poly[i].y); 
		j = i;
	}

	return fabs(area*0.5);
}
