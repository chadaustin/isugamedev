// Levi VanOort -- lvanoort@aol.com 2/4/2002

#include <gl/glut.h>
#include <stdlib.h>
#include "MyObject.h"
#include "PowerupObject.h"
#include <time.h>

extern GLuint powerup[1];
extern int dt;
extern bool drawtextures;


PowerupObject::PowerupObject()
{
  
	GameX = 0.0;
	GameY = 0.0;
	SizeX = 20.0;
	SizeY = 20.0;
	VelocityX = 0.0;
	VelocityY = -0.1;

	TheObjectName = POWERUP;

	srand( (unsigned)time( NULL ) );
	int TheRand = rand()%2;

	switch(TheRand)
	{
	case 0:
		CurrentState = STICKYPADDLE;
		break;
	case 1:
		CurrentState = SHOOTPADDLE;
		break;
	}
}

PowerupObject::~PowerupObject()
{
	//No memory allocated so nothing to give back
}

void PowerupObject::CollisionResponse(MyObject* CollisionObject)
{
	ObjectName CollisionName = CollisionObject->GetObjectName();

	if(CollisionName == PADDLE)
	{
		CollisionObject->SetState(CurrentState);
		CurrentState = DEAD;
	}
	if(CollisionName == BALL)
		CurrentState = DEAD;

}

void PowerupObject::Update()
{
	GameY = GameY + VelocityY*dt;

	if(GameY < -SizeY)
		CurrentState = DEAD;
}

void PowerupObject::Draw()
{
	if(drawtextures)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, powerup[0]);
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
		glColor3f(1.0, 0.0, 1.0);
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
void PowerupObject::SetGameCoordinates(float x, float y)
{ GameX = x; GameY = y;}

void PowerupObject::SetSize(float x, float y)
{ SizeX = x; SizeY = y;}

void PowerupObject::SetState(State TheState)
{ CurrentState = TheState;}

void PowerupObject::SetVelocityX(float Vel)
{ VelocityX = Vel;}

void PowerupObject::SetVelocityY(float Vel)
{ VelocityY = Vel;}

void PowerupObject::GetGameCoordinates(float& x, float& y)
{ x = GameX; y = GameY;}

void PowerupObject::GetSize(float& x, float& y)
{ x = SizeX; y = SizeY;}

void PowerupObject::GetState(State& TheState)
{ TheState = CurrentState;}

void PowerupObject::GetVelocityX(float& Vel)
{ Vel = VelocityX;}

void PowerupObject::GetVelocityY(float& Vel)
{ Vel = VelocityY;}

ObjectName PowerupObject::GetObjectName()
{ return TheObjectName;}
