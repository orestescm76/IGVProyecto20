#include "igvInterfaz.h"
extern igvInterfaz interfaz;

igvInterfaz::igvInterfaz() 
{
	boton_retenido = false;
}
igvInterfaz::~igvInterfaz() {}

void igvInterfaz::crearMundo()
{
	/*interfaz.camara.set(IGV_PARALELA, igvPunto3D(5,5,5), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0),
		-1 * 4.5, 1 * 4.5, -1 * 4.5, 1 * 4.5, -1 * 3, 200);*/
	interfaz.camara.set(IGV_PERSPECTIVA, igvPunto3D(5,5,5), igvPunto3D(0,0,0), igvPunto3D(0, 1.0, 0), 60, (double)interfaz.ancho_ventana/(double)interfaz.alto_ventana, 1,200);
}

void igvInterfaz::configurarEntorno(int argc, char** argv, int _ancho_ventana, int _alto_ventana, int _pos_X, int _pos_Y, std::string _titulo)
{
	alto_ventana = _alto_ventana;
	ancho_ventana = _ancho_ventana;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(ancho_ventana, alto_ventana);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_titulo.c_str());
	crearMenu();
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana
	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	glEnable(GL_TEXTURE_2D); // activa el uso de texturas

	crearMundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::iniciarBucle()
{
	glutMainLoop();
}

void igvInterfaz::crearMenu()
{
	int menu_textura = glutCreateMenu(procesarTextura);
	glutAddMenuEntry("Giygas", GIYGAS);
	glutAddMenuEntry("Paracletus", PARACLETO);
	glutAddMenuEntry("Windows 95", WINDOWS_95);
	glutAddMenuEntry("Piedra", PIEDRA);
	glutAddMenuEntry("Marmol", MARMOL);
	glutAddMenuEntry("Ninguna", NINGUNA);
	int menu_color = glutCreateMenu(procesarColor);
	glutAddMenuEntry("Rojo", ROJO);
	glutAddMenuEntry("Dorado", DORADO);
	glutAddMenuEntry("Verde", VERDE);
	glutAddMenuEntry("Azul", AZUL);
	glutAddMenuEntry("Morado", MORADO);
	glutAddMenuEntry("Gris", GRIS);
	int menu_aplicacion_textura = glutCreateMenu(procesarAplicacionTextura);
	glutAddMenuEntry("Replace", GL_REPLACE);
	glutAddMenuEntry("Decal", GL_DECAL);
	glutAddMenuEntry("Blend", GL_BLEND);
	glutAddMenuEntry("Modulate", GL_MODULATE);
	int menu_aplicacion_filtro = glutCreateMenu(procesarFiltro);
	glutAddMenuEntry("Linear", GL_LINEAR);
	glutAddMenuEntry("Nearest", GL_NEAREST);
	int menu = glutCreateMenu(menuHandle);
	glutAddSubMenu("Texturas", menu_textura);
	glutAddSubMenu("Colores", menu_color);
	glutAddSubMenu("Aplicacion textura", menu_aplicacion_textura);
	glutAddSubMenu("Filtro de la textura", menu_aplicacion_filtro);
	glutAddMenuEntry("Salir", 200);




	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void igvInterfaz::set_glutReshapeFunc(int w, int h)
{
	// dimensiona el viewport al nuevo ancho y alto de la ventana
	//guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);
	interfaz.camara.setRAspecto((double)w / (double)h);
	//establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}
void igvInterfaz::set_glutMotionFunc(GLint x, GLint y)
{
	if (interfaz.boton_retenido)
	{
		//mover el punto de referencia.
		igvPunto3D punto = interfaz.camara.getPuntoReferencia();
		float a = interfaz.camara.getAngulo();
		int dx = interfaz.cursorX - x;
		int dy = interfaz.cursorY - y;

		//se mueve un poco janky pero funciona...
		if (dx < 0 && abs(dy) < 5)
			a += .2*dx;
		else if (dx > 0 && abs(dy) < 5)
			a += .2* dx;
		if (dy < 0 && abs(dx) < 5)
			punto[1] += .04 *(-dy);
		else if (dy > 0 && abs(dx) < 5)
			punto[1] -= .04* (dy);

		//guardar la nueva posición del ratón 
		interfaz.cursorX = x;
		interfaz.cursorY = y;
		interfaz.camara.setPuntoReferencia(punto);
		interfaz.camara.setAnguloyRotar(a);
	}
	interfaz.camara.aplicar();
	glutPostRedisplay();
}
void igvInterfaz::set_glutSpecialFunc(int key, int x, int y)
{
	// Manejo de la cámara con las teclas del ratón...
	igvPunto3D punto = interfaz.camara.getPuntoReferencia();
	float a = interfaz.camara.getAngulo();
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		a += 7;
		break;
	case GLUT_KEY_LEFT:
		a -= 7;
		break;
	case GLUT_KEY_UP:
		punto.c[1] += .75;
		break;
	case GLUT_KEY_DOWN:
		punto.c[1] -= .75;
		break;
	default:
		break;
	}
	interfaz.camara.setPuntoReferencia(punto);
	interfaz.camara.setAnguloyRotar(a);
	interfaz.camara.aplicar();
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}
void igvInterfaz::menuHandle(int value)
{
	interfaz.seleccionMenu = value;
	if (value == 200)
		exit(0);
	glutPostRedisplay();
}
void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y)
{
	igvPunto3D punto(interfaz.camara.getPuntoReferencia());
	igvPunto3D pos(interfaz.camara.getPosicion());
	float vecForward[3] = { punto.c[0] - pos.c[0], punto.c[1] - pos.c[1], punto.c[2] - pos.c[2] };
	igvPunto3D mov(vecForward[0], vecForward[1], vecForward[2]);
	mov.normalizar();
	float a = interfaz.camara.getAngulo();
	igvPunto3D arriba(0, 1, 0);
	igvPunto3D movLat = mov.getProductoVectorial(arriba);
	switch (key)
	{
	case 'w': //delante
		pos[0] += mov[0] * 1.15;
		pos[1] += mov[1] * 1.15;
		pos[2] += mov[2] * 1.15;
		punto[0] += mov[0] * 1.15;
		punto[1] += mov[1] * 1.15;
		punto[2] += mov[2] * 1.15;
		break;
	case 's': //detrás
		pos[0] -= mov[0] * 1.15;
		pos[1] -= mov[1] * 1.15;
		pos[2] -= mov[2] * 1.15;
		break;
	case 'd': //ve a la derecha
		pos[0] += movLat[0] * 1.15;
		pos[1] += movLat[1] * 1.15;
		pos[2] += movLat[2] * 1.15;
		break;
	case 'a': //ve a la derecha
		pos[0] -= movLat[0] * 1.15;
		pos[1] -= movLat[1] * 1.15;
		pos[2] -= movLat[2] * 1.15;
		break;
	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);
		break;
	case 'E': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);
		break;
	case 27: // tecla de escape para SALIR
		exit(1);
		break;
	default:
		break;
	}
	interfaz.camara.setPos(pos);
	interfaz.camara.setPuntoReferencia(punto);
	interfaz.camara.setAnguloyRotar(a);
	interfaz.camara.aplicar();
	glutPostRedisplay();
}
void igvInterfaz::set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y)
{
	interfaz.cursorX = x;
	interfaz.cursorY = y;
	switch (boton)
	{
	case GLUT_MIDDLE_BUTTON:
		if (estado == GLUT_DOWN)
		{
			interfaz.boton_retenido = true;
			interfaz.cursorX = x;
			interfaz.cursorY = y;
		}
		break;
	case GLUT_LEFT_BUTTON:
		if (estado == GLUT_DOWN)
		{
			interfaz.boton_retenido = false;
			interfaz.modo = IGV_SELECCIONAR;
			// Apartado A: guardar el pixel pulsado
			interfaz.cursorX = x;
			interfaz.cursorY = interfaz.alto_ventana - y;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();

}
void igvInterfaz::set_glutDisplayFunc() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	// se establece el viewport
	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());
	if (interfaz.modo == IGV_SELECCIONAR)
	{
		//Si estamos en modo selección...
		glDisable(GL_LIGHTING);
		glDisable(GL_DITHER);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);
		if (interfaz.objeto_seleccionado != -1)
		{
			float cS[3] = { 0.0, (interfaz.objeto_seleccionado*2) / 255.0f, 0.0 };
			interfaz.escena.activarSeleccion(interfaz.objeto_seleccionado);
		}
		interfaz.objeto_seleccionado = -1;
		interfaz.camara.aplicar();
		interfaz.escena.visualizarSeleccion();
		GLubyte colorSeleccionado[3];
		glReadPixels(interfaz.cursorX, interfaz.cursorY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, colorSeleccionado);
		interfaz.objeto_seleccionado = colorSeleccionado[1];
		if (interfaz.objeto_seleccionado >= 255)
			interfaz.objeto_seleccionado = -1;
		interfaz.escena.activarSeleccion(interfaz.objeto_seleccionado);
		interfaz.modo = IGV_VISUALIZAR;
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		// establece los parámetros de la cámara y de la proyección
		interfaz.camara.aplicar();

		//visualiza la escena
		interfaz.escena.visualizar();
		// refresca la ventana
		glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
	}

}
void igvInterfaz::inicializarEventos()
{
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutMouseFunc(set_glutMouseFunc);
	glutMotionFunc(set_glutMotionFunc);
	glutSpecialFunc(set_glutSpecialFunc);
}

void igvInterfaz::procesarTextura(int val)
{
	interfaz.escena.setAplicacionTextura(interfaz.objeto_seleccionado, val);
	interfaz.objeto_seleccionado = -1;
	interfaz.escena.restablecerColores();
	glutPostRedisplay();
}

void igvInterfaz::procesarColor(int val)
{
	interfaz.escena.setAplicacionColor(interfaz.objeto_seleccionado, val);
	interfaz.objeto_seleccionado = -1;
	interfaz.escena.restablecerColores();
	glutPostRedisplay();
}

void igvInterfaz::procesarAplicacionTextura(int val)
{
	interfaz.escena.setAplicacionTexturaOpenGL(interfaz.objeto_seleccionado, val);
	interfaz.objeto_seleccionado = -1;
	interfaz.escena.restablecerColores();
	glutPostRedisplay();
}

void igvInterfaz::procesarFiltro(int val)
{
	interfaz.escena.setFiltro(interfaz.objeto_seleccionado, val);
	interfaz.objeto_seleccionado = -1;
	interfaz.escena.restablecerColores();
	glutPostRedisplay();
}
