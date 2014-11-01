/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"main.h"
#include"Vector.h"

Vector::Vector()
{
	this->fX = 0.00;
	this->fY = 0.00;
	this->fZ = 0.00;
	this->fMag = 0.00;
}

Vector::Vector(float fX, float fY, float fZ)
{
	this->fX = fX;
	this->fY = fY;
	this->fZ = fZ;
	this->fMag = sqrtf(fX*fX + fY*fY + fZ*fZ );
}

Vector* Vector::GetUnitVector()
{
	Vector *pvecNew = new Vector();
	pvecNew->SetVector(this->fX/this->fMag, this->fY/this->fMag, this->fZ/this->fMag);

	return pvecNew;
}

float Vector::GetMagnitude()
{
	return this->fMag;
}

float Vector::GetX()
{
	return this->fX;
}

float Vector::GetY()
{
	return this->fY;
}

float Vector::GetZ()
{
	return this->fZ;
}

void Vector::SetVector(float fX, float fY, float fZ)
{
	this->fX = fX;
	this->fY = fY;
	this->fZ = fZ;
	this->fMag = sqrtf(fX*fX + fY*fY + fZ*fZ );
}

void Vector::SetVector(Vector vecV)
{
	this->fX = vecV.GetX();
	this->fY = vecV.GetY();
	this->fZ = vecV.GetZ();
	this->fMag = vecV.GetMagnitude();
}
		
Vector* Vector::VectorCrossProduct(Vector V1, Vector V2)
{
	Vector *pvecNew = new Vector();

	float fX = V1.GetY()*V2.GetZ() - V1.GetZ()*V2.GetY();
	float fY = V1.GetZ()*V2.GetX() - V1.GetX()*V2.GetZ();
	float fZ = V1.GetX()*V2.GetY() - V1.GetY()*V2.GetX();

	pvecNew->SetVector(fX,fY,fZ);

	return pvecNew;
}

float Vector::VectorDotProduct(Vector V1, Vector V2)
{
	return (V1.GetX()*V2.GetX() + V1.GetY()*V2.GetY() + V1.GetZ()*V2.GetZ());
}

void Vector::operator= (Vector &vecV)
{
	this->SetVector(vecV);
}

Vector* Vector::operator* (float fScal)
{
	Vector *pvecNew = new Vector();

	pvecNew->SetVector(fScal*this->GetX(), fScal*this->GetY(), fScal*this->GetZ());

	return pvecNew;
}

Vector Vector::operator - (Vector &vecV)
{
	Vector pvecNew;// = new Vector();

	pvecNew.SetVector(this->fX - vecV.GetX(), this->fY - vecV.GetY(), this->fZ - vecV.GetZ());

	return pvecNew;
}

Vector Vector::operator - ()
{
	Vector pvecNew;// = new Vector();

	pvecNew.SetVector(-this->fX , -this->fY , -this->fZ);

	return pvecNew;
}

Vector Vector::operator + (Vector &vecV)
{
	Vector pvecNew;// = new Vector();

	pvecNew.SetVector(this->fX + vecV.GetX(), this->fY + vecV.GetY(), this->fZ + vecV.GetZ());

	return pvecNew;
}

void Vector::operator *= (float fScale)
{
	this->fX *= fScale;
	this->fY *= fScale;
	this->fZ *= fScale;
}
