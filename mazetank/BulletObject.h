/////////////////////////////////////
// Copyright Levi VanOort 4-21-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// BulletObject.h
/////////////////////////////////////

#ifndef __BULLETOBJECT_H
#define __BULLETOBJECT_H

#include <GL/glut.h>
#include "GraphicsObject.h"
#include "GameObject.h"

class BulletObject : public GameObject
{
public:
	BulletObject();

	~BulletObject();

	void Init();
	void Update();
	void Draw();
	void GetGraphicsPointer(GraphicsObject*& TheGraphics);

private:
	

};
#endif

