#pragma once
#include <GL/glut.h>
class igvQuad
{
	int div_x;
	int div_z;
	float tam_x, tam_z;
public:
	igvQuad(int dx, int dz, float tx, float tz);
	~igvQuad();
	void visualizar();
};

