/////////////////////////////////////
// Copyright Levi VanOort 5-3-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// FloorObject.h
/////////////////////////////////////

#ifndef __FLOOROBJECT_H
#define __FLOOROBJECT_H

#include <GL/glut.h>
#include "GraphicsObject.h"
#include "FloorGraphics.h"
#include "GameObject.h"

class FloorObject : public GameObject
{
public:
	FloorObject()
	{
		TheFloor = new FloorGraphics;

		TheFloor->Init();

		this->SetCurrentObjectType(FLOOR);
		this->SetVelocity(0.0);
		this->SetObjectSphere(0.0);
	}

	~FloorObject()
	{
		delete TheFloor;
	}

	void Init()
	{
	}

	void Update()
	{
	}

	void GetGraphicsPointer(GraphicsObject*& TheGraphics)
	{
		TheGraphics = TheFloor;
	}

	void Draw()
	{
		TheFloor->Draw();
	}
private:
	
	GraphicsObject* TheFloor;

};
#endif

