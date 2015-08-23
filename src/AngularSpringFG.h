#pragma once
#include "ForceGenerator.h"
#include "particle.h"


class CAngularSpringFG : public CForceGenerator
{
public:
	CAngularSpringFG(CParticle* _c, CParticle* _rh, CParticle* _lh, double _ek, double _dk );
	void Update(double timelapse);
	CParticle* center;
	CParticle* leftHandP;
	CParticle* rightHandP;
	double dKoef;
	double eKoef;
	double restAngle;
};