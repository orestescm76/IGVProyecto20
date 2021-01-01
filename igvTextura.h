#ifndef __IGVTEXTURA
#define __IGVTEXTURA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <SDL_image.h>
#include <stdio.h>
#include <string>

class igvTextura {

	protected:
		// Atributos
		unsigned int idTextura; // identificador de la textura
		unsigned int alto,  // alto de la textura
			           ancho; // ancho de la textura
		SDL_Surface* imagen = nullptr;
		std::string fichero;
		int modoAplicacion;
		int filtro;
		int repeticion;
		// Metodos

	public:
		// Constructores por defecto y destructor
		igvTextura(std::string fich); // Textura cargada desde un fichero
		~igvTextura();

		// Metodos
		void aplicar(void); //Establece la textura como la activa
		void setIdTextura(unsigned int id) { this->idTextura = id;}
		unsigned int getIdTextura() { return this->idTextura; }
		void crearTextura(char* fichero);
		void setAplicacion(int app) { modoAplicacion = app; }
		void setFiltro(int f) { filtro = f; }
		void setRepeticion(int r) { repeticion = r; }
};

#endif

