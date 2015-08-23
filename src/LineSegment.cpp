#include "LineSegment.h"
#include "f_distance.h"
#include "draw.h"

int CLineSegment::globalID=0;

double CLineSegment::Lenght() const
{
	return F::DISTANCE::GetDistance(a,b);
}

void CLineSegment::Draw()
{
	Draw::Line(a,b);
}
