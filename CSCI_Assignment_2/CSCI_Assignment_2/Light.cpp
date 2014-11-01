/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"Light.h"
#include"Color.h"
#include"Point.h"

Light::Light(GLenum lightID, Color Amb, Color Diff, Color Spec, Point Loc)
{
	this->iLightID = lightID;

	this->cmatAmb = Amb;
	this->cmatDiff = Diff;
	this->cmatSpec = Spec;
	this->ptLoc = Loc;
	
}

void Light::InitLight()
{	
}

void Light::ActivateLight()
{
	float fAmb[4] = {this->cmatAmb.GetR(), this->cmatAmb.GetG(), this->cmatAmb.GetB(), this->cmatAmb.GetA()};
	float fDiff[4] = {this->cmatDiff.GetR(), this->cmatDiff.GetG(), this->cmatDiff.GetB(), this->cmatDiff.GetA()};
	float fSpec[4] = {this->cmatSpec.GetR(), this->cmatSpec.GetG(), this->cmatSpec.GetB(), this->cmatSpec.GetA()};
	float fLoc[4] = {this->ptLoc.GetX(), this->ptLoc.GetY(), this->ptLoc.GetZ(), 1.0};
	float fVec[4] = {-1,0,0};

	glEnable(this->iLightID);
	glLightfv( this->iLightID, GL_AMBIENT, fAmb);
	glLightfv( this->iLightID, GL_DIFFUSE, fDiff);
	glLightfv( this->iLightID, GL_SPECULAR, fSpec);
	glLightfv( this->iLightID, GL_POSITION, fLoc);
    glLightfv( this->iLightID, GL_SPOT_DIRECTION,  fVec);
    glLightf( this->iLightID, GL_SPOT_EXPONENT, 0 );
    glLightf( this->iLightID, GL_SPOT_CUTOFF, 180.0 );
    glLightf( this->iLightID, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf( this->iLightID, GL_LINEAR_ATTENUATION, 0.0);
    glLightf( this->iLightID, GL_QUADRATIC_ATTENUATION, 0.0);
}

void Light::DeactivateLight()
{
	glDisable(this->iLightID);
}