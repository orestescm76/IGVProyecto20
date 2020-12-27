#include "igvEscena3D.h"
void igvEscena3D::aplicarTextura(int objeto)
{
	if (texturaAplicada[objeto] != -1)
		texturas[texturaAplicada[objeto]]->aplicar();
}
void igvEscena3D::aplicarColor(int objeto)
{
	switch (objeto)
	{
	case 0:
		cilindro->setColor(*colores[colorAplicado[objeto]]);
		break;
	case 1:
		quad->setColor(*colores[colorAplicado[objeto]]);
		break;
	case 2:
		colorTetera = *colores[colorAplicado[objeto]];
		break;
	}
}
/*
* POR HACER:
* implementar la rotacion de la camara con el boton central - done?
* funciones sencillas con el teclado para moverla y ampliar (será perspectiva)
* cargar texturas //done, aunque sean una porquería
* crear varios materiales, investigando - configurar parametros material con teclas ya implementadas, fácil porque sé cual es el activo para cada uno.
* crear la textura del cilindro //uhh
* coordtex para el cilindro //hecho
* crear la clase igvCD
* meter una tetera si eso
* meter mas luces si eso
* seleccion
* EXTRA: meter modelos
*/
igvEscena3D::igvEscena3D(): texturas(std::vector<igvTextura*>()), ejes(true)
{
	cilindro = new igvCilindro(2,2,50,10);
	cilindro->setColorSeleccion(igvColor(0, 0, 0));
	luzFija = new igvFuenteLuz(GL_LIGHT0, igvPunto3D(2.0, 2.0, 3.0), igvColor(0, 0, 0, 1), igvColor(1, 1, 1, 1), igvColor(1, 1, 1, 1), 1, 0, 0);
	quad = new igvQuad(200,200,5,5);
	quad->setColorSeleccion(igvColor(0, 1.0/255.0, 0));

	texturas.push_back(new igvTextura("./texturas/giygas.png"));
	texturas.push_back(new igvTextura("./texturas/paracleto.jpg"));
	texturas.push_back(new igvTextura("./texturas/win95setup.png"));
	texturas.push_back(new igvTextura("./texturas/piedra.jpg"));
	texturas.push_back(new igvTextura("./texturas/diamante.jpg"));
	for (int i = 0; i < numObjetos; i++)
	{
		texturaAplicada[i] = -1;
	}
	colores.push_back(new igvColor(1, 0, 0)); //rojo
	colores.push_back(new igvColor(0.918, 0.745, 0.247)); //oro
	colores.push_back(new igvColor(0, 1, 0)); //verde
	colores.push_back(new igvColor(0, 0, 1)); //azul
	colores.push_back(new igvColor(0.333, 0.141, 0.424)); //morado
	colores.push_back(new igvColor(.4,.4,.4));
	colorAplicado[0] = 2;
	colorAplicado[1] = 0;
	colorAplicado[2] = 5;
	restablecerColores();
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
		glPushMatrix();
			glRotatef(180, 0,0,1);
			glTranslatef(0, -2, 0);
			glRotatef(90, 0, 1, 0);
			aplicarTextura(0);
			cilindro->visualizar();
		glPopMatrix();
		aplicarTextura(1);
		quad->visualizar();
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_EMISSION, colorTetera.cloneToFloatArray());
			glTranslatef(0, 0, 5);
			aplicarTextura(2);
			glutSolidTeapot(1);
		glPopMatrix();
	glPopMatrix();
}

void igvEscena3D::visualizarSeleccion()
{
	cilindro->visualizar();
	quad->visualizar();
	glPushMatrix();
		glColor3f(0, 2.0 / 255, 0);
		glTranslatef(0, 0, 5);
		glutSolidTeapot(1);
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

void igvEscena3D::activarSeleccion(int obj)
{
	switch (obj)
	{
	case 0: //cilindro
		cilindro->setColor(igvColor(0.75, 0.75, 0.4));
		break;
	case 1: //quad
		quad->setColor(igvColor(.75, .75, .4));
		break;
	case 2: //tetera
		colorTetera = igvColor(.75, .75, .4);
		break;
	case -1:
		restablecerColores();
		break;
	}
}

void igvEscena3D::restablecerColores()
{
	for (int i = 0; i < numObjetos; i++)
	{
		aplicarColor(i);
	}
}

void igvEscena3D::setAplicacionTextura(int objeto, int textura)
{
	texturaAplicada[objeto] = textura;
}

void igvEscena3D::setAplicacionColor(int objeto, int color)
{
	colorAplicado[objeto] = color;
}
