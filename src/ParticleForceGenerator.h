#pragma once

#include "particle.h"

class CParticleForceGenerator
{
public:
	virtual void Update(CParticle *particle, double timelapse) = 0;
};