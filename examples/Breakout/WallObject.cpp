// Levi VanOort -- lvanoort@aol.com 2/4/2002

#include <gl/glut.h>
#include <stdlib.h>
#include "MyObject.h"
#include "WallObject.h"

extern GLuint wall[1];
extern bool drawtextures;

WallObject::WallObject()
{
	GameX = 0.0;
	GameY = 0.0;
	SizeX = 79.0;
	SizeY = 20.0;
	VelocityX = 0.0;
	VelocityY = 0.0;

	CurrentState = NORMAL;
	TheObjectName = WALL;

}

WallObject::~WallObject()
{
	//No memory allocated so nothing to give back
}

void WallObject::CollisionResponse(MyObject* CollisionObject)
{
	ObjectName CollisionName = CollisionObject->GetObjectName();

}

void WallObject::Update()
{
	NULL;
}

void WallObject::Draw()
{
	if(drawtextures)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, wall[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0); glVertex2f(GameX, GameY);
			glTexCoord2f(0.0,1.0); glVertex2f(GameX, GameY+SizeY);
			glTexCoord2f(1.0,1.0); glVertex2f(GameX+SizeX, GameY+SizeY);
			glTexCoord2f(1.0,0.0); glVertex2f(GameX+SizeX, GameY);
		glEnd();
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.0, 1.0, 1.0);
		glBegin(GL_QUADS);
			glVertex2f(GameX, GameY);
			glVertex2f(GameX, GameY+SizeY);
			glVertex2f(GameX+SizeX, GameY+SizeY);
			glVertex2f(GameX+SizeX, GameY);
		glEnd();
	}

}
/////////////////////////////////////////////////////////
// Functions below will not change for different objects
/////////////////////////////////////////////////////////
void WallObject::SetGameCoordinates(float x, float y)
{ GameX = x; GameY = y;}

void WallObject::SetSize(float x, float y)
{ SizeX = x; SizeY = y;}

void WallObject::SetState(State TheState)
{ CurrentState = TheState;}

void WallObject::SetVelocityX(float Vel)
{ VelocityX = Vel;}

void WallObject::SetVelocityY(float Vel)
{ VelocityY = Vel;}

void WallObject::GetGameCoordinates(float& x, float& y)
{ x = GameX; y = GameY;}

void WallObject::GetSize(float& x, float& y)
{ x = SizeX; y = SizeY;}

void WallObject::GetState(State& TheState)
{ TheState = CurrentState;}

void WallObject::GetVelocityX(float& Vel)
{ Vel = VelocityX;}

void WallObject::GetVelocityY(float& Vel)
{ Vel = VelocityY;}

ObjectName WallObject::GetObjectName()
{ return TheObjectName;}
