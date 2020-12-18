#pragma once
#include <GL/glut.h>
#include "igvCilindro.h"
#include "igvFuenteLuz.h"
#include "igvQuad.h"
#include "igvMaterial.h"

class igvEscena3D
{
	bool ejes;
	igvCilindro* cilindro;
	igvFuenteLuz* luzFija;
	igvQuad* quad;
public:
	igvEscena3D();
	~igvEscena3D();
	void visualizar();
	void visualizarEjes();
	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };
};

