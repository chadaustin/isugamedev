//////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//				lvanoort@aol.com 
//
// FrogObject.cpp
// 4-5-2002
//////////////////////////////////////////////////////

#include <stdlib.h>
#include <GL/glut.h>
#include <iostream.h>
#include "FrogObject.h"

extern enum Movement{NONE = 0, LEFT, RIGHT, UP, DOWN} FrogMove;
extern int LaneSize;


float MoveDistanceX = 20;
float MoveDistanceY = LaneSize;


FrogObject::FrogObject()
{ 
	Move = false;
	MoveX = 0;
	MoveY = 0;
	Name = FROG;
	VelocityX = 0;
	VelocityY = 0;
	ObjectState = ALIVE;
}


FrogObject::~FrogObject()
{ 

}


void FrogObject::SetGameCoordinates(float x, float y)
{
	GameX=x;
	GameY=y;
}



void FrogObject::SetSize(float x, float y)
{
	ObjectSizeX = x;
	ObjectSizeY = y;
}


void FrogObject::SetState(State TheState)
{
	ObjectState = TheState;
}


void FrogObject::SetVelocityX(float Vel)
{
	VelocityX = Vel;
}


void FrogObject::SetVelocityY(float Vel)
{
	VelocityY = Vel;
}


void FrogObject::GetGameCoordinates(float& x, float& y)
{
	x = GameX;
	y = GameY;
}


void FrogObject::GetSize(float& x, float& y)
{
	x = ObjectSizeX;
	y = ObjectSizeY;
}



void FrogObject::GetState(State& TheState)

{

	TheState = ObjectState;

}



void FrogObject::GetVelocityX(float& Vel)
{
	Vel = VelocityX;
}


void FrogObject::GetVelocityY(float& Vel)
{
	Vel = VelocityY;
}


ObjectName FrogObject::GetObjectName()
{
	return Name;
}


void FrogObject::CollisionResponse(MyObject* CollisionObject)
{
	ObjectName CollisionName;
	CollisionName = CollisionObject->GetObjectName();

	switch(CollisionName)
	{
	case LOG:	
		CollisionObject->GetVelocityX(VelocityX);
		ObjectState = LOGRIDING;
		break;

	default:
		ObjectState = ALIVE;
		VelocityX = 0;
	}
}


bool FrogObject::Moved(float& x, float& y)
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


void FrogObject::Update()
{	
	switch (FrogMove)
	{
	case RIGHT: MoveX = MoveX + MoveDistanceX;
				Move = true;
				FrogMove = NONE;
				break;

	case LEFT : MoveX = MoveX - MoveDistanceX;
				Move = true;
				FrogMove = NONE;
				break;

	case UP :	MoveY = MoveY + MoveDistanceY;
				Move = true;
				FrogMove = NONE;
				break;

	case DOWN:	MoveY = MoveY - MoveDistanceY;
				Move = true;
				FrogMove = NONE;
				break;

	default :
				break;
	}



	switch (ObjectState)
	{
	case LOGRIDING:
		MoveX = MoveX + VelocityX;
		Move = true;
		break;
	}

}


void FrogObject::Draw()
{ 

	switch(ObjectState)
	{
	case ALIVE:
		glColor3f(1.0,0.0,0.0);
		break;

	case COLLISION:
		glColor3f(0.0,0.0,1.0);
		break;

	case LOGRIDING:
		glColor3f(1.0,0.0,0.0);
		break;
	}
	glRectf(float(GameX),float(GameY), float(GameX+ObjectSizeX), float(GameY+ObjectSizeY)); 
}

