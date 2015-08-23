#pragma once
#include "Vector.h"
#include <vector>

using namespace std;

namespace F
{
	namespace GEOMETRY
	{
		double GetAngleOppositeBaseOfIsescelesTriangle(double base, double side);
		double GetBaseOfIsoscelesTriangle(double side, double angleOppositeTheBase);
		double PolygonArea(const vector<CVector> &poly);

		void GetConvexHullFromVectorArray( const vector<CVector> &_vecArr, vector<CVector> &_convexArr );
		bool PolygonClockwise(const vector<CVector> &poly);

	}
}