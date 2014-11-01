/////////////////////////////////////////////
//Name: Shreyansh Daga
//CSCI 420 Submission 2
//Date: 3/5/2014
//USC ID: 6375334833
//Email: sdaga@usc.edu
/////////////////////////////////////////////

#ifndef _VECTOR_H
#define _VECTOR_H

	class Vector
	{
		private:
			float fX;
			float fY;
			float fZ;
			float fMag;			

		public:
			Vector();
			Vector(float fX, float fY, float fZ);

			Vector* GetUnitVector();
			float GetMagnitude();
			float GetX();
			float GetY();
			float GetZ();
			
			void SetVector(float fX, float fY, float fZ);
			void SetVector(Vector vecV);
			
			static Vector* VectorCrossProduct(Vector V1, Vector V2);
			static float VectorDotProduct(Vector V1, Vector V2);

			void operator = (Vector &vecV);
			Vector* operator * (float fScal);
			Vector operator - (Vector &vecV);
			Vector operator - ();
			Vector operator + (Vector &vecV);
			void operator *= (float fScale);

	};

#endif