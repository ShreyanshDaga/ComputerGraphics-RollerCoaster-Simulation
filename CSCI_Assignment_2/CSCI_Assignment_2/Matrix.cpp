/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#include"main.h"
#include"Matrix.h"


Matrix::Matrix()
{
	this->iM = 0;
	this->iN = 0;

	this->daMat = NULL;
}

Matrix::~Matrix()
{	
}

void Matrix::FreeMemory()
{
	for(int i = 0;i<this->GetM();i++)
	{
		delete [] this->daMat[i];
	}
	
	delete [] this->daMat;
}

Matrix::Matrix(int iM, int iN)
{
	this->iM = iM;
	this->iN = iN;

	this->AllocMatrixMem();
}

Matrix::Matrix(int iM)
{
	this->iM = iM;
	this->iN = iM;

	this->AllocMatrixMem();
}

void Matrix::AllocMatrixMem()
{
	this->daMat = new float*[iM];

	for(int i = 0;i<iM;i++)
		this->daMat[i] = new float[iN];

	for(int i = 0;i<iM;i++)
	{
		for(int j = 0;j<iN;j++)
		{
			this->SetElement(i,j,0.00);
		}
	}
}

void Matrix::SetM(int iM)
{
	this->iM = iM;
}

void Matrix::SetN(int iN)
{
	this->iN = iN;
}

void Matrix::SetElement(int i, int j, float dElem)
{
	this->daMat[i][j] = dElem;
}

void Matrix::SetElements(float daElems[])
{
	for(int i = 0;i<iM;i++)
	{
		for(int j = 0;j<iN;j++)
		{
			this->SetElement(i,j,daElems[i*this->iN + j]);
		}
	}
}

int Matrix::GetM()
{
	return this->iM;
}

int Matrix::GetN()
{
	return this->iN;
}

float Matrix::GetElement(int i, int j)
{
	return this->daMat[i][j];
}

double Matrix::FindDet()
{
	double dDet = 0.00;

	// order must be >= 0
    // stop the recursion when matrix is a single element
	if( this->iM == 1 )
		return this->GetElement(0,0);
 
    // allocate the cofactor matrix
	Matrix matCofactor(this->iM - 1);
 
    for(int i = 0; i < this->iM; i++ )
    {
        // get minor of element (0,i)
        matCofactor = this->GetMinor(0, i);
        
		// Call recursively		
		dDet += (i%2==1?-1.0:1.0) * this->GetElement(0,i) * matCofactor.FindDet();       
    }
 
    return dDet;
}

Matrix Matrix::GetMinor(int iRow, int iCol)
{
	// indicate which col and row is being copied to dest
    int colCount=0,rowCount=0;
	Matrix matCofact(this->iM - 1);
    
	for(int i = 0; i < this->iM; i++ )
    {
        if( i != iRow )
        {
            colCount = 0;
            for(int j = 0; j < this->iM; j++ )
            {
                // when j is not the element
                if( j != iCol )
                {
					matCofact.SetElement(rowCount,colCount, this->GetElement(i,j));
                    colCount++;
                }
            }
            rowCount++;
        }
    }
 
    return matCofact;
}

Matrix* Matrix::MatrixTranspose()
{
	Matrix *pmatTemp = new Matrix(this->iN,this->iM);

	for(int i = 0;i<iN;i++)
	{
		for(int j = 0;j<iM;j++)
		{
			pmatTemp->SetElement(i,j,this->GetElement(j,i));
		}
	}

	return pmatTemp;
}

Matrix* Matrix::InverseMatrix()
{
	if(this->iM != this->iN)
	{
		cout<<"\n Error Matrix is not square matrix, Cannot compute Inverse.!";
		exit(1);
	}

	Matrix *pmatInv = new Matrix(this->iM);

	//MatrixInversion(this->daMat,this->iM,pmatInv->daMat);

	return pmatInv;
}

void Matrix::PrintMatrix()
{
	for(int i = 0;i<this->GetM();i++)
	{
		cout<<"\n";
		for(int j = 0;j<this->GetN();j++)
		{
			cout.precision(4);
			cout<<"\t"<<this->GetElement(i,j);
		}
	}
}


//Static Functions

Matrix* Matrix::MatrixMultiply(Matrix M1, Matrix M2)
{
	Matrix *matNULL;

	if(M1.GetN() != M2.GetM())
	{
		cout<<"\n ERROR!!! Matrix Size Incompatible!";
		return matNULL;
	}

	Matrix *matAns = new Matrix(M1.iM, M2.iN);

	for(int i = 0;i<M1.iM;i++)
	{
		for(int j = 0;j<M2.iN;j++)
		{
			matAns->SetElement(i,j,0.00);
			double daElem = 0.00;

			for(int l = 0;l<M1.iN;l++)
			{				
				daElem += M1.GetElement(i,l)*M2.GetElement(l,j);			
			}
			matAns->SetElement(i,j,daElem);
		}
	}

	return matAns;
}

Matrix* Matrix::MatrixAdd(Matrix M1, Matrix M2)
{
	Matrix *matNULL;

	if(M1.GetN() != M2.GetN() || M1.GetM() != M2.GetM())
	{
		cout<<"\n ERROR!!! Matrix Size Incompatible!";
		return matNULL;
	}

	Matrix *matAns = new Matrix(M1.iM, M2.iN);

	for(int i = 0;i<M1.iM;i++)
	{
		for(int j = 0;j<M2.iN;j++)
		{			
			double daElem = 0.00;

			daElem = M1.GetElement(i,j) + M2.GetElement(i,j);
			matAns->SetElement(i,j,daElem);
		}
	}

	return matAns;
}

Matrix* Matrix::MatrixSubtract(Matrix M1, Matrix M2)
{
	Matrix *matNULL;

	if(M1.GetN() != M2.GetN() || M1.GetM() != M2.GetM())
	{
		cout<<"\n ERROR!!! Matrix Size Incompatible!";
		return matNULL;
	}

	Matrix *matAns = new Matrix(M1.iM, M2.iN);

	for(int i = 0;i<M1.iM;i++)
	{
		for(int j = 0;j<M2.iN;j++)
		{			
			double daElem = 0.00;

			daElem = M1.GetElement(i,j) - M2.GetElement(i,j);
			matAns->SetElement(i,j,daElem);
		}
	}

	return matAns;
}

Matrix* Matrix::IdentityMatrix(int iSize)
{
	Matrix *matIden = new Matrix(iSize);
	double dElem = 0.00;

	for(int i = 0;i<iSize;i++)
	{
		for(int j = 0;j<iSize;j++)
		{			
			if(i == j)
				dElem = 1.00;
			else
				dElem = 0.00;

			matIden->SetElement(i,j,dElem);
		}
	}

	return matIden;
}

Matrix* Matrix::FindMatrixA(Matrix matU, Matrix matV, int iOrder)
{
	int iUorder = matU.GetM();
	Matrix *pmatA;


	if(iOrder ==  1)
	{
		pmatA = new Matrix(3,3);
		
		for(int i = 0;i<iUorder;i++)
		{
			pmatA->SetElement(i,0,1);				
			pmatA->SetElement(i,1,matU.GetElement(i,0));
			pmatA->SetElement(i,2,matV.GetElement(i,0));
		}		
	}
	else if(iOrder == 2)
	{
		pmatA = new Matrix(6,6);
		for(int i = 0;i<iUorder;i++)
		{
			pmatA->SetElement(i,0,1);				
			pmatA->SetElement(i,1,matU.GetElement(i,0));
			pmatA->SetElement(i,2,matV.GetElement(i,0));
			pmatA->SetElement(i,3,matU.GetElement(i,0)*matU.GetElement(i,0));
			pmatA->SetElement(i,4,matV.GetElement(i,0)*matU.GetElement(i,0));
			pmatA->SetElement(i,5,matV.GetElement(i,0)*matV.GetElement(i,0));			
		}
	}
	
	return pmatA;
}

Matrix* Matrix::MergeByRow(Matrix matM1, Matrix matM2)
{
	Matrix *pmatM;

	if(matM1.GetN() != matM2.GetN())
	{
		return pmatM;
	}

	pmatM = new Matrix(matM1.GetM() + matM2.GetM(),matM1.GetN());

	for(int j = 0;j<matM1.GetN();j++)
	{
		for(int i = 0;i<matM1.GetM();i++)
		{
			pmatM->SetElement(i,j,matM1.GetElement(i,j));
		}

		for(int i = 0;i<matM2.GetM();i++)
		{
			pmatM->SetElement(i + matM1.GetM(),j,matM2.GetElement(i,j));
		}
	}

	return pmatM;
}

Matrix* Matrix::MergeByCol(Matrix matM1, Matrix matM2)
{
	Matrix *pmatM;

	if(matM1.iM != matM2.iM)
	{
		return pmatM;
	}

	pmatM = new Matrix(matM1.GetM(),matM1.GetN() + matM2.GetN());

	for(int i = 0;i<matM1.GetM();i++)
	{
		for(int j = 0;j<matM1.GetN();j++)
		{
			pmatM->SetElement(i,j,matM1.GetElement(i,j));
		}

		for(int j = 0;j<matM2.GetN();j++)
		{
			pmatM->SetElement(i,j + matM1.GetN(),matM2.GetElement(i,j));
		}
	}

	return pmatM;
}
