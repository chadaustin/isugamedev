//////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//				lvanoort@aol.com 
//
// AutoObject.cpp
// 4-5-2002
//////////////////////////////////////////////////////

#include <stdlib.h>
#include <GL/glut.h>
#include "AutoObject.h"

extern int WindowSizeX, WindowSizeY;

AutoObject::AutoObject()
{ 
	Move = false;
	MoveX = 0;
	MoveY = 0;
	Name = AUTO;
	VelocityX = 0;
	VelocityY = 0;
	ObjectState = ALIVE;
}

AutoObject::~AutoObject()
{ 

}

void AutoObject::SetGameCoordinates(float x, float y)
{
	GameX=x;
	GameY=y;
}

void AutoObject::SetSize(float x, float y)
{
	ObjectSizeX = x;
	ObjectSizeY = y;
}


void AutoObject::SetState(State TheState)
{
	ObjectState = TheState;
}


void AutoObject::SetVelocityY(float Vel)
{
	VelocityY = Vel;
}

void AutoObject::SetVelocityX(float Vel)
{
	VelocityX = Vel;
}

void AutoObject::GetGameCoordinates(float& x, float& y)
{
	x = GameX;
	y = GameY;
}


void AutoObject::GetSize(float& x, float& y)
{
	x = ObjectSizeX;
	y = ObjectSizeY;
}

void AutoObject::GetState(State& TheState)
{
	TheState = ObjectState;
}



void AutoObject::GetVelocityX(float& Vel)
{
	Vel = VelocityX;
}


void AutoObject::GetVelocityY(float& Vel)
{
	Vel = VelocityX;
}


ObjectName AutoObject::GetObjectName()
{
	return Name;
}


void AutoObject::CollisionResponse(MyObject* CollisionObject)
{
	SetState(COLLISION);
	VelocityX = 0;
}


bool AutoObject::Moved(float& x, float& y)
{
	bool temp = Move;
	float tempX = MoveX;
	float tempY = MoveY;


	Move = false;
	MoveX = 0;
	MoveY = 0;


	x = tempX;
	y = tempY;
	return temp;
}


void AutoObject::Update()
{	
  if (GameX > WindowSizeX && VelocityX > 0)
	  MoveX = (WindowSizeX+ObjectSizeX)* -1;

  else if(GameX < -ObjectSizeX && VelocityX < 0)
	  MoveX = WindowSizeX+ObjectSizeX;

  else
	MoveX = MoveX + VelocityX;

  Move = true;
}

		 
void AutoObject::Draw()
{ 

	switch(ObjectState)
	{
	case ALIVE:
		glColor3f(1.0,0.0,0.0);
		break;

	case COLLISION:
		glColor3f(0.0,1.0,0.0);
		break;
	}

	glRectf(float(GameX),float(GameY), float(GameX+ObjectSizeX), float(GameY+ObjectSizeY)); 
}

