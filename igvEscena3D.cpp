#include "igvEscena3D.h"
/*
* POR HACER:
* implementar la rotacion de la camara con el boton central
* funciones sencillas con el teclado para moverla y ampliar (será perspectiva)
* cargar texturas
* crear varios materiales, investigando - configurar parametros material con teclas ya implementadas, fácil porque sé cual es el activo para cada uno.
* crear la textura del cilindro
* coordtex para el cilindro
* crear la clase igvCD
* meter una tetera si eso
* meter mas luces si eso
* EXTRA: meter modelos
*/
igvEscena3D::igvEscena3D()
{
	ejes = true;
	cilindro = new igvCilindro(1, 1, 50, 50);
	luzFija = new igvFuenteLuz(GL_LIGHT0, igvPunto3D(2.0, 4.0, 3.0), igvColor(0, 0, 0, 1), igvColor(1, 1, 1, 1), igvColor(1, 1, 1, 1), 1, 0, 0);
	quad = new igvQuad(50, 50, 6, 6);
}

igvEscena3D::~igvEscena3D()
{
	delete cilindro;
	delete luzFija;
}

void igvEscena3D::visualizar()
{
	if (ejes)
		visualizarEjes();

	glPushMatrix();

	luzFija->aplicar();
	cilindro->visualizar();
	quad->visualizar();
	glPopMatrix();
}

void igvEscena3D::visualizarEjes()
{
	GLfloat rojo[] = { 1,0,0,1 };
	GLfloat verde[] = { 0,1,0,1.0 };
	GLfloat azul[] = { 0,0,1,1.0 };
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
		glBegin(GL_LINES);
		glVertex3f(1000, 0, 0);
		glVertex3f(-1000, 0, 0);
		glEnd();

		glMaterialfv(GL_FRONT, GL_EMISSION, verde);
		glBegin(GL_LINES);
		glVertex3f(0, 1000, 0);
		glVertex3f(0, -1000, 0);
		glEnd();

		glMaterialfv(GL_FRONT, GL_EMISSION, azul);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 1000);
		glVertex3f(0, 0, -1000);
		glEnd();
	glPopMatrix();
}
