/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

class Matrix
{
	private:
		float **daMat;
		int iM,iN;

	public:
		//Matrix Functions
		Matrix();
		~Matrix();
		void FreeMemory();
		Matrix(int iM, int iN);
		Matrix(int iM);
		void AllocMatrixMem();
		void SetM(int iM);
		void SetN(int iN);	
		void SetElements(float daElems[]);
		void SetElement(int i, int j, float dElem);		
		int GetM();
		int GetN();		
		float GetElement(int i, int j);	
		Matrix* MatrixTranspose();
		double FindDet();
		Matrix GetMinor(int iRow, int iCol);
		void PrintMatrix();
		Matrix* InverseMatrix();

		//Static Functions
		static Matrix* MatrixMultiply(Matrix M1, Matrix M2);
		static Matrix* MatrixAdd(Matrix M1, Matrix M2);
		static Matrix* MatrixSubtract(Matrix M1, Matrix M2);
		static Matrix* IdentityMatrix(int iSize);
		static Matrix* FindMatrixA(Matrix matU, Matrix matV, int iOrder);	
		static Matrix* MergeByRow(Matrix matM1, Matrix matM2);
		static Matrix* MergeByCol(Matrix matM1, Matrix matM2);
};

#endif