#include <stdlib.h>
#include <GL/glut.h>
#include <iostream.h>
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

void LogObject::SetGameCoordinates(int x, int y)
{
	GameX=x;
	GameY=y;
}

void LogObject::SetSize(int x, int y)
{
	ObjectSizeX = x;
	ObjectSizeY = y;
}

void LogObject::SetState(State TheState)
{
	ObjectState = TheState;
}

void LogObject::SetVelocityY(int Vel)
{
	VelocityY = Vel;
}

void LogObject::SetVelocityX(int Vel)
{
	VelocityX = Vel;
}

void LogObject::GetGameCoordinates(int& x, int& y)
{
	x = GameX;
	y = GameY;
}

void LogObject::GetSize(int& x, int& y)
{
	x = ObjectSizeX;
	y = ObjectSizeY;
}

void LogObject::GetState(State& TheState)
{
	TheState = ObjectState;
}

void LogObject::GetVelocityX(int& Vel)
{
	Vel = VelocityX;
}

void LogObject::GetVelocityY(int& Vel)
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
	case FROG: break;
	}

}

bool LogObject::Moved(int& x, int& y)
{
	bool temp = Move;
	int tempX = MoveX;
	int tempY = MoveY;

	Move = false;
	MoveX = 0;
	MoveY = 0;

	x = tempX;
	y = tempY;
	return temp;
}

void LogObject::Update()
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
