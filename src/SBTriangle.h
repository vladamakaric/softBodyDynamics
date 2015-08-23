#pragma once
#include "Vector.h"
#include "particle.h"

class SBTriangle
{
public:
	SBTriangle(CVector a, CVector b, CVector c)
	{
		points[0] = a;
		points[1] = b;
		points[2] = c;

		particles[0] = 0;
		particles[1] = 0;
		particles[2] = 0;
	}

	CVector points[3];

	CParticle* particles[3];
};