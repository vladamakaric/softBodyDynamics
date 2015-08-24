#pragma once

#include <vector>

#include "ParticleForceGenerator.h"

using namespace std;

class CParticleForcesManager
{
public:
	vector<CParticleForceGenerator*> PFGs;
	vector<vector<CParticle*> > particles;

	void AddParticle(CParticle* particle, int PFGIndx);
	void AddPFG(CParticleForceGenerator* newPFG);
	void Update(double timelapse);
};
