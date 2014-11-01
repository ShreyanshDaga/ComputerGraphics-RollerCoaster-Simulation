/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef _LIGHT_H
#define _LIGHT_H

	#include"main.h"
	#include"Color.h"
	#include"Point.h"

	class Light
	{
		private:
			GLenum iLightID;
			Color cmatAmb;
			Color cmatSpec;
			Color cmatDiff;
			Point ptLoc;

		public:
			Light(GLenum lightID, Color Amb, Color Diff, Color Spec, Point Loc);
			
			void InitLight();
			void ActivateLight();
			void DeactivateLight();
	};

#endif