// Weapon.h: interface for the Weapon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEAPON_H__5A7CA2E0_AD18_11D5_98FF_0001023C9B87__INCLUDED_)
#define AFX_WEAPON_H__5A7CA2E0_AD18_11D5_98FF_0001023C9B87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

#include "Tank.h"
#include "generic.h"

class Weapon : public generic
{
public:
	Weapon();
	virtual ~Weapon();

	virtual void draw();

	void move(GLint dir);
	void initialize(GLfloat x, GLfloat z, GLfloat theta);

	Weapon *next;
	GLuint *weaponTex;

protected:

	GLfloat xPos;
	GLfloat yPos;
	GLfloat zPos;
	GLfloat speed;
	GLfloat angle;

};

#endif // !defined(AFX_WEAPON_H__5A7CA2E0_AD18_11D5_98FF_0001023C9B87__INCLUDED_)
