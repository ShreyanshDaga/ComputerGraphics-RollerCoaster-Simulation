/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef IMAGE_H
#define IMAGE_H

	#include"Main.h"
	
	//Image class encapsulates Pic datastruct with additional functions
	class Image
	{
		private:
			Pic *pImageData;			// The Pic structure
			int iWidth;					// The Width of the Image
			int iHeight;					// The Height of the Image
			int iType;						// The Image Type
			string strFileName;		// File Name
	
		public:
			Image();						//Ctor
			Image(string strName);	//Ctor
	
			void ReadImage();							// Reads the Image file after initializing the attributes
			Pic* GetImageData();						// Returns the Pic structure
			unsigned char GetR(int iX, int iY);	// Returns the Red
			unsigned char GetG(int iX, int iY);	// Returns the Green
			unsigned char GetB(int iX, int iY);	// Returns the Blue
			unsigned char GetBW(int iX, int iY);	// Returns the BW/Luminance
			int GetType();									// Returns the bpp/Image type
			int GetHeight();
			int GetWidth();
	
			void AllocMemory(int iWidth, int iHeight, int iType);
			void FreeImage();								// Frees the Image
	};

#endif