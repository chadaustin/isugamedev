#include "MyObject.h"
#include "FrogObject.h"
#include "AutoObject.h"
#include "LogObject.h"
#include "LilyPadObject.h"
#include "myobjectstore.h"
#include "GameWorld.h"
#include <gl/glut.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>

extern int WindowSizeX;
extern int WindowSizeY;
extern int LaneSize;
extern int FrogZone;
extern int CurrentLevel;

#define drawOneLine(x1,y1,x2,y2) glBegin(GL_LINES); glVertex2f((x1),(y1)); \
	glVertex2f((x2),(y2)); glEnd();

int ObjectHeight;
int ObjectOffset;

GameWorld::GameWorld()
{ Create(); }

GameWorld::~GameWorld()
{ Destroy(); }

void GameWorld::Create()
{ 
	int i = 0;
	int NumItems;
	MyObject* Item;

	FrogZone = 0;

	ObjectHeight = 33;
	ObjectOffset = 0;

	int Lilypadspacing = WindowSizeX/12;

	for(i = 0; i < 6; i++)
	{
		Item = new LilypadObject;
		Item->SetGameCoordinates(Lilypadspacing*i*2+7, LaneSize*12+ObjectOffset);
		Item->SetSize(40,ObjectHeight);

		MobileObjects.Insert(Item);
		ThePond.AddObject(Item);
	}

	i=0;
	NumItems = ReadGameData();

	while(i < NumItems)
	{
		switch(GameData[i])
		{
		case FROG: 
			Item = new FrogObject;
			ObjectHeight = 15;
			ObjectOffset = 10;
			break;
		case AUTO: 
			Item = new AutoObject;
			ObjectHeight = 30;
			ObjectOffset = 3;
			break;
		case LOG:
			Item = new LogObject;
			ObjectHeight = 30;
			ObjectOffset = 3;
			break;
		}
		Item->SetGameCoordinates(GameData[i+2],LaneSize*GameData[i+1]+ObjectOffset);
		Item->SetSize(GameData[i+3],ObjectHeight);
		Item->SetVelocityX(GameData[i+4]);

		MobileObjects.Insert(Item);
		ThePond.AddObject(Item);

		i = i + 5;
	}
	
}

void GameWorld::Update()
{ 	
	MyObject* Cursor;
	MyObject* TheMainCollision;
	MyObjectStore* TheCollisions = NULL;
	int MoveX, MoveY, GameX, GameY, FrogX, FrogY;
	int NumCollisions;

	// Update the Movement for all Mobile Objects
	MobileObjects.ResetCursor();
	MobileObjects.GetCurrentObject(Cursor);
	while(Cursor != NULL)
	{
		Cursor->Update();
		MobileObjects.GetCurrentObject(Cursor);
	}

	MobileObjects.ResetCursor();
	MobileObjects.GetCurrentObject(Cursor);
	while(Cursor != NULL)
	{
		if (Cursor->Moved(MoveX, MoveY))
		{
			Cursor->GetGameCoordinates(GameX, GameY);
			ThePond.Move(Cursor, GameX+MoveX, GameY+MoveY);

			if(Cursor->GetObjectName() == FROG)
			{
				if(FrogZone < 7)
					Cursor->SetVelocityX(0);

			Cursor->GetGameCoordinates(FrogX, FrogY);
			if((FrogX < 0 || FrogX > WindowSizeX) && FrogZone > 6)
				ResetGame();
			}

		}
		MobileObjects.GetCurrentObject(Cursor);
	}


	if(ThePond.CheckForCollisions(TheCollisions, NumCollisions))
	{
		for(int i = 0; i < NumCollisions; i++)
		{
			TheCollisions[i].ResetCursor();
			TheCollisions[i].GetCurrentObject(TheMainCollision);
			TheCollisions[i].GetCurrentObject(Cursor);
			while(Cursor != NULL)
			{
				TheMainCollision->CollisionResponse(Cursor);
				Cursor->CollisionResponse(TheMainCollision);

				if((TheMainCollision->GetObjectName() == AUTO &&
					Cursor->GetObjectName() == FROG) ||
					(Cursor->GetObjectName() == AUTO && TheMainCollision->GetObjectName() == FROG))
					ResetGame();
				else if((TheMainCollision->GetObjectName() == LILY &&
					Cursor->GetObjectName() == FROG) ||
					(Cursor->GetObjectName() == LILY && TheMainCollision->GetObjectName() == FROG))
				{
					if(Cursor->GetObjectName() == FROG)
						ThePond.Move(Cursor, 100, ObjectOffset);
					else
						ThePond.Move(TheMainCollision, 100, ObjectOffset);
				}

				TheCollisions[i].GetCurrentObject(Cursor);
			}
			
		}
	}
	else
	{
		if(FrogZone > 6)
			ResetGame();
	}

}

void GameWorld::Destroy()
{ 
	 MyObject* temp;

	 MobileObjects.ResetCursor();

	 MobileObjects.GetCurrentObject(temp);
	 while(temp != NULL)
	 {
		ThePond.RemoveObject(temp);
		MobileObjects.Remove(temp);

		delete temp;
		MobileObjects.GetCurrentObject(temp);
	 }
}

void GameWorld::Draw()
{  
	MyObject* drawn;

	DrawGameField();

	MobileObjects.ResetCursor();

	MobileObjects.GetCurrentObject(drawn);
	while(drawn != NULL)
	{
		drawn->Draw();
		MobileObjects.GetCurrentObject(drawn);
	}
}

void GameWorld::DrawGameField()
{
	glColor3f(0.0,1.0,0.0);
	glRectf(0.0,0*LaneSize, WindowSizeX, 1*LaneSize-1); 

	glColor3f(1.0,1.0,0.0);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(4,0xAAAA);

	for(int i = 2; i < 6; i++)
	{
		drawOneLine(0.0, i*LaneSize, WindowSizeX, i*LaneSize-1);
	}

	glDisable(GL_LINE_STIPPLE);


	glColor3f(0.5,0.5,0.5);
	glRectf(0.0,6*LaneSize, WindowSizeX, 7*LaneSize-1); 

	glColor3f(0.0,0.0,1.0);
	glRectf(0.0,7*LaneSize , WindowSizeX, 12*LaneSize-1);

	glColor3f(0.6,1.0,0.2);
	glRectf(0.0,12*LaneSize , WindowSizeX, 13*LaneSize-1);

}

void GameWorld::ResetGame()
{
	Destroy();
	Create();
	glutPostRedisplay();
}

int GameWorld::ReadGameData()
{
	ifstream infile;
	int i = 0;

	infile.open("Level1.txt");
	infile >> GameData[i];
	i++;
	while(infile)
	{
			infile >> GameData[i];
			i++;
	}
	infile.close();
	return i-1;
}