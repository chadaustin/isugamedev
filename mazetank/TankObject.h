/////////////////////////////////////
// Copyright Levi VanOort 4-21-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// TruckObject.h
/////////////////////////////////////
#ifndef __TANKOBJECT_H__
#define __TANKOBJECT_H__

#include <gl/glut.h>
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
	void Update();
	void Draw();

private:
	
	GraphicsObject* Body;
   GraphicsObject* Turret;

};
#endif
