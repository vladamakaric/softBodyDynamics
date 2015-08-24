#pragma once
#include "Vector.h"
#include "Circle.h"
#include <vector>
#include "Line.h"

using namespace std;

namespace F
{
	namespace MISC
	{
		template<class T> inline T MinByRef(T& _a,T& _b)  { return _a > _b ? _b : _a; }
		template<class T> inline T MaxByRef(T& _a,T& _b)  { return _a > _b ? _a : _b; }
		template<class T> inline T Min(T _a,T _b)  { return _a > _b ? _b : _a; }
		template<class T> inline T Max(T _a,T _b)  { return _a > _b ? _a : _b; }

		template<class T> inline void Swap(T &_a, T &_b) 
		{
			T temp = _a;
			_a = _b;
			_b = temp;
		}

		template<class T> void FillArrayWithValue(T *_pContainer, int size, T &_value)
		{
			for(int i=0; i<size; i++)
				_pContainer[i] = _value;
			
		}

		template<class T> void DeletePointerContainer(T &_pContainer)
		{
			if(!_pContainer.size())
				return;

			for( typename T::iterator iter = _pContainer.begin(); iter!=_pContainer.end(); iter++)
				delete (*iter);
			
			_pContainer.clear();
		}

		template<class T> void UntagPointerContainer(T &_pContainer)
		{
			for(int i=0; i < _pContainer.size(); i++)
				_pContainer[i]->tagged=false;
		}

		template<class T> void TagPointerContainer(T &_pContainer)
		{
			for(int i=0; i < _pContainer.size(); i++)
				_pContainer[i]->tagged=true;
		}

		bool LineSegmentPartOfVectorArray(const CLineSegment &_ls, const vector<CVector> &_vecArr);
		void CalculateCircleFrom3Points(const CVector& _p1, const CVector &_p2,const CVector &_p3, CCircle& _c);
		void DrawBorder(int _width, int _height, double _thickness);
		void GetLeftRightTopBottomFrom2Vecs(const CVector &_a, const CVector &_b, double &right, double &left,  double &top, double &bottom);
		void GetLeftRightTopBottomFromLineSegment(const CLineSegment &_ls, double &right, double &left,  double &top, double &bottom);
		bool IsCircleOutOfMap(int _HR, const CVector &_v, int _mHeight, int _mWidth , int _border = 0 );
		bool AddIntersection(double _upper, double _lower, double _y);
		bool ValueBetweenValues(double _v1, double _v2, double _value, double leeway=0 );

		double ToRadians(double degrees);
		double ToDegrees(double radians);

		int GetLowestPointIndx(const vector<CVector> &_points);



	//	bool ValueBetweenValuesWithLeeway(double _v1, double _v2, double _value, double leeWay );
		CLine GetTangentFromPointOnCircle(const CVector &_circleCenter, const CVector &_pointOnCircle);
	}
}
