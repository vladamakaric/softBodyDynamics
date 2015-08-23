#pragma once
#include "particle.h"
#include "ForceGenerator.h"


class SpringForceGenerator : public CForceGenerator
{
public:
	CParticle *p1, *p2;
	double elasticityKoef;
	double dampingKoef;
	double restLenght;
	int workMode; //0 na oba partikla se primenjuje sila, 1 na prvi, 2 drugi
	bool noPush;
	bool edge;

	//SpringForceGenerator(CParticleLS* _pls, int eK, double dK, int rL, int wM = 0): p1(_pls->p1), p2(_pls->p2), elasticityKoef(eK), restLenght(_pls->length), workMode(wM), dampingKoef(dK) { noPush = false; }
	SpringForceGenerator(CParticle *_p1, CParticle *_p2, int eK, double dK, int rL, int wM = 0) : p1(_p1), p2(_p2), elasticityKoef(eK), restLenght(rL), workMode(wM), dampingKoef(dK) { noPush = false; }
	void Update(double timelapse);
	void Draw();
};