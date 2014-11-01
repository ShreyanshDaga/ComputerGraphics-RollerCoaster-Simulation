/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"main.h"
#include"Camera.h"

Camera::Camera()
{
	this->fCamX = 0.00;
	this->fCamY = 0.00;
	this->fCamZ = 0.00;

	this->fEyeX = 0.00;
	this->fEyeY = 0.00;
	this->fEyeZ = 1.00;

	this->fUpX = 0.00;
	this->fUpY = 1.00;
	this->fUpZ = 0.00;
}

Camera::Camera(Point ptCam, Vector vecEye, Vector vecUp)
{
	this->fCamX = ptCam.GetX();
	this->fCamY = ptCam.GetY();
	this->fCamZ = ptCam.GetZ();

	this->fEyeX = vecEye.GetX();
	this->fEyeY = vecEye.GetY();
	this->fEyeZ = vecEye.GetZ();

	this->fUpX = vecUp.GetX();
	this->fUpY = vecUp.GetY();
	this->fUpZ = vecUp.GetZ();
}

void Camera::SetCamera(Point ptCam, Vector vecEye, Vector vecUp)
{
	this->fCamX = ptCam.GetX();
	this->fCamY = ptCam.GetY();
	this->fCamZ = ptCam.GetZ();

	this->fEyeX = vecEye.GetX();
	this->fEyeY = vecEye.GetY();
	this->fEyeZ = vecEye.GetZ();

	this->fUpX = vecUp.GetX();
	this->fUpY = vecUp.GetY();
	this->fUpZ = vecUp.GetZ();
}

void Camera::CamLook()
{
	gluLookAt(this->fCamX, this->fCamY, this->fCamZ, this->fEyeX, this->fEyeY, this->fEyeZ, this->fUpX, this->fUpY, this->fUpZ);
}

void Camera::CamLookAt(Point ptCam, Vector vecEye, Vector vecUp)
{
	this->SetCamera(ptCam, vecEye, vecUp);
	this->CamLook();
}