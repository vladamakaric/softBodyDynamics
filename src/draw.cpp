#include "draw.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Draw::PushCircle(double _x, double _y,double _HRadius, int _vertices)
{
	double angleStep = 2*M_PI/_vertices;
	for(int i=0; i < _vertices; i++)
	{
		glVertex2d( cos(i*angleStep)*_HRadius + _x, sin(i*angleStep)*_HRadius + _y);
	}
}

void Draw::CircleFill(double _x, double _y,double _HRadius, int _vertices)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d( _x, _y);
	PushCircle(_x,_y,_HRadius,_vertices);
	glVertex2d( _HRadius + _x,0 + _y);
	glEnd();
}

void Draw::CircleOutline(double _x, double _y,double _HRadius, int _vertices)
{
	glBegin(GL_LINE_LOOP);
	PushCircle(_x,_y,_HRadius,_vertices);
	glEnd();
}

void Draw::Line(CVector &_a, CVector &_b)
{
	glBegin(GL_LINES);
	PushVertex(_a);
	PushVertex(_b);
	glEnd();
}

void Draw::Line( CVector ln[], int size )
{
	glBegin(GL_LINES);
	for(int i=0; i<size-1; i++)
	{
		PushVertex(ln[i]);
		PushVertex(ln[i+1]);
	}
	glEnd();
}

void Draw::Border(int _width, int _height, double _thickness, const CVector &_pos)
{
	glPushMatrix();
	glTranslatef(_pos.x, _pos.y, 0);
	glBegin(GL_QUADS);
	glVertex2d(0,0);
	glVertex2d(_thickness,0);
	glVertex2d(_thickness,_height);
	glVertex2d(0,_height);

	glVertex2d(0,0);
	glVertex2d(_width,0);
	glVertex2d(_width,_thickness);
	glVertex2d(0,_thickness);

	glVertex2d(_width-_thickness,0);
	glVertex2d(_width,0);
	glVertex2d(_width,_height);
	glVertex2d(_width-_thickness,_height);

	glVertex2d(_width,_height-_thickness);
	glVertex2d(_width,_height);
	glVertex2d(0,_height);
	glVertex2d(0,_height-_thickness);
	glEnd();
	glPopMatrix();
}

void Draw::CircleFill(const CVector &_v, double _HRadius, int _vertices) { CircleFill(_v.x, _v.y,_HRadius, _vertices); }
void Draw::CircleOutline(const CVector &_v, double _HRadius, int _vertices) { CircleOutline(_v.x, _v.y, _HRadius, _vertices); }