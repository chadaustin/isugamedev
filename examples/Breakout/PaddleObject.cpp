// Levi VanOort -- lvanoort@aol.com 2/4/2002

#include <GL/glut.h>
#include <stdlib.h>
#include "MyObject.h"
#include "PaddleObject.h"


extern int MouseX;
extern int MouseY;
extern int WindowSizeX;
extern GLuint paddle[2];
extern bool drawtextures;


PaddleObject::PaddleObject()
{
	GameX = 0.0;
	GameY = 0.0;
	SizeX = 50.0;
	SizeY = 10.0;
	VelocityX = 0.0;
	VelocityY = 0.0;

	CurrentState = NORMAL;
	TheObjectName = PADDLE;
	CurrentTexture = 0;

	NumTextures = 2;
	Blinktime = 500;
	ShootPaddletime = 5000;
	StickyPaddletime = 10000;
}

PaddleObject::~PaddleObject()
{
	//No memory allocated so nothing to give back
}

void PaddleObject::CollisionResponse(MyObject* CollisionObject)
{
	ObjectName CollisionName = CollisionObject->GetObjectName();

	if(CurrentState == STICKYPADDLE && CollisionName == BALL)
	{
		CollisionObject->SetState(PADDLERIDING);
	}

}

void PaddleObject::Update()
{
	GameX = MouseX;

	if(GameX+SizeX/2 < 0)
		GameX = -SizeX/2;
	else if(GameX+SizeX/2 > WindowSizeX)
		GameX = WindowSizeX - SizeX/2;

	unsigned int currenttime = glutGet(GLUT_ELAPSED_TIME);

	switch(CurrentState)
	{
	case BLINKPADDLE:
		if( currenttime - StartStateTimer > Blinktime)
			CurrentState = NORMAL;
		break;

	case SHOOTPADDLE:
		if( currenttime - StartStateTimer > ShootPaddletime)
			CurrentState = NORMAL;
		break;

	case STICKYPADDLE:
		if( currenttime - StartStateTimer > StickyPaddletime)
			CurrentState = NORMAL;
		break;
	}

}

void PaddleObject::Draw()
{
	glEnable(GL_TEXTURE_2D);

	switch(CurrentState)
	{

	case SHOOTPADDLE:
		CurrentTexture = 3;
		break;
	case STICKYPADDLE:
		CurrentTexture = 2;
		break;
	case BLINKPADDLE: 
		CurrentTexture = 1;
		break;
	case NORMAL:
		CurrentTexture = 0;
		break;
	}
	
	if(drawtextures)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, paddle[CurrentTexture]);
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
		glColor3f(0.0, 0.0, 1.0);
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
void PaddleObject::SetGameCoordinates(float x, float y)
{ GameX = x; GameY = y;}

void PaddleObject::SetSize(float x, float y)
{ SizeX = x; SizeY = y;}

void PaddleObject::SetState(State TheState)
{ 
	CurrentState = TheState; 
	StartStateTimer = glutGet(GLUT_ELAPSED_TIME);
}

void PaddleObject::SetVelocityX(float Vel)
{ VelocityX = Vel;}

void PaddleObject::SetVelocityY(float Vel)
{ VelocityY = Vel;}

void PaddleObject::GetGameCoordinates(float& x, float& y)
{ x = GameX; y = GameY;}

void PaddleObject::GetSize(float& x, float& y)
{ x = SizeX; y = SizeY;}

void PaddleObject::GetState(State& TheState)
{ TheState = CurrentState;}

void PaddleObject::GetVelocityX(float& Vel)
{ Vel = VelocityX;}

void PaddleObject::GetVelocityY(float& Vel)
{ Vel = VelocityY;}

ObjectName PaddleObject::GetObjectName()
{ return TheObjectName;}
