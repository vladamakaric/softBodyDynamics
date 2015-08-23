#pragma once
#include "Vector.h"

namespace F
{
	namespace ANGLE
	{
		double GetSmallerAngleBetweenTwoVectors(const CVector &_a, const CVector &_b);
		double GetAngleBetweenTwoSidesOfATriangle(double _s1, double _s2, double _s3);
		double GetCWAFromV1toV2(const CVector &_v1, const CVector &_v2);
		double GetCCWAFromV1toV2(const CVector &_v1, const CVector &_v2);
		double DegToRad(double _angle);
		double RadToDeg(double _angle);
	}
}