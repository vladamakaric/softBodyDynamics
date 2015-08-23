#ifndef DRAW_H
#define DRAW_H

#include "global.h"
#include "Vector.h"


namespace Draw
{
	inline void PushVertex(const CVector &_v) { glVertex2d(_v.x,_v.y); }
	inline void PushVertex(double _x, double _y) { glVertex2d(_x,_y); }
	void Border(int _width, int _height, double _thickness, const CVector &_pos);
	void CircleFill(double _x, double _y,double _HRadius, int _vertices);
	void CircleOutline(double _x, double _y,double _HRadius, int _vertices);
	void CircleFill(const CVector &_v, double _HRadius, int _vertices);
	void CircleOutline(const CVector &_v, double _HRadius, int _vertices);
	void PushCircle(double _x, double _y,double _HRadius, int _vertices);
	void Line(CVector &_a, CVector &_b);
	void Line( CVector ln[], int size);




	template<class T> void VectorObjectContainerAsLine(T &_oContainer, bool openLine = true)
	{
		if(!_oContainer.size())
			return;

		typename T::iterator limit = _oContainer.end();
		limit--;
		typename T::iterator tempIter;


		for(typename T::iterator iter = _oContainer.begin(); iter!=limit; iter++)
		{
			tempIter = iter;
			tempIter++;

			Line(*iter, *tempIter);
		}

		if(!openLine)
			Line(*limit, *_oContainer.begin());
	}

	template<class T> void PointerToObjectWithPositionVector_Container_AsOpenLine(T &_oContainer)
	{
		if(!_oContainer.size())
			return;

		typename T::iterator limit = _oContainer.end();
		limit--;
		typename T::iterator tempIter;


		for(typename T::iterator iter = _oContainer.begin(); iter!=limit; iter++)
		{
			tempIter = iter;
			tempIter++;

			Line((*iter)->position, (*tempIter)->position);
		}
	}
}

#endif
