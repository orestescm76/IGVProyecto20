#pragma once
#include <string>
#include <cstdlib>
#include "igvCamara.h"
#include "igvEscena3D.h"

typedef enum
{
	IGV_VISUALIZAR,
	IGV_SELECCIONAR,
}
modoInterfaz;

enum colores
{
	ROJO,
	DORADO,
	VERDE,
	AZUL,
	MORADO,
	GRIS
};

enum texturas
{
	CACODEMON,
	MIRAGE,
	WINDOWS_95,
	PIEDRA,
	MARMOL,
	HIERBA,
	NINGUNA = -1
};
class igvInterfaz
{
	int ancho_ventana;
	int alto_ventana;
	igvCamara camara;
	igvEscena3D escena;
	int seleccionMenu;
	int textura;
	int color;
	//Atributos para el mouse.
	modoInterfaz modo;
	int cursorX = 0, cursorY = 0;
	bool boton_retenido;
	int objeto_seleccionado = -1; //cada objeto tendrá su código
	float colorSeleccion[3] = { 0.992, 0.961, 0.427 };

public:
	igvInterfaz();
	~igvInterfaz();
	void set_ancho_ventana(int a) { ancho_ventana = a; }
	void set_alto_ventana(int a) { alto_ventana = a; }
	int get_ancho_ventana() { return ancho_ventana; }
	int get_alto_ventana() { return alto_ventana; }
	void crearMundo();
	void configurarEntorno(int argc, char** argv, int _ancho_ventana, int _alto_ventana, int _pos_X, int _pos_Y, std::string _titulo);
	void iniciarBucle();
	void crearMenu();
	//Eventos de OpenGL
	static void set_glutReshapeFunc(int w, int h);
	static void set_glutDisplayFunc();
	static void set_glutKeyboardFunc(unsigned char key, int x, int y);
	static void set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y);
	static void set_glutMotionFunc(GLint x, GLint y);
	static void set_glutSpecialFunc(int key, int x, int y);
	static void menuHandle(int value); //Función para manejar menús
	void inicializarEventos();
	//Métodos del menú que sirven para aplicar los colores y las texturas, asi como su configuracion.
	static void procesarTextura(int val);
	static void procesarColor(int val);
	static void procesarAplicacionTextura(int val);
	static void procesarFiltro(int val);
	static void procesarRepeticion(int val);
};

