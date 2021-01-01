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
	//Punteros que representan los objetos.
	igvCilindro* cilindro;
	igvFuenteLuz* luzFija;
	igvQuad* quad;
	igvCaballo* caballitoDePalo;
	std::vector<igvTextura*> texturas;
	std::vector<igvColor*> colores;
	//Arrays que representan qué color y qué textura tienen los objetos, así como su aplicación.
	int texturaAplicada[numObjetos];
	int colorAplicado[numObjetos];
	//Métodos privados para aplicar el color y la textura.
	void aplicarTextura(int objeto);
	void aplicarColor(int objeto);
	igvColor colorTetera;
public:
	igvEscena3D();
	~igvEscena3D();
	void visualizar();
	//Método para visualizar la selección.
	void visualizarSeleccion();
	void visualizarEjes();
	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };
	//Métodos para la selección.
	void activarSeleccion(int obj);
	void restablecerColores();
	//Métodos para configurar texturas y colores.
	void setAplicacionTextura(int objeto, int textura);
	void setAplicacionColor(int objeto, int color);
	void setAplicacionTexturaOpenGL(int objeto, int val);
	void setFiltro(int objeto, int val);
	void setRepeticion(int objeto, int val);
};

