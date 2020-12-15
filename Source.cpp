#include <cstdlib>
#include "igvInterfaz.h"
igvInterfaz interfaz;
int main(int argc, char** argv)
{
	interfaz.configurarEntorno(argc, argv, 500, 500, 600, 300, "Proyecto Fuck v0.01");
	interfaz.inicializarEventos();
	interfaz.iniciarBucle();
	return 0;
}