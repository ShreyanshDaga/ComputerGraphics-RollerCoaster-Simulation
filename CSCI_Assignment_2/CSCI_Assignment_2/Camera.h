/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef _CAMERA_H
#define _CAMERA_H

	#include"main.h"
	#include"Point.h"
	#include"Vector.h"

	class Camera
	{
		public:
			float fCamX, fCamY, fCamZ;
			float fEyeX, fEyeY, fEyeZ;
			float fUpX, fUpY, fUpZ;

		public:
			Camera();
			Camera(Point ptCam, Vector vecEye, Vector vecUp);

			void SetCamera(Point ptCam, Vector vecEye, Vector vecUp);
			void CamLook();
			void CamLookAt(Point ptCam, Vector vecEye, Vector vecUp);			
	};

#endif