/////////////////////////////////////
// Copyright Levi VanOort 4-21-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// TruckObject.h
/////////////////////////////////////
#ifndef __TANKOBJECT_H__
#define __TANKOBJECT_H__

#include <GL/glut.h>
#include "GraphicsObject.h"
#include "TankGraphics.h"
#include "TurretGraphics.h"
#include "GameObject.h"

class TankObject : public GameObject
{
public:
	TankObject();
	~TankObject();

	void Init();
	void Draw();
	void GetGraphicsPointer(GraphicsObject*& TheGraphics);

private:
	
	GraphicsObject* Body;
	GraphicsObject* Turret;

	float OldAngle;

};
#endif
