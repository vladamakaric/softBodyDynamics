#pragma once

#include "Vector.h"
#include "f_distance.h"
#include "draw.h"

//#include <boost/math/special_functions/asinh.hpp>
class COrientedParabola
{
public:
	COrientedParabola(double baseWidth, double arcLenth)
	{
		b = baseWidth/2;
		a = CalculateAFromWAndRL(baseWidth/2, arcLenth/2);
	}

	COrientedParabola(const CVector &p0, const CVector &p1, const CVector &p2)
	{
		b = F::DISTANCE::GetDistance(p0,p2)/2;
		CVector middle = (p0 + p2)/2;

		double heigth = F::DISTANCE::GetDistance(middle, p1);
		a = heigth/(b*b);
	}

	void Draw()
	{

		CVector coords[21];

		double tempX = -b;
		double xStep = (b*2)/20;

		for(int i=0; i< 21; i++)
		{
			coords[i] = CVector( tempX + 400, a*(b*b - tempX*tempX));
			tempX += xStep;
		}


		Draw::Line(coords, 21);
	}

	double CalculateAFromWAndRL(double x, double q)
	{
		//return (sqrt(3.0/2.0)*sqrt(rl-w))/pow(w, 3/2);

		return sqrt((5 * x*x*x - sqrt(5.0)*sqrt( (x*x*x*x*x) * (23*x - 18*q)))/ (x*x*x*x*x))/sqrt(6.0);

	}

	double SnajderSize()
	{
//		return 2*(b+(2 * pow(a,2) * pow(b,3))/3-(2 * pow(b,4) * pow(b,5))/5+(4 *pow(a,6) * pow(b,7))/7-(10 * pow(a,8) * pow(b,9))/9+(28 * pow(a,10) * pow(b,11))/11-(84 * pow(a,12) * pow(b,13))/13+(88 * pow(a,14) * pow(b,15))/5-(858 *  pow(a,16) * pow(b,17))/17);
	



		double s =  b + (2 * pow(a,2) * pow(b,3))/3;
					//	(2 * pow(a,4) * pow(b,5))/5;
						//(4 * pow(a,6) * pow(b,7))/7;
					//	(10 * pow(a,8) * pow(b,9))/9 +
						//(28 * pow(a,10) * pow(b,11))/11 - 
						//(84 * pow(a,12) * pow(b,13))/13;
						//(88 * pow(a,14) * pow(b,15))/ 5  - 
						//(858 *  pow(a,16) * pow(b,17))/17;
	
		return 2*s;

	}

	double SehiSize()
	{
		return 2*(2*a*b*sqrt(1 + 4*a*a*b*b) +2);// boost::math::asinh(2*a*b))/(4*a);
	}

	double LjakSize()
	{
		CVector coords[21];

		double tempX = -b;
		double xStep = (b*2)/20;

		for(int i=0; i< 21; i++)
		{
			coords[i] = CVector( tempX + 400, a*(b*b - tempX*tempX));
			tempX += xStep;
		}

		double sum = 0;

		for(int i=0; i<20; i++)
		{
			sum += F::DISTANCE::GetDistance(coords[i],coords[i+1]);
		}

		return sum;
	}

	//y = a(b^2 - x^2)
	double b,a;




};