#pragma once

#include "ParticleForceGenerator.h"
#include "Vector.h"

class GravityPFG : public CParticleForceGenerator
{
public:
	CVector gravity;
	GravityPFG(CVector _gravity) : gravity(_gravity) {}
	void Update(CParticle *particle, double timelapse);	
};

void GravityPFG::Update( CParticle *particle, double timelapse )
{
	//particle->AddForce(gravity * particle->mass);
}
