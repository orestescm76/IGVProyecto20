#include <cstdlib>
#include "igvInterfaz.h"
igvInterfaz interfaz;
const std::string version = "v0.03a Codename Octavarium";
int main(int argc, char** argv)
{
	interfaz.configurarEntorno(argc, argv, 500, 500, 600, 300, "Proyecto IGV " + version);
	interfaz.inicializarEventos();
	interfaz.iniciarBucle();
	return 0;
}