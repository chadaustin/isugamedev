/////////////////////////////////////
// Copyright Levi VanOort 4-21-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// TankGraphics.h
/////////////////////////////////////
#ifndef __TANKGRAPHICS_H__
#define __TANKGRAPHICS_H__

#include "GraphicsObject.h"
#include "glm.h"
#include <GL/glut.h>

class TankGraphics:public GraphicsObject
{
public:
	TankGraphics();

	~TankGraphics();

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
