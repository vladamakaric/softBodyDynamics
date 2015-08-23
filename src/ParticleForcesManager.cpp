#include "ParticleForcesManager.h"

void CParticleForcesManager::AddParticle( CParticle* particle, int PFGIndx )
{
	if(particles.size() == PFGIndx)
	{
		particles.push_back(vector<CParticle*>());
	}

	particles[PFGIndx].push_back(particle);	
}

void CParticleForcesManager::AddPFG( CParticleForceGenerator* newPFG )
{
	PFGs.push_back(newPFG);
}

void CParticleForcesManager::Update( double timelapse )
{
	for(int i=0; i<PFGs.size(); i++)
	{
	//	if(particles[i].size())

		if(particles.size())
		for(int j=0; j<particles[i].size(); j++)
		{
			PFGs[i]->Update(particles[i][j], timelapse);
		}
	}
}
