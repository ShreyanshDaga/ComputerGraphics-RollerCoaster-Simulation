/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"main.h"
#include"Material.h"

Material::Material(Color amb, Color Diff, Color Spec, float fShine)
{
	this->cmatAmb = amb;
	this->cmatDiff = Diff;
	this->cmatSpec = Spec;
	this->fShine = fShine;
}

void Material::Apply()
{
	float fAmb[4] = {this->cmatAmb.GetR(), this->cmatAmb.GetG(), this->cmatAmb.GetB(), this->cmatAmb.GetA()};
	float fDiff[4] = {this->cmatDiff.GetR(), this->cmatDiff.GetG(), this->cmatDiff.GetB(), this->cmatDiff.GetA()};
	float fSpec[4] = {this->cmatSpec.GetR(), this->cmatSpec.GetG(), this->cmatSpec.GetB(), this->cmatSpec.GetA()};
	
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,  fAmb);
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, fDiff);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, fSpec );    
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, this->fShine);
}