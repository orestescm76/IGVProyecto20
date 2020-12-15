#include "igvMaterial.h"
//Copia pr�ctica 4
igvMaterial::igvMaterial() 
{

}

igvMaterial::~igvMaterial() 
{

}

igvMaterial::igvMaterial(const igvMaterial& p) 
{	//de copia
	Ka = p.Ka;
	Kd = p.Kd;
	Ks = p.Ks;
	Ns = p.Ns;
}

igvMaterial::igvMaterial(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) 
{
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

// Metodos publicos 

void igvMaterial::aplicar(void) 
{
	// - coeficiente de reflexi�n de la luz ambiental
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ka.cloneToFloatArray());
	// - coeficiente de reflexi�n difuso
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Kd.cloneToFloatArray());
	// - coeficiente de reflesi�n especular
	glMaterialfv(GL_FRONT, GL_SPECULAR, Ks.cloneToFloatArray());
	// - exponente de Phong
	glMaterialf(GL_FRONT, GL_SHININESS, Ns);
	// establecer como color de emisi�n (0.0, 0.0, 0.0) (el objeto no es una fuente de luz)
	float negro[] = { 0,0,0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negro);
}

void igvMaterial::set(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) 
{
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}