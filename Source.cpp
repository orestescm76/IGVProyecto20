#define SDL_MAIN_HANDLED //Tengo errores de vinculación, Dios sabrá...
#include <cstdlib>
#include "igvInterfaz.h"
igvInterfaz interfaz;
const std::string version = "v1.0 RC1";
int main(int argc, char*argv[])
{
	interfaz.configurarEntorno(argc, argv, 1024, 768, 300,300, "Proyecto IGV " + version);
	interfaz.inicializarEventos();
	interfaz.iniciarBucle();
	return 0;
}