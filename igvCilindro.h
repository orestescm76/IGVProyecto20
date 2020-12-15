#define _USE_MATH_DEFINES

#include <cmath>
#include "igvMallaTriangulos.h"
//Resolución mía de la práctica 3A
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

