#include "igvQuad.h"


igvQuad::igvQuad(int dx, int dz, float tx, float tz): div_x(dx), div_z(dz), tam_x(tx), tam_z(tz)
{

}

igvQuad::~igvQuad()
{
}

void igvQuad::visualizar()
{
	float divisionX = tam_x / div_x;
	float divisionZ = tam_z / div_z;
	float x, z, s, t, ss, tt;
	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
	for (int i = 0; i < div_x; i++)
	{
		for (int j = 0; j < div_z; j++)
		{
			x = i * divisionX;
			z = j * divisionZ;
			//ir indicando coordenada s y t conforme se va construyendo la malla.
			s = x / tam_x;
			t = z / tam_z;
			ss = (x + divisionX) / tam_x;
			tt = (z + divisionX) / tam_z;

			glTexCoord2f(s, t);
			glVertex3f(x, 0.0, z);
			glTexCoord2f(s, tt);
			glVertex3f(x, 0.0, (z)+divisionZ);
			glTexCoord2f(ss, tt);
			glVertex3f((x)+divisionX, 0.0, (z)+divisionZ);
			glTexCoord2f(s, tt);
			glVertex3f((x)+divisionX, 0.0, z);
		}
	}
	glEnd();
}