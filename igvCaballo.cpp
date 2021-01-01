#include "igvCaballo.h"
#include <OBJ_Loader.h>
igvCaballo::igvCaballo(): mat()
{
	std::cout << "Cargando caballo\n";
	objl::Loader cargador;
	bool cargado = cargador.LoadFile(filename);
	//Cargar el modelo obj con la librería.
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
		//Cargado de vértices, normales, texcoords e índices.
		for (int i = 0; i < numvertices * 3; i += 3)
		{
			vertices[i] = cargador.LoadedVertices[i / 3].Position.X;
			vertices[i + 1] = cargador.LoadedVertices[i / 3].Position.Y;
			vertices[i + 2] = cargador.LoadedVertices[i / 3].Position.Z;
			normales[i] = cargador.LoadedVertices[i / 3].Normal.X;
			normales[i + 1] = cargador.LoadedVertices[i / 3].Normal.Y;
			normales[i + 2] = cargador.LoadedVertices[i / 3].Normal.Z;
		}
		for (int i = 0; i < numvertices * 2; i += 2)
		{
			texCoords[i] = cargador.LoadedVertices[i / 2].TextureCoordinate.X;
			texCoords[i + 1] = cargador.LoadedVertices[i / 2].TextureCoordinate.Y;
		}
		for (int i = 0; i < num_triangulos * 3; i++)
		{
			triangulos[i] = cargador.LoadedIndices[i];
		}
		//Config material
		igvColor ka(cargador.LoadedMaterials[0].Ka.X, cargador.LoadedMaterials[0].Ka.Y, cargador.LoadedMaterials[0].Ka.Z);
		igvColor kd(cargador.LoadedMaterials[0].Kd.X, cargador.LoadedMaterials[0].Kd.Y, cargador.LoadedMaterials[0].Kd.Z);
		igvColor ks(cargador.LoadedMaterials[0].Ks.X, cargador.LoadedMaterials[0].Ks.Y, cargador.LoadedMaterials[0].Ks.Z);
		float ns =  cargador.LoadedMaterials[0].Ns;
		mat.set(ka, kd, ks, ns);

	}
	else
		std::cout << "No se ha podido cargar el modelo\n";

}