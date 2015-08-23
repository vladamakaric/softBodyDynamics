#include "ComplexSoftBodyGenerator.h"
#include "draw.h"
#include "global.h"
#include "SBTriangle.h"
#include "SpringForceGenerator.h"
#include "f_distance.h"
#include "SoftBody.h"
#include <iostream>
#include "f_intersection.h"
#include "f_geometry.h"

using namespace std;

ComplexSoftBodyGenerator::ComplexSoftBodyGenerator()
{
	inputInProgress = true;
	softBody = 0;
}

void ComplexSoftBodyGenerator::HandleEvents()
{
	CVector mpos;

	if(event.type == SDL_KEYDOWN)
	{
		if( event.key.keysym.sym == SDLK_RETURN )
		{
			inputInProgress = false;
		//	CreateSoftBody( 2, 25, 4 );
			softBody = new CSoftBody(vectorPolyLine, 10, 10, 80, 0.5);

			//CreateSBWithRods(10, 200, 100 , 200,100);
			//CreateSoftBodyConstrainedDelanay(10, 200, 100 );
		}
	}

	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		mpos.Set(event.button.x, SCREEN_HEIGHT - event.button.y);

		if( event.button.button == SDL_BUTTON_LEFT )
		{
			vectorPolyLine.push_back(mpos);
		}

		if( event.button.button == SDL_BUTTON_RIGHT )
		{
			if(F::INTERSECTION::PointInPolygon(mpos, vectorPolyLine))
				cout << "kurCHINA" << endl;
			else
				cout << "VAN KURCHINE" << endl;
		}
	}
}

void ComplexSoftBodyGenerator::Render()
{
	if(inputInProgress)
	for (int i=0; i<vectorPolyLine.size(); i++)
	{
		Draw::Line(vectorPolyLine[i], vectorPolyLine[(i+1)%vectorPolyLine.size()]);
	}

	if(softBody)
	{
		softBody->Update();
		softBody->Draw();
/*
		vector<p2t::Point*> tempVecLine;
		for(int i=0; i<softBody->visibleParticles.size(); i++)
			tempVecLine.push_back(new p2t::Point(softBody->visibleParticles[i]->position.x, softBody->visibleParticles[i]->position.y) );
		
		p2t::CDT *TempTriangulator = new p2t::CDT(tempVecLine);
		TempTriangulator->Triangulate();

		F::MISC::DeletePointerContainer(triangles);
		triangles = TempTriangulator->GetTriangles();

		glColor3f(0,1,0);

		glBegin(GL_TRIANGLES);
			for(int i=0; i<triangles.size(); i++)
			{
				Draw::PushVertex(triangles[i]->GetPoint(0)->x, triangles[i]->GetPoint(0)->y);
				Draw::PushVertex(triangles[i]->GetPoint(1)->x, triangles[i]->GetPoint(1)->y);
				Draw::PushVertex(triangles[i]->GetPoint(2)->x, triangles[i]->GetPoint(2)->y);
			}
		glEnd();

		
		F::MISC::DeletePointerContainer(tempVecLine);*/
	}

	glLineWidth(4);
	glColor3f(0,0,1);
	Draw::VectorObjectContainerAsLine(convexPolyLine, false);
	glLineWidth(1);
}

void ComplexSoftBodyGenerator::CreateSoftBodyConstrainedDelanay( double mass, double ek, double dk )
{
	for(int i=0; i<vectorPolyLine.size(); i++)
		pointsPolyLine.push_back(new p2t::Point(vectorPolyLine[i].x, vectorPolyLine[i].y));

	constrainedDelaney = new p2t::CDT(pointsPolyLine);
	constrainedDelaney->Triangulate();
	triangles = constrainedDelaney->GetTriangles();

	p2t::Triangle *triangle;
	vector<SBTriangle*> sbTriangles;

	for(int i=0; i<triangles.size(); i++)
	{
		triangle = triangles[i];
		sbTriangles.push_back(new SBTriangle(CVector(triangle->GetPoint(0)->x,triangle->GetPoint(0)->y), 
			CVector(triangle->GetPoint(1)->x,triangle->GetPoint(1)->y), 
			CVector(triangle->GetPoint(2)->x,triangle->GetPoint(2)->y)));
	}

	currentWorld->CreateSoftBody(&sbTriangles, mass, ek, dk);
}

void ComplexSoftBodyGenerator::CreateSBWithRods( double mass, double ek, double dk, double rek, double rdk )
{
	CVector sum(0,0);

	for(int i=0; i< vectorPolyLine.size(); i++)
		sum+=vectorPolyLine[i];

	sum/= vectorPolyLine.size();

	CParticle* center = new CParticle(mass, sum);

	CParticle* prev = new CParticle(mass, vectorPolyLine[0]);
	CParticle* first= prev;
	currentWorld->AddParticle(prev);

	for(int i=1; i< vectorPolyLine.size(); i++)
	{
		CParticle* current = new CParticle(mass, vectorPolyLine[i]);

		currentWorld->AddParticle(current);

		double restLenght = F::DISTANCE::GetDistance(current->position, prev->position);
		currentWorld->AddForceGenerator(new SpringForceGenerator(prev,current, ek, dk, restLenght));

		if(i==vectorPolyLine.size()-1)
		{
			restLenght = F::DISTANCE::GetDistance(first->position, current->position); 
			currentWorld->AddForceGenerator(new SpringForceGenerator(first,current, ek, dk, restLenght));
		}

		prev = current;
	}
}
