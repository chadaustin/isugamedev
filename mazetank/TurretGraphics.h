/////////////////////////////////////
// Copyright Levi VanOort 4-21-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// TankGraphics.h
/////////////////////////////////////

#ifndef __TURRETGRAPHICS_H__
#define __TURRETGRAPHICS_H__

#include "GraphicsObject.h"
#include "glm.h"
#include <gl/glut.h>

class TurretGraphics:public GraphicsObject
{
public:
	TurretGraphics();

	~TurretGraphics();

	void Draw();

	void Init();

private:

	GLuint     model_list;		
	GLMmodel*  model;
	GLfloat    smoothing_angle;

    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;

};
#endif