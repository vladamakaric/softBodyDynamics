#pragma once

#include "ParticleForcesManager.h"
#include "LineSegment.h"
#include "ForceGenerator.h"
#include "ComplexSoftBodyGenerator.h"
#include "SBTriangle.h"


class CSWorld
{
public:
	CSWorld();
	void Simulate();
	void InitGraphix();
	bool run;
	int TIME;
	bool popusiga;
	CParticleForcesManager *PFM;
	ComplexSoftBodyGenerator *CSBG;

	

	vector<CForceGenerator*> forceGenerators;
	vector<CParticle*> particles;
	vector<CLineSegment> lineSegments;
	vector<CVector> boundingBoxVecs;

	void AddForceGenerator(CForceGenerator* _fg);
	void AddParticle(CParticle *_p);
	void CreateSoftBody( vector<SBTriangle*> *_triangles, double mass, double ek, double dk );
	void UpdateForceGenerators(double timeLapse);
	void UpdateParticles(double timeLapse);
	void DrawParticles();
	void DrawLineSegments();
	void Logic();
	void Draw();
	void Collision();
	void CreateBoudningBox();
	void RotateBBAroundPoint(const CVector &point, double angle);
	void HandleKeyStates();

	void GenerateCircularBlobConnectedToCenter(const CVector &_pos, double r, int vertCount, double massCenter, double massRim, double elasticKoefCenter, double elasticKoefRim );
	void GenerateParticleCircleWithDoubleRim(const CVector &_pos, double r, double layerR, int vertCount );
	void AvoidTunneling(CParticle *_particle);
	CVector GetVectorConnectedToParticles(CParticle* _a, CParticle* _b, SBTriangle** _triangle, int *triPartIndx);
	void ExtendSide(CParticle* _a, CParticle* _b, double mass, double ek, double dk);
	
	vector<SBTriangle*> *triangles;
	bool changeElasticity;
	double timeStep;
	double globalDragKoef;
	double currentDragKoef;
};

