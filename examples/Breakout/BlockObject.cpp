// Levi VanOort -- lvanoort@aol.com 2/4/2002

#include <GL/glut.h>
#include <stdlib.h>
#include "MyObject.h"
#include "BlockObject.h"

// External Globals/////
extern GLuint block[1];
extern int NumberOfBlocks;
extern bool drawtextures;

////////////////////////

BlockObject::BlockObject()
{
	GameX = 0.0;
	GameY = 0.0;
	SizeX = 79.0;
	SizeY = 20.0;
	VelocityX = 0.0;
	VelocityY = 0.0;

	CurrentState = NORMAL;
	TheObjectName = BLOCK;

	NumberOfBlocks++;

}

BlockObject::~BlockObject()
{
	//No memory allocated so nothing to give back
}

void BlockObject::CollisionResponse(MyObject* CollisionObject)
{
	ObjectName CollisionName = CollisionObject->GetObjectName();

	if(CollisionName == BALL || CollisionName == BULLET)
		CurrentState = DEAD;
}

void BlockObject::Update()
{
	NULL;
}

void BlockObject::Draw()
{
	if(drawtextures)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, block[0]);
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
		glColor3f(1.0, 1.0, 0.0);
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
void BlockObject::SetGameCoordinates(float x, float y)
{ GameX = x; GameY = y;}

void BlockObject::SetSize(float x, float y)
{ SizeX = x; SizeY = y;}

void BlockObject::SetState(State TheState)
{ CurrentState = TheState;}

void BlockObject::SetVelocityX(float Vel)
{ VelocityX = Vel;}

void BlockObject::SetVelocityY(float Vel)
{ VelocityY = Vel;}

void BlockObject::GetGameCoordinates(float& x, float& y)
{ x = GameX; y = GameY;}

void BlockObject::GetSize(float& x, float& y)
{ x = SizeX; y = SizeY;}

void BlockObject::GetState(State& TheState)
{ TheState = CurrentState;}

void BlockObject::GetVelocityX(float& Vel)
{ Vel = VelocityX;}

void BlockObject::GetVelocityY(float& Vel)
{ Vel = VelocityY;}

ObjectName BlockObject::GetObjectName()
{ return TheObjectName;}
