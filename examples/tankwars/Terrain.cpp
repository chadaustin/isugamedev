// Terrain.cpp: implementation of the Terrain class.
//
//////////////////////////////////////////////////////////////////////

#include "Terrain.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Terrain::Terrain()
{
	xsize = 5.0f;
	zsize = 5.0f;
}

Terrain::~Terrain()
{

}

void Terrain::draw()
{
	glTranslatef(-3.0f, 0.0f, -11.0f*zsize);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, terrainTex[0]);
	for (int x = 0; x<13; x++)
	{
		glTranslatef(xsize, 0.0f, 0.0f);
		for (int z = 0; z<13; z++)
		{
			glTranslatef(0.0f, 0.0f, zsize);
			
			glBegin(GL_QUADS); // coordinates for the square
				//glNormal3f(0.0f, 1.0f, 0.0f);
				glTexCoord2f(0.02f, 0.02f);	glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(.98f, 0.02f);	glVertex3f(xsize, 0.0f, 0.0f);
				glTexCoord2f(0.98f, 0.98f);	glVertex3f(xsize, 0.0f, zsize);
				glTexCoord2f(0.02f, 0.98f);	glVertex3f(0.0f, 0.0f, zsize);
			glEnd();
		}
		glTranslatef(0.0f, 0.0f, -13*zsize);
	}

	return;

}

void Terrain::setx(GLfloat x)
{
	xsize = x;
	return;
}

void Terrain::setz(GLfloat z)
{
	zsize = z;
	return;
}