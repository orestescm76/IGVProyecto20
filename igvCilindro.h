#define _USE_MATH_DEFINES

#include <cmath>
#include "igvMallaTriangulos.h"
//Resoluci�n m�a de la pr�ctica 3A
class igvCilindro : public igvMallaTriangulos 
{

public:

	//// Constructores por y destructor
	igvCilindro();
	igvCilindro(float r, float a, int divU, int divV);
	~igvCilindro();
	void visualizar();
	void visualizar(bool n, bool g);
};

