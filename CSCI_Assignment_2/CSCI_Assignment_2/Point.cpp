/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"main.h"
#include"Point.h"

Point::Point()
{
	this->fX = 0.00;
	this->fY = 0.00;
	this->fZ = 0.00;

	this->clColor.SetR(0.00);
	this->clColor.SetG(0.00);
	this->clColor.SetB(0.00);
}

Point::Point(float fX, float fY, float fZ)
{
	this->fX = fX;
	this->fY = fY;
	this->fZ = fZ;	
}

Point::Point(float fX, float fY, float fZ, float fBW)
{
	this->fX = fX;
	this->fY = fY;
	this->fZ = fZ;

	this->clColor.SetR(fBW);
	this->clColor.SetG(fBW);
	this->clColor.SetB(fBW);
}

Point::Point(float fX, float fY, float fZ, float fCR, float fCG, float fCB)
{
	this->fX = fX;
	this->fY = fY;
	this->fZ = fZ;

	this->clColor.SetR(fCR);
	this->clColor.SetG(fCG);
	this->clColor.SetB(fCB);
}

float Point::GetX()
{
	return this->fX;
}

float Point::GetY()
{
	return this->fY;
}

float Point::GetZ()
{
	return this->fZ;
}

float Point::GetR()
{
	return this->clColor.GetR();
}

float Point::GetG()
{
	return this->clColor.GetG();
}

float Point::GetB()
{
	return this->clColor.GetB();
}

float Point::GetBW()
{
	return (0.30*this->clColor.GetR() + 0.59*this->clColor.GetG() + 0.11*this->clColor.GetB());
}

float Point::GetAbsDistanceFrom(Point ptP)
{
	float fX2, fY2, fZ2;
	float fDist;

	fX2 = this->fX - ptP.GetX();
	fY2 = this->fY - ptP.GetY();
	fZ2 = this->fZ - ptP.GetZ();

	fX2 = fX2*fX2;
	fY2 = fY2*fY2;
	fZ2 = fZ2*fZ2;

	fDist = sqrt(fX2 + fY2 + fZ2);

	return fDist;
}

void Point::SetPoint(float fX, float fY, float fZ)
{
	this->fX = fX;
	this->fY = fY;
	this->fZ = fZ;
}

void Point::SetColor(float fCR, float fCG, float fCB)
{
	this->clColor.SetR(fCR);
	this->clColor.SetG(fCG);
	this->clColor.SetB(fCB);
}

void Point::operator=(Point &ptP)
{
	this->fX = ptP.GetX();
	this->fY = ptP.GetY();
	this->fZ = ptP.GetZ();
}

Point Point::operator + (Point &ptP)
{
	Point pt;

	pt.fX = this->GetX() + ptP.GetX();
	pt.fY = this->GetY() + ptP.GetY();
	pt.fZ = this->GetZ() + ptP.GetZ();

	return pt;
}