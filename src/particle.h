#ifndef PARTICLE_H
#define PARTICLE_H

#include "physicalentity.h"
#include <vector>

using namespace std;


class CParticle : public CPhysicalEntity
{
public:
	CParticle(double m, CVector pos) : compoundForce(0, 0), velocity(0, 0), previousVel(0, 0), acceleration(0, 0), mass(m), visible(1) { position = pos; radius = mass*0.8; }
	void Update(double duration);
	void AddForce(CVector newForce);
	void AddNeighbour(CParticle *n) { neighbours.push_back(n); }
	bool IsNeighbour(CParticle* _p);
	void DrawForces();

	CVector compoundForce;
	CVector velocity;
	CVector acceleration;
	CVector previousVel;
	
	vector<CParticle*> neighbours;

	
	bool visible;
	int SBEIndx; //softBodyEnvelopeIndex

	double radius;
	double mass;
};

#endif
