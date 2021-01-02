#pragma once
#include <GL/glut.h>
#include "igvColor.h"
#include "igvMaterial.h"
class igvQuad
{
	int div_x;
	int div_z;
	float tam_x, tam_z;
	igvColor colorSeleccion;
	igvColor color;
public:
	igvQuad(int dx, int dz, float tx, float tz);
	~igvQuad();
	void visualizar();
	void setColor(igvColor c) { color = c; }
	void setColorSeleccion(igvColor c) { colorSeleccion = c; }
};

