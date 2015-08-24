#include "sworld.h"
#include "global.h"
#include "draw.h"
#include <math.h>
#include "particle.h"
#include "fzconstants.h"
#include "GravityPFG.h"
#include "SpringForceGenerator.h"
#include <iostream>

#include "f_vector.h"
#include "f_angle.h"
#include "draw.h"

#include "f_intersection.h"
#include "f_collision.h"
#include "f_geometry.h"
#include "f_distance.h"
#include "AngularSpringFG.h"
#include "BezierCurve.h"
#include "Line.h"

#include "OrientedParabola.h"


//#include <boost/random/mersenne_twister.hpp>
//#include <boost/random/uniform_int_distribution.hpp>

//boost::random::mt19937 gen;

#define PI (3.141592653589793)

double getFlatBezierLength(double L, double V)
{
	return 1.0/(512.0)*(1.0/(V*V*V)) * (  256.0*(V*V*V)*sqrt(L*L + 4.0*V*V) + (64.0*V*V*L*L)*log(   (2.0*sqrt(L*L + 4.0*V*V) + 4.0*V) / (  2.0*sqrt(L*L + 4.0*V*V) - 4.0*V )  )  );
}

CSWorld::CSWorld()
{
	run = false;
	globalDragKoef = 0.9;
	currentDragKoef = globalDragKoef;

	changeElasticity = true;
}

void CSWorld::Simulate()
{

	popusiga = 0;

	srand( (unsigned int)time(NULL) );
	run = true;
	InitGraphix();
	float ang = 0;
	int elapsedTime = 0;
	timeStep = 0;
	
	CSBG = new ComplexSoftBodyGenerator();

	//particles.push_back(new CParticle(12, CVector(500,500)));
	//particles.push_back(new CParticle(12, CVector(400,400)));
	//particles.push_back(new CParticle(12, CVector(400,500)));
	//particles.push_back(new CParticle(12, CVector(500,400)));
	//particles.push_back(new CParticle(12, CVector(450,450)));

	boundingBoxVecs.push_back(CVector(0,400));
	boundingBoxVecs.push_back(CVector(260,40));
	boundingBoxVecs.push_back(CVector(560,70));
	boundingBoxVecs.push_back(CVector(800,500));
	CreateBoudningBox();

	CVector v1(100,100);
	CVector c1(300,300);
	CVector v2(300, 600);

	PFM = new CParticleForcesManager();
	PFM->AddPFG(new GravityPFG(CVector(0, -30)));

	CVector djole(0.1182, -0.0068);
	CLine cdjo(-450.0, -300.0, 150000.0);

//	F::VECTOR::ReflectVectorRayFromLine(djole, cdjo);

	printf("Obrnu  vektor: (%lf, %lf)\n", djole.x,djole.y);

	//particles.push_back(new CParticle(12, CVector(200,100)));
	//particles.push_back(new CParticle(12, CVector(400,100)));
	//particles.push_back(new CParticle(12, CVector(200,240)));

	
	//AddForceGenerator(new CAngularSpringFG(particles[2], particles[1], particles[0], 50, 25));
	//AddForceGenerator(new CAngularSpringFG(particles[1], particles[0], particles[2], 50, 25));
	//AddForceGenerator(new SpringForceGenerator(particles[1], particles[0], 200, 200, F::DISTANCE::GetDistance(particles[1]->position, particles[0]->position)));
	//AddForceGenerator(new SpringForceGenerator(particles[1], particles[2], 200, 200, F::DISTANCE::GetDistance(particles[1]->position, particles[2]->position)));
	

	//AddForceGenerator(new SpringForceGenerator(particles[0], particles[2], 10, 10, F::DISTANCE::GetDistance(particles[0]->position, particles[2]->position)));
	//AddForceGenerator(new CAngularSpringFG(particles[1], particles[2], particles[0], 100, 10));
	//AddForceGenerator(new CAngularSpringFG(particles[1], particles[2], particles[0], 100, 10));
	//particles.push_back(new CParticle(12, CVector(500,500)));
	//particles.push_back(new CParticle(12, CVector(400,400)));
	//particles.push_back(new CParticle(12, CVector(400,500)));
	//particles.push_back(new CParticle(12, CVector(500,400)));
	//particles.push_back(new CParticle(12, CVector(450,450)));



	/*
	forceGenerators.push_back(new SpringForceGenerator(particles[2], particles[1], 50, 100));
	forceGenerators.push_back(new SpringForceGenerator(particles[1], particles[3], 50, 100));

	forceGenerators.push_back(new SpringForceGenerator(particles[2], particles[0], 50, 100));
	forceGenerators.push_back(new SpringForceGenerator(particles[3], particles[0], 50, 100));

	forceGenerators.push_back(new SpringForceGenerator(particles[0], particles[4], 50, 100*1.41/2));
	forceGenerators.push_back(new SpringForceGenerator(particles[1], particles[4], 50, 100*1.41/2));

	forceGenerators.push_back(new SpringForceGenerator(particles[2], particles[4], 50, 100*1.41/2));
	forceGenerators.push_back(new SpringForceGenerator(particles[3], particles[4], 50, 100*1.41/2));
	*/

	//GenerateCircularBlobConnectedToCenter(CVector(400,300), 120, 4, 10, 10, 70, 70);

	/*
	for(int i=0; i<n-1; i++)
		for(int j=i+1; j<n; j++)
		{
			forceGenerators.push_back(new SpringForceGenerator(particles[i],particles[j], 5,(float)sqrt((particles[i]->position.x-particles[j]->position.x)*(particles[i]->position.x-particles[j]->position.x)+(particles[i]->position.y-particles[j]->position.y)*(particles[i]->position.y-particles[j]->position.y))));
		}
*/
	CVector leftB(200,0);
	CVector rightB(600,0);
	CVector middleB(400,1);

	CBezierCurve bc;
	bc.Set(leftB,middleB,rightB);

	CVector mpos;
	while(run)
	{
		TIME = SDL_GetTicks();
		ang += 0.001;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				run = false;

			mpos.Set(event.button.x, SCREEN_HEIGHT - event.button.y);
			//printf("%d \n" ,event.button.x);
			//printf("%d \n" , SCREEN_HEIGHT - event.button.y);	


			CSBG->HandleEvents();





			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if( event.button.button == SDL_BUTTON_MIDDLE )
				{
					//for()

					CVector sum(0,0);
					for(int i=0; i<particles.size(); i++)
					{
						sum += particles[i]->position;
					}

					sum/=particles.size();


					CVector dis = F::VECTOR::GetVectorFromAToB(sum, mpos);

					for(int i=0; i<particles.size(); i++)
						particles[i]->position += dis;	
				}


				if( event.button.button == SDL_BUTTON_LEFT )
				{

					//particles.push_back(new CParticle(10,mpos));

				//	printf("Stisno si lokaciju: %lf, %lf \n" , mpos.x, mpos.y );	

					v2 = mpos;
					/*
					CVector dis = F::VECTOR::GetVectorFromAToB(particles[0]->position, mpos);

					for(int i=0; i<particles.size(); i++)
						particles[i]->position += dis;		*/		
				}

				if( event.button.button == SDL_BUTTON_RIGHT )
				{
					changeElasticity = !changeElasticity;
				}

				double eCoefStep = 7;
				double dCoefStep = 1;

				if( event.button.button == SDL_BUTTON_WHEELUP || event.button.button == SDL_BUTTON_WHEELDOWN )
				{
					double diff;

					if(changeElasticity)
					{
						if( event.button.button == SDL_BUTTON_WHEELUP)
							diff = eCoefStep;

						if( event.button.button == SDL_BUTTON_WHEELDOWN)
							diff = -eCoefStep;

						for(int i=0; i<forceGenerators.size(); i++)
						{
							if(dynamic_cast<SpringForceGenerator*>(forceGenerators[i])->elasticityKoef > 10)
							dynamic_cast<SpringForceGenerator*>(forceGenerators[i])->elasticityKoef += diff;
							else
								dynamic_cast<SpringForceGenerator*>(forceGenerators[i])->elasticityKoef = 11;
						}
					}
					else
				    {
						if( event.button.button == SDL_BUTTON_WHEELUP)
							diff = dCoefStep;

						if( event.button.button == SDL_BUTTON_WHEELDOWN)
							diff = -dCoefStep;

						for(int i=0; i<forceGenerators.size(); i++)
						{
							if(dynamic_cast<SpringForceGenerator*>(forceGenerators[i])->dampingKoef > 1)
							dynamic_cast<SpringForceGenerator*>(forceGenerators[i])->dampingKoef += diff;
							else
							dynamic_cast<SpringForceGenerator*>(forceGenerators[i])->dampingKoef = 2;

							double t = dynamic_cast<SpringForceGenerator*>(forceGenerators[i])->dampingKoef;
						}
					}
				}
			}
		}


		

		HandleKeyStates();
		
		//RotateBBAroundPoint(CVector(400,300), elapsedTime/1000);

		CLineSegment rty(CVector(100,100), CVector(300,100));
		CLineSegment rtu(CVector(200,100), CVector(240,400));

		glClear(GL_COLOR_BUFFER_BIT);

		PFM->Update(timeStep);
		UpdateForceGenerators(timeStep);
		
		
		/*
		CVector toLineC, normToLineC;
		CLine dj(CVector(100,100), CVector(400,130));
		F::VECTOR::BreakVectorIntoComponentsToLine(dj, F::VECTOR::GetVectorFromAToB(CVector(100,100), mpos)/10.0, toLineC, normToLineC);


		Draw::Line(CVector(100,100),CVector(100,100) + F::VECTOR::GetVectorFromAToB(CVector(100,100), mpos)*100);
		dj.Draw();

		glColor3f(1,0,0);
		Draw::Line(CVector(100,100), CVector(100,100) + toLineC*100);
		Draw::Line(CVector(100,100), CVector(100,100) + normToLineC*100);
		*/

		//for(int i=0; i< particles.size(); i++) particles[i]->DrawForces();

		UpdateParticles(timeStep);	
		Collision();

		Draw();

	//	Draw::Line(leftB,bc.points[1]);
	//	Draw::Line(rightB,bc.points[1]);
	//	bc.Draw();

	//	cdjo.Draw();
		SDL_GL_SwapBuffers();

		int oldElapsedTime = elapsedTime;

		elapsedTime = SDL_GetTicks() - TIME;
	
		if(elapsedTime>100)
			elapsedTime = 1;

		timeStep = double(elapsedTime)/100;
		currentDragKoef = pow(globalDragKoef, timeStep);
	}

	SDL_Quit();
}

void CSWorld::InitGraphix()
{
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 
	SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_OPENGL );

	glClearColor( 0, 0, 0, 0 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);
	//glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	SDL_WM_SetCaption( "zorpro", NULL );
}

void CSWorld::UpdateParticles( double timeLapse )
{
	for(int i=0; i<particles.size(); i++)
	{
		particles[i]->Update(timeLapse);
	}
}

void CSWorld::DrawParticles()
{
	if(forceGenerators.size())
	{
		
	}

	glPointSize(5);
	glBegin(GL_POINTS);
	for(int i=0; i<particles.size(); i++)
		Draw::PushVertex(particles[i]->position);
	glEnd();
}

void CSWorld::DrawLineSegments()
{
	for(int i=0; i<forceGenerators.size(); i++)
	{

	}

	glColor3d(1,0,1);
	for(int i=0; i<lineSegments.size(); i++)
	{
		glBegin(GL_LINES);
			Draw::PushVertex(lineSegments[i].a);
			Draw::PushVertex(lineSegments[i].b);
		glEnd();
	}
}

void CSWorld::Logic()
{

}

void CSWorld::Draw()
{
	if(popusiga)
	glColor3d(1,1,0);
	else
		glColor3d(0,1,0);

	for(int i=0; i<forceGenerators.size(); i++) ((SpringForceGenerator*)forceGenerators[i])->Draw();

	DrawParticles();

	CSBG->Render();
	DrawLineSegments();
}

void CSWorld::Collision()
{
	if(timeStep == 0)
		return;

	for(int j=0; j<particles.size(); j++)
		AvoidTunneling(particles[j]);
}

void CSWorld::UpdateForceGenerators( double timeLapse )
{
	/*if(!forceGenerators.size())
		return;

	bool *arr = new bool[forceGenerators.size()];

	for(int i=0; i< forceGenerators.size(); i++)
		arr[i] = 0;


	boost::random::uniform_int_distribution<> dist(0, forceGenerators.size()-1);

	while(1)
	{
		int indx = dist(gen);

		if(!arr[indx])
		{
			forceGenerators[indx]->Update(timeLapse);
			arr[indx] = 1;
		}

		bool over = true;
		for(int i=0; i< forceGenerators.size(); i++)
		{
			if(!arr[i])
				over = false;
		}

		if(over)
			break;
	}*/

	for(int i=0; i< forceGenerators.size(); i++)
		forceGenerators[i]->Update(timeLapse);

}

void CSWorld::CreateBoudningBox()
{
	for(int i=0; i< boundingBoxVecs.size()-1; i++)
		lineSegments.push_back(CLineSegment(boundingBoxVecs[i], boundingBoxVecs[i+1]));
}

void CSWorld::RotateBBAroundPoint( const CVector &point, double angle )
{
	for(int i=0; i< lineSegments.size(); i++)
	{
		F::VECTOR::RotateVectorAroundVector(lineSegments[i].a, point, angle);
		F::VECTOR::RotateVectorAroundVector(lineSegments[i].b, point, angle);
	}
}

void CSWorld::HandleKeyStates()
{
	if( keystates[ SDLK_LEFT ] )
		RotateBBAroundPoint(CVector(400,300), timeStep/10);

	if( keystates[ SDLK_RIGHT ] )
		RotateBBAroundPoint(CVector(400,300), -timeStep/10);
}

void CSWorld::GenerateCircularBlobConnectedToCenter( const CVector &_pos, double r, int vertCount, double massCenter, double massRim, double elasticKoefCenter, double elasticKoefRim )
{
	double angleIncrement = 2*PI/vertCount;
	double angle = 0;
	CParticle* prev = 0;
	CParticle* current = 0;
	CVector curentPartPos;

	double arcLength = F::GEOMETRY::GetBaseOfIsoscelesTriangle(r, angleIncrement);

	CParticle* centerParticle = new CParticle(massCenter, _pos);
	particles.push_back(centerParticle);
	PFM->AddParticle(centerParticle, 0);
	
	int firstPartIndx = particles.size();

	for(int i=0; i<vertCount; i++)
	{
		curentPartPos = _pos;
		curentPartPos.x += cos(angle)*r;
		curentPartPos.y += sin(angle)*r;
		prev = current;
		current = new CParticle(massRim, curentPartPos);
		particles.push_back(current);
		PFM->AddParticle(current, 0);

		forceGenerators.push_back(new SpringForceGenerator(centerParticle, current, elasticKoefCenter, 10,r));

		if(prev)
			forceGenerators.push_back(new SpringForceGenerator(current, prev, elasticKoefRim, 10, arcLength));

		angle += angleIncrement;
	}

	forceGenerators.push_back(new SpringForceGenerator(current, particles[firstPartIndx], elasticKoefRim, 10, arcLength));
}

void CSWorld::GenerateParticleCircleWithDoubleRim( const CVector &_pos, double r, double layerR, int vertCount )
{

}

void CSWorld::AvoidTunneling( CParticle *_particle )
{
	if(_particle->velocity.Length()*timeStep < 0.05)
		return;

	double reflectionDamping = 0.9;
	CVector displacement = _particle->velocity*timeStep;
	//CVector displacement2 = displacement.Direction()*0.1;
	CLineSegment tunnel(_particle->position, _particle->position + displacement);

	int firstCollisionLS = -1;

	CVector intersection;

	if(_particle->visible)
		for(int i=0; i<lineSegments.size(); i++)
		{
			if(F::INTERSECTION::LineSegmentIntersection(lineSegments[i], tunnel, &intersection))
			{
				CLine l(lineSegments[i]);

				F::VECTOR::ReflectVectorRayFromLine( _particle->velocity, l);
				_particle->velocity*=reflectionDamping;
				firstCollisionLS = i;

				double distToIntersection = F::DISTANCE::GetDistance(intersection, _particle->position);

				double reflectedDistance = tunnel.Lenght() - distToIntersection;
				CVector reflectedDisplacement = _particle->velocity;
				reflectedDisplacement.Rescale(reflectedDistance);

				CVector reflectedPosition = intersection + reflectedDisplacement;

				CLineSegment reflectedTunnel(intersection, reflectedPosition);
				CLineSegment tempLs(_particle->position, reflectedPosition);


				for(int j=0; j<lineSegments.size(); j++)
				{
					if(j == firstCollisionLS)
						continue;

					CVector intersection2;
					if(F::INTERSECTION::LineSegmentIntersection(lineSegments[j], reflectedTunnel, &intersection2))
					{
						CLine l(lineSegments[j]);

						F::VECTOR::ReflectVectorRayFromLine( _particle->velocity, l);
						_particle->velocity*=reflectionDamping;

						double distToIntersection = F::DISTANCE::GetDistance(intersection, intersection2);

						double reflectedDistance = reflectedTunnel.Lenght() - distToIntersection;

						CVector reflectedDisplacement = _particle->velocity;
						reflectedDisplacement.Rescale(reflectedDistance);

						CVector reflectedPosition = intersection2 + reflectedDisplacement;

						CLineSegment tempLs(_particle->position, reflectedPosition);

						for(int k=0; k<lineSegments.size(); k++)
						{
							if(F::INTERSECTION::LineSegmentIntersection(lineSegments[k], tempLs))
								return;
						}




						_particle->position = reflectedPosition;
						return;
					}



				}

				
				for(int k=0; k<lineSegments.size(); k++)
				{
					if(F::INTERSECTION::LineSegmentIntersection(lineSegments[k], tempLs))
						return;
				}

				_particle->position = reflectedPosition;
				return;
			}
		}


		CLineSegment tempLs(_particle->position, _particle->position + displacement);
		for(int k=0; k<lineSegments.size(); k++)
		{
			if(F::INTERSECTION::LineSegmentIntersection(lineSegments[k], tempLs))
				return;
		}

		_particle->position += displacement;
}


static bool VecInTriangle(SBTriangle* _t, const CVector& _vec)
{
	for(int i=0; i<3; i++)
	{
		if(_t->points[i] == _vec )
			return true;
	}

	return false;
}

static int GetIndxFromTriangleThatIsNot(SBTriangle* _t,const CVector& _v1, const CVector& _v2)
{
	for(int i=0; i<3; i++)
	{
		if(_t->points[i] != _v1 && _t->points[i] != _v2 )
			return i;
	}
}

void CSWorld::ExtendSide(CParticle* _a, CParticle* _b, double mass, double ek, double dk)
{
	SBTriangle *triAngle;
	int indx;
	CVector newVec = GetVectorConnectedToParticles(_a,_b, &triAngle, &indx);

	if(newVec.x == -1.0)
		return;

	CParticle *c = new CParticle(mass, newVec);

	triAngle->particles[indx] = c;
	c->neighbours.push_back(_a);
	c->neighbours.push_back(_b);
	_b->neighbours.push_back(c);
	_a->neighbours.push_back(c);

	PFM->AddParticle(c, 0);

	particles.push_back(c);

	double da = F::DISTANCE::GetDistance(newVec,  _a->position);
	double db = F::DISTANCE::GetDistance(newVec,  _b->position);

	forceGenerators.push_back(new SpringForceGenerator(c, _a, ek, dk,da));
	forceGenerators.push_back(new SpringForceGenerator(c, _b, ek, dk,db));

	ExtendSide(c, _b, mass, ek, dk);
	ExtendSide(c, _a, mass, ek, dk);
}

CVector CSWorld::GetVectorConnectedToParticles(CParticle* _a, CParticle* _b, SBTriangle** _triangle, int *triPartIndx)
{
	CVector a(_a->position);
	CVector b(_b->position);

	for(int i=0; i< triangles->size(); i++)
	{
		if((*triangles)[i]->points[0] == a)
			(*triangles)[i]->particles[0] = _a;

		if((*triangles)[i]->points[1] == a)
			(*triangles)[i]->particles[1] = _a;

		if((*triangles)[i]->points[2] == a)
			(*triangles)[i]->particles[2] = _a;

		if((*triangles)[i]->points[0] == b)
			(*triangles)[i]->particles[0] = _b;

		if((*triangles)[i]->points[1] == b)
			(*triangles)[i]->particles[1] = _b;

		if((*triangles)[i]->points[2] == b)
			(*triangles)[i]->particles[2] = _b;

		if( VecInTriangle((*triangles)[i], a) && VecInTriangle((*triangles)[i], b) )
		{
			int indx = GetIndxFromTriangleThatIsNot((*triangles)[i], a,b);

			if(!(*triangles)[i]->particles[indx])
			{
				*triPartIndx = indx;
				*_triangle = (*triangles)[i];
				return (*triangles)[i]->points[indx];
			}
			
			if(!(*triangles)[i]->particles[indx]->IsNeighbour(_a))
			{
				*triPartIndx = indx;
				*_triangle = (*triangles)[i];
				return (*triangles)[i]->points[indx];
			}
		}
	}

	return CVector(-1,-1);
}



void CSWorld::CreateSoftBody( vector<SBTriangle*> *_triangles, double mass, double ek, double dk )
{
	triangles = _triangles;
	SBTriangle* current = (*triangles)[0];
	CParticle* p1 = new CParticle(mass, current->points[0]);
	CParticle* p2 = new CParticle(mass, current->points[1]);
	CParticle* p3 = new CParticle(mass, current->points[2]);

	current->particles[0] = p1;
	current->particles[1] = p2;
	current->particles[2] = p3;

	p1->neighbours.push_back(p2);
	p1->neighbours.push_back(p3);
	p2->neighbours.push_back(p1);
	p2->neighbours.push_back(p3);
	p3->neighbours.push_back(p1);
	p3->neighbours.push_back(p2);

	double d1to2 = F::DISTANCE::GetDistance(current->points[0], current->points[1]);
	double d2to3 = F::DISTANCE::GetDistance(current->points[2], current->points[1]);
	double d3to1 = F::DISTANCE::GetDistance(current->points[0], current->points[2]);

	PFM->AddParticle(p1, 0);
	PFM->AddParticle(p2, 0);
	PFM->AddParticle(p3, 0);

	particles.push_back(p1);
	particles.push_back(p2);
	particles.push_back(p3);

	forceGenerators.push_back(new SpringForceGenerator(p1, p2, ek, dk, d1to2));
	forceGenerators.push_back(new SpringForceGenerator(p2, p3, ek, dk, d2to3));
	forceGenerators.push_back(new SpringForceGenerator(p3, p1, ek, dk, d3to1));

	ExtendSide(p1, p2, mass, ek, dk);
	ExtendSide(p1, p3, mass, ek, dk);
	ExtendSide(p3, p2, mass, ek, dk);
}

void CSWorld::AddForceGenerator( CForceGenerator* _fg )
{
	forceGenerators.push_back(_fg);
}

void CSWorld::AddParticle( CParticle *_p )
{
	particles.push_back(_p);
}
