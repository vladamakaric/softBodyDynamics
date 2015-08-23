#pragma once
#include "ParticleLS.h"
#include <vector>
#include <list>
#include "SpringForceGenerator.h"


using namespace std;

class ENVPC
{
public:
	enum {OUTSIDE, INSIDE, ENVELOPE};
	enum {NO_WAY = -1};


	ENVPC() : connection(0), sfg(0), pls(0) {}
	void MakeConnection(int typ, SpringForceGenerator* s, CParticleLS *p) { type = typ; sfg = s; pls = p; connection = true; }

	int connection;
	int type;
	SpringForceGenerator* sfg;
	CParticleLS *pls;
};



class CSoftBody
{
public:
	typedef pair<CParticle*,CParticle*> CParticlePair; 
	CSoftBody(const vector<CVector> &_refEnv, double _mass, double _cMass, double _ek, double _dk);
	void GenerateEnvolopeParticles();
	void CalculateInnerAngles();
	void DeterminePossibleConnections();
	void ConnectReflexAngleParticles();
	void UpdatePossibleConnections();
	void GenerateConnectionsWithMinimalAngleConstraint(double minAngle);


	bool ConnectionFree(CParticle* a, CParticle* b) { return !connectionMatrix[a->SBEIndx][b->SBEIndx].connection; };
	void MarkConnectionAsImpossible(CParticle* a, CParticle* b) {connectionMatrix[a->SBEIndx][b->SBEIndx].connection = ENVPC::NO_WAY; connectionMatrix[b->SBEIndx][a->SBEIndx].connection = ENVPC::NO_WAY;}


	bool Connected( CParticle* a, CParticle *b ) { return connectionMatrix[a->SBEIndx][b->SBEIndx].connection; }
	bool Connected( int aIndx, int bIndx ) { return connectionMatrix[aIndx][bIndx].connection; }
	void AddConnectionToMatrix( CParticle* a, CParticle *b, int type, SpringForceGenerator* sfg, CParticleLS *pls);
	void CreateConnection( CParticle* a, CParticle *b, int type, double eK = -1, double dK = -1);
	bool ConnectionIntersectsEnvelope(int i, int j);
	bool ConnectionIntersectsHelperConnections(CParticle* a, CParticle* b);


	double GetSmallestAngleCreatedWithConnection(CParticle* a, CParticle *b);

	//////////////////////////////////////////////
	void MakeInnerConnectionsWithMinimumAngle(double minAngle);
	bool MakeBestPossibleConnection(double minAngle);
	//////////////////////////////////////////////



	void GenerateSpringEnvelope();
	void GenerateCenterOfMassToAllParticlesSprings();
	void GenerateConvexHullSprings();
	void GenerateAngleSprings();
	void Draw();
	void Update();

	const int envelopeSize;
	double centerMass;
	double mass;
	double eKoef;
	double dKoef;

	bool clockWiseEnvolope;

	bool PointInSoftBody( const CVector &p);

	void DrawBezierFromSpring(SpringForceGenerator *_sfg);

	CParticle* centerOfMassP;
	const vector<CVector> &envolope;
	list<CParticlePair> possibleConnections;

	double *envolopeInnerAngles;
	CParticleLS  **visibleParticleLS;
	CParticle **visibleParticles;
	ENVPC **connectionMatrix;

	vector<CParticleLS*> helperParticleLS;
};



