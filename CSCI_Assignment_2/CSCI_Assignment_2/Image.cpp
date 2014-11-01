/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"Main.h"
#include"Image.h"

Image::Image()
{
	//Parameter less Ctor
	this->pImageData = NULL;
	this->strFileName.assign("");

	this->iHeight = 0;
	this->iWidth = 0;
	this->iType = 0;
}

Image::Image(string strName)
{
	
	this->strFileName = strName;

	//Read Image Here itself
	this->pImageData = jpeg_read((char *)strName.c_str(),NULL);
	
	if(!this->pImageData )
	{
		cout<<"\n*Error Reading "<<this->strFileName<<" file.!";
		exit(1);
	}

	this->iHeight = this->pImageData->ny;
	this->iWidth = this->pImageData->nx;
	this->iType = this->pImageData->bpp;	
	cout<<"\n *File "<<this->strFileName<<" read complete..";
}

void Image::ReadImage()
{
	//Additional Function to Read Image
	this->pImageData = jpeg_read((char *)this->strFileName.c_str(),NULL);

	if(!this->pImageData )
	{
		cout<<"\n*Error Reading "<<this->strFileName<<" file.!";
		exit(1);
	}
}

Pic* Image::GetImageData()
{
	//Get accessor for the Pic struct
	return this->pImageData;
}

unsigned char Image::GetR(int iX, int iY)
{
	//Returns the red for RGBA, or Returns red for luminances
	unsigned char cR;

	if(this->iType == 1)
		cR = PIC_PIXEL(this->pImageData,iX,iY,0);
	else
		cR = PIC_PIXEL(this->pImageData,iX,iY,0);

	return cR;
}

unsigned char Image::GetG(int iX, int iY)
{
	//Returns the Green for RGBA, or Returns Green for luminances
	unsigned char cG;

	if(this->iType == 1)
		cG = PIC_PIXEL(this->pImageData,iX,iY,0);
	else
		cG = PIC_PIXEL(this->pImageData,iX,iY,1);

	return cG;
}

unsigned char Image::GetB(int iX, int iY)
{
	//Returns the Blue for RGBA, or Returns Blue for luminance
	unsigned char cB;

	if(this->iType == 1)
		cB = PIC_PIXEL(this->pImageData,iX,iY,0);
	else
		cB = PIC_PIXEL(this->pImageData,iX,iY,2);

	return cB;
}

unsigned char Image::GetBW(int iX, int iY)
{
	//Returns the actual luminance of the pixel location
	unsigned char cBW,cR,cG,cB;

	if(this->iType == 1)
		cBW = PIC_PIXEL(this->pImageData,iX,iY,0);
	else
	{
		//Return the luminance of the color image
		cR = this->GetR(iX, iY);
		cG = this->GetR(iX, iY);
		cB = this->GetR(iX, iY);

		cBW = (unsigned char)((float)cR*0.3 + (float)cG*0.59 + (float)cB*0.11);
	}

	return cBW;	
}

int Image::GetType()
{
	//Returns the type of image (RGB, RGBA or Gray) i.e. the bpp
	return this->iType;
}

int Image::GetHeight()
{
	return this->iHeight;
}

int Image::GetWidth()
{
	return this->iWidth;
}

void Image::AllocMemory(int iWidth, int iHeight, int iType)
{
}

void Image::FreeImage()
{
	//Frees the image
	pic_free(this->pImageData);
}