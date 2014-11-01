/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"main.h"
#include"Track.h"
#include"Camera.h"

Track::Track()
{
	this->iNumOfSplines = 0;
	this->pspSplines = NULL;	
}

Track::Track(string strTrackName)
{
	this->ReadTrackFile(strTrackName);
}

int Track::GetNumOfSplines()
{
	return this->iNumOfSplines;
}

int Track::GetNumOfSplinePoints()
{
	return this->iSpPoints;
}

void Track::ReadTrackFile(string strTrackName)
{
	FILE *fpTrackFile = fopen(strTrackName.c_str(),"r");
	int iNumOfSplines;
	char szSplineFileName[128];

	if(fpTrackFile == NULL)
		exit(1);

	cout<<"\n*Reading Track File "<<strTrackName;

	fscanf(fpTrackFile,"%d",&iNumOfSplines);
	this->iNumOfSplines = iNumOfSplines;
	this->strTrackName = strTrackName;
	this->pspSplines = new Spline[iNumOfSplines];

	int iContPointCount = 0;
	for(int i = 0;i<iNumOfSplines;i++)
	{
		fscanf(fpTrackFile,"%s",&szSplineFileName);		
		this->pspSplines[i].ReadSpline(string::basic_string(szSplineFileName));
		iContPointCount += this->pspSplines[i].GetNumContPoints();
	}
	
	fclose(fpTrackFile);
	cout<<"\n*Track File Reading Complete.";

	this->GenerateTrack();
}

void Track::GenerateTrack()
{
	Point ptLastPoint();

	cout<<"\n*Generating Track...";

	int iSpCount = 0;

	for(int i = 0;i<this->iNumOfSplines;i++)
	{
		if(i == 0)
		{
			//this->pspSplines[i].GenerateSpline();			
			this->pspSplines[i].GenerateRecirsive();
			iSpCount += this->pspSplines[i].GetNumSpPoints();
		}
		else
		{			
			this->pspSplines[i].GenerateSpline(this->pspSplines[i-1].GetSplinePoints()[this->pspSplines[i-1].GetNumSpPoints() - 1], this->pspSplines[i-1].GetSplineNormalV()[this->pspSplines[i-1].GetNumSpPoints() - 1], this->pspSplines[i-1].GetSplineCrossSectionV()[this->pspSplines[i-1].GetNumSpPoints() - 1], this->pspSplines[i-1].GetSplineTangentV()[this->pspSplines[i-1].GetNumSpPoints() - 1]);
			iSpCount += this->pspSplines[i].GetNumSpPoints();
		}
	}

	this->iSpPoints = iSpCount;

	cout<<"\n*Cenerating Track Complete.!";
}

void Track::DrawTrack()
{
	for(int i = 0;i<this->iNumOfSplines;i++)
	{
		this->pspSplines[i].DrawSpline(true);
	}
}

void Track::MoveCam(Camera *pcam1)
{
	static int iPtsCount = 0;
	static int iSpCount = 0;
	
	if(iPtsCount == this->pspSplines[iSpCount].GetNumSpPoints() - 1)
	{
		iPtsCount = 0;
		iSpCount++;
		if(iSpCount == this->iNumOfSplines)
			iSpCount = 0;
	}
	//Get Cam Co-ords

	Vector *pVec, *pScalVec, *pUnit;

	int i = iPtsCount;
	int j = iSpCount;

	pVec = this->pspSplines[j].lstNormal[i].GetUnitVector();		
	pUnit = *pVec * 0.15;

	//Static Generation
	/*pcam1->fCamX = this->pspSplines[j].GetSplinePoints()[i].GetX();
	pcam1->fCamY = this->pspSplines[j].GetSplinePoints()[i].GetY();
	pcam1->fCamZ = this->pspSplines[j].GetSplinePoints()[i].GetZ();

	pcam1->fCamX = this->pspSplines[j].GetSplinePoints()[i].GetX() + pUnit->GetX();
	pcam1->fCamY = this->pspSplines[j].GetSplinePoints()[i].GetY() + pUnit->GetY();
	pcam1->fCamZ = this->pspSplines[j].GetSplinePoints()[i].GetZ() + pUnit->GetZ();

	pcam1->fEyeX = pcam1->fCamX + this->pspSplines[j].GetSplineTangentV()[i].GetX();// - pUnit->GetX();
	pcam1->fEyeY = pcam1->fCamY + this->pspSplines[j].GetSplineTangentV()[i].GetY();// - pUnit->GetY();
	pcam1->fEyeZ = pcam1->fCamZ + this->pspSplines[j].GetSplineTangentV()[i].GetZ();// - pUnit->GetZ();

	pcam1->fUpX = this->pspSplines[j].GetSplineNormalV()[i].GetX();
	pcam1->fUpY = this->pspSplines[j].GetSplineNormalV()[i].GetY();
	pcam1->fUpZ = this->pspSplines[j].GetSplineNormalV()[i].GetZ();
	*/

	//Recursive Generation
	pcam1->fCamX = this->pspSplines[j].lstPoints[i].GetX();
	pcam1->fCamY = this->pspSplines[j].lstPoints[i].GetY();
	pcam1->fCamZ = this->pspSplines[j].lstPoints[i].GetZ();

	pcam1->fCamX = this->pspSplines[j].lstPoints[i].GetX() + pUnit->GetX();
	pcam1->fCamY = this->pspSplines[j].lstPoints[i].GetY() + pUnit->GetY();
	pcam1->fCamZ = this->pspSplines[j].lstPoints[i].GetZ() + pUnit->GetZ();

	pcam1->fEyeX = pcam1->fCamX + this->pspSplines[j].lstTangent[i].GetX() - pUnit->GetX();
	pcam1->fEyeY = pcam1->fCamY + this->pspSplines[j].lstTangent[i].GetY() - pUnit->GetY();
	pcam1->fEyeZ = pcam1->fCamZ + this->pspSplines[j].lstTangent[i].GetZ() - pUnit->GetZ();

	pcam1->fUpX = pVec->GetX();//this->pspSplines[j].lstNormal[i].GetX();
	pcam1->fUpY = pVec->GetY();//this->pspSplines[j].lstNormal[i].GetY();
	pcam1->fUpZ = pVec->GetZ();//this->pspSplines[j].lstNormal[i].GetZ();

	delete pVec;
	delete pUnit;

	pcam1->CamLook();

	iPtsCount++;	
}