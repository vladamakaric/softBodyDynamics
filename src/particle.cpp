#include "particle.h"
#include "global.h"
#include "draw.h"

void CParticle::Update( double duration )
{
	if(mass == 0)
		return;

	//position += velocity * duration;
	CVector newAcceleration(acceleration);
	newAcceleration.y -= 10;

	previousVel = velocity;

	newAcceleration += compoundForce / mass;
	velocity += newAcceleration * duration;



	velocity *= currentWorld->currentDragKoef;




	compoundForce.Set(0,0);
}

void CParticle::AddForce( CVector newForce )
{
	compoundForce += newForce;
}

bool CParticle::IsNeighbour( CParticle* _p )
{
	for(int i=0; i<neighbours.size(); i++)
	{
		if(neighbours[i] == _p)
			return true;
	}

	return false;
}

void CParticle::DrawForces()
{
	glColor3f(1,0,0);
	Draw::Line(position, position + compoundForce/5);
}
