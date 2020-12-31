#include "igvCaballo.h"
#include <OBJ_Loader.h>
igvCaballo::igvCaballo()
{
	std::cout << "Cargando caballo\n";
	objl::Loader cargador;
	bool cargado = cargador.LoadFile(filename);

	if (cargado)
	{
		//Cargar vertices.
		int numvertices = cargador.LoadedVertices.size();
		this->num_vertices = numvertices;
		this->num_triangulos = cargador.LoadedIndices.size() / 3;
		vertices = new float[numvertices * 3];
		normales = new float[numvertices * 3];
		texCoords = new float[numvertices * 2];
		triangulos = new unsigned int[num_triangulos * 3];
		for (int i = 0; i < numvertices * 3; i += 3)
		{
			vertices[i] = cargador.LoadedVertices[i / 3].Position.X;
			vertices[i + 1] = cargador.LoadedVertices[i / 3].Position.Y;
			vertices[i + 2] = cargador.LoadedVertices[i / 3].Position.Z;
			normales[i] = cargador.LoadedVertices[i / 3].Normal.X;
			normales[i+1] = cargador.LoadedVertices[i / 3].Normal.Y;
			normales[i+2] = cargador.LoadedVertices[i / 3].Normal.Z;
		}
		for (int i = 0; i < numvertices*2; i+=2)
		{
			texCoords[i] = cargador.LoadedVertices[i / 2].TextureCoordinate.X;
			texCoords[i+1] = cargador.LoadedVertices[i / 2].TextureCoordinate.Y;
		}
		for (int i = 0; i < num_triangulos*3; i++)
		{
			triangulos[i] = cargador.LoadedIndices[i];
		}
	}

}
