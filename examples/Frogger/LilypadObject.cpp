#include <stdlib.h>
#include <gl/glut.h>
#include <iostream.h>
#include "LilypadObject.h"

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

void LilypadObject::SetGameCoordinates(int x, int y)
{
	GameX=x;
	GameY=y;
}

void LilypadObject::SetSize(int x, int y)
{
	ObjectSizeX = x;
	ObjectSizeY = y;
}

void LilypadObject::SetState(State TheState)
{
	ObjectState = TheState;
}

void LilypadObject::SetVelocityY(int Vel)
{
	VelocityY = Vel;
}

void LilypadObject::SetVelocityX(int Vel)
{
	VelocityX = Vel;
}

void LilypadObject::GetGameCoordinates(int& x, int& y)
{
	x = GameX;
	y = GameY;
}

void LilypadObject::GetSize(int& x, int& y)
{
	x = ObjectSizeX;
	y = ObjectSizeY;
}

void LilypadObject::GetState(State& TheState)
{
	TheState = ObjectState;
}

void LilypadObject::GetVelocityX(int& Vel)
{
	Vel = VelocityX;
}

void LilypadObject::GetVelocityY(int& Vel)
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

bool LilypadObject::Moved(int& x, int& y)
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
