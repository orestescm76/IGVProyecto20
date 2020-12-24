#pragma once
#include <GL/glut.h>
#include "igvCilindro.h"
#include "igvFuenteLuz.h"
#include "igvQuad.h"
#include "igvMaterial.h"
#include "igvTextura.h"

class igvEscena3D
{
	bool ejes;
	igvCilindro* cilindro;
	igvFuenteLuz* luzFija;
	igvQuad* quad;
	igvTextura paracleto;
public:
	igvEscena3D();
	~igvEscena3D();
	void visualizar();
	void visualizarSeleccion();
	void visualizarEjes();
	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };
	void activarSeleccion(int obj);
	void restablecerColores();
};

