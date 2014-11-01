/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef _TRACK_H
#define _TRACK_H

	#include"main.h"
	#include"Point.h"
	#include"Spline.h"
	#include"Camera.h"

	class Track
	{
		private:
			int iNumOfSplines;
			int iSpPoints;			
			Spline *pspSplines;
			string strTrackName;

		public:
			Track();
			Track(string strTrackName);

			int GetNumOfSplines();
			int GetNumOfSplinePoints();

			void ReadTrackFile(string strTrackName);
			void GenerateTrack();
			void DrawTrack();

			void MoveCam(Camera *pcam1);
	};

#endif