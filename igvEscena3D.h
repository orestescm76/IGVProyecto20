#pragma once
#include <GL/glut.h>
#include "igvCilindro.h"
#include "igvFuenteLuz.h"
class igvEscena3D
{
	bool ejes;
	igvCilindro* cilindro;
	igvFuenteLuz* luzFija;
public:
	igvEscena3D();
	~igvEscena3D();
	void visualizar();
	void visualizarEjes();
	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };
};

