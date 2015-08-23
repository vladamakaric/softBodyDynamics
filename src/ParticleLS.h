#pragma once
#include "LineSegment.h"
#include "particle.h"
#include "SpringForceGenerator.h"


class CParticleLS : public CLineSegment
{
public:
	CParticleLS(CParticle *_a, CParticle *_b, SpringForceGenerator* _sfg=0 );
	CParticle *p1,*p2;
	double length;
	SpringForceGenerator* sfg;
};