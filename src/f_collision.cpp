#include "f_collision.h"
#include "f_intersection.h"
#include "f_vector.h"
#include "f_distance.h"
#include "f_misc.h"

void BallHitsLSEndPoint(CCircle &_c, const CLineSegment & _ls, CVector &_ballSpeed, CVector lsEndPoint)
{
	CLineSegment displacementLS(lsEndPoint, lsEndPoint + _ballSpeed*_c.r); //_c.r je nebitno, moze i 10000, ovako je sigunrno jedan kraj van kruga
	CVector interPoint[2];

	F::INTERSECTION::GetLineSegmentCircleIntersection(displacementLS, _c, interPoint, false);
	CVector displacement = F::VECTOR::GetVectorFromAToB(interPoint[0], lsEndPoint);
	_c.position += displacement;

	CLine tangent = F::MISC::GetTangentFromPointOnCircle(_c.position, interPoint[0]);
	F::VECTOR::ReflectVectorRayFromLine(_ballSpeed, tangent);
}

void F::COLLISION::BallLineSegmentCollisionResponse( CCircle &_c, const CLineSegment & _ls, CVector &_ballSpeed )
{
	CVector interPoints[2];
	int interCount = F::INTERSECTION::GetLineSegmentCircleIntersection(_ls, _c, interPoints, false);

	if(interCount == 0)
		return;
	
	if(F::INTERSECTION::PointInCircle(_ls.a, _c))
	{
		BallHitsLSEndPoint(_c, _ls, _ballSpeed, _ls.a);
		return;
	}
	
	if(F::INTERSECTION::PointInCircle(_ls.b, _c))
	{
		BallHitsLSEndPoint(_c, _ls, _ballSpeed, _ls.b);
		return;
	}
	
	CVector centerIntersect;

	if(interCount == 2)
		centerIntersect = F::VECTOR::GetVectorBetweenVectors(interPoints[0], interPoints[1]);
	else
		centerIntersect = interPoints[0];

	CVector displacement = F::VECTOR::GetVectorFromAToB(centerIntersect, _c.position);
	double centerToInter = F::DISTANCE::GetDistance(centerIntersect, _c.position);
	double displacementSize = _c.r - centerToInter;
	displacement.Rescale(displacementSize);

	_c.position += displacement;

	CLine line(_ls);

	F::VECTOR::ReflectVectorRayFromLine(_ballSpeed, line);
}


class ParticleLineSegmentCollisionInfo
{
public:
	CVector inter;
	int LSID;
	//CVector 
	
};
/*
void F::COLLISION::ParticleLineSegmentCollisionAnticipationResponseRecursive(CVector &_pos, const CLineSegment & _ls, CVector &_vel )
{
	CLine l(_ls);
	bool aboveLine = F::VECTOR::AboveLine(_pos, l);

	CVector updatedPos = _pos + _vel;

	bool aboveLineAfterUpdate = F::VECTOR::AboveLine(_pos, l);

	//if(aboveLineAfterUpdate == aboveLine)
	//	return;

	if(!_vel.LengthSq())
		return;

	CLineSegment particleMovement(_pos, updatedPos);

	CVector *intersection = new CVector(0,0);
	if(F::INTERSECTION::LineSegmentIntersection2(_ls, particleMovement, intersection))
	{
		double lenghtToLineInVelDirection = F::DISTANCE::GetDistance(_pos, *intersection);
		double particleMovementLenght = particleMovement.Lenght();
		double reflectedPositionLenght = particleMovementLenght - lenghtToLineInVelDirection;
		F::VECTOR::ReflectVectorRayFromLine( _vel, l);




		CVector displacement = _vel;
		displacement.Rescale(reflectedPositionLenght);
		_pos = *intersection + displacement;
	}
}
*/

/*
CVector F::COLLISION::GetDisplacementFromParticleLSCollisionAndFlipVelocity(const CVector &_pos, const CVector &_displacement, const CLineSegment & _ls)
{
	CLine l(_ls);

	CVector updatedPos = _pos + _displacement;

	if(!_displacement.LengthSq())
		return _displacement;

	CLineSegment particleMovement(_pos, updatedPos);

	CVector *intersection = new CVector(0,0);
	if(F::INTERSECTION::LineSegmentIntersection(_ls, particleMovement, intersection))
	{
		_vel*= 0.99;

		double lenghtToLineInVelDirection = F::DISTANCE::GetDistance(_pos, *intersection);
		double particleMovementLenght = particleMovement.Lenght();
		double reflectedPositionLenght = particleMovementLenght - lenghtToLineInVelDirection;
		F::VECTOR::ReflectVectorRayFromLine( _vel, l);

		colided = true;

		CVector fromWenceItcame = F::VECTOR::GetVectorFromAToB(*intersection, _pos);
		//fromWenceItcame.Rescale(0.3);
		//_pos = *intersection + fromWenceItcame; 

		if(*intersection == _ls.a || *intersection == _ls.b)
		{
			int djole = 45;
			__debugbreak();
		}
		delete intersection;

		return CVector(0,0);
	}

	return _displacement;
}*/
/*
void F::COLLISION::ParticleLineSegmentCollisionAnticipationResponseGetDisplacement(CVector &_pos, const CLineSegment & _ls, CVector &_vel )
{
	CLine l(_ls);
	bool aboveLine = F::VECTOR::AboveLine(_pos, l);

	CVector updatedPos = _pos + _vel;

	bool aboveLineAfterUpdate = F::VECTOR::AboveLine(_pos, l);

	//if(aboveLineAfterUpdate == aboveLine)
	//	return;

	if(!_vel.LengthSq())
		return;

	CLineSegment particleMovement(_pos, updatedPos);

	CVector *intersection = new CVector(0,0);
	if(F::INTERSECTION::LineSegmentIntersection2(_ls, particleMovement, intersection))
	{
		double lenghtToLineInVelDirection = F::DISTANCE::GetDistance(_pos, *intersection);
		double particleMovementLenght = particleMovement.Lenght();
		double reflectedPositionLenght = particleMovementLenght - lenghtToLineInVelDirection;
		F::VECTOR::ReflectVectorRayFromLine( _vel, l);

		CVector displacement = _vel;
		displacement.Rescale(reflectedPositionLenght);

		_pos = *intersection; 
	}
}
*/