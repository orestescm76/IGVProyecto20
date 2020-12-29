#include "igvPunto3D.h"
//Copia práctica 4
// Constructores
igvPunto3D::igvPunto3D() 
{
	c[X] = c[Y] = c[Z] = 0.0;
}

igvPunto3D::igvPunto3D (const double& x, const double& y, const double& z )
{
	c[X] = x;
	c[Y] = y;
	c[Z] = z;	
}

// Constructor de copia
igvPunto3D::igvPunto3D (const igvPunto3D& p )
{
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
}

// Operador de asignación
igvPunto3D& igvPunto3D::operator = (const igvPunto3D& p)
{
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
	return(*this);
}

int igvPunto3D::operator == (const igvPunto3D& p) 
{
	return ((fabs(c[X]-p[X])<IGV_EPSILON) && (fabs(c[Y]-p[Y])<IGV_EPSILON) && (fabs(c[Z]-p[Z])<IGV_EPSILON));
}

int igvPunto3D::operator != (const igvPunto3D& p) {
	return ((fabs(c[X]-p[X])>=IGV_EPSILON) || (fabs(c[Y]-p[Y])>=IGV_EPSILON) || (fabs(c[Z]-p[Z])>=IGV_EPSILON));
}

// Destructor
igvPunto3D::~igvPunto3D() 
{
}

// Operadores

void igvPunto3D::set( const double& x, const double& y, const double& z) 
{
	c[X] = x;
	c[Y] = y;
	c[Z] = z;
}

float* igvPunto3D::cloneToFloatArray() const
{
	float* res = new float[4]{ (float)c[0], (float)c[1], (float)c[2], 1.0 };
	return res;
}

void igvPunto3D::normalizar()
{
	double distancia = pow(c[0], 2) + pow(c[1], 2) + pow(c[2], 2);
	distancia = sqrt(distancia);
	for (int i = 0; i < 3; i++)
	{
		c[i] /= distancia;
	}
}

igvPunto3D igvPunto3D::getProductoVectorial(const igvPunto3D& vec)
{
	igvPunto3D ans;
	ans[0] = c[1] * vec[2] - c[2] * vec[1];
	ans[1] = -(c[0] * vec[2] - c[2] * vec[0]);
	ans[2] = c[0] * vec[1] - c[1] * vec[0];
	return ans;
}
