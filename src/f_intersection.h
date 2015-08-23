#pragma once
#include "Vector.h"
#include "Line.h"
#include "LineSegment.h"
#include "Circle.h"
#include "Square.h"

namespace F
{
	namespace INTERSECTION
	{
		CVector GetLineIntersection(const CLine &_a, const CLine &_b);
		int GetLineCircleIntersection(const CLine &_l, const CCircle &_c, CVector *_interPoints, bool checkForIntersection = true);
		int GetLineSegmentCircleIntersection(const CLineSegment &_ls, const CCircle &_c, CVector *_interPoints, bool checkForIntersection = true);
		bool CircleOutOfSquare(const CCircle &_c, const CSquare &_s);

		bool LineSegmentIntersection2(const CLineSegment &_ls1, const CLineSegment &_ls2, CVector *_ip = 0);

		CVector LineIntersection(const CLine &_l, const CLine &_l2);

		bool PointInPolygon(const CVector& _v, const vector<CVector> &_polygon);
		bool CircleInSquare(const CCircle &_c, const CSquare &_s);
		bool PointInSquare(const CVector &_p, const CSquare &_s);
		bool PointInCircle(const CVector &_p, const CCircle &_c);
		bool PointOnLineOnLineSegment(const CVector &_p, const CLineSegment &_ls);
		bool LineSegmentIntersection(const CLineSegment &_ls1, const CLineSegment &_ls2, CVector *_ip = 0);
		bool PointProjectionOnLineSegment(const CVector &_p, const CLineSegment &_ls);
		bool LineSegmentIntersectsCircle(const CLineSegment &_ls, const CCircle &_c);
		bool LineIntersectsCircle(const CLine &_l, const CCircle &_c);
		bool CircleIntersectsCircle(const CCircle &_c1, const CCircle &_c2);
	}
}