#include "SoftBody.h"
#include "global.h"
#include "SpringForceGenerator.h"
#include "f_distance.h"
#include "f_geometry.h"
#include "f_intersection.h"
#include "f_vector.h"
#include "f_misc.h"
#include "f_angle.h"
#include "draw.h"
#include "AngularSpringFG.h"
#include "BezierCurve.h"
#include <set>

#define _USE_MATH_DEFINES
#include "math.h"

CSoftBody::CSoftBody(const vector<CVector> &_refEnv, double _mass, double _cMass, double _ek, double _dk) : envolope(_refEnv), envelopeSize(_refEnv.size()), mass(_mass), centerMass(_cMass), eKoef(_ek), dKoef(_dk)
{
	clockWiseEnvolope = F::GEOMETRY::PolygonClockwise(envolope);
	envolopeInnerAngles = new double[envelopeSize];
	visibleParticles = new CParticle*[envelopeSize];
	visibleParticleLS = new CParticleLS*[envelopeSize];

	connectionMatrix = new ENVPC*[envelopeSize];
	for(int i=0; i<envelopeSize; i++)
		connectionMatrix[i] = new ENVPC[envelopeSize];
	
	GenerateEnvolopeParticles();
	GenerateSpringEnvelope();
	CalculateInnerAngles();
	DeterminePossibleConnections();
	ConnectReflexAngleParticles();
	GenerateConnectionsWithMinimalAngleConstraint(M_PI/10);
}

void CSoftBody::GenerateEnvolopeParticles()
{
	CParticle * current;
	for(int i=0; i<envelopeSize; i++)
	{
		current = new CParticle(mass, envolope[i]);
		current->SBEIndx = i;
		visibleParticles[i] = current;
		currentWorld->AddParticle(current);
	}
}

void CSoftBody::GenerateSpringEnvelope()
{
	CParticle *current;
	CParticle *next;

	for(int i=0; i<envelopeSize; i++)
	{
		current = visibleParticles[i];
		next = visibleParticles[(i+1)%envelopeSize];

		CreateConnection(current, next, ENVPC::ENVELOPE);
	}
}

void CSoftBody::CalculateInnerAngles()
{
	CParticle *current;
	CParticle *lower;
	CParticle *upper;

	double (*AngleCalculatingFunctionPointer)(const CVector&, const CVector&);

	if(clockWiseEnvolope)
		AngleCalculatingFunctionPointer = &F::ANGLE::GetCCWAFromV1toV2;
	else
		AngleCalculatingFunctionPointer = &F::ANGLE::GetCWAFromV1toV2;

	for(int i=0; i<envelopeSize; i++)
	{
		current = visibleParticles[i];
		upper = visibleParticles[(i+1)%envelopeSize];
		lower = visibleParticles[((i-1) + envelopeSize)%envelopeSize];


		CVector toLower = F::VECTOR::GetVectorFromAToB(current->position, lower->position);
		CVector toUpper = F::VECTOR::GetVectorFromAToB(current->position, upper->position);

		envolopeInnerAngles[i] =  (*AngleCalculatingFunctionPointer)(toLower, toUpper);
	}

	//for(int i=0; i<envelopeSize; i++)
	//	printf("%d \n" ,(int) F::MISC::ToDegrees(envolopeInnerAngles[i]));
}

void CSoftBody::DeterminePossibleConnections()
{
	for(int i=0; i< envelopeSize; i++)
	{
		for(int j=i+2; j < envelopeSize; j++)
		{
			if(Connected(i,j)) continue;
			if(ConnectionIntersectsEnvelope(i,j)) continue;

			possibleConnections.push_back(CParticlePair(visibleParticles[i], visibleParticles[j]));
		}
	}
}

void CSoftBody::GenerateCenterOfMassToAllParticlesSprings()
{
	CVector sum(0,0);

	for(int i=0; i<envelopeSize; i++)
		sum += visibleParticles[i]->position;

	sum /= envelopeSize;

	centerOfMassP = new CParticle(centerMass,  sum);
	centerOfMassP->visible = false;
	currentWorld->AddParticle(centerOfMassP);

	CParticleLS* pls;
	for(int i=0; i<envelopeSize; i++)
	{
		pls = new CParticleLS(centerOfMassP, visibleParticles[i]);
		helperParticleLS.push_back(pls);
		currentWorld->AddForceGenerator(new SpringForceGenerator(pls->p1, pls->p2, eKoef, dKoef, pls->length));
	}
}

void CSoftBody::Update()
{
	for(int i=0; i < helperParticleLS.size(); i++)
	{
		helperParticleLS[i]->a = helperParticleLS[i]->p1->position;
		helperParticleLS[i]->b = helperParticleLS[i]->p2->position;
	}

	for(int i=0; i < envelopeSize; i++)
	{
		visibleParticleLS[i]->a = visibleParticleLS[i]->p1->position;
		visibleParticleLS[i]->b = visibleParticleLS[i]->p2->position;
	}
}

static CParticle* GetParticleWithPosition(const CVector& _pos, const vector<CParticle*> &_particles )
{
	for(int i=0; i<_particles.size(); i++)
	{
		if(_pos == _particles[i]->position)
			return _particles[i];
	}

	return 0;
}

void CSoftBody::GenerateConvexHullSprings()
{
	/*vector<CVector> convexHull;
	F::GEOMETRY::GetConvexHullFromVectorArray(envolope, convexHull);

	for(int i=0; i<convexHull.size(); i++)
	{
		CVector a = convexHull[i];
		CVector b = convexHull[(i+1)%convexHull.size()];

		CLineSegment ls(a,b);

		if(!F::MISC::LineSegmentPartOfVectorArray(ls, envolope))
		{
			CParticle *p1 = GetParticleWithPosition(a, visibleParticles);
			CParticle *p2 = GetParticleWithPosition(b, visibleParticles);

			CParticleLS* pls = new CParticleLS(p1, p2);
			helperParticleLS.push_back(pls);
			currentWorld->AddForceGenerator(new SpringForceGenerator(pls->p1, pls->p2, eKoef/15, dKoef, pls->length));
		}
	}*/
}

void CSoftBody::GenerateAngleSprings()
{
	CParticle *p1, *p2; 
	for(int i=0; i<envelopeSize; i++)
	{
		p1 = visibleParticles[i];
		p2 = visibleParticles[(i+1)%envelopeSize];
		currentWorld->AddForceGenerator(new CAngularSpringFG(centerOfMassP, p1, p2, 300, 130));
	}

	//p2 = visibleParticles[((i-1)+visibleParticles.size())%visibleParticles.size()  ];
}

void CSoftBody::DrawBezierFromSpring( SpringForceGenerator *_sfg )
{
	double lenghtDiff = F::DISTANCE::GetDistance(_sfg->p1->position, _sfg->p2->position) - _sfg->restLenght;

	bool bigger = lenghtDiff > 0;

	lenghtDiff = fabs(lenghtDiff);

	CVector middleVec = (_sfg->p1->position + _sfg->p2->position)/2;

	CVector normalVec = F::VECTOR::GetVectorFromAToB(_sfg->p1->position,_sfg->p2->position).GetPerp();
	normalVec.Rescale(lenghtDiff);

	CVector middlePointBezier = middleVec + normalVec;

	CVector middlePointDirection = middleVec + normalVec.Direction();

	if(PointInSoftBody(middlePointDirection))
	{
		if(!bigger) middlePointBezier = middleVec - normalVec;
	}
	else
		if(bigger) middlePointBezier = middleVec - normalVec;

	CBezierCurve bz;
	bz.Set(_sfg->p1->position, middlePointBezier, _sfg->p2->position);
	bz.Draw();
}

bool CSoftBody::PointInSoftBody( const CVector &p )
{
	vector<CVector> polygon; 

	for(int i=0; i<envelopeSize; i++)
		polygon.push_back(visibleParticles[i]->position);

	return F::INTERSECTION::PointInPolygon(p,polygon);
}

void CSoftBody::AddConnectionToMatrix( CParticle* a, CParticle *b, int type, SpringForceGenerator* sfg, CParticleLS *pls)
{
	connectionMatrix[a->SBEIndx][b->SBEIndx].MakeConnection(type, sfg, pls);
	connectionMatrix[b->SBEIndx][a->SBEIndx].MakeConnection(type, sfg, pls);
}

class CPotentialConnection
{
public:
	CPotentialConnection(CParticle* _a, CParticle* _b, double smA, int t) : a(_a), b(_b), smallestAngle(smA), type(t) {}
	friend bool operator<(const CPotentialConnection& a, const CPotentialConnection& b)
	{
		return a.smallestAngle > b.smallestAngle;
	}

	CParticle* a;
	CParticle* b;
	double smallestAngle;
	int type; 
};

void CSoftBody::MakeInnerConnectionsWithMinimumAngle( double minAngle )
{
	std::set<CPotentialConnection> potConnections;
	double smallestAngle;

	for(int i=0; i< envelopeSize; i++)
	{
		for(int j=i+2; j < envelopeSize; j++)
		{
			if(Connected(i,j)) continue;

			if(ConnectionIntersectsEnvelope(i,j)) continue;

			CVector middlePointOfConnection = (envolope[i] + envolope[j])/2;
			bool connectionInside = F::INTERSECTION::PointInPolygon(middlePointOfConnection, envolope);

			smallestAngle = GetSmallestAngleCreatedWithConnection(visibleParticles[i], visibleParticles[j]);

			if(minAngle>smallestAngle) continue;

			potConnections.insert(CPotentialConnection(visibleParticles[i], visibleParticles[j], smallestAngle, connectionInside ? ENVPC::INSIDE : ENVPC::OUTSIDE));

			/*
			if(connectionInside)
			CreateConnection(visibleParticles[i], visibleParticles[j], ENVPC::INSIDE);
			else
				CreateConnection(visibleParticles[i], visibleParticles[j], ENVPC::OUTSIDE, eKoef/5);
				*/
			//printf( " [ %d ][ %d ]  \n", i, j);
		}
	}

	CParticle *a,*b;
	std::set<CPotentialConnection>::iterator it;

	for( it = potConnections.begin(); it != potConnections.end(); it++ ) 
	{
		a = it->a;
		b = it->b;

		if(envolopeInnerAngles[a->SBEIndx] < M_PI || envolopeInnerAngles[b->SBEIndx] < M_PI)
		{
			smallestAngle = GetSmallestAngleCreatedWithConnection(a, b);
			if(minAngle>smallestAngle) continue;
		}

		if(ConnectionIntersectsHelperConnections(a,b)) continue;

		CreateConnection(a,b, it->type );
	}

	//potConnections.size();
}

bool CSoftBody::ConnectionIntersectsEnvelope( int aIndx, int bIndx )
{
	CLineSegment connection(envolope[aIndx], envolope[bIndx]);
	int nextIndx;

	for(int i=0; i<envelopeSize; i++)
	{
		nextIndx = (i+1)%envelopeSize;

		if(nextIndx == aIndx || nextIndx == bIndx || i==aIndx || i==bIndx)
			continue;

		if(F::INTERSECTION::LineSegmentIntersection(connection, *connectionMatrix[i][nextIndx].pls))
			return true;
	}

	return false;
}

bool CSoftBody::ConnectionIntersectsHelperConnections( CParticle* a, CParticle* b )
{
	CLineSegment connection(a->position, b->position);
	int nextIndx;

	for(int i=0; i<helperParticleLS.size(); i++)
	{
		if(a == helperParticleLS[i]->p1 || a == helperParticleLS[i]->p2 ||
			b == helperParticleLS[i]->p1 || b == helperParticleLS[i]->p2)
			continue;

		if(F::INTERSECTION::LineSegmentIntersection(connection, *helperParticleLS[i]))
			return true;
	}

	return false;
}

void CSoftBody::CreateConnection( CParticle* a, CParticle *b, int type, double eK /*= -1*/, double dK /*= -1*/ )
{
	if(eK < 0) eK = eKoef;
	if(dK < 0) dK = dKoef;

	CParticleLS *pls = new CParticleLS(a, b);
	SpringForceGenerator* sfg = new SpringForceGenerator(pls->p1, pls->p2, eK, dK, pls->length);
	pls->sfg = sfg;

	if(type == ENVPC::ENVELOPE)
		visibleParticleLS[a->SBEIndx] = pls;
	else
		helperParticleLS.push_back(pls);
	
	a->AddNeighbour(b);
	b->AddNeighbour(a);
	AddConnectionToMatrix(a, b, type, sfg, pls);
	currentWorld->AddForceGenerator(sfg);
}

double CSoftBody::GetSmallestAngleCreatedWithConnection( CParticle* a, CParticle *b )
{
	double curAngle;
	double minAngle = M_PI;

	CVector toB = F::VECTOR::GetVectorFromAToB(a->position, b->position);
	CVector toA = -toB;

	for(int i=0; i<a->neighbours.size(); i++)
	{
		CVector toNeighbour = F::VECTOR::GetVectorFromAToB(a->position, a->neighbours[i]->position);
		curAngle = F::ANGLE::GetSmallerAngleBetweenTwoVectors(toNeighbour, toB);

		if(curAngle<minAngle)
			minAngle = curAngle;
	}

	for(int i=0; i<b->neighbours.size(); i++)
	{
		CVector toNeighbour = F::VECTOR::GetVectorFromAToB(b->position, b->neighbours[i]->position);
		curAngle = F::ANGLE::GetSmallerAngleBetweenTwoVectors(toNeighbour, toA);

		if(curAngle<minAngle)
			minAngle = curAngle;
	}

	return minAngle;
}

void CSoftBody::Draw()
{
	glLineWidth(2);
	glColor3f(0,1,0);

	for(int i=0; i < envelopeSize; i++)
	{
		//visibleParticleLS[i]->Draw();

		SpringForceGenerator* sfg = visibleParticleLS[i]->sfg;

		DrawBezierFromSpring(sfg);
	}

	glLineWidth(1);
	glColor4f(0,1,1,0.5);

	for(int i=0; i < helperParticleLS.size(); i++)
		helperParticleLS[i]->Draw();


	vector<CVector> polygon; 

	for(int i=0; i<envelopeSize; i++)
		polygon.push_back(visibleParticles[i]->position);

	double area = F::GEOMETRY::PolygonArea(polygon);
	printf("Polaria: %f, \n", area);
}

void CSoftBody::ConnectReflexAngleParticles()
{
	std::set<CPotentialConnection> potReflexAngleSortedConnections;
	double currentSmallestAngle;
	CParticle *a,*b;

	list<CParticlePair>::iterator it = possibleConnections.begin();
	for(; it != possibleConnections.end(); it++)
	{
		a = it->first;
		b = it->second;

		if(envolopeInnerAngles[a->SBEIndx] > M_PI && envolopeInnerAngles[b->SBEIndx] > M_PI )
		{
			currentSmallestAngle = GetSmallestAngleCreatedWithConnection(a, b);

			CVector middlePoint = (a->position + b->position)/2;
			int conType = F::INTERSECTION::PointInPolygon(middlePoint, envolope);
			potReflexAngleSortedConnections.insert( CPotentialConnection( a,b, currentSmallestAngle, conType) );
		}
	}
	
	std::set<CPotentialConnection>::iterator it2 = potReflexAngleSortedConnections.begin();
	for(; it2 != potReflexAngleSortedConnections.end(); it2++ ) 
	{
		a = it2->a;
		b = it2->b;

		if(ConnectionIntersectsHelperConnections(a,b)) 
		{
			MarkConnectionAsImpossible(a,b);		
			continue;
		}

		CreateConnection(a,b, it2->type );
	}
}

void CSoftBody::UpdatePossibleConnections()
{
	list<CParticlePair>::iterator it = possibleConnections.begin();
	for(; it != possibleConnections.end(); )
	{
		if(ConnectionFree(it->first, it->second))
			it++;
		else
			it = possibleConnections.erase(it);
	}
}

void CSoftBody::GenerateConnectionsWithMinimalAngleConstraint( double minAngle )
{
	CParticle *a,*b;
	std::set<CPotentialConnection> potOuterConnections;
	double currentSmallestAngle;

	list<CParticlePair>::iterator it = possibleConnections.begin();
	for(; it != possibleConnections.end(); it++)
	{
		a = it->first;
		b = it->second;

		CVector middlePoint = (a->position + b->position)/2;

		int type = F::INTERSECTION::PointInPolygon(middlePoint, envolope);

		currentSmallestAngle = GetSmallestAngleCreatedWithConnection(a, b);
		
		bool reflexAngle = envolopeInnerAngles[a->SBEIndx] > M_PI || envolopeInnerAngles[b->SBEIndx] > M_PI; 

		if(currentSmallestAngle < minAngle && !reflexAngle)
			MarkConnectionAsImpossible(a,b);	
		else
			potOuterConnections.insert( CPotentialConnection( a,b, currentSmallestAngle, type) );
	}

	std::set<CPotentialConnection>::iterator it2 = potOuterConnections.begin();
	for(; it2 != potOuterConnections.end(); it2++ ) 
	{
		a = it2->a;
		b = it2->b;

		if(ConnectionIntersectsHelperConnections(a,b)) 
			MarkConnectionAsImpossible(a,b);		
		else
		{
			if(it2->type == ENVPC::OUTSIDE)
			CreateConnection(a,b, ENVPC::OUTSIDE, eKoef*0.6);
			else
				CreateConnection(a,b, ENVPC::INSIDE);
		}
		
	}
}
