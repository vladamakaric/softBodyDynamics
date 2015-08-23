#pragma once
#include "poly2tri.h"
#include "SoftBody.h"

class ComplexSoftBodyGenerator
{
public:
	ComplexSoftBodyGenerator();
	p2t::Point* p;
	std::vector<p2t::Point*> pointsPolyLine;
	std::vector<p2t::Triangle*> triangles;
	std::vector<CVector> vectorPolyLine;
	std::vector<CVector> convexPolyLine;
	p2t::CDT *constrainedDelaney;
	bool inputInProgress;
	CSoftBody* softBody;

	void CreateSoftBodyConstrainedDelanay( double mass, double ek, double dk );
	void CreateSBWithRods( double mass, double ek, double dk, double rek, double rdk );



	void HandleEvents();
	void Render();
};