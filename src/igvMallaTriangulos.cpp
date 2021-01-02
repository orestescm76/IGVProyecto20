
#include "igvMallaTriangulos.h"

igvMallaTriangulos::igvMallaTriangulos() :num_vertices(0), vertices(nullptr), num_triangulos(0), triangulos(nullptr),normales(nullptr)
{
}

igvMallaTriangulos::igvMallaTriangulos(long int _num_vertices, float* _vertices, long int _num_triangulos, unsigned int* _triangulos) 
{

	num_vertices = _num_vertices;
	vertices = new float[num_vertices * 3];
	for (long int i = 0; i < (num_vertices * 3); ++i) {
		vertices[i] = _vertices[i];
	}

	normales = nullptr;

	num_triangulos = _num_triangulos;
	triangulos = new unsigned int[num_triangulos * 3];
	for (long int i = 0; i < (num_triangulos * 3); ++i) {
		triangulos[i] = _triangulos[i];
	}


}

igvMallaTriangulos::~igvMallaTriangulos() 
{
	if (vertices)
		delete []vertices;
	if (normales)
		delete []normales;
	if (triangulos)
		delete []triangulos;
}


void igvMallaTriangulos::visualizar(void) 
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color.cloneToFloatArray());
	glColor3fv(colorSeleccion.cloneToFloatArray());

	glShadeModel(GL_SMOOTH);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normales);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

	glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

