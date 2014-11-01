/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef _POINT_H
#define _POINT_H

	#include"main.h"
	#include"Color.h"

	class Point
	{
		private:
			//Co-ordinate
			float fX;
			float fY;
			float fZ;

			//Color
			Color clColor;

		public:
			Point();
			Point(float fX, float fY, float fZ);
			Point(float fX, float fY, float fZ, float fCBW);
			Point(float fX, float fY, float fZ, float fCR, float fCG, float fCB);

			float GetX();
			float GetY();
			float GetZ();
			float GetBW();
			float GetR();
			float GetG();
			float GetB();
			float GetAbsDistanceFrom(Point ptP);
			
			void SetPoint(float fX, float fY, float fZ);
			void SetColor(float fCR, float fCG, float fCB);

			void operator = (Point &ptP);
			Point operator + (Point &ptP);
	};

#endif