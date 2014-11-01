CSCI 420 Assignment 2 Submission
Name: Shreyansh Daga
USC ID: 6375 3348 33
EMail: sdaga@usc.edu


1) How to Run the program
The program has the following total 27 files 
Main.h			- Prototype Decln
Main.cpp		- Main starting point
GlutWinObj.h		- Class Decln
GlutWinObj.cpp		- Class Functions
Image.h			- Class Decln
Image.cpp		- Class Fucntions
Camera.h		- Class Decln	
Camra.cpp		- Class Fucntions
Color.h			- Class Decln
Color.cpp		- Class Fucntions
Light.h			- Class Decln
Light.cpp		- Class Fucntions
Material.h		- Class Decln
Material.cpp		- Class Fucntions
pic.h			- PIC Library
Point.h			- Class Decln		
Point.cpp		- Class Fucntions
Spline.h		- Class Decln
Spline.cpp		- Class Fucntions
Texture.h		- Class Decln
Textire.cpp		- Class Fucntions
Track.h			- Class Decln
Track.cpp		- Class Fucntions
Vector.h		- Class Decln
Vector.cpp		- Class Fucntions


There are the following directories in the root folder of the project
\splines		- Contains all the spline files
\textures		- Contains all the texture image files
\track			- Contains one track file which is read during the init

For Texture mappings the following images are required
\textures\tex_Mars.jpg
\textures\tex_Space_3.jpg
\textures\tex_Steel_1.jpg
\texture\tex_Earth.jpg
\texture\tex_Moon.jpg

These are directly read and initialized in the main.cpp file. The grader is welcomed to change these images to see how the change takes place in the code.
I have also provided aditional images in the \textures directory

I tried Lighting however I am not able to get the desired effect. Hence I have not removed the code which works for the lighting effects.

The program is compiled in VS 2012

I have used some OOP concepts and encapsulated some of the GL functions.
I have used the Recursive Generation of spline points method. This function can be found in the Spline.cpp file and its name is GenerateRecursive()
For this I have kept tha maxline length to be 0.08.
I have also implemented the Double Rail which can be seen when the program runs.
Other extra features like earth and moon rotation can be seen in the space, for which i have rendered a dome using sphere functions.

I have used display lists for Rendering the track and the spherical objects as well.

3) Funcionality of the program

Use the following to operate the functions
	Shft + W/S - Rotate in Z
	Shft + A/D - Rotate in X
	Shft + Q/E - Rotate in Y

        	w/s - Translate in z
		a/d - Translate in x
		q/e - translate in y
	
	Normal Mouse - Rotate in Y and X	
	Ctrl + Mouse - Translate in Z and X

	End key - Pause/Start Ride Animation

	Context Menu will give various options to change speed of the ride.


3) Animation

I also submitting the 1000 images files along with the video i made out of it
there is a choice in context menu whic when selected will start recording the animation and save the 1000 files of the screen
