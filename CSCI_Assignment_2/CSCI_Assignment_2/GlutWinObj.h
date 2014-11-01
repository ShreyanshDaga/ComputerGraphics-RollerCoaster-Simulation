/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef _GLUTWINOBJ_H
#define _GLUTWINOBJ_H

#include"Main.h"
#include"Image.h"

//Glut Window Object
class GlutWinObj
{
	private:
		int iWinHandle;								// Handele to this Window Object
		int iWidth, iHeight;							// Current Dimensions of the Window
		int iPosX, iPosY;								// Init Start Position
		bool bGlutReady;								// Flag indiciating whether window is ready to render anything

	public:
		static int iMenuID;							//Menu selection id

		static float fZMultiplier;					//For deformation
		
		static float fTranX;							//For translaton
		static float fTranY;
		static float fTranZ;
		
		static float fRotX;								//For rotation
		static float fRotY;
		static float fRotZ;
		
		static float fScaleX;							//For Scaling
		static float fScaleY;
		static float fScaleZ;
		
		static unsigned int cRenderMode;		//Rendering mode
		static int iMode;									//Operation mode

		static bool bToggleSun;
		static bool bToggleDefAnim;
		static bool bRecAnim;

	public:	
		GlutWinObj(int iW, int iH, int iX, int iY);
		void InitGlut(int argc, char* argv[]);
		int GlutCreateWindow(const char *pszWinTitle);
		void StartGlutLoop();

		//Regestering Call back functions
		void Reg_Callbacks_Prime();
		void RegCallback_RenderDisplay();
		void RegCallback_HandleMouse();
		void RegCallback_HandleMouseDrag();
		void RegCallback_HandleMouseIdle();
		void RegCallback_HandleKeyboard();
		void RegCallback_HandleSpecialKey();
		void RegCallback_Idle();
		void RegCallback_HandleReshape();		
		void InitContextMenu();

		//Callbacks
		static void DisplayFunc(void);
		static void MouseFunc(int iButton, int iState, int iX, int iY);
		static void KeyboardFunc(unsigned char cKey, int iX, int iY);
		static void SpecialKeyFunc(int iKey, int iX, int iY);
		static void IdleFunc(void);
		static void ReshapeFunc(int iW, int iH);
		static void ContextMenuFunc(int iVal);
		static void MouseDragFunc(int iX, int iY);
		static void MouseIdleFunc(int iX, int iY);

		//Misc Functions
		static void ResetGlutWinParam();
};

#endif