#pragma once

#include "Circle.h"
#include "LineSegment.h"

namespace F
{
	namespace COLLISION
	{
		void BallLineSegmentCollisionResponse( CCircle &_c, const CLineSegment & _ls, CVector &_ballSpeed);
		//void ParticleLineSegmentCollisionAnticipationResponse(CVector &_pos, const CLineSegment & _ls, CVector &_vel);
		//CVector GetDisplacementFromParticleLSCollisionAndFlipVelocity(CVector &_pos, const CVector &_displacement, const CLineSegment & _ls, CVector &_vel, bool &colided);
	}
}