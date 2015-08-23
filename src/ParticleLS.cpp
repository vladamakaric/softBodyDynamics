#include "ParticleLS.h"
#include "f_distance.h"

CParticleLS::CParticleLS( CParticle *_a, CParticle *_b, SpringForceGenerator* _sfg )
{
	a = _a->position;
	b = _b->position;
	p1 = _a;
	p2 = _b;

	length = F::DISTANCE::GetDistance(a,b);
	sfg = _sfg;
}
