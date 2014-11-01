/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"main.h"
#include"Spline.h"
#include"Matrix.h"
#include"Texture.h"

extern Texture txrRail;
//extern GLuint texName[3];

Spline::Spline()
{
	this->iContPoints = 0;
	this->ptsPoints = NULL;

	this->clSplineColr.SetR(0.1);
	this->clSplineColr.SetG(0.1);
	this->clSplineColr.SetB(0.1);
}

Spline::Spline(string strName)
{
	this->ReadSpline(strName);

	this->clSplineColr.SetR(1.0);
	this->clSplineColr.SetG(1.0);
	this->clSplineColr.SetB(0.1);
}

void Spline::ReadSpline(string strName)
{
	FILE *fpSplineFile = fopen(strName.c_str(),"r");
	int iType, iLength, i = 0;

	if(fpSplineFile == NULL)
	{
		cout<<"\nSpline File Error: "<<strName<<" Unable to read file";
		return;
	}

	cout<<"\n *Reading Spline File "<<strName<<"...";

	this->strName = strName;

	//Read length and type
	fscanf(fpSplineFile,"%d %d",&iLength,&iType);

	//Allocate memory for points in spline
	this->ptsControl = new Point[iLength];
	this->iContPoints = iLength;

	double dX,dY,dZ;

	while(fscanf(fpSplineFile,"%lf %lf %lf", &dX, &dY, &dZ) != EOF)
	{
		this->ptsControl[i].SetPoint(dX,dY,dZ);
		i++;
	}

	fclose(fpSplineFile);

	cout<<"\n *Reading complete.!";
	//this->GenerateSpline();
}

void Spline::DrawSpline(bool bColor)
{
	if(bColor)
	{
		glPushAttrib(GL_COLOR);
		Color::SetColor(&this->clSplineColr);		
	}

	for(int i = 0;i<this->iSpPoints-1;i++)
	{
		Vector *pScalarVec, vecN2, vecB2, vecN1, vecB1;
		float a = 0.01;

		vecB1.SetVector(this->lstCross[i]);
		vecB2.SetVector(this->lstCross[i+1]);	
		vecN1.SetVector(this->lstNormal[i]);
		vecN2.SetVector(this->lstNormal[i+1]);

		float fx1,fy1,fz1;
		float fx2,fy2,fz2;

		glLineWidth(1.0);		
		fx1 = this->lstPoints[i].GetX();
		fy1 = this->lstPoints[i].GetY();
		fz1 = this->lstPoints[i].GetZ();
		
		fx2 = this->lstPoints[i+1].GetX();
		fy2 = this->lstPoints[i+1].GetY();
		fz2 = this->lstPoints[i+1].GetZ();
		
		float fLx1, fLy1, fLz1;
		float fRx1, fRy1, fRz1;		

		pScalarVec = vecB1 * 0.10f;		
		fLx1 = pScalarVec->GetX() + fx1;
		fLy1 = pScalarVec->GetY() + fy1;
		fLz1 = pScalarVec->GetZ() + fz1;

		delete pScalarVec;		
		
		pScalarVec = vecB1 * -0.10f;
		fRx1 = pScalarVec->GetX() + fx1;
		fRy1 =  pScalarVec->GetY() + fy1;
		fRz1 =  pScalarVec->GetZ() + fz1;
			
		delete pScalarVec;

		float fLx2,fLy2,fLz2;
		float fRx2, fRy2, fRz2;		
			
		pScalarVec = vecB1 * 0.10f;
		fLx2 = pScalarVec->GetX() + fx2;
		fLy2 = pScalarVec->GetY() + fy2;
		fLz2 = pScalarVec->GetZ() + fz2;		
		
		delete pScalarVec;		
		
		pScalarVec = vecB1 * -0.10f;
		fRx2 = pScalarVec->GetX() + fx2;
		fRy2 = pScalarVec->GetY() + fy2;
		fRz2 = pScalarVec->GetZ() + fz2;

		delete pScalarVec;

		Vector vecDiff;

		float fR1ULx, fR1ULy, fR1ULz;
		float fR1URx, fR1URy, fR1URz;
		float fR1BLx, fR1BLy, fR1BLz;
		float fR1BRx, fR1BRy, fR1BRz;
		//R1 all 4 CO-ordinates		
		//UL
		vecDiff = vecN1 - vecB1;
		vecDiff *= a;		
		fR1ULx = fRx1 + vecDiff.GetX();
		fR1ULy = fRy1 + vecDiff.GetY();
		fR1ULz = fRz1 + vecDiff.GetZ();

		//UR
		vecDiff = vecB1 + vecN1;
		vecDiff *= a;		
		fR1URx = fRx1 + vecDiff.GetX();
		fR1URy = fRy1 + vecDiff.GetY();
		fR1URz = fRz1 + vecDiff.GetZ();		

		//BL
		vecDiff = -vecN1 - vecB1;
		vecDiff *= a;		
		fR1BLx = fRx1 + vecDiff.GetX();
		fR1BLy = fRy1 + vecDiff.GetY();
		fR1BLz = fRz1 + vecDiff.GetZ();		

		//BR
		vecDiff = vecB1 - vecN1;
		vecDiff *= a;		
		fR1BRx = fRx1 + vecDiff.GetX();
		fR1BRy = fRy1 + vecDiff.GetY();
		fR1BRz = fRz1 + vecDiff.GetZ();		

		float fL1ULx, fL1ULy, fL1ULz;
		float fL1URx, fL1URy, fL1URz;
		float fL1BLx, fL1BLy, fL1BLz;
		float fL1BRx, fL1BRy, fL1BRz;
		//L1 all 4 CO-ordinates
		//UL
		vecDiff = vecN1 - vecB1;
		vecDiff *= a;		
		fL1ULx = fLx1 + vecDiff.GetX();
		fL1ULy = fLy1 + vecDiff.GetY();
		fL1ULz = fLz1 + vecDiff.GetZ();

		//UR
		vecDiff = vecB1 + vecN1;
		vecDiff *= a;		
		fL1URx = fLx1 + vecDiff.GetX();
		fL1URy = fLy1 + vecDiff.GetY();
		fL1URz = fLz1 + vecDiff.GetZ();		

		//BL
		vecDiff = - vecN1 - vecB1;
		vecDiff *= a;		
		fL1BLx = fLx1 + vecDiff.GetX();
		fL1BLy = fLy1 + vecDiff.GetY();
		fL1BLz = fLz1 + vecDiff.GetZ();		

		//BR
		vecDiff = vecB1 - vecN1;
		vecDiff *= a;		
		fL1BRx = fLx1 + vecDiff.GetX();
		fL1BRy = fLy1 + vecDiff.GetY();
		fL1BRz = fLz1 + vecDiff.GetZ();

		float fR2ULx, fR2ULy, fR2ULz;
		float fR2URx, fR2URy, fR2URz;
		float fR2BLx, fR2BLy, fR2BLz;
		float fR2BRx, fR2BRy, fR2BRz;
		//R2 all 4 Co-ordinates
		//UL
		vecDiff = vecN1 - vecB1;
		vecDiff *= a;		
		fR2ULx = fRx2 + vecDiff.GetX();
		fR2ULy = fRy2 + vecDiff.GetY();
		fR2ULz = fRz2 + vecDiff.GetZ();

		//UR
		vecDiff = vecN1 + vecB1;
		vecDiff *= a;		
		fR2URx = fRx2 + vecDiff.GetX();
		fR2URy = fRy2 + vecDiff.GetY();
		fR2URz = fRz2 + vecDiff.GetZ();		

		//BL
		vecDiff =  - vecN1 - vecB1;
		vecDiff *= a;		
		fR2BLx = fRx2 + vecDiff.GetX();
		fR2BLy = fRy2 + vecDiff.GetY();
		fR2BLz = fRz2 + vecDiff.GetZ();		

		//BR
		vecDiff = vecB1 - vecN1;
		vecDiff *= a;		
		fR2BRx = fRx2 + vecDiff.GetX();
		fR2BRy = fRy2 + vecDiff.GetY();
		fR2BRz = fRz2 + vecDiff.GetZ();

		float fL2ULx, fL2ULy, fL2ULz;
		float fL2URx, fL2URy, fL2URz;
		float fL2BLx, fL2BLy, fL2BLz;
		float fL2BRx, fL2BRy, fL2BRz;
		//L2 all 4 Co-ordinates
		//UL
		vecDiff = vecN1 - vecB1;
		vecDiff *= a;		
		fL2ULx = fLx2 + vecDiff.GetX();
		fL2ULy = fLy2 + vecDiff.GetY();
		fL2ULz = fLz2 + vecDiff.GetZ();

		//UR
		vecDiff = vecN1 + vecB1;
		vecDiff *= a;		
		fL2URx = fLx2 + vecDiff.GetX();
		fL2URy = fLy2 + vecDiff.GetY();
		fL2URz = fLz2 + vecDiff.GetZ();		

		//BL
		vecDiff =  - vecN1 - vecB1;
		vecDiff *= a;		
		fL2BLx = fLx2 + vecDiff.GetX();
		fL2BLy = fLy2 + vecDiff.GetY();
		fL2BLz = fLz2 + vecDiff.GetZ();		

		//BR
		vecDiff = vecB1 - vecN1;
		vecDiff *= a;		
		fL2BRx = fLx2 + vecDiff.GetX();
		fL2BRy = fLy2 + vecDiff.GetY();
		fL2BRz = fLz2 + vecDiff.GetZ();

		//Rail QUADS		
		glColor3f(1.0,0.10,0);
		glBegin(GL_QUADS);
			//Rail R				
			//Top Face
			glVertex3f(fR1ULx, fR1ULy, fR1ULz);
			glVertex3f(fR1URx, fR1URy, fR1URz);
			glVertex3f(fR2URx, fR2URy, fR2URz);
			glVertex3f(fR2ULx, fR2ULy, fR2ULz);				
			//Bottom	Face	
			glVertex3f(fR1BLx, fR1BLy, fR1BLz);
			glVertex3f(fR1BRx, fR1BRy, fR1BRz);
			glVertex3f(fR2BRx, fR2BRy, fR2BRz);
			glVertex3f(fR2BLx, fR2BLy, fR2BLz);
			//Left	Face
			glVertex3f(fR1ULx, fR1ULy, fR1ULz);
			glVertex3f(fR2ULx, fR2ULy, fR2ULz);
			glVertex3f(fR2BLx, fR2BLy, fR2BLz);
			glVertex3f(fR1BLx, fR1BLy, fR1BLz);
			//Right	 Face	
			glVertex3f(fR1URx, fR1URy, fR1URz);
			glVertex3f(fR2URx, fR2URy, fR2URz);
			glVertex3f(fR2BRx, fR2BRy, fR2BRz);
			glVertex3f(fR1BRx, fR1BRy, fR1BRz);

			//Rail L
			//Top face
			glVertex3f(fL1ULx, fL1ULy, fL1ULz);
			glVertex3f(fL1URx, fL1URy, fL1URz);
			glVertex3f(fL2URx, fL2URy, fL2URz);
			glVertex3f(fL2ULx, fL2ULy, fL2ULz);
			//Bottom	Face	
			glVertex3f(fL1BLx, fL1BLy, fL1BLz);
			glVertex3f(fL1BRx, fL1BRy, fL1BRz);
			glVertex3f(fL2BRx, fL2BRy, fL2BRz);			
			glVertex3f(fL2BLx, fL2BLy, fL2BLz);
			//Left Face				
			glVertex3f(fL1ULx, fL1ULy, fL1ULz);			
			glVertex3f(fL2ULx, fL2ULy, fL2ULz);			
			glVertex3f(fL2BLx, fL2BLy, fL2BLz);			
			glVertex3f(fL1BLx, fL1BLy, fL1BLz);
			//Right	Face				
			glVertex3f(fL1URx, fL1URy, fL1URz);			
			glVertex3f(fL2URx, fL2URy, fL2URz);			
			glVertex3f(fL2BRx, fL2BRy, fL2BRz);			
			glVertex3f(fL1BRx, fL1BRy, fL1BRz);
		glEnd();

		//Rail Sleepers		
		if(i%8 == 0)
		{
			txrRail.BindTexture();			
			//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);			
			glBegin(GL_QUADS);
				glTexCoord2f(0.0,0.0);	 glVertex3f(fR1BLx, fR1BLy, fR1BLz);
				glTexCoord2f(0.0,1.0); glVertex3f(fR2BLx, fR2BLy, fR2BLz);
				glTexCoord2f(1.0,1.0); glVertex3f(fL2BRx, fL2BRy, fL2BRz);
				glTexCoord2f(1.0,0.0); glVertex3f(fL1BRx, fL1BRy, fL1BRz);
			glEnd();
			txrRail.UnBindTexture();			
		}		

		//Rail Solid Lines
		glLineWidth(2.0);
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINES);
			//R Rail
			glVertex3f(fR1ULx, fR1ULy, fR1ULz);
			glVertex3f(fR2ULx, fR2ULy, fR2ULz);
			glVertex3f(fR1BLx, fR1BLy, fR1BLz);
			glVertex3f(fR2BLx, fR2BLy, fR2BLz);
			glVertex3f(fR1URx, fR1URy, fR1URz);
			glVertex3f(fR2URx, fR2URy, fR2URz);
			glVertex3f(fR1BRx, fR1BRy, fR1BRz);
			glVertex3f(fR2BRx, fR2BRy, fR2BRz);

			//L Rail
			glVertex3f(fL1ULx, fL1ULy, fL1ULz);
			glVertex3f(fL2ULx, fL2ULy, fL2ULz);
			glVertex3f(fL1BLx, fL1BLy, fL1BLz);
			glVertex3f(fL2BLx, fL2BLy, fL2BLz);
			glVertex3f(fL1URx, fL1URy, fL1URz);
			glVertex3f(fL2URx, fL2URy, fL2URz);		
			glVertex3f(fL1BRx, fL1BRy, fL1BRz);
			glVertex3f(fL2BRx, fL2BRy, fL2BRz);
		glEnd();		
	}

	if(bColor)
		glPopAttrib();
}

void Spline::SetSplineColor(Color clSplineColr)
{
	this->clSplineColr = clSplineColr;
}

void Spline::GenerateSpline()
{
	Matrix matU(1,4);
	Matrix matUdiff(1,4);
	Matrix *pmatXYZ;
	Matrix matCatmullRomBasis(4);
	Matrix matControl(4,3);
	Matrix *pmatTemp;

	Point ptP0, ptP1, ptP2, ptP3;

	float s = 0.500f;

	float faCatRomBasis[16] = {-s,2-s,s-2,s,2*s,s-3,3-2*s,-s,-s,0,s,0,0,1,0,0};		
	float faU[4] = {0.00,0.00,0.00,0.00};
	float faUdiff[4] = {0.00,0.00,0.00,0.0};

	matCatmullRomBasis.SetElements(faCatRomBasis);	

	//100 Points
	this->ptsPoints = new Point[(this->iContPoints-3)*101];
	this->pvecTangent = new Vector[(this->iContPoints-3)*101];
	this->pvecCorssSection = new Vector[(this->iContPoints-3)*101];
	this->pvecNormal = new Vector[(this->iContPoints-3)*101];
	this->iSpPoints = (this->iContPoints-3)*101;	

	int i = 0;

	for(int c = 0;c < this->iContPoints - 3;c++)
	{	
		ptP0 = this->ptsControl[c];
		ptP1 = this->ptsControl[c+1];
		ptP2 = this->ptsControl[c+2];
		ptP3 = this->ptsControl[c+3];

		float faControl[12] = {ptP0.GetX(), ptP0.GetY(), ptP0.GetZ(), ptP1.GetX(), ptP1.GetY(), ptP1.GetZ(), ptP2.GetX(), ptP2.GetY(), ptP2.GetZ(), ptP3.GetX(), ptP3.GetY(), ptP3.GetZ()};
		matControl.SetElements(faControl);
		pmatTemp = Matrix::MatrixMultiply(matCatmullRomBasis,matControl);
		
		for(float u = 0.00f;u <= 1.00f;u+=0.01)
		{
			faU[3] = 1.00f;
			faU[2] = u;
			faU[1] = faU[2]*u;
			faU[0] = faU[1]*u;

			faUdiff[0] = 3*u*u;
			faUdiff[1] = 2*u;
			faUdiff[2] = 1;
			faUdiff[3] = 0;
			
			matU.SetElements(faU);
			matUdiff.SetElements(faUdiff);

			pmatXYZ = Matrix::MatrixMultiply(matU,*pmatTemp);

			//Array
			this->ptsPoints[i].SetPoint(pmatXYZ->GetElement(0,0), pmatXYZ->GetElement(0,1), pmatXYZ->GetElement(0,2));
			this->ptsPoints[i].SetColor(1.00,0,0);					
			pmatXYZ->FreeMemory();		

			pmatXYZ = Matrix::MatrixMultiply(matUdiff,*pmatTemp);
			this->pvecTangent[i].SetVector(pmatXYZ->GetElement(0,0), pmatXYZ->GetElement(0,1), pmatXYZ->GetElement(0,2));			
			pmatXYZ->FreeMemory();

			Vector *pvUnit, *pvCross;
			if(i == 0)
			{
				this->pvecNormal[0].SetVector(0,1,0);

				pvCross = Vector::VectorCrossProduct(this->pvecTangent[0], this->pvecNormal[0]);
				pvUnit = pvCross->GetUnitVector();

				this->pvecCorssSection[0] = *pvUnit;

				delete pvCross;
				delete pvUnit;
			}
			else
			{
				pvCross = Vector::VectorCrossProduct(this->pvecCorssSection[i-1],this->pvecTangent[i]);
				pvUnit = pvCross->GetUnitVector();
				this->pvecNormal[i] = *pvUnit;
				//this->pvecNormal[i].SetVector(this->pvecNormal[i].GetX(),sqrt(this->pvecNormal[i].GetY()*this->pvecNormal[i].GetY()), this->pvecNormal[i].GetZ());
				delete pvCross;
				delete pvUnit;

				pvCross = Vector::VectorCrossProduct(this->pvecTangent[i], this->pvecNormal[i]);
				pvUnit = pvCross->GetUnitVector();
				this->pvecCorssSection[i] = *pvUnit;
				//this->pvecCorssSection[i].SetVector(-sqrt(this->pvecCorssSection[i].GetX()*this->pvecCorssSection[i].GetX()),this->pvecCorssSection[i].GetY(), this->pvecCorssSection[i].GetZ());
				delete pvCross;
				delete pvUnit;
			}
			//cout<<"\nI; "<<i;
			i++;				
		}
	}
}

void Spline::GenerateRecirsive()
{
	Matrix matCatmullRomBasis(4);
	Matrix matControl(4,3);
	Matrix *pmatTemp;

	Point ptP0, ptP1, ptP2, ptP3;

	float s = 0.500f;

	float faCatRomBasis[16] = {-s,2-s,s-2,s,2*s,s-3,3-2*s,-s,-s,0,s,0,0,1,0,0};	

	matCatmullRomBasis.SetElements(faCatRomBasis);

	this->iSpPoints = 0;

	for(int c = 0;c < this->iContPoints - 3;c++)
	{	
		ptP0 = this->ptsControl[c];
		ptP1 = this->ptsControl[c+1];
		ptP2 = this->ptsControl[c+2];
		ptP3 = this->ptsControl[c+3];

		float faControl[12] = {ptP0.GetX(), ptP0.GetY(), ptP0.GetZ(), ptP1.GetX(), ptP1.GetY(), ptP1.GetZ(), ptP2.GetX(), ptP2.GetY(), ptP2.GetZ(), ptP3.GetX(), ptP3.GetY(), ptP3.GetZ()};
		matControl.SetElements(faControl);
		pmatTemp = Matrix::MatrixMultiply(matCatmullRomBasis,matControl);

		Subdivide(0.00, 1.00, 0.08, pmatTemp);
	}

	cout<<"\nSize of lstPoints: "<<this->lstPoints.size();
	cout<<"\nSize of lstTangent: "<<this->lstTangent.size();
	cout<<"\nSize of lstNormal: "<<this->lstNormal.size();
	cout<<"\nSize of lstCross: "<<this->lstCross.size();
}

void Spline::GenerateSpline(Point ptLastSPPoint, Vector vecN, Vector vecB, Vector vecT)
{
	Matrix matU(1,4);
	Matrix matUdiff(1,4);
	Matrix *pmatXYZ;
	Matrix matCatmullRomBasis(4);
	Matrix matControl(4,3);
	Matrix *pmatTemp;

	Point ptP0, ptP1, ptP2, ptP3;

	float s = 0.500f;

	float faCatRomBasis[16] = {-s,2-s,s-2,s,2*s,s-3,3-2*s,-s,-s,0,s,0,0,1,0,0};	
	//float faControl[12] = {ptP0.GetX(), ptP0.GetY(), ptP0.GetZ(), ptP1.GetX(), ptP1.GetY(), ptP1.GetZ(), ptP2.GetX(), ptP2.GetY(), ptP2.GetZ(), ptP3.GetX(), ptP3.GetY(), ptP3.GetZ()};
	float faU[4] = {0.00,0.00,0.00,0.00};
	float faUdiff[4] = {0.00,0.00,0.00,0.0};

	matCatmullRomBasis.SetElements(faCatRomBasis);	

	//101 Points
	this->ptsPoints = new Point[(this->iContPoints-3)*101];
	this->pvecTangent = new Vector[(this->iContPoints-3)*101];
	this->pvecCorssSection = new Vector[(this->iContPoints-3)*101];
	this->pvecNormal = new Vector[(this->iContPoints-3)*101];
	this->iSpPoints = (this->iContPoints-3)*101;
	int i = 0;

	for(int c = 0;c < this->iContPoints - 3;c++)
	{	
		ptP0 = this->ptsControl[c];
		ptP1 = this->ptsControl[c+1];
		ptP2 = this->ptsControl[c+2];
		ptP3 = this->ptsControl[c+3];

		float faControl[12] = {ptP0.GetX(), ptP0.GetY(), ptP0.GetZ(), ptP1.GetX(), ptP1.GetY(), ptP1.GetZ(), ptP2.GetX(), ptP2.GetY(), ptP2.GetZ(), ptP3.GetX(), ptP3.GetY(), ptP3.GetZ()};
		matControl.SetElements(faControl);
		pmatTemp = Matrix::MatrixMultiply(matCatmullRomBasis,matControl);
		
		for(float u = 0.00f;u <= 1.00f;u+=0.01)
		{
			faU[3] = 1.00f;
			faU[2] = u;
			faU[1] = faU[2]*u;
			faU[0] = faU[1]*u;

			faUdiff[0] = 3*u*u;
			faUdiff[1] = 2*u;
			faUdiff[2] = 1;
			faUdiff[3] = 0;
			

			matU.SetElements(faU);
			matUdiff.SetElements(faUdiff);

			pmatXYZ = Matrix::MatrixMultiply(matU,*pmatTemp);

			this->ptsPoints[i].SetPoint(pmatXYZ->GetElement(0,0), pmatXYZ->GetElement(0,1), pmatXYZ->GetElement(0,2));
			this->ptsPoints[i] = this->ptsPoints[i] + ptLastSPPoint;
			this->ptsPoints[i].SetColor(1.00,0,0);			
			pmatXYZ->FreeMemory();		

			pmatXYZ = Matrix::MatrixMultiply(matUdiff,*pmatTemp);
			this->pvecTangent[i].SetVector(pmatXYZ->GetElement(0,0), pmatXYZ->GetElement(0,1), pmatXYZ->GetElement(0,2));			
			pmatXYZ->FreeMemory();

			Vector *pvUnit, *pvCross;
			if(i == 0)
			{
				pvCross = Vector::VectorCrossProduct(vecB, this->pvecTangent[0]);
				pvUnit = pvCross->GetUnitVector();
				this->pvecNormal[0] = *pvUnit;
				
				delete pvCross;
				delete pvUnit;

				pvCross = Vector::VectorCrossProduct(this->pvecTangent[0], this->pvecNormal[0]);
				pvUnit = pvCross->GetUnitVector();

				this->pvecCorssSection[0] = *pvUnit;

				delete pvCross;
				delete pvUnit;
			}
			else
			{
				pvCross = Vector::VectorCrossProduct(this->pvecCorssSection[i-1],this->pvecTangent[i]);
				pvUnit = pvCross->GetUnitVector();
				this->pvecNormal[i] = *pvUnit;
				//this->pvecNormal[i].SetVector(this->pvecNormal[i].GetX(),sqrt(this->pvecNormal[i].GetY()*this->pvecNormal[i].GetY()), this->pvecNormal[i].GetZ());
				delete pvCross;
				delete pvUnit;

				pvCross = Vector::VectorCrossProduct(this->pvecTangent[i], this->pvecNormal[i]);
				pvUnit = pvCross->GetUnitVector();
				this->pvecCorssSection[i] = *pvUnit;
				//this->pvecCorssSection[i].SetVector(-sqrt(this->pvecCorssSection[i].GetX()*this->pvecCorssSection[i].GetX()),this->pvecCorssSection[i].GetY(), this->pvecCorssSection[i].GetZ());
				delete pvCross;
				delete pvUnit;
			}
			//cout<<"\nI; "<<i;
			i++;				
		}
	}
}

int Spline::GetNumContPoints()
{
	return this->iContPoints;
}

int Spline::GetNumSpPoints()
{
	return this->iSpPoints;
}

Point* Spline::GetContPoints()
{
	return this->ptsControl;
}

Point* Spline::GetSplinePoints()
{
	return this->ptsPoints;
}

Vector* Spline::GetSplineTangentV()
{
	return this->pvecTangent;
}

Vector* Spline::GetSplineCrossSectionV()
{
	return this->pvecCorssSection;
}

Vector* Spline::GetSplineNormalV()
{
	return this->pvecNormal;
}

void Spline::ShowMinMax()
{
	float fMinX=0.00, fMinY=0.00, fMinZ=0.00, fMaxX=0.00, fMaxY=0.00, fMaxZ=0.00;

	for(int i = 0;i<this->iSpPoints-1;i++)
	{
		if(fMinX > this->ptsPoints[i].GetX())
			fMinX = this->ptsPoints[i].GetX();

		if(fMinY > this->ptsPoints[i].GetY())
			fMinY = this->ptsPoints[i].GetY();

		if(fMinZ > this->ptsPoints[i].GetZ())
			fMinZ = this->ptsPoints[i].GetZ();

		if(fMaxX < this->ptsPoints[i].GetX())
			fMaxX = this->ptsPoints[i].GetX();

		if(fMaxY < this->ptsPoints[i].GetY())
			fMaxY = this->ptsPoints[i].GetY();

		if(fMaxZ < this->ptsPoints[i].GetZ())
			fMaxZ = this->ptsPoints[i].GetZ();
	}

	cout<<"\nMax X: "<<fMaxX<<" Min X: "<<fMinX;
	cout<<"\nMax Y: "<<fMaxY<<" Min Y: "<<fMinY;
	cout<<"\nMax Z: "<<fMaxZ<<" Min Z: "<<fMinZ;
}

void Spline::Subdivide(float fU0, float fU1, float fMaxLen, Matrix *pmatCMCont)
{
	float fUmid = (fU0 + fU1)/2.00;
	Point P1, P2;
	Vector vecT1, vecT2;

	float faU[4];
	float faUdiff[4];

	Matrix matU(1,4);
	Matrix *pmatXYZ;

	//For U0
	faU[3] = 1.00f;
	faU[2] = fU0;
	faU[1] = faU[2]*fU0;
	faU[0] = faU[1]*fU0;

	faUdiff[0] = 3*fU0*fU0;
	faUdiff[1] = 2*fU0;
	faUdiff[2] = 1;
	faUdiff[3] = 0;

	//F(U0)
	matU.SetElements(faU);
	pmatXYZ = Matrix::MatrixMultiply(matU, *pmatCMCont);
	P1.SetPoint(pmatXYZ->GetElement(0,0), pmatXYZ->GetElement(0,1), pmatXYZ->GetElement(0,2));
	pmatXYZ->FreeMemory();
	//F'(U0)
	matU.SetElements(faUdiff);
	pmatXYZ = Matrix::MatrixMultiply(matU, *pmatCMCont);
	vecT1.SetVector(pmatXYZ->GetElement(0,0), pmatXYZ->GetElement(0,1), pmatXYZ->GetElement(0,2));
	pmatXYZ->FreeMemory();
	
	//For U1
	faU[2] = fU1;
	faU[1] = faU[2]*fU1;
	faU[0] = faU[1]*fU1;

	faUdiff[0] = 3*fU1*fU1;
	faUdiff[1] = 2*fU1;	

	//F(U1)
	matU.SetElements(faU);
	pmatXYZ = Matrix::MatrixMultiply(matU, *pmatCMCont);
	P2.SetPoint(pmatXYZ->GetElement(0,0), pmatXYZ->GetElement(0,1), pmatXYZ->GetElement(0,2));
	pmatXYZ->FreeMemory();
	//F'(U1)
	matU.SetElements(faUdiff);
	pmatXYZ = Matrix::MatrixMultiply(matU, *pmatCMCont);
	vecT2.SetVector(pmatXYZ->GetElement(0,0), pmatXYZ->GetElement(0,1), pmatXYZ->GetElement(0,2));
	pmatXYZ->FreeMemory();

	float fDist = P1.GetAbsDistanceFrom(P2);

	if(fDist > fMaxLen)
	{
		//Divide Points Further
		Subdivide(fU0, fUmid, fMaxLen, pmatCMCont);
		Subdivide(fUmid, fU1, fMaxLen, pmatCMCont);
	}
	else
	{
		//Add Points and compute N and B vectors as well
		Vector vecB1, vecB2, vecN1, vecN2;
		Vector *pvecUnit, *pvecCross;

		if(this->iSpPoints == 0)
		{
			// First Point
			vecN1.SetVector(0,1,0);
			pvecCross = Vector::VectorCrossProduct(vecT1, vecN1);
			pvecUnit = pvecCross->GetUnitVector();
			vecB1.SetVector(*pvecUnit);
			delete pvecCross;
			delete pvecUnit;

			//Second Point
			pvecCross = Vector::VectorCrossProduct(vecB1, vecT2);
			pvecUnit = pvecCross->GetUnitVector();
			vecN2.SetVector(*pvecUnit);
			delete pvecCross;
			delete pvecUnit;

			pvecCross = Vector::VectorCrossProduct(vecT2, vecN2);
			pvecUnit = pvecCross->GetUnitVector();
			vecB2.SetVector(*pvecUnit);
			delete pvecCross;
			delete pvecUnit;

		}
		else
		{
			//Other Points
			Vector vecB0 = this->lstCross[iSpPoints-1];

			pvecCross = Vector::VectorCrossProduct(vecB0, vecT1);
			pvecUnit = pvecCross->GetUnitVector();
			vecN1.SetVector(*pvecUnit);
			delete pvecCross;
			delete pvecUnit;

			pvecCross = Vector::VectorCrossProduct(vecT1, vecN1);
			pvecUnit = pvecCross->GetUnitVector();
			vecB1.SetVector(*pvecUnit);
			delete pvecCross;
			delete pvecUnit;

			pvecCross = Vector::VectorCrossProduct(vecB1, vecT2);
			pvecUnit = pvecCross->GetUnitVector();
			vecN2.SetVector(*pvecUnit);
			delete pvecCross;
			delete pvecUnit;

			pvecCross = Vector::VectorCrossProduct(vecT2, vecN2);
			pvecUnit = pvecCross->GetUnitVector();
			vecB2.SetVector(*pvecUnit);
			delete pvecCross;
			delete pvecUnit;
		}		

		this->lstPoints.resize(this->iSpPoints + 2);
		this->lstTangent.resize(this->iSpPoints + 2);
		this->lstNormal.resize(this->iSpPoints + 2);
		this->lstCross.resize(this->iSpPoints + 2);

		this->lstPoints[this->iSpPoints] = P1;
		this->lstPoints[this->iSpPoints+1] = P2;

		this->lstTangent[this->iSpPoints] = vecT1;
		this->lstTangent[this->iSpPoints+1] = vecT2;

		this->lstNormal[this->iSpPoints] = vecN1;
		this->lstNormal[this->iSpPoints+1] = (vecN2);

		this->lstCross[this->iSpPoints] = (vecB1);
		this->lstCross[this->iSpPoints+1] = (vecB2);
		
		this->iSpPoints+=2;
	}
}

//Prev Code
		/*
		//CrossSection
		if(i%1 == 0)
		{
			glColor3f(1.0,0,0);
			glVertex3f(fLx1, fLy1, fLz1);
			glVertex3f(fRx1, fRy1, fRz1);
			glVertex3f(fLx2, fLy2, fLz2);
			glVertex3f(fRx2, fRy2, fRz2);
		}
		glColor3f(0.1,0.1,0.8);
		//Pillars
		if(i%40 == 0)
		{
			glVertex3f(fLx1,-18.75,fLz1);
			glVertex3f(fLx1, fLy1, fLz1);
		
			glVertex3f(fRx1,-18.75,fRz1);
			glVertex3f(fRx1, fRy1, fRz1);
		}

		//Line Section
		glColor3f(1.0,1.0,0);
		glVertex3f(fLx1, fLy1, fLz1);
		glVertex3f(fLx2, fLy2, fLz2);		
		
		glVertex3f(fRx1, fRy1, fRz1);
		glVertex3f(fRx2, fRy2, fRz2);
		*/