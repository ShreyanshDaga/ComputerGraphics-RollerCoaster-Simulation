/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef MAIN_H
#define MAIN_H


	//Headers
	#include<stdio.h>
	#include<conio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<iostream>
	#include<fstream>
	#include<Windows.h>
	#include<gl\GL.h>	
	#include<gl\glut.h>
	#include"pic.h"
	#include<string>
	
	using namespace std;

	//Misc Function Prototypes
	void DisplayVertex();
	void DisplayFrustumVolume();
	void RenderWorld();
	void DrawCube();
	void DrawEarth();
	void DrawMoon();
	void DrawAsteroid();
	void SaveFrame(char *pszTitle);

#endif