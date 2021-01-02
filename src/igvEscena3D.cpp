#include "igvEscena3D.h"
void igvEscena3D::aplicarTextura(int objeto)
{
	if (texturaAplicada[objeto] != -1)
		texturas[texturaAplicada[objeto]]->aplicar();
	else
		glDisable(GL_TEXTURE_2D);
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
	case 3:
		caballitoDePalo->setColor(*colores[colorAplicado[objeto]]);
		break;
	}
}
igvEscena3D::igvEscena3D(): texturas(std::vector<igvTextura*>()), ejes(true), colores(std::vector<igvColor*>())
{
	//Creación de la escena, colores y texturas.
	cilindro = new igvCilindro(2,2,50,10);
	cilindro->setColorSeleccion(igvColor(0, 0, 0));
	luzFija = new igvFuenteLuz(GL_LIGHT0, igvPunto3D(2.0, 5.0, 3.0), igvColor(0, 0, 0, 1), igvColor(1, 1, 1, 1), igvColor(1, 1, 1, 1), 1, 0, 0);
	quad = new igvQuad(200,200,5,5);
	quad->setColorSeleccion(igvColor(0, 1.0/255.0, 0));

	texturas.push_back(new igvTextura("./texturas/cacodemon.jpg"));
	texturas.push_back(new igvTextura("./texturas/mirage.jpg"));
	texturas.push_back(new igvTextura("./texturas/win95.jpg"));
	texturas.push_back(new igvTextura("./texturas/piedra.jpg"));
	texturas.push_back(new igvTextura("./texturas/marmol.jpg"));
	texturas.push_back(new igvTextura("./texturas/hierba.jpg"));
	for (int i = 0; i < numObjetos; i++)
	{
		texturaAplicada[i] = -1;
	}
	colores.push_back(new igvColor(1, 0, 0)); //rojo
	colores.push_back(new igvColor(0.918, 0.745, 0.247)); //oro
	colores.push_back(new igvColor(0, 1, 0)); //verde
	colores.push_back(new igvColor(0, 0, 1)); //azul
	colores.push_back(new igvColor(0.333, 0.141, 0.424)); //morado
	colores.push_back(new igvColor(.4,.4,.4)); //gris
	colorAplicado[0] = 2;
	colorAplicado[1] = 0;
	colorAplicado[2] = 5;
	colorAplicado[3] = 5;
	caballitoDePalo = new igvCaballo();
	caballitoDePalo->setColorSeleccion(igvColor(0, 3.0 / 255.0, 0));
	restablecerColores();
}

igvEscena3D::~igvEscena3D()
{
	delete cilindro;
	delete luzFija;
	delete quad;
	delete caballitoDePalo;
	for (igvTextura* t : texturas)
		delete t;
	for (igvColor* c : colores)
		delete c;
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
		glPushMatrix();
			aplicarTextura(1);
			quad->visualizar();
		glPopMatrix();
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_EMISSION, colorTetera.cloneToFloatArray());
			glTranslatef(0, 1, 5);
			aplicarTextura(2);
			glutSolidTeapot(1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(4.5,0,0);
			glScalef(.15,.15,.15);
			aplicarTextura(3);
			caballitoDePalo->visualizar();
		glPopMatrix();
	glPopMatrix();
}

void igvEscena3D::visualizarSeleccion()
{
	cilindro->visualizar();
	quad->visualizar();
	glPushMatrix();
		glColor3f(0, 2.0 / 255, 0);
		glTranslatef(0, 1, 5);
		glutSolidTeapot(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(4.5, 0, 0);
		glScalef(.15,.15,.15);
		caballitoDePalo->visualizar();
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
	case 3: //caballito
		caballitoDePalo->setColor(igvColor(.75, .75, .4));
		break;
	case -1:
		restablecerColores();
		break;
	}
}
//Restablece los colores tras una selección
void igvEscena3D::restablecerColores()
{
	for (int i = 0; i < numObjetos; i++)
	{
		aplicarColor(i);
	}
}
//Metodos para editar la textura de cada objeto y los colores y más opciones.
void igvEscena3D::setAplicacionTextura(int objeto, int textura)
{
	texturaAplicada[objeto] = textura;
}

void igvEscena3D::setAplicacionColor(int objeto, int color)
{
	colorAplicado[objeto] = color;
}

void igvEscena3D::setAplicacionTexturaOpenGL(int objeto, int val)
{
	if(texturaAplicada[objeto] != -1)
		texturas[texturaAplicada[objeto]]->setAplicacion(val);
}

void igvEscena3D::setFiltro(int objeto, int val)
{
	if (texturaAplicada[objeto] != -1)
		texturas[texturaAplicada[objeto]]->setFiltro(val);
}

void igvEscena3D::setRepeticion(int objeto, int val)
{
	if (texturaAplicada[objeto] != -1)
		texturas[texturaAplicada[objeto]]->setRepeticion(val);
}
