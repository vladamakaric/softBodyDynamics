#include "f_vector.h"
#include "global.h"

bool F::VECTOR::VectorBetweenTwoVectors(CVector &_v, CVector &_v1, CVector &_v2)
{
	CVector a = _v1.Direction();
	CVector b = _v.Direction();
	CVector c = _v2.Direction();

	return a*b>a*c && b*c>a*c;
}

double F::VECTOR::GetLenghtOfVectorProjectionAToB( const CVector& _a,const CVector& _b )
{
	return fabs(((_a*_b)/_b.Length()));
}

double F::VECTOR::GetLenghtSqOfVectorProjectionAToB( const CVector& _a,const CVector& _b )
{
	double dotP = (_a*_b);
	return fabs((dotP*dotP/_b.LengthSq()));
}

CVector F::VECTOR::GetVectorProjectionAToB(const CVector& _a, const CVector& _b)
{
	return _b.Direction() * GetLenghtOfVectorProjectionAToB(_a,_b);
}

CVector F::VECTOR::GetVectorNormalFromAToB(const CVector& _a,const CVector& _b)
{
	return GetVectorFromAToB(GetVectorProjectionAToB(_b, _a), _b);
}

CVector F::VECTOR::GetVectorFromAToB(const CVector& _a, const CVector& _b)
{
	return _b - _a;
}

CVector F::VECTOR::GetVectorProjectionOnLineSegment( const CVector& _v, const CLineSegment& _ls )
{
	CVector LSDirection = GetVectorFromAToB(_ls.a,_ls.b);
	CVector projection = GetVectorProjectionAToB(_v,LSDirection);

	if(_v*LSDirection < 0)
		projection*=-1;

	return projection;
}

CVector F::VECTOR::GetRandVector( double minX, double maxX, double minY, double maxY )
{
	double koef = (rand()%1000 + 1) / 1000.0;

	CVector randVec;

	randVec.x = minX + (maxX - minX) * koef;
	koef = (rand()%1000 + 1) / 1000.0;
	randVec.y = minY + (maxY - minY) * koef;

	return randVec;
}

CVector F::VECTOR::GetVectorBetweenVectors( const CVector& _a,const CVector& _b )
{
	return (_a + _b)/2;
}

void F::VECTOR::BreakVectorIntoComponentsToLine( const CLine &_l, const CVector &_v, CVector &_toLineComponent, CVector &_normalComponent )
{
	_toLineComponent = GetNormalisedVectorOnLine(_l);
	_normalComponent = _toLineComponent.GetPerp();

	double toLineLenght, normalLenght;

	if(_toLineComponent*_v < 0)
		_toLineComponent*=-1;

	if(_normalComponent*_v < 0)
		_normalComponent*=-1;

	toLineLenght = _toLineComponent*_v;
	normalLenght = _normalComponent*_v;

	_normalComponent *= normalLenght;
	_toLineComponent *= toLineLenght;
}

CVector F::VECTOR::GetNormalisedVectorOnLine( const CLine &_l )
{
	if(_l.a==0) return CVector(1,0);
	if(_l.b==0) return CVector(0,1);

	CVector A, B;
	A.y = 0;
	A.x = _l.GetX(A.y);

	B.y = 10;
	B.x = _l.GetX(B.y);

	CVector normVecOnLine = F::VECTOR::GetVectorFromAToB(A,B);
	normVecOnLine.Normalise();
	return normVecOnLine;
}

void F::VECTOR::ReflectVectorRayFromLine( CVector &_ray, const CLine &_l )
{
	CVector toLineC, normToLineC;
	F::VECTOR::BreakVectorIntoComponentsToLine(_l, _ray, toLineC, normToLineC);
	_ray = -normToLineC + toLineC;


	//CVector dj = normToLineC + toLineC;
}

void F::VECTOR::RotateVectorAroundVector( CVector &_v, const CVector &_pointOfRotation, double angle)
{
	CVector tempVec = GetVectorFromAToB(_pointOfRotation, _v);
	tempVec.rotate(angle);
	_v = tempVec + _pointOfRotation;
}

CVector F::VECTOR::GetVectorComponentToLine( const CLine &_l, const CVector &_v )
{
	CVector _toLineComponent = GetNormalisedVectorOnLine(_l);

	if(_toLineComponent*_v < 0)
		_toLineComponent*=-1;

	double toLineLenght = _toLineComponent*_v;
	return _toLineComponent*toLineLenght;
}

bool F::VECTOR::AboveLine( const CVector &_v, const CLine &_c )
{
	if(_c.a == 0 || _c.b != 0)
	{
		if(_v.y > _c.GetY(0))
			return true;
		else 
			return false;
	}

	if(_v.x > _c.GetX(0))
		return true;
	else 
		return false;
}

CVector F::VECTOR::GetNormalisedVectorBisector( const CVector &firstHand, const CVector &secondHand )
{
	return (firstHand.Direction() + secondHand.Direction()).Direction();
}
