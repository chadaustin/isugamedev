// Levi VanOort -- lvanoort@aol.com 2/4/2002

#include <GL/glut.h>
#include <stdlib.h>
#include "MyObject.h"
#include "BallObject.h"
#include <time.h>

//External Globals////////////// 
extern int WindowSizeX;
extern int WindowSizeY;
extern int dt;
extern int MouseX, MouseY;
extern bool LeftButtonPressed;
extern int NumberOfBalls;
extern GLuint ball[1];
extern bool drawtextures;
///////////////////////////////

BallObject::BallObject()
{
	GameX = 0.0;
	GameY = 0.0;
	SizeX = 20.0;
	SizeY = 20.0;
	VelocityX = 0.0;
	VelocityY = 0.0;
	LastX = 0.0;
	LastY = 0.0;
	responded = false;
	AngleCoefficient = 0.03;

	CurrentState = PADDLERIDING;
	TheObjectName = BALL;

	KillerBalltime = 5000;
   srand( (unsigned)time( NULL ) );
   NumberOfBalls++;

}

BallObject::~BallObject()
{
	//No memory allocated so nothing to give back
}

void BallObject::CollisionResponse(MyObject* CollisionObject)
{
	ObjectName TheName = CollisionObject->GetObjectName();
	float CollX, CollY, CollSizeX, CollSizeY;
	float i;
	int ZoneNumber;

	if(!responded && CurrentState != PADDLERIDING)
	{
		////////////////////////////////////////////////////
		// Check which side of other object ball bounces off
		////////////////////////////////////////////////////
		if(CurrentState != KILLERBALL || TheName == PADDLE ||
			(CurrentState == KILLERBALL && TheName == WALL))
			BallObject::ReflectOffObject(CollisionObject);

		switch (TheName)
		{
		case PADDLE:
			CollisionObject->GetGameCoordinates(CollX, CollY);
			CollisionObject->GetSize(CollSizeX, CollSizeY);

			for(i = CollX, ZoneNumber = 0; GameX > i; i = i + CollSizeX/7, ZoneNumber++);

			/////////////////////////////////////////////////////
			// The balls needs to bounce off paddles at different
			// angles to make game fun!!
			////////////////////////////////////////////////////
			if(ZoneNumber < 4)	
				VelocityX = VelocityX + ((3-ZoneNumber)*AngleCoefficient);
			else 
				VelocityX = VelocityX + ((4-ZoneNumber)*AngleCoefficient);
			break;

		case POWERUP:
			SetState(KILLERBALL);
			break;

		case BLOCK:

			////////////////////////////////////
			// Randomly adds velocity to ball 
			// to make game more challanging the
			// longer it is played
			////////////////////////////////////
			int Myrand = rand()%5;
			if(Myrand == 3)
			{
				if(VelocityY < 0)
					VelocityY = VelocityY - .05;
				else
					VelocityY = VelocityY + .05;
			}
			break;
		}
			
		responded = true;
	}

}

/////////////////////////////////
// Update
/////////////////////////////////
// Based on object state update
// accordingly
//////////////////////////////////

void BallObject::Update()
{
	if(LeftButtonPressed && CurrentState == PADDLERIDING)
	{
		CurrentState = NORMAL;
		VelocityX = ((rand()%5)/10.0) - ((rand()%5)/10.0);
		VelocityY = -0.3;
		GameY = GameY + 15;
		LeftButtonPressed = false;
	}
	if(CurrentState == NORMAL || CurrentState == KILLERBALL)
	{

		// Check to see if we need to bounce off a boundary
		if(GameX < 0.0) 
		{
			GameX = -GameX;
			VelocityX = VelocityX * -1;
		}

		else if(GameX+SizeX > WindowSizeX)
		{
			GameX = WindowSizeX - ((GameX+SizeX) - WindowSizeX);
			VelocityX = VelocityX * -1;
		}

		else if(GameY+SizeY < 0.0) 
		{
			CurrentState = DEAD;
		}
		else if (GameY > WindowSizeY)
		{
			GameY = WindowSizeY - ((GameY+SizeY) - WindowSizeY);
			VelocityY = VelocityY * -1;
		}

		LastX = GameX;
		LastY = GameY;

		GameX = GameX + VelocityX*dt;
		GameY = GameY + VelocityY*dt;

		responded = false;
	}
		
	else if (CurrentState == PADDLERIDING)
	{
		GameX = MouseX+20;
		GameY = 49;
	}

	if(CurrentState == KILLERBALL)
	{
		int currenttime = glutGet(GLUT_ELAPSED_TIME);

		if(currenttime - StartStateTimer > KillerBalltime)
			CurrentState = NORMAL;

	}
}

void BallObject::Draw()
{

	if(drawtextures)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ball[0]);
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
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
			glVertex2f(GameX, GameY);
			glVertex2f(GameX, GameY+SizeY);
			glVertex2f(GameX+SizeX, GameY+SizeY);
			glVertex2f(GameX+SizeX, GameY);
		glEnd();
	}
}

/////////////////////////////////////////////
// Use CrossProduct to see if two line
// segments overlap
////////////////////////////////////////////////
bool BallObject::SegmentIntersection(float X1, float Y1, 
									 float X2, float Y2,
									 float X3, float Y3, 
									 float X4, float Y4)
{
	float firstCross = ((X3-X1)*(Y2-Y1))-((Y3-Y1)*(X2-X1));
	float secondCross = ((X4-X1)*(Y2-Y1))-((Y4-Y1)*(X2-X1));

	if(firstCross < 0 && secondCross > 0)
		return true;
	else if(firstCross > 0 && secondCross < 0)
		return true;
	else
		return false;
}


/////////////////////////////////////////////////////////
// Functions below will not change for different objects
/////////////////////////////////////////////////////////
void BallObject::SetGameCoordinates(float x, float y)
{ GameX = x; GameY = y;}

void BallObject::SetSize(float x, float y)
{ SizeX = x; SizeY = y;}

void BallObject::SetState(State TheState)
{ CurrentState = TheState;
   StartStateTimer = glutGet(GLUT_ELAPSED_TIME);}

void BallObject::SetVelocityX(float Vel)
{ VelocityX = Vel;}

void BallObject::SetVelocityY(float Vel)
{ VelocityY = Vel;}

void BallObject::GetGameCoordinates(float& x, float& y)
{ x = GameX; y = GameY;}

void BallObject::GetSize(float& x, float& y)
{ x = SizeX; y = SizeY;}

void BallObject::GetState(State& TheState)
{ TheState = CurrentState;}

void BallObject::GetVelocityX(float& Vel)
{ Vel = VelocityX;}

void BallObject::GetVelocityY(float& Vel)
{ Vel = VelocityY;}

ObjectName BallObject::GetObjectName()
{ return TheObjectName;}
///////////////////////////////////////////////////////////

/////////////////////////////////////////
// ReflectOffObject
//////////////////////////////////////////
// Long set of code to Reflect ball off
// collision object correctly based on
// which side of object ball hits
////////////////////////////////////////////
void BallObject::ReflectOffObject(MyObject* TheObject)
{
	float CollX,CollY;
	float CollSizeX, CollSizeY;
	float dx, dy;

	TheObject->GetGameCoordinates(CollX, CollY);
	TheObject->GetSize(CollSizeX, CollSizeY);

	//We need to find which side of the Object the ball
	//ran into so we can reflect it properly.

	dx = GameX-LastX;
	dy = GameY-LastY;

	// Going up and right
	if(dx > 0 && dy > 0)
	{
		if(BallObject::SegmentIntersection(GameX+SizeX,GameY+SizeY,GameX+SizeX+dx,GameY+SizeY+dy,
							CollX, CollY, CollX, CollY+CollSizeY))
		{
			VelocityX = VelocityX * -1;

		}
		else if(SegmentIntersection(GameX+SizeX,GameY+SizeY,GameX+SizeX+dx,GameY+SizeY+dy,
							CollX, CollY, CollX+CollSizeX, CollY))
		{
			VelocityY = VelocityY * -1;
		}
		else if(SegmentIntersection(GameX+SizeX,GameY,GameX+SizeX+dx,GameY+dy,
								CollX, CollY, CollX, CollY+CollSizeY))
		{
			VelocityX = VelocityX * -1;
		}
		else if(SegmentIntersection(GameX,GameY+SizeY,GameX+dx,GameY+SizeY+dy,
							CollX, CollY, CollX+CollSizeX, CollY))
		{
			VelocityY = VelocityY * -1;
		}
	}

	// Going up and left
	if (dy > 0 && dx < 0)
	{
		if(SegmentIntersection(GameX,GameY+SizeY,GameX+dx,GameY+SizeY+dy,
							CollX+CollSizeX, CollY, CollX+CollSizeX, CollY+CollSizeY))
		{
			VelocityX = VelocityX * -1;
		}
		else if(SegmentIntersection(GameX,GameY+SizeY,GameX+dx,GameY+SizeY+dy,
							CollX+CollSizeX, CollY, CollX, CollY))
		{
			VelocityY = VelocityY * -1;
		}
		else if(SegmentIntersection(GameX,GameY,GameX+dx,GameY+dy,
							CollX+CollSizeX, CollY, CollX+CollSizeX, CollY+CollSizeY))
		{
			VelocityX = VelocityX * -1;
		}
		else if(SegmentIntersection(GameX+SizeX,GameY+SizeY,GameX+SizeX+dx,GameY+SizeY+dy,
							CollX, CollY, CollX+CollSizeX, CollY))
		{
			VelocityY = VelocityY * -1;
		}
	}

	//Going Down and right
	if(dy < 0 && dx > 0)
	{
		if(SegmentIntersection(GameX+SizeX,GameY,GameX+SizeX+dx,GameY+dy,
							CollX, CollY+CollSizeY, CollX, CollY))
		{
			VelocityX = VelocityX * -1;
		}
		else if(SegmentIntersection(GameX+SizeX,GameY,GameX+SizeX+dx,GameY+dy,
							CollX, CollY+CollSizeY, CollX+CollSizeX, CollY+CollSizeY))
		{
			VelocityY = VelocityY * -1;
		}
		else if(SegmentIntersection(GameX+SizeX,GameY+SizeY,GameX+SizeX+dx,GameY+SizeY+dy,
							CollX, CollY, CollX, CollY+CollSizeY))
		{
			VelocityX = VelocityX * -1;
		}
		else if(SegmentIntersection(GameX,GameY,GameX+dx,GameY+dy,
							CollX, CollY+CollSizeY, CollX+CollSizeX, CollY+CollSizeY))
		{
			VelocityY = VelocityY * -1;
		}
	}

		//Going Down and left
	if(dy < 0 && dx < 0)
	{
		if(SegmentIntersection(GameX,GameY,GameX+dx,GameY+dy,
							CollX+CollSizeX, CollY+CollSizeY, CollX+CollSizeX, CollY))
		{
			VelocityX = VelocityX * -1;
		}
		else if(SegmentIntersection(GameX,GameY,GameX+dx,GameY+dy,
							CollX+CollSizeX, CollY+CollSizeY, CollX, CollY+CollSizeY))
		{
			VelocityY = VelocityY * -1;
		}
		else if(SegmentIntersection(GameX,GameY+SizeY,GameX+dx,GameY+SizeY+dy,
							CollX+CollSizeX, CollY+CollSizeY, CollX+CollSizeX, CollY))
		{
			VelocityX = VelocityX * -1;
		}
		else if(SegmentIntersection(GameX+SizeX,GameY,GameX+SizeX+dx,GameY+dy,
							CollX+CollSizeX, CollY+CollSizeY, CollX, CollY+CollSizeY))
		{
			VelocityY = VelocityY * -1;
		}
	}

	if(dx==0)
	{
		VelocityY=VelocityY * -1;
		VelocityX=0.05;
	}
}
