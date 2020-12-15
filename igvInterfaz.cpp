#include "igvInterfaz.h"
extern igvInterfaz interfaz;

igvInterfaz::igvInterfaz() {}
igvInterfaz::~igvInterfaz() {}

void igvInterfaz::crearMundo()
{
	interfaz.camara.set(IGV_PARALELA, igvPunto3D(3.0, 2.0, 4), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0),
		-1 * 4.5, 1 * 4.5, -1 * 4.5, 1 * 4.5, -1 * 3, 200);
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
	int menu_id = glutCreateMenu(menuHandle);
	glutAddMenuEntry("Test", 0);
	glutAddMenuEntry("Test2", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void igvInterfaz::set_glutReshapeFunc(int w, int h)
{
	// dimensiona el viewport al nuevo ancho y alto de la ventana
// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}
void igvInterfaz::menuHandle(int value)
{
	interfaz.seleccionMenu = value;
	glutPostRedisplay();
}
void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
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
	glutPostRedisplay();
}
void igvInterfaz::set_glutDisplayFunc() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	// se establece el viewport
	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();

	//visualiza la escena
	interfaz.escena.visualizar();

	// refresca la ventana
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}
void igvInterfaz::inicializarEventos()
{
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutKeyboardFunc(set_glutKeyboardFunc);
}