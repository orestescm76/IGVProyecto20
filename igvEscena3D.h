#pragma once
#include <GL/glut.h>
#include <vector>
#include "igvCilindro.h"
#include "igvFuenteLuz.h"
#include "igvQuad.h"
#include "igvMaterial.h"
#include "igvTextura.h"
#include "igvCaballo.h"
const unsigned short numObjetos = 4;

class igvEscena3D
{
	bool ejes;
	igvCilindro* cilindro;
	igvFuenteLuz* luzFija;
	igvQuad* quad;
	igvCaballo* caballitoDePalo;
	std::vector<igvTextura*> texturas;
	std::vector<igvColor*> colores;
	int texturaAplicada[numObjetos];
	int colorAplicado[numObjetos];
	void aplicarTextura(int objeto);
	void aplicarColor(int objeto);
	igvColor colorTetera;
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
	void setAplicacionTextura(int objeto, int textura);
	void setAplicacionColor(int objeto, int color);
};

