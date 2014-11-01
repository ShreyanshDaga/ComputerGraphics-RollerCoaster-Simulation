/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"main.h"
#include"Image.h"
#include"Texture.h"


Texture::Texture()
{
	
}

void Texture::LoadTexture(Image imgImage)
{
	this->iH = imgImage.GetHeight();
	this->iW = imgImage.GetWidth();

	this->pTexData = new GLubyte[this->iW*this->iH*4];

	for(int i = 0;i<iH;i++)
	{
		for(int j = 0;j<iW;j++)
		{
			//this->pTextureData[i][j][0] = imgImage.GetR(i,j);
			//this->pTextureData[i][j][1] = imgImage.GetG(i,j);
			//this->pTextureData[i][j][2] = imgImage.GetB(i,j);
			//this->pTextureData[i][j][3] = 255;

			this->pTexData[i*iW*4 + j*4] = imgImage.GetR(i,j);
			this->pTexData[i*iW*4 + j*4 + 1] = imgImage.GetG(i,j);
			this->pTexData[i*iW*4 + j*4 + 2] = imgImage.GetB(i,j);
			this->pTexData[i*iW*4 + j*4 + 3] = 255;
		}
	}	
}

void Texture::GenTexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &this->iTexName);	
	glBindTexture(GL_TEXTURE_2D, this->iTexName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->iW, this->iH, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->pTexData);
}

void Texture::BindTexture()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D,this->iTexName);
}

void Texture::UnBindTexture()
{
	glDisable(GL_TEXTURE_2D);
}

unsigned char*** Texture::GetTexData()
{
	//return this->pTextureData;
	return NULL;
}