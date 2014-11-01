/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef _SPLINE_H
#define _SPLINE_H

	#include"main.h"
	#include"Point.h"
	#include"Vector.h"
	#include"Matrix.h"
	#include<list>
	#include<vector>

	using namespace std;

	class Spline
	{
		private:
			int iContPoints;
			int iSpPoints;
			Point *ptsPoints;			
			Point *ptsControl;

			Vector *pvecTangent;
			Vector *pvecNormal;
			Vector *pvecCorssSection;			

			string strName;
			Color clSplineColr;

			void Subdivide(float fU0, float fU1, float fMaxLen, Matrix *pmatCMCont);

		public:
			vector<Point> lstPoints;
			vector<Vector> lstTangent;
			vector<Vector> lstNormal;
			vector<Vector> lstCross;

			Spline();
			Spline(string strName);

			void SetSplineColor(float fCR, float fCG, float fCB);
			void SetSplineColor(Color clSplineColr);
			int GetNumContPoints();
			int GetNumSpPoints();
			Point* GetContPoints();
			Point* GetSplinePoints();
			Vector* GetSplineTangentV();
			Vector* GetSplineCrossSectionV();
			Vector* GetSplineNormalV();
			Color* GetSplineColor();

			void ReadSpline(string strName);
			void DrawSpline(bool bColor);
			void GenerateSpline();
			void GenerateRecirsive();
			void GenerateSpline(Point ptLastSPPoint, Vector vecN, Vector vecB, Vector vecT);
			void ShowMinMax();
	};

#endif