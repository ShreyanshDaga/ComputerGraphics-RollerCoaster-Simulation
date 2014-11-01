/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef _COLOR_H
#define _COLOR_H

	#include"main.h"

	class Color
	{
		private:
			float fR;
			float fG;
			float fB;
			float fA;

		public:
			Color();
			Color(float fR, float fG, float fB);
			Color(float fR, float fG, float fB, float fA);

			void SetR(float fR);
			void SetG(float fG);
			void SetB(float fB);
			void SetA(float fA);

			float GetR();
			float GetG();
			float GetB();
			float GetA();

			static void SetColor(Color *pclColor);

			void operator = (Color &clColArg);
			bool operator == (Color &clColArg);
	};

#endif
