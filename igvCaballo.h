#pragma once
#include "igvMallaTriangulos.h"
#include <iostream>

//Clase que es un caballo del ajedrez.

class igvCaballo : public igvMallaTriangulos
{
	std::string filename = "Knight.obj";
public:
	igvCaballo();
};

