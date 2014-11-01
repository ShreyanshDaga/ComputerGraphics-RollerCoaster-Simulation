/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////


#include"Main.h"
#include"glutWinObj.h"
#include"pic.h"
#include"Image.h"
#include"Point.h"
#include"Spline.h"
#include"Track.h"
#include"Texture.h"
#include"Camera.h"
#include"Material.h"
#include"Light.h"

using namespace std;

extern Track trTrack1;
extern Image imgTexGround;
extern Image imgTexSky;
extern Image imgTexRail;

extern Texture txrGround;
extern Texture txrSky;
extern Texture txrRail;
extern Texture txrEarth;
extern Texture txrMoon;

extern Light ltSun;

extern Material mtrEarth;
extern Material mtrMoon;
extern Material mtrSpace;
extern Material mtrGround;

static int WTF = 0;

//Stores the prev value of mouse points
int iPrevX, iPrevY;
int iDelay = 1;
static GLuint texName[3];

//Spline spTest("splines//Loop_L_5.sp");
Track trkTrack1("track/track_test.txt");
                                                                                                                                                                  
//Initializing all the GlutWinObjate variables
int GlutWinObj::iMenuID=0;
	
float GlutWinObj::fZMultiplier = 1;

float GlutWinObj::fTranX = 0;
float GlutWinObj::fTranY = 0;
float GlutWinObj::fTranZ = 0;

float GlutWinObj::fRotX = 0;
float GlutWinObj::fRotY = 0;
float GlutWinObj::fRotZ = 0;
	
float GlutWinObj::fScaleX = 1;
float GlutWinObj::fScaleY = 1;
float GlutWinObj::fScaleZ = 1;
	
unsigned int GlutWinObj::cRenderMode = 1;
int GlutWinObj::iMode = 0;

bool GlutWinObj::bToggleSun = true;
bool GlutWinObj::bToggleDefAnim = true;
bool GlutWinObj::bRecAnim = false;

GLuint TrackList;
GLuint SphereList;

Camera cam1;
void DrawTrack();
void InitLights();

void InitTesting();
void InitSphereList();

//Ctor for GLutWinObj
GlutWinObj::GlutWinObj(int iW, int iH, int iX, int iY)
{
	//Fill up values
	this->iHeight = iH;
	this->iWidth = iW;
	this->iPosX = iX;
	this->iPosY = iY;

	//Init Handle to 0
	this->iWinHandle = 0;
	this->bGlutReady = false;
}

void GlutWinObj::InitGlut(int argc, char* argv[])
{
	//Perform all the initialization tasks
	glutInit(&argc,(char**)argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(this->iWidth, this->iHeight);
	glutInitWindowPosition(this->iPosX, this->iPosY);

}

int GlutWinObj::GlutCreateWindow(const char *pszTitle)
{
	//Create window here and also set required flags
	this->iWinHandle = glutCreateWindow_ATEXIT_HACK(pszTitle);		
	glClearColor (0.0, 0.0, 0.0, 0.0);
	
	void InitLights();
	
	ltSun.ActivateLight();

	glEnable(GL_DEPTH_TEST);		
	glShadeModel(GL_SMOOTH);	
	glEnable( GL_NORMALIZE );
	
	txrEarth.GenTexture();
	txrMoon.GenTexture();
	txrGround.GenTexture();
	txrSky.GenTexture();
	txrRail.GenTexture();

	this->bGlutReady = true;

	TrackList = glGenLists(1);
	glNewList(TrackList,GL_COMPILE);
	DrawTrack();
	glEndList();

	InitSphereList();

	return this->iWinHandle;
}

void GlutWinObj::StartGlutLoop()
{	
	if(this->bGlutReady)
	{
		cout<<"\n* glut Main Loop started..";
		glutMainLoop();	
	}
}

void GlutWinObj::Reg_Callbacks_Prime()
{
	//Register all the callbacks
	this->RegCallback_RenderDisplay();
	this->RegCallback_HandleMouse();
	this->RegCallback_HandleMouseDrag();
	this->RegCallback_HandleMouseIdle();
	this->RegCallback_HandleReshape();
	this->RegCallback_Idle();
	this->RegCallback_HandleKeyboard();
	this->RegCallback_HandleSpecialKey();
	this->InitContextMenu();
}

void GlutWinObj::RegCallback_RenderDisplay()
{
	glutDisplayFunc(&GlutWinObj::DisplayFunc);
}

void GlutWinObj::RegCallback_HandleMouse()
{
	glutMouseFunc(GlutWinObj::MouseFunc);
}

void GlutWinObj::RegCallback_HandleMouseDrag()
{
	glutMotionFunc(GlutWinObj::MouseDragFunc);
}

void GlutWinObj::RegCallback_HandleMouseIdle()
{
	glutPassiveMotionFunc(GlutWinObj::MouseIdleFunc);
}

void GlutWinObj::RegCallback_HandleKeyboard()
{
	glutKeyboardFunc(GlutWinObj::KeyboardFunc);
}

void GlutWinObj::RegCallback_HandleSpecialKey()
{
	glutSpecialFunc(GlutWinObj::SpecialKeyFunc);
}

void GlutWinObj::RegCallback_Idle()
{
	glutIdleFunc(GlutWinObj::IdleFunc);
}

void GlutWinObj::RegCallback_HandleReshape()
{
	glutReshapeFunc(GlutWinObj::ReshapeFunc);
}

void GlutWinObj::InitContextMenu()
{
	iMenuID = glutCreateMenu(GlutWinObj::ContextMenuFunc);
	glutSetMenu(iMenuID);	
	glutAddMenuEntry("Quit",0);
	glutAddMenuEntry("Record Animation",1);
	glutAddMenuEntry("Re-Orient Cam",2);
	glutAddMenuEntry("Speed Up",3);
	glutAddMenuEntry("Slow Down",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void GlutWinObj::DisplayFunc()
{		
	static float alpha = 0.0;	
	static int iFrameCount = 0;
	static float fz = 0.00;
	static int i = 0;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();			

	//Perform ops based on the GlutWinObj's state variables
	glTranslatef(fTranX,fTranY,fTranZ);
	glRotatef(-fRotX,1,0,0);
	glRotatef(-fRotY,0,1,0);
	glRotatef(-fRotZ,0,0,1);
	glScalef(fScaleX,fScaleY,fScaleZ);		

	if(GlutWinObj::bToggleDefAnim == true)
		trkTrack1.MoveCam(&cam1);
	else
		cam1.CamLook();
		
	ltSun.ActivateLight();

	RenderWorld();
	glCallList(TrackList);		
					
	glFlush();
	glutSwapBuffers();	
}

void GlutWinObj::MouseFunc(int iButton, int iState, int iX, int iY)
{	
	//Update Operation Mode based on the user input on mouse input

	switch(glutGetModifiers())
	{
		case GLUT_ACTIVE_CTRL:
			//Translate
			iMode = 1;
			break;

		case GLUT_ACTIVE_SHIFT:
			//Scale
			iMode = 2;
			break;

		case GLUT_ACTIVE_ALT:
			//Deform in the Z direction
			iMode = 4;
			break;

		default:
			//Rotation
			iMode = 3;
	}

	iPrevX = iX;
	iPrevY = iY;
}

void GlutWinObj::MouseDragFunc(int iX, int iY)
{
	int iDeltaX = iX - iPrevX, iDeltaY = iY - iPrevY;

	switch(iMode)
	{
		case 1:	//Translate in Z and X direction
			fTranZ += iDeltaY*0.01;
			fTranX += iDeltaX*0.01;
			break;

		case 3:	//Rotate in Y and X direction
			fRotX -= iDeltaY;
			fRotY -= iDeltaX;
			break;

		case 2:	//Scale uniformly by just DeltaX
			fScaleX *= 1.0 + iDeltaX*0.01;
			fScaleY *= 1.0 + iDeltaX*0.01;//((float)iDeltaX)/sqrt(iDeltaX*iDeltaX)*sqrt(iDeltaX*iDeltaX + iDeltaY*iDeltaY)*0.01;
			fScaleZ *= 1.0 + iDeltaX*0.01;//((float)iDeltaX)/sqrt(iDeltaX*iDeltaX)*sqrt(iDeltaX*iDeltaX + iDeltaY*iDeltaY)*0.01;
			break;

		case 4:	//Deformation multiplier in the Z direction
			fZMultiplier *= 1.0 - iDeltaY*0.03;
			break;
	}

	//Capture Mouse movement
	iPrevX = iX;
	iPrevY = iY;
}

void GlutWinObj::MouseIdleFunc(int iX, int iY)
{
	//Capture Mouse movement
	iPrevX = iX;
	iPrevY = iY;
}

void GlutWinObj::KeyboardFunc(unsigned char cKey, int iX, int iY)
{	
	//Alternate ways of Translate and rotate in all three axes

	if(cKey == 'W')	//Shift + w
	{
		fRotX += 1;
	}
	else if(cKey == 'S')	//Shift + s
	{
		fRotX -= 1;
	}
	else if(cKey == 'A') // and like wise...
	{
		fRotY += 1;
	}
	else if(cKey == 'D')
	{
		fRotY -= 1;
	}
	else if(cKey == 'Q')
	{
		fRotZ += 1;
	}
	else if(cKey == 'E')
	{
		fRotZ -= 1;
	}
	else if(cKey == 'w')
	{
		fTranZ -= 0.1;
	}
	else if(cKey == 's')
	{
		fTranZ += 0.1;
	}
	else if(cKey == 'a')
	{
		fTranX -= 0.1;
	}
	else if(cKey == 'd')
	{
		fTranX += 0.1;
	}
	else if(cKey == 'q')
	{
		fTranY -= 0.1;
	}
	else if(cKey == 'e')
	{
		fTranY += 0.1;
	}	
	
	//Capture Mouse movement
	iPrevX = iX;
	iPrevY = iY;
}

void GlutWinObj::SpecialKeyFunc(int iKey, int iX, int iY)
{
	//Cyclicly rotate the rendering mode state variables

	switch(iKey)
	{
		case GLUT_KEY_RIGHT:
			//Switch Mode to right
			cRenderMode = cRenderMode << 1;
			if(cRenderMode > 16)
				cRenderMode = 1;
			break;
		
		case GLUT_KEY_LEFT:
			//Switch Mode to left
			cRenderMode = cRenderMode >> 1;
			if(cRenderMode < 1)
				cRenderMode = 16;
			break;

		case GLUT_KEY_END:
			//Start/Stop Animation
			if(bToggleDefAnim == true)
				bToggleDefAnim = false;
			else
				bToggleDefAnim = true;
			break;
	}

	//Capture Mouse movement
	iPrevX = iX;
	iPrevY = iY;
}

void GlutWinObj::IdleFunc()
{
	static int iFrameCount = 0;
	static float fz = 0.00;
	static int U=0,T=0,H=0,Th=0;

	//Record the animation if user says to record the animations
	
	if(bRecAnim)
	{		
		if(iFrameCount < 1000)
		{		
			char szTitle[25];

			sprintf(szTitle,"Frames\\%d%d%d.jpg",H,T,U);
			SaveFrame(szTitle);
			U++;

			if(U == 10)
			{
				U = 0;
				T++;
				if(T == 10)
				{
					T = 0;
					H++;
					if(H == 10)
					{
						H = 0;
						Th++;
					}						
				}
			}
			iFrameCount++;
		}
	}//Delay
	else
	{
		for(int i = 0;i<1000*iDelay;i++)
			for(int j = 0;j<500*iDelay;j++)
				;
	}


	//cout<<"\nWTF: "<<WTF;
	glutPostRedisplay();
}

void GlutWinObj::ReshapeFunc(int iW, int iH)
{
	//Adjust according to new window size
	glViewport(0, 0, iW, iH);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, ((float)iW)/((float) iH), 0.1, 5000);	

	glMatrixMode(GL_MODELVIEW);	
}

void GlutWinObj::ContextMenuFunc(int iVal)
{
	//Context menu selections
	switch(iVal)
	{
		case 0:
			exit(0);
			break;

			
		case 1:
			if(bRecAnim == true)
				bRecAnim = false;
			else
				bRecAnim = true;
			break;

		case 2:
			ResetGlutWinParam();
			break;

		case 3:
			iDelay += 10;			
			break;

		case 4:
			iDelay -= 10;
			break;

		case 5:
			
			break;

		case 6:
			
			break;

		case 7:
			
			break;

		case 8:			
			break;

		case 9:			
			break;

		case 10:	
			break;
	}
}

void GlutWinObj::ResetGlutWinParam()
{
	//Reset all the parameters to original vaues
	
	iMenuID;
	
	fZMultiplier = 1.0;

	fTranX = 0;
	fTranY = 0;
	fTranZ = 0;
	
	fRotX = 0;
	fRotY = 0;
	fRotZ = 0;
	
	fScaleX = 1;
	fScaleY = 1;
	fScaleZ = 1;
	
	cRenderMode = 1;
	iMode;
}

void DisplayVertex()
{
	glColor3f(1.0,1.0,1.0);	
	glLineWidth(1.5);
	glBegin(GL_LINES);	
	trTrack1.DrawTrack();
	glEnd();
}

void DisplayFrustumVolume()
{
	//glPushMatrix();
	//glLoadIdentity();

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0,1.0,1.0);
	glVertex3f(-1,1,-1.1);
	glVertex3f(-1,-1,-1.1);
	glVertex3f(1,-1,-1.1);
	glVertex3f(1,1,-1.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1,1,-99.9);
	glVertex3f(-1,-1,-99.9);
	glVertex3f(1,-1,-99.9);
	glVertex3f(1,1,-99.9);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(1,1,-1.1);
	glVertex3f(1,1,-99.9);
	glVertex3f(1,-1,-99.9);
	glVertex3f(1,-1,-1.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1,1,-1.1);
	glVertex3f(-1,1,-99.9);
	glVertex3f(-1,-1,-99.9);
	glVertex3f(-1,-1,-1.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1,1,-1.1);
	glVertex3f(1,1,-1.1);
	glVertex3f(1,1,-99.9);
	glVertex3f(-1,1,-99.9);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1,-1,-1.1);
	glVertex3f(1,-1,-1.1);
	glVertex3f(1,-1,-99.9);
	glVertex3f(-1,-1,-99.9);
	glEnd();

	//glPopMatrix();
}

void RenderWorld()
{
	glEnable(GL_LIGHTING);	
	txrGround.BindTexture();	
	mtrGround.Apply();	
	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(-700.0, -20, 700.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(700.0, -20, 700.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(700.0, -20, -700.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(-700.0, -20, -700.0);		
	glEnd();
	txrGround.UnBindTexture();	
			
	
	/*
			
	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	GLUquadricObj *obj;
	obj = gluNewQuadric();
	gluQuadricDrawStyle( obj, GLU_FILL );
	gluQuadricOrientation( obj, GLU_OUTSIDE );
	gluQuadricTexture( obj, GL_TRUE );
	gluQuadricNormals( obj, GLU_SMOOTH );

	gluSphere(obj,800,360,180);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	*/

	glPushMatrix();
	glRotatef(90,1,0,0);
	glScalef(800,800,800);
	
	txrSky.BindTexture();
	mtrSpace.Apply();
	glCallList(SphereList);

	txrSky.UnBindTexture();	
	glPopMatrix();

	DrawEarth();
	DrawMoon();
}

void DrawTrack()
{		
	glDisable(GL_LIGHTING);
	trkTrack1.DrawTrack();
}

void DrawCube()
{
	static float fTheta = 0;
	float fX, fY;

	fX = 4*cos(fTheta);
	fY = 4*sin(fTheta);
	GLfloat light_position[] = { fX, fY, 0.0, 0.0 };
	GLfloat amb[] = {0.5,0.5,0.5,1.0};
	glPointSize(10.0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glBegin(GL_POINTS);
		glVertex3f(fX,fY ,0);
	glEnd();

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glBegin(GL_QUADS);
		glNormal3f(-1,0,0);
		glColor3f(0, 0, 1); glVertex3f(-1, -1, -1);
		glColor3f(0, 0, 1); glVertex3f(-1, -1,  1);
		glColor3f(0, 0, 1); glVertex3f(-1,  1,  1);
		glColor3f(0, 0, 1); glVertex3f(-1,  1, -1);

		glNormal3f(1,0,0);
		glColor3f(1, 0, 0); glVertex3f( 1, -1, -1);
		glColor3f(1, 0, 0); glVertex3f( 1, -1,  1);
		glColor3f(1, 0, 0); glVertex3f( 1,  1,  1);
		glColor3f(1, 0, 0); glVertex3f( 1,  1, -1);

		glNormal3f(0,-1,0);
		glColor3f(0, 1, 0); glVertex3f(-1, -1, -1);
		glColor3f(0, 1, 0); glVertex3f(-1, -1,  1);
		glColor3f(0, 1, 0); glVertex3f( 1, -1,  1);
		glColor3f(0, 1, 0); glVertex3f( 1, -1, -1);

		glNormal3f(0,1,0);
		glColor3f(0, 1, 1); glVertex3f(-1,  1, -1);
		glColor3f(0, 1, 1); glVertex3f(-1,  1,  1);
		glColor3f(0, 1, 1); glVertex3f( 1,  1,  1);
		glColor3f(0, 1, 1); glVertex3f( 1,  1, -1);

		glNormal3f(0,0,-1);
		glColor3f(1, 1, 0); glVertex3f(-1, -1, -1);
		glColor3f(1, 1, 0); glVertex3f(-1,  1, -1);
		glColor3f(1, 1, 0); glVertex3f( 1,  1, -1);
		glColor3f(1, 1, 0); glVertex3f( 1, -1, -1);

		glNormal3f(0,0,1);
		glColor3f(1, 0, 1); glVertex3f(-1, -1,  1);
		glColor3f(1, 0, 1); glVertex3f(-1,  1,  1);
		glColor3f(1, 0, 1); glVertex3f( 1,  1,  1);
		glColor3f(1, 0, 1); glVertex3f( 1, -1,  1);
	glEnd();	

	glPushMatrix();
	glTranslatef(3,0,0);
	glutSolidSphere (0.50, 32, 32);
	glPopMatrix();
	fTheta+=0.01;
}

void DrawEarth()
{
	static float fAngle = 0;

	glPushMatrix();	
	glTranslatef(0,200,300);	
	glRotatef(fAngle,0,-1,0);
	glScalef(70,70,70);
	txrEarth.BindTexture();
	mtrEarth.Apply();
	glCallList(SphereList);
	
	txrEarth.UnBindTexture();	
	glPopMatrix();
	fAngle+=0.5;
}

void DrawMoon()
{
	static float fAngle = 0.0;

	glPushMatrix();		
	glRotatef(fAngle,0,1,0);
	glTranslatef(0,200,300);	
	glScalef(20,20,20);
	txrMoon.BindTexture();
	mtrMoon.Apply();
	glCallList(SphereList);
	
	txrMoon.UnBindTexture();	
	glPopMatrix();
	fAngle += 0.8;
}

void DrawAsteroid()
{

}

void InitLights()
{	
	glEnable(GL_LIGHTING);
	GLfloat globalAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, globalAmbient );
}

void SaveFrame(char *pszTitle)
{
	//Saves the frame
	int i, j;
	Pic *in = NULL;

	 if (pszTitle == NULL)
		return;
	
	in = pic_alloc(640, 480, 3, NULL);

	printf("File to save to: %s\n", pszTitle);

	for (i=479; i>=0; i--) 
	{
		glReadPixels(0, 479-i, 640, 1, GL_RGB, GL_UNSIGNED_BYTE, &in->pix[i*in->nx*in->bpp]);
	}

	if (jpeg_write(pszTitle, in))
		printf("File saved Successfully\n");
	else
		printf("Error in Saving\n");

	pic_free(in);
}

/* Temp Dump
float fCamX, fCamY, fCamZ;
	float fEyeX, fEyeY, fEyeZ;
	float fUpX, fUpY, fUpZ;

	Vector *pVec, *pScalVec, *pUnit;

	pVec = spTest.GetSplineNormalV()[i].GetUnitVector();		
	pUnit = *pVec * 0.3;

	fCamX = spTest.GetSplinePoints()[i].GetX();
	fCamY = spTest.GetSplinePoints()[i].GetY();
	fCamZ = spTest.GetSplinePoints()[i].GetZ();
	
	//delete pScalVec;

	/*glBegin(GL_LINES);

	glColor3f(1.0,0,0);
	glVertex3f(fCamX, fCamY, fCamZ);
	glVertex3f(fCamX + 0.5, fCamY, fCamZ);
	glColor3f(0,1.0,0);
	glVertex3f(fCamX, fCamY, fCamZ);
	glVertex3f(fCamX , fCamY + 0.5, fCamZ);
	glColor3f(0,0,1.0);
	glVertex3f(fCamX, fCamY, fCamZ);
	glVertex3f(fCamX, fCamY, fCamZ + 0.5);

	glEnd(); 

	fCamX = spTest.GetSplinePoints()[i].GetX() + pUnit->GetX();
	fCamY = spTest.GetSplinePoints()[i].GetY() + pUnit->GetY();
	fCamZ = spTest.GetSplinePoints()[i].GetZ() + pUnit->GetZ();

	fEyeX = fCamX + spTest.GetSplineTangentV()[i].GetX();// - pUnit->GetX();
	fEyeY = fCamY + spTest.GetSplineTangentV()[i].GetY();// - pUnit->GetY();
	fEyeZ = fCamZ + spTest.GetSplineTangentV()[i].GetZ();// - pUnit->GetZ();

	fUpX = spTest.GetSplineNormalV()[i].GetX();
	fUpY = spTest.GetSplineNormalV()[i].GetY();
	fUpZ = spTest.GetSplineNormalV()[i].GetZ();
	
	delete pVec;
	delete pUnit;

	gluLookAt(fCamX, fCamY, fCamZ, fEyeX, fEyeY, fEyeZ, fUpX, fUpY, fUpZ); */

void InitTesting()
{
	 
}

void InitSphereList()
{
	SphereList = glGenLists(1);
	GLUquadric* obj = gluNewQuadric();
	gluQuadricDrawStyle( obj, GLU_FILL );
	gluQuadricOrientation( obj, GLU_OUTSIDE );
	gluQuadricTexture( obj, GL_TRUE );
	gluQuadricNormals( obj, GLU_SMOOTH );
	glNewList( SphereList, GL_COMPILE );
	{
	    gluSphere( obj, 1.0, 360, 180 );
	}
	glEndList();
	gluDeleteQuadric( obj );
}

/*float fX1, fX2, fX3, fX4;
	float fY1, fY2, fY3, fY4;
	float fZ1, fZ2, fZ3, fZ4;	
	
	glBegin(GL_QUADS);

	for(int iTheta = 0;iTheta<359;iTheta+=3)
	{
		for(int iPhi = 0;iPhi<89;iPhi+=3)
		{			
			float fP = 3.14159*iPhi/180.00;
			float fT = 3.14159*iTheta/180.00;

			fX1 = sin(fP)*sin(fT)*1500;
			fY1 = cos(fP)*1500;
			fZ1 = sin(fP)*cos(fT)*1500;

			fX2 = sin(fP+1)*sin(fT)*1500;
			fY2 = cos(fP+1)*1500;
			fZ2 = sin(fP+1)*cos(fT)*1500;

			fX3 = sin(fP+1)*sin(fT+1)*1500;
			fY3 = cos(fP+1)*1500;
			fZ3 = sin(fP+1)*cos(fT+1)*1500;

			fX4 = sin(fP)*sin(fT+1)*1500;
			fY4 = cos(fP)*1500;
			fZ4 = sin(fP)*cos(fT+1)*1500;

			//glColor3f(1.0,1.0,1.0);
			glVertex3f(fX1,fY1,fZ1);
			//glColor3f(1.0,1.0,0.0);
			glVertex3f(fX2,fY2,fZ2);
			//glColor3f(1.0,0.0,0.0);
			glVertex3f(fX3,fY3,fZ3);
			//glColor3f(0.0,1.0,0.0);
			glVertex3f(fX4,fY4,fZ4);
		}
	}	
	glEnd();
	*/