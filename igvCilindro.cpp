#include "igvCilindro.h"


igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV): divU(divU), divV(divV)
{
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

	coordTex = new float[num_vertices*2];
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
				y = ((float)h / (float)(divV))*a;
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
	//Para generar la coordenada de textura, me baso en el triángulo en el que estoy y el número de divisiones.
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
			}
			triangulo++;
		}
		esqInf += divU;
	}

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
	//Generar texcoords:
	int triangulo = 0;
	for (int h = 0; h <= divV; h++) //por cada altura...
	{
		for (int triangulo = 0; triangulo < divU; triangulo++)
		{
			float t = (float)h / (float)divV;
			if (triangulo == divU - 1 + (h * divU))
				glTexCoord2d(1.0, t);
			else
			{
				float s = (float)triangulo / (float)divU;
				glTexCoord2d((triangulo) / divU, (h) / divV);
			}

		}
	}
	glShadeModel(GL_FLAT);
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
	//Generar texcoords:
	int k = 0;
	for (int h = 0; h < divV; h++) //por cada altura...
	{
		for (int triangulo = 0; triangulo < divU; triangulo++)
		{
			if (triangulo == divU - 1 + (h * divU))
			{
				float s = (float)h / divV;
				coordTex[k] = 1;
				coordTex[k+1] = s;
				//glTexCoord2d(1, s);
			}

			else
			{
				float s = (float)triangulo / (float)divU;
				float t = (float)h / (float)divV;
				coordTex[k] = s;
				coordTex[k + 1] = t;
			}
		}
		k += 2;
	}
	glShadeModel(GL_FLAT);
	if (g)
		glShadeModel(GL_SMOOTH);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	if (n)
	{


		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, normales);

		glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);


		glDisableClientState(GL_NORMAL_ARRAY);
	}
	else
	{
		
		glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);	
		glTexCoordPointer(2, GL_FLOAT, 0, coordTex);
	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

