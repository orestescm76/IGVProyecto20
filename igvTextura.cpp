#include "igvTextura.h"

// Metodos constructores y destructor

igvTextura::igvTextura(std::string fich) {
	ancho = 0;
	alto = 0;
	idTextura = 0;
	fichero = fich;
}

void igvTextura::aplicar(void) 
{
	if (idTextura == 0)
		crearTextura((char*) fichero.c_str());
  glBindTexture(GL_TEXTURE_2D, idTextura);
}

void igvTextura::crearTextura(char* fichero)
{
	SDL_Surface* imagen = NULL;

	glEnable(GL_TEXTURE_2D);
	if (!glIsTexture(idTextura)) {

		imagen = IMG_Load(fichero);
		if (!imagen)
		{
			/* Fallo de carga de la imagen */
			printf("Error al cargar la imagen: %s\n", IMG_GetError());
			return;

		}
		/* Muestra alguna información sobre la imagen */
		printf("Cargando %s: %dx%d %dbpp\n", fichero,
			imagen->w, imagen->h, imagen->format->BitsPerPixel);


		// Apartado G: Añadir aquí el código para cargar como textura OpenGL la imagen */
		//	- Generar el identificador de textura y asignarlo al atributo idTextura (glGenTextures)
		glGenTextures(1, &idTextura);
		//	- Enlazar el identificador creado a GL_TEXTURE_2D (glBindTexture)
		glBindTexture(GL_TEXTURE_2D, idTextura);
		//  - Especificar la textura, asignádole como textura el array imagen (glTexImage2D)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen->w, imagen->h, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->pixels);
		//  - Modo de aplicación de la textura (glTexEnvf)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//	- Parámetros de la textura: repetición y filtros (glTexParameteri)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		SDL_FreeSurface(imagen);

	}
}

igvTextura::~igvTextura() {
  glDeleteTextures(1, &idTextura); 
}
