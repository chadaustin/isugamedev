// Terrain.h: interface for the Terrain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TERRAIN_H__A162D271_AD16_11D5_9939_0001023C9B90__INCLUDED_)
#define AFX_TERRAIN_H__A162D271_AD16_11D5_9939_0001023C9B90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

#include "generic.h"

class Terrain  : public generic
{
public:
	Terrain();
	~Terrain();


	void draw();
	void setx(GLfloat x);
	void setz(GLfloat z);

	GLuint *terrainTex;

	GLfloat getX() {return xPos;};
	GLfloat getZ() {return zPos;};
	GLfloat getExtents() {return extents;};

private:

	GLfloat xsize;
	GLfloat zsize;
	GLfloat xPos;
	GLfloat zPos;
	GLfloat extents;

};

#endif // !defined(AFX_TERRAIN_H__A162D271_AD16_11D5_9939_0001023C9B90__INCLUDED_)
