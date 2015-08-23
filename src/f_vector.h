#pragma once
#include "Vector.h"
#include "LineSegment.h"
#include "Line.h"

namespace F
{
	namespace VECTOR
	{

		void ReflectVectorRayFromLine(CVector &_ray, const CLine  &_l);

		void BreakVectorIntoComponentsToLine(const CLine &_l, const CVector &_v, CVector &_toLineComponent, CVector &_normalComponent );
		CVector GetVectorFromAToB(const CVector& _a,const CVector& _b);
		CVector GetVectorProjectionAToB(const CVector& _a,const CVector& _b);
		CVector GetVectorNormalFromAToB(const CVector& _a,const CVector& _b);
		CVector GetVectorProjectionOnLineSegment(const CVector& _v, const CLineSegment& _ls);
		CVector GetVectorComponentToLine(const CLine &_l, const CVector &_v);
		CVector GetNormalisedVectorOnLine(const CLine &_l);
		CVector GetNormalisedVectorBisector(const CVector &firstHand, const CVector &secondHand); //order of hands is irrelevant

		void RotateVectorAroundVector(CVector &_v, const CVector &_pointOfRotation, double angle);
		bool AboveLine( const CVector &_v, const CLine &_c );


		CVector GetRandVector(double minX, double maxX, double minY, double maxY);
		CVector GetVectorBetweenVectors(const CVector& _a,const CVector& _b);

		double GetLenghtOfVectorProjectionAToB(const CVector& _a,const CVector& _b);
		double GetLenghtSqOfVectorProjectionAToB(const CVector& _a,const CVector& _b);
		bool VectorBetweenTwoVectors(CVector &_v, CVector &_v1, CVector &_v2);
	}
}