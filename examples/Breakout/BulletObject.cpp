// Levi VanOort -- lvanoort@aol.com 2/4/2002

#include <GL/glut.h>
#include <stdlib.h>
#include "MyObject.h"
#include "BulletObject.h"

extern GLuint bullet[1];
extern int dt;
extern int WindowSizeY;
extern bool drawtextures;


BulletObject::BulletObject()
{
  
	GameX = 0.0;
	GameY = 0.0;
	SizeX = 10.0;
	SizeY = 28.0;
	VelocityX = 0.0;
	VelocityY = -0.1;
	TheObjectName = BULLET;
}

BulletObject::~BulletObject()
{
	//No memory allocated so nothing to give back
}

void BulletObject::CollisionResponse(MyObject* CollisionObject)
{
	ObjectName CollisionName = CollisionObject->GetObjectName();

	if(CollisionName == BLOCK || CollisionName == WALL)
		CurrentState = DEAD;

}

void BulletObject::Update()
{
	GameY = GameY + VelocityY*dt;

	if(GameY > WindowSizeY)
		CurrentState = DEAD;
}

void BulletObject::Draw()
{
	if(drawtextures)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, bullet[0]);
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
		glColor3f(0.0, 1.0, 0.0);
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
void BulletObject::SetGameCoordinates(float x, float y)
{ GameX = x; GameY = y;}

void BulletObject::SetSize(float x, float y)
{ SizeX = x; SizeY = y;}

void BulletObject::SetState(State TheState)
{ CurrentState = TheState;}

void BulletObject::SetVelocityX(float Vel)
{ VelocityX = Vel;}

void BulletObject::SetVelocityY(float Vel)
{ VelocityY = Vel;}

void BulletObject::GetGameCoordinates(float& x, float& y)
{ x = GameX; y = GameY;}

void BulletObject::GetSize(float& x, float& y)
{ x = SizeX; y = SizeY;}

void BulletObject::GetState(State& TheState)
{ TheState = CurrentState;}

void BulletObject::GetVelocityX(float& Vel)
{ Vel = VelocityX;}

void BulletObject::GetVelocityY(float& Vel)
{ Vel = VelocityY;}

ObjectName BulletObject::GetObjectName()
{ return TheObjectName;}
