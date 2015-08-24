#include "SpringForceGenerator.h"
#include "f_vector.h"
#include "draw.h"

void SpringForceGenerator::Update( double timelapse )
{
	CVector springVecToOther = F::VECTOR::GetVectorFromAToB(p1->position, p2->position);
	double currSpringLenght = springVecToOther.Length();
	springVecToOther.Normalise();

	double springLenghtDiff = currSpringLenght - restLenght;

	if((springLenghtDiff < 0) && noPush)
		return;

	double tempEk = elasticityKoef;
	double tempDk = dampingKoef;

	if(springLenghtDiff>0)
	{
		//dampingKoef = 300;
		//elasticityKoef = 400;
	}

	CVector force = elasticityKoef*springLenghtDiff*springVecToOther;



	//////////////////////////////////////////////////////

	CLine springBearing(springVecToOther);

	CVector p1VelocityComponentToSpring = F::VECTOR::GetVectorComponentToLine(springBearing, p1->velocity);
	CVector p2VelocityComponentToSpring = F::VECTOR::GetVectorComponentToLine(springBearing, p2->velocity);
	CVector dampingForce = F::VECTOR::GetVectorFromAToB(p1VelocityComponentToSpring,p2VelocityComponentToSpring);
	dampingForce*= dampingKoef;

	//////////////////////////////////////////
	if(workMode == 0)
	{
		p1->AddForce(force + dampingForce);
		p2->AddForce(-force - dampingForce);
	//	return;
	}
	
	if(workMode == 1)
		p1->AddForce(force);

	if(workMode == 2)
		p1->AddForce(-force);

	elasticityKoef = tempEk;
	dampingKoef = tempDk;
}

void SpringForceGenerator::Draw()
{
	//Draw::Line(p1->position,p2->position);
}
