#include "igvEscena3D.h"
/*
* POR HACER:
* implementar la rotacion de la camara con el boton central - done?
* funciones sencillas con el teclado para moverla y ampliar (será perspectiva)
* cargar texturas
* crear varios materiales, investigando - configurar parametros material con teclas ya implementadas, fácil porque sé cual es el activo para cada uno.
* crear la textura del cilindro
* coordtex para el cilindro //jodido y medio
* crear la clase igvCD
* meter una tetera si eso
* meter mas luces si eso
* seleccion
* EXTRA: meter modelos
*/
igvEscena3D::igvEscena3D() : paracleto("cheers.jpg")
{
	ejes = true;
	cilindro = new igvCilindro(2,2,50,10);
	cilindro->setColorSeleccion(igvColor(0, 1.0/255.0, 0));
	luzFija = new igvFuenteLuz(GL_LIGHT0, igvPunto3D(2.0, 4.0, 3.0), igvColor(0, 0, 0, 1), igvColor(1, 1, 1, 1), igvColor(1, 1, 1, 1), 1, 0, 0);
	quad = new igvQuad(200,200,5,5);
	quad->setColorSeleccion(igvColor(0, 2.0/255.0, 0));
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
	paracleto.aplicar();
	glPushMatrix();
	glRotatef(180, 0,0,1);
	glTranslatef(0, -2, 0);
	glRotatef(90, 0, 1, 0);
	cilindro->visualizar();
	glPopMatrix();
	quad->visualizar();
	glPopMatrix();
}

void igvEscena3D::visualizarSeleccion()
{
	cilindro->visualizar();
	quad->visualizar();
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

void igvEscena3D::activarSeleccion(int obj)
{
	switch (obj)
	{
	case 1: //cilindro
		cilindro->setColor(igvColor(0.75, 0.75, 0.4));
		break;
	case 2: //quad
		quad->setColor(igvColor(.75, .75, .4));
		break;
	case -1:
		restablecerColores();
		break;
	}
}

void igvEscena3D::restablecerColores()
{
	cilindro->setColor(igvColor(.5, .5, 0));
	quad->setColor(igvColor(1, 0, 0));
}
