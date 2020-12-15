#include "igvCilindro.h"


igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV)
{
	/* Apartado B: Construir la malla de triángulos para representar el cilindro */
	//0 divsiones seria num divisiones *2 
	//1 divisiones seria *3 
	//2 divisiones seria *4
	num_vertices = divU * (2 + divV);
	//el numero de triangulos seria el numero de divisiones * 2 mas las divisiones en altura * 2.
	num_triangulos = divU * (2 + (divV * 2));
	int verticesTam = num_vertices * 3;
	vertices = new float[num_vertices * 3];
	normales = new float[num_vertices * 3];
	triangulos = new unsigned int[num_triangulos * 3];


	//Rellenado de vértices, caso de abajo.
	float div = (2 * 3.141592) / divU;

	for (int h = 0; h <= divV+1; h++) //por cada altura...
	{
		float aux = 0;
		for (int i = h * divU*3; i < h * divU * 3+(divU * 3); i += 3)
		{
			float x = cos(aux) * r;
			float y;
			if (divV != 0)
				y = (float)h / (divV + 1);
			else if (h == 0)
				y = 0;
			else
				y = a;
			float z = sin(aux) * r;
			vertices[i] = x;
			vertices[i + 1] = y;
			vertices[i + 2] = z;
			aux += div;
		}
	}

	//Construcción triangulos
	//Parte inferior.
	int triangulo = 0; //Iterador que representa la esquina inferior del triangulo que estoy haciendo
	int esqInf = 0;
	for (int h = 0; h <= divV; h++) //por cada altura...
	{
		for (int i = esqInf*3; i < (esqInf+divU)*3; i+=3)
		{
			if (triangulo == divU - 1+(h*divU))
			{
				triangulos[i] = esqInf;
				triangulos[i + 1] = i / 3;
				triangulos[i + 2] = triangulo + divU;

			}
			else
			{

				triangulos[i] = triangulo+divU;
				triangulos[i + 1] = triangulo+1;
				triangulos[i + 2] = triangulo;
			}
			triangulo++;
		}
		esqInf+=divU;
	}
	//i=60
	//Parte superior.
	triangulo = 0; //Iterador que representa el triángulo que estoy haciendo.
	esqInf = 0;
	for (int h = 0; h <= divV; h++) //por cada altura...
	{
		for (int i = esqInf*3+((num_triangulos/2)*3); i < ((esqInf + divU) * 3 )+ ((num_triangulos / 2)*3); i += 3)
		{
			if (triangulo == divU - 1 + (h * divU))
			{
				triangulos[i] = esqInf + divU;
				triangulos[i + 1] = esqInf;
				triangulos[i + 2] = triangulo + divU;

			}
			else
			{
				triangulos[i] = triangulo + divU + 1;
				triangulos[i + 1] = triangulo + 1;
				triangulos[i + 2] = triangulo + divU;

				/*triangulos[i] = triangulo + divU;
				triangulos[i + 1] = triangulo+1;
				triangulos[i + 2] = triangulo + 1 + divU;*/
			}
			triangulo++;
		}
		esqInf += divU;
	}

	/* Apartado C: Añadir el vector de normales */
	//Cálculo normales.
	for (int h = 0; h <= divV + 1; h++) //por cada altura...
	{
		float aux = 0;
		for (int i = h * divU * 3; i < h * divU * 3 + (divU * 3); i += 3)
		{
			float x = cos(aux);
			float y;
			if (divV != 0)
				y = (float)h / (divV + 1);
			else if (h == 0)
				y = 0;
			else
				y = a;
			float z = sin(aux);
			normales[i] = x;
			normales[i + 1] = 0;
			normales[i + 2] = z;
			aux += div;
		}
	}

}

igvCilindro::~igvCilindro()
{
}

void igvCilindro::visualizar()
{
	glShadeModel(GL_SMOOTH);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normales);

	glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void igvCilindro::visualizar(bool n, bool g)
{
	glShadeModel(GL_FLAT);
	if (n)
	{
		if (g)
			glShadeModel(GL_SMOOTH);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, normales);

		glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	else
	{
		if (g)
			glShadeModel(GL_SMOOTH);
		glEnableClientState(GL_VERTEX_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);

		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

