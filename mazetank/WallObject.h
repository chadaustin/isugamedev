/////////////////////////////////////
// Copyright Levi VanOort 4-21-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// WallObject.h
/////////////////////////////////////
#ifndef __WALLOBJECT_H__
#define __WALLOBJECT_H__

#include <GL/glut.h>
#include "GraphicsObject.h"
#include "GameObject.h"

class WallObject : public GameObject
{
public:
	WallObject();

	~WallObject();

	void Init();
	void Update();
	void Draw();
	void GetGraphicsPointer(GraphicsObject*& TheGraphics);

private:
	GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
};
#endif
