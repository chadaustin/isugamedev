#include <stdlib.h>
#include <GL/glut.h>
#include <iostream.h>
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

void AutoObject::SetGameCoordinates(int x, int y)
{
	GameX=x;
	GameY=y;
}

void AutoObject::SetSize(int x, int y)
{
	ObjectSizeX = x;
	ObjectSizeY = y;
}

void AutoObject::SetState(State TheState)
{
	ObjectState = TheState;
}

void AutoObject::SetVelocityY(int Vel)
{
	VelocityY = Vel;
}

void AutoObject::SetVelocityX(int Vel)
{
	VelocityX = Vel;
}

void AutoObject::GetGameCoordinates(int& x, int& y)
{
	x = GameX;
	y = GameY;
}

void AutoObject::GetSize(int& x, int& y)
{
	x = ObjectSizeX;
	y = ObjectSizeY;
}

void AutoObject::GetState(State& TheState)
{
	TheState = ObjectState;
}

void AutoObject::GetVelocityX(int& Vel)
{
	Vel = VelocityX;
}

void AutoObject::GetVelocityY(int& Vel)
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

bool AutoObject::Moved(int& x, int& y)
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
