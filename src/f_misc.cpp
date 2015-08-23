#include "f_misc.h"
#include "f_intersection.h"
#include "f_distance.h"
#include "Line.h"
#include "f_vector.h"

#define _USE_MATH_DEFINES
#include "math.h"

bool F::MISC::ValueBetweenValues(double _v1, double _v2, double _value, double leeway )
{
	double maxValue = _v1;
	double minValue;

	if(maxValue < _v2)
		maxValue = _v2;

	if(maxValue == _v2)
		minValue = _v1;
	else
		minValue = _v2;

	return _value >= minValue-leeway && _value <= maxValue + leeway;
}

void F::MISC::GetLeftRightTopBottomFrom2Vecs(const CVector &_a, const CVector &_b, double &right, double &left,  double &top, double &bottom)
{
	if(_a.x < _b.x)
	{
		left = _a.x;
		right = _b.x;
	}
	else
	{
		right = _a.x;
		left = _b.x;
	}

	if(_a.y < _b.y)
	{
		bottom = _a.y;
		top = _b.y;
	}
	else
	{
		top = _a.y;
		bottom = _b.y;
	}
}

void F::MISC::CalculateCircleFrom3Points(const CVector& _p1, const CVector &_p2,const CVector &_p3, CCircle& _c)
{
	CVector _mp1 = (_p1+_p2)/2; 
	CVector _mp2 = (_p2+_p3)/2;

	CLine a(_p1,_p2);
	CLine b(_p3,_p2);
	a.Perp();
	b.Perp();
	a.ThroughPoint(_mp1);
	b.ThroughPoint(_mp2);

	_c.position = F::INTERSECTION::GetLineIntersection(a,b);
	_c.r = F::DISTANCE::GetDistance(_p1, _c.position);
}

bool F::MISC::AddIntersection(double _upper, double _lower, double _y)
{
	if( _upper - _y < 0.0001)
		return false;

	if(_y - _lower < 0.0001)
		return true;

	return true;
}

bool F::MISC::IsCircleOutOfMap(int _HR, const CVector &_position, int _mHeight, int _mWidth , int _border)
{
	return _position.x + _HR + _border > _mWidth || _position.x - _HR - _border < 0 || _position.y + _HR + _border > _mHeight ||  _position.y - _HR - _border < 0;
}

void F::MISC::GetLeftRightTopBottomFromLineSegment(const CLineSegment &_ls, double &right, double &left,  double &top, double &bottom)
{
	GetLeftRightTopBottomFrom2Vecs(_ls.a,_ls.a, right,left,top,bottom);
}

CLine F::MISC::GetTangentFromPointOnCircle( const CVector &_circleCenter, const CVector &_pointOnCircle )
{
	CVector toPoint = F::VECTOR::GetVectorFromAToB(_circleCenter, _pointOnCircle);
	toPoint.Perp();

	return CLine(_pointOnCircle + toPoint, _pointOnCircle);
}

int F::MISC::GetLowestPointIndx( const vector<CVector> &_points )
{
	double minY = _points[0].y;
	int indx = 0;
	for(int i=0; i<_points.size(); i++)
	{
		
		if(_points[i].y < minY)
		{
			minY = _points[i].y;
			indx = i;
		}
	}

	return indx;
}

bool F::MISC::LineSegmentPartOfVectorArray(const CLineSegment &_ls, const vector<CVector> &_vecArr)
{
	for(int i=0; i < _vecArr.size(); i++)
	{
		CVector a = _vecArr[i];
		CVector b = _vecArr[(i+1)%_vecArr.size()];

		if ((a == _ls.a && b == _ls.b) || (a == _ls.b && b == _ls.a))
			return true;
	}

	return false;
}

double F::MISC::ToRadians( double degrees )
{
	return (degrees/360)*2*M_PI;
}

double F::MISC::ToDegrees( double radians )
{
	return radians/(2*M_PI)*360;
}
