/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef _MATERIAL_H
#define _MATERIAL_H

	#include"main.h"
	#include"Color.h"	

	class Material
	{
		private:
			Color cmatAmb;
			Color cmatDiff;
			Color cmatSpec;

			float fShine;

		public:
			Material(Color amb, Color Diff, Color Spec, float fShine);
			void Apply();
			
	};

#endif