// tank.h: interface for the tank class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TANK_H__D2278140_0245_4D16_92AD_CD3101D318E3__INCLUDED_)
#define AFX_TANK_H__D2278140_0245_4D16_92AD_CD3101D318E3__INCLUDED_

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


class Tank  : public generic
{
public:
	Tank(GLfloat x, GLfloat y, GLfloat z, GLfloat angleIn);
	~Tank();

	//void initialize( GLfloat angle, GLfloat x, Glfloat y, Glfloat z);
	void draw();
	void move(GLint dir);
	void turn(GLint dir);
	void deathDraw();

	GLfloat getX() { return xPos; };
	GLfloat getY() { return yPos; };
	GLfloat getZ() { return zPos; };
	GLfloat getAngle() { return angle; };

	GLuint *treadTex;

private:

	GLfloat angle;
	GLfloat xPos;
	GLfloat yPos;
	GLfloat zPos;
	GLfloat speed;
	GLfloat rotateSpeed;

	GLint shotsLeft;
	bool alive;
	GLint hitPoints;

};


#endif // !defined(AFX_TANK_H__D2278140_0245_4D16_92AD_CD3101D318E3__INCLUDED_)
