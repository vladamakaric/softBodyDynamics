#pragma once

#include <vector>
#include "Vector.h"

using namespace std;

class CBezierCurve
{
public:
	void Set(const CVector &p0, const CVector &p1, const CVector &p2);
	CVector GetPointOnCurve(double t);
	double CalculateLenghtForQuadratic();
	double CalculateLenghtBySegmentation();
	vector<CVector> points; 
	void Draw();
};