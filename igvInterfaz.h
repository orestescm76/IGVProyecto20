#pragma once
#include <string>
#include <cstdlib>
#include "igvCamara.h"
#include "igvEscena3D.h"

class igvInterfaz
{
	int ancho_ventana;
	int alto_ventana;
	igvCamara camara;
	igvEscena3D escena;
	int seleccionMenu;

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
	static void set_glutReshapeFunc(int w, int h);
	static void set_glutDisplayFunc();
	static void set_glutKeyboardFunc(unsigned char key, int x, int y);
	static void menuHandle(int value); //Función para manejar menús
	void inicializarEventos();
};

