#include "BezierCurve.h"
#include "draw.h"
#include "f_vector.h"


void CBezierCurve::Draw()
{
	CVector zni[21];
	double p = 0;
	for(int i=0; i<21; i++)
	{
		zni[i] = GetPointOnCurve(p);
		p += 1.0/20;
	}

	Draw::Line(zni, 21);
}

CVector CBezierCurve::GetPointOnCurve( double t )
{
	double oneMinT = 1 - t;
	return (oneMinT*oneMinT)*points[0] + 2*oneMinT*t*points[1] + t*t*points[2];
}

void CBezierCurve::Set( const CVector &p0, const CVector &p1, const CVector &p2 )
{
	points.clear();
	points.push_back(p0);
	points.push_back(p1);
	points.push_back(p2);
}

double CBezierCurve::CalculateLenghtBySegmentation()
{
	CVector zni[101];
	double p = 0;
	for(int i=0; i<101; i++)
	{
		zni[i] = GetPointOnCurve(p);
		p += 1.0/100;
	}

	double summm = 0; 

	for(int i=0; i<100; i++)
		summm += F::VECTOR::GetVectorFromAToB(zni[i], zni[i+1]).Length();
	
	return summm;
}

double CBezierCurve::CalculateLenghtForQuadratic()
{
	CVector *p0 = &points[0];
	CVector *p1 = &points[1];
	CVector *p2 = &points[2];

	CVector a,b;
	a.x = p0->x - 2*p1->x + p2->x;
	a.y = p0->y - 2*p1->y + p2->y;
	b.x = 2*p1->x - 2*p0->x;
	b.y = 2*p1->y - 2*p0->y;
	float A = 4*(a.x*a.x + a.y*a.y);
	float B = 4*(a.x*b.x + a.y*b.y);
	float C = b.x*b.x + b.y*b.y;

	float Sabc = 2*sqrt(A+B+C);
	float A_2 = sqrt(A);
	float A_32 = 2*A*A_2;
	float C_2 = 2*sqrt(C);
	float BA = B/A_2;

	return ( A_32*Sabc + A_2*B*(Sabc-C_2) + (4*C*A-B*B)*log( (2*A_2+BA+Sabc)/(BA+C_2) ) )/(4*A_32);
}
