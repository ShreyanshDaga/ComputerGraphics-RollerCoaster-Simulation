/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"main.h"
#include"GlutWinObj.h"
#include"Texture.h"
#include"Point.h"
#include"Spline.h"
#include"Track.h"
#include<time.h>
#include<omp.h>
#include"Light.h"
#include"Material.h"

using namespace std;

Track trTrack1;
Image imgTexGround(string::basic_string("textures\\tex_Mars.jpg"));
Image imgTexSky(string::basic_string("textures\\tex_Space_3.jpg"));
Image imgTexRail(string::basic_string("textures\\tex_Steel_1.jpg"));
Image imgTexEarth(string::basic_string("textures\\tex_Earth.jpg"));
Image imgTexMoon(string::basic_string("textures\\tex_Moon.jpg"));

Texture txrGround;
Texture txrSky;
Texture txrRail;
Texture txrEarth;
Texture txrMoon;

Light ltSun(GL_LIGHT0, *new Color(0,0,0,1), *new Color(1,1,1,1), *new Color(1,1,1,1), *new Point(-10,200,300));

Material mtrEarth(*new Color(0.2,0.2,0.2,1), *new Color(1,1,1,1), *new Color(1,1,1,1),100);
Material mtrMoon(*new Color(0.1,0.1,0.01,1), *new Color(1,1,1,1), *new Color(1,1,1,1), 80);
Material mtrSpace(*new Color(0,0,0.01,1), *new Color(0.1,0.1,0.1,1), *new Color(0.1,0.1,0.1,1), 50);
Material mtrGround(*new Color(0.1,0.0,0.0,1), *new Color(0.5,0.5,0.1,1), *new Color(0.8,0.3,0.1,1), 50); 

void Test();

int main(int argc, char* argv[])
{

	if(true)
	{
		GlutWinObj glWin1(640,480,100,100);
		
		//imgTexGround.ReadImage();
		//imgTexSky.ReadImage();
		//imgTexRail.ReadImage();

		txrGround.LoadTexture(imgTexGround);
		txrSky.LoadTexture(imgTexSky);	
		txrRail.LoadTexture(imgTexRail);
		txrEarth.LoadTexture(imgTexEarth);
		txrMoon.LoadTexture(imgTexMoon);

		//Init the GlutWinObj and register all the callbacks
		glWin1.InitGlut(argc,argv);
		glWin1.GlutCreateWindow("CSCI420_ASSIGNMENT 2");		
		glWin1.Reg_Callbacks_Prime();

		//Main Loop start
		glWin1.StartGlutLoop();	
	}
	else
	{
		Test();
	}
	return 0;
}

void Test()
{	
	Vector V1(1,1,1), V2(2,3,4), p;

	V1 = -V2;
}