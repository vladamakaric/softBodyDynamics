/*#include "AngularSpringFG.h"
#include "f_angle.h"
#include "f_vector.h"
#include "f_distance.h"
#include "f_geometry.h"



static bool BiggerUpdCWA(CVector leftHandPrev, CVector rightHandPrev, CVector leftHandUpd, CVector rightHandUpd)
{
	return F::ANGLE::GetCWAFromV1toV2(leftHandUpd, rightHandUpd) > F::ANGLE::GetCWAFromV1toV2(leftHandPrev, rightHandPrev);
}

CAngularSpringFG::CAngularSpringFG(CParticle* _c, CParticle* _rh, CParticle* _lh, double _ek , double _dk ) : center(_c), leftHandP(_lh), rightHandP(_rh), eKoef(_ek), dKoef(_dk)
{
	CVector leftHandVec = F::VECTOR::GetVectorFromAToB(center->position, leftHandP->position);
	CVector rightHandVec = F::VECTOR::GetVectorFromAToB(center->position, rightHandP->position);
	restAngle = F::ANGLE::GetCWAFromV1toV2(leftHandVec, rightHandVec);
}

void CAngularSpringFG::Update( double timelapse )
{
	CVector leftHandVec = F::VECTOR::GetVectorFromAToB(center->position, leftHandP->position);
	CVector rightHandVec = F::VECTOR::GetVectorFromAToB(center->position, rightHandP->position);
	double leftHandHRadius = leftHandVec.Length();
	double rightHandHRadius = rightHandVec.Length();
	double currentAngle = F::ANGLE::GetCWAFromV1toV2(leftHandVec, rightHandVec);
	double dAngle = currentAngle - restAngle;

	CVector lHNormalForceDecreasingTheCWA = leftHandVec.GetPerp();
	CVector rHNormalForceDecreasingTheCWA = rightHandVec.GetPerp();
	lHNormalForceDecreasingTheCWA.Normalise();
	rHNormalForceDecreasingTheCWA.Normalise();


	CVector tempR = rightHandVec;
	tempR.rotate(PI/18);
	CVector rForce = F::VECTOR::GetVectorFromAToB(tempR, rightHandVec)*rightHandP->mass;
	rightHandP->AddForce(rForce);


	/*
	CVector rightTotalForce = rHNormalForceDecreasingTheCWA*500;
	CVector leftTotalForce = lHNormalForceDecreasingTheCWA*500;

	rightTotalForce/=rightHandP->mass;
	leftTotalForce/=leftHandP->mass;

	double rTa = rightTotalForce.Length();
	double lTa = leftTotalForce.Length();

	double leftDAngle = PI/2 - F::GEOMETRY::GetAngleOppositeBaseOfIsescelesTriangle(lTa, leftHandVec.Length());
	double rightDAngle = PI/2 - F::GEOMETRY::GetAngleOppositeBaseOfIsescelesTriangle(rTa, rightHandVec.Length());

	//--rightHandP->AddForce(rightTotalForce);
	//--leftHandP->AddForce(leftTotalForce);

	CVector tempRightForce = rightTotalForce;
	CVector tempLeftForce = leftTotalForce;

	tempRightForce.rotate(rightDAngle);

	if(tempRightForce*rightHandVec < 0)
	{
		tempRightForce = rightTotalForce;
		tempRightForce.rotate(-rightDAngle);
	}

	tempLeftForce.rotate(leftDAngle);

	if(tempLeftForce*leftHandVec < 0)
	{
		tempLeftForce = leftTotalForce;
		tempLeftForce.rotate(-leftDAngle);
	}

	leftHandP->AddForce(tempLeftForce*leftHandP->mass);
	rightHandP->AddForce(tempRightForce*rightHandP->mass);
	//GetAngleOppositeBaseOfIsescelesTriangle( double base, double side )
}
*/
//zarotirati manuelno vektor za jedanmali ugao i onda naci vektor pomeraja da nebi doslo do curenja sila
//mozda obrisati onu interpolaciju da bi lakse bilo racunati unapred putanju
//takodje osim ugla se zajebavati sa spoljasnjim springovima

#include "AngularSpringFG.h"
#include "f_angle.h"
#include "f_vector.h"
#include "f_distance.h"
#include "f_geometry.h"

#define PI 3.14159265

static bool BiggerUpdCWA(CVector leftHandPrev, CVector rightHandPrev, CVector leftHandUpd, CVector rightHandUpd)
{
	return F::ANGLE::GetCWAFromV1toV2(leftHandUpd, rightHandUpd) > F::ANGLE::GetCWAFromV1toV2(leftHandPrev, rightHandPrev);
}

CAngularSpringFG::CAngularSpringFG(CParticle* _c, CParticle* _rh, CParticle* _lh, double _ek , double _dk ) : center(_c), leftHandP(_lh), rightHandP(_rh), eKoef(_ek), dKoef(_dk)
{
	CVector leftHandVec = F::VECTOR::GetVectorFromAToB(center->position, leftHandP->position);
	CVector rightHandVec = F::VECTOR::GetVectorFromAToB(center->position, rightHandP->position);
	restAngle = F::ANGLE::GetCWAFromV1toV2(leftHandVec, rightHandVec);
}

void CAngularSpringFG::Update( double timelapse )
{
	CVector leftHandVec = F::VECTOR::GetVectorFromAToB(center->position + center->velocity*timelapse, leftHandP->position);
	CVector rightHandVec = F::VECTOR::GetVectorFromAToB(center->position, rightHandP->position);
	double leftHandHRadius = leftHandVec.Length();
	double rightHandHRadius = rightHandVec.Length();
	double currentAngle = F::ANGLE::GetCWAFromV1toV2(leftHandVec, rightHandVec);
	double dAngle = currentAngle - restAngle;

	CVector lHNormalForceDecreasingTheCWA = leftHandVec.GetPerp();
	CVector rHNormalForceDecreasingTheCWA = rightHandVec.GetPerp();
	lHNormalForceDecreasingTheCWA.Normalise();
	rHNormalForceDecreasingTheCWA.Normalise();

	double angularSpeed = dAngle/2;
	bool rightHandToBeDecresed = false;
	bool leftHandToBeDecresed = false;

	if(BiggerUpdCWA(leftHandVec, rightHandVec, leftHandVec, rightHandVec + rHNormalForceDecreasingTheCWA))
		rHNormalForceDecreasingTheCWA*=-1;

	if(BiggerUpdCWA(leftHandVec, rightHandVec, leftHandVec + lHNormalForceDecreasingTheCWA, rightHandVec))
		lHNormalForceDecreasingTheCWA*=-1;

	rHNormalForceDecreasingTheCWA *= angularSpeed * 100 * eKoef; 
	lHNormalForceDecreasingTheCWA *= angularSpeed * 100 * eKoef;

	////////////////////////////////////////////

	CLine rightHandNormal(rHNormalForceDecreasingTheCWA);
	CLine leftHandNormal(lHNormalForceDecreasingTheCWA);

	CVector rightHandNormalVelocity = F::VECTOR::GetVectorComponentToLine(rightHandNormal, rightHandP->velocity);
	CVector leftHandNormalVelocity = F::VECTOR::GetVectorComponentToLine(leftHandNormal, leftHandP->velocity);

	CVector leftHandNormalInrightWay = F::VECTOR::GetVectorComponentToLine(rightHandNormal, leftHandNormalVelocity).Direction()*leftHandNormalVelocity.Length();
	CVector rightHandNormalInLeftWay = F::VECTOR::GetVectorComponentToLine(leftHandNormal, rightHandNormalVelocity).Direction()*rightHandNormalVelocity.Length();

	CVector RFORCE = rHNormalForceDecreasingTheCWA; //- (F::VECTOR::GetVectorComponentToLine(rightHandNormal,rightHandNormalVelocity - leftHandNormalVelocity))*dKoef;
	CVector LFORCE = lHNormalForceDecreasingTheCWA; //- (F::VECTOR::GetVectorComponentToLine(leftHandNormal,leftHandNormalVelocity - rightHandNormalVelocity))*dKoef;

	center->AddForce(-RFORCE - LFORCE);
	rightHandP->AddForce(RFORCE);
	leftHandP->AddForce(LFORCE);
}
