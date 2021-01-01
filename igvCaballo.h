#pragma once
#include "igvMallaTriangulos.h"
#include "igvMaterial.h"
#include "igvColor.h"

//Clase que es un caballo del ajedrez.

class igvCaballo : public igvMallaTriangulos
{
	std::string filename = "Knight.obj";
	igvMaterial mat;
	
public:
	igvCaballo();
	void aplicarMaterial() { mat.aplicar(); }
};

