//////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//				lvanoort@aol.com 
//
// LilypadObject.cpp
// 4-5-2002
//////////////////////////////////////////////////////

#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include "LilypadObject.h"

using namespace std;

extern int WindowSizeX, WindowSizeY;

LilypadObject::LilypadObject()
{ 
	Move = false;
	MoveX = 0;
	MoveY = 0;
	Name = LILY;
	VelocityX = 0;
	VelocityY = 0;
	ObjectState = ALIVE;
}


LilypadObject::~LilypadObject()
{ 

}


void LilypadObject::SetGameCoordinates(float x, float y)
{
	GameX=x;
	GameY=y;
}


void LilypadObject::SetSize(float x, float y)
{
	ObjectSizeX = x;
	ObjectSizeY = y;
}


void LilypadObject::SetState(State TheState)
{
	ObjectState = TheState;
}


void LilypadObject::SetVelocityY(float Vel)
{
	VelocityY = Vel;
}


void LilypadObject::SetVelocityX(float Vel)
{
	VelocityX = Vel;
}


void LilypadObject::GetGameCoordinates(float& x, float& y)
{
	x = GameX;
	y = GameY;
}


void LilypadObject::GetSize(float& x, float& y)
{
	x = ObjectSizeX;
	y = ObjectSizeY;
}


void LilypadObject::GetState(State& TheState)
{
	TheState = ObjectState;
}


void LilypadObject::GetVelocityX(float& Vel)
{
	Vel = VelocityX;
}


void LilypadObject::GetVelocityY(float& Vel)
{
	Vel = VelocityX;
}


ObjectName LilypadObject::GetObjectName()
{
	return Name;
}


void LilypadObject::CollisionResponse(MyObject* CollisionObject)
{
	ObjectName CollisionName;
	CollisionName = CollisionObject->GetObjectName();

	switch(CollisionName)
	{
	case FROG: 
		ObjectState = COLLISION;
		break;
	}
}

bool LilypadObject::Moved(float& x, float& y)
{
	return false;
}

void LilypadObject::Update()
{	
	NULL;
}

		 
void LilypadObject::Draw()
{ 
	switch(ObjectState)
	{
	case ALIVE:
		glColor3f(0.0,0.0,1.0);
		break;

	case COLLISION:
		glColor3f(1.0,1.0,1.0);
		break;
	}
	glRectf(float(GameX),float(GameY), float(GameX+ObjectSizeX), float(GameY+ObjectSizeY)); 
}

