//////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//				lvanoort@aol.com 
//
// LogObject.cpp
// 4-5-2002
//////////////////////////////////////////////////////
#include <stdlib.h>
#include <SDL_opengl.h>
#include "LogObject.h"

extern int WindowSizeX, WindowSizeY;


LogObject::LogObject()
{ 
	Move = false;
	MoveX = 0;
	MoveY = 0;
	Name = LOG;
	VelocityX = 0;
	VelocityY = 0;
	ObjectState = ALIVE;
}


LogObject::~LogObject()
{ 

}

void LogObject::SetGameCoordinates(float x, float y)
{
	GameX=x;
	GameY=y;
}



void LogObject::SetSize(float x, float y)
{
	ObjectSizeX = x;
	ObjectSizeY = y;
}



void LogObject::SetState(State TheState)
{
	ObjectState = TheState;
}


void LogObject::SetVelocityY(float Vel)
{
	VelocityY = Vel;
}



void LogObject::SetVelocityX(float Vel)
{
	VelocityX = Vel;
}


void LogObject::GetGameCoordinates(float& x, float& y)
{
	x = GameX;
	y = GameY;
}


void LogObject::GetSize(float& x, float& y)
{
	x = ObjectSizeX;
	y = ObjectSizeY;
}


void LogObject::GetState(State& TheState)
{
	TheState = ObjectState;
}



void LogObject::GetVelocityX(float& Vel)
{
	Vel = VelocityX;
}


void LogObject::GetVelocityY(float& Vel)
{
	Vel = VelocityX;
}

ObjectName LogObject::GetObjectName()
{
	return Name;
}


void LogObject::CollisionResponse(MyObject* CollisionObject)
{
	ObjectName CollisionName;
	CollisionName = CollisionObject->GetObjectName();


	switch(CollisionName)
	{
	case FROG: 
		break;
	}

}

bool LogObject::Moved(float& x, float& y)
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


void LogObject::Update(int dt)
{	

  if (GameX > WindowSizeX && VelocityX > 0)
	  MoveX = (WindowSizeX+ObjectSizeX)* -1;

  else if(GameX < -ObjectSizeX && VelocityX < 0)
	  MoveX = WindowSizeX+ObjectSizeX;

  else
	MoveX = MoveX + VelocityX;

  Move = true;

}

		 

void LogObject::Draw()
{ 

	switch(ObjectState)
	{
	case ALIVE:
		glColor3f(0.3,0.5,0.8);
		break;

	case COLLISION:
		glColor3f(0.0,1.0,0.0);
		break;
	}

	glRectf(float(GameX),float(GameY), float(GameX+ObjectSizeX), float(GameY+ObjectSizeY)); 
}

