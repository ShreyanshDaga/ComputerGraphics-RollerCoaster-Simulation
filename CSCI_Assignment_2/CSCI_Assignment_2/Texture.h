/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef _TEXTURE_H
#define _TEXTURE_H

	#include"main.h"
	#include"pic.h"
	#include"Image.h"

	class Texture
	{
		private:
			string strTexName;
		public:
			GLubyte pTextureData[1600][1600][4];
			GLubyte *pTexData;
			int iH, iW;
			GLuint iTexName;

		public:
			Texture();
			void LoadTexture(Image imgImage);
			void GenTexture();
			void BindTexture();
			void UnBindTexture();
			GLubyte*** GetTexData();
	};

#endif