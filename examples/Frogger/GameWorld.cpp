//////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//				lvanoort@aol.com 
//
// GameWorld.cpp
// 4-5-2002
//////////////////////////////////////////////////////

#include "MyObject.h"
#include "FrogObject.h"
#include "AutoObject.h"
#include "LogObject.h"
#include "LilypadObject.h"
#include "GameWorld.h"
#include <SDL_opengl.h>
#include <stdlib.h>
#include <fstream>

using namespace std;


extern int WindowSizeX;
extern int WindowSizeY;
extern int LaneSize;
extern int FrogZone;
extern int CurrentLevel;


void drawOneLine(float x1,float y1,float x2,float y2) 
{
	glBegin(GL_LINES); 
	glVertex2f((x1),(y1));
	glVertex2f((x2),(y2)); 
	glEnd();
}


int ObjectHeight;
int ObjectOffset;


GameWorld::GameWorld()
{ Create(); }


GameWorld::~GameWorld()
{ Destroy(); }

/////////////////////////////////////
// Create()
/////////////////////////////////////
// Notes:
//	Initializes the game.  Reads data
//  from file and sets up game.
/////////////////////////////////////
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

		MobileObjects.push_back(Item);
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

		MobileObjects.push_back(Item);
		ThePond.AddObject(Item);

		i = i + 5;
	}

}

/////////////////////////////////////
// void Update()
/////////////////////////////////////
// Notes:
//	Updates all the game data.
/////////////////////////////////////
void GameWorld::Update(int dt)
{ 	
	MyObject* Cursor;
	MyObject* TheMainCollision;
	vector <MyObject*> TheCollisions[30];
	float MoveX, MoveY, GameX, GameY, FrogX, FrogY;
	int NumCollisions;
	int i;

	//////////////////////////////////////////////
	// Update the Movement for all Mobile Objects
	//////////////////////////////////////////////
	for(i = 0; i < int(MobileObjects.size()); i++)
	{
		MobileObjects[i]->Update(dt);
	}

	//////////////////////////////////////////////
	// Tell collision detection engine about 
	// each object that moved
	//////////////////////////////////////////////
	for(i = 0; i < int(MobileObjects.size()); i++)
	{
		if (MobileObjects[i]->Moved(MoveX, MoveY))
		{
			MobileObjects[i]->GetGameCoordinates(GameX, GameY);
			MobileObjects[i]->SetGameCoordinates(GameX+MoveX, GameY+MoveY);

			ThePond.Move(MobileObjects[i], GameX+MoveX, GameY+MoveY);

			if(MobileObjects[i]->GetObjectName() == FROG)
			{
				if(FrogZone < 7)
					MobileObjects[i]->SetVelocityX(0);

			MobileObjects[i]->GetGameCoordinates(FrogX, FrogY);
			if((FrogX < 0 || FrogX > WindowSizeX) && FrogZone > 6)
				ResetGame();
			}

		}
	}

	///////////////////////////////////////
	// Check for collisions and respond 
	//////////////////////////////////////
	if(ThePond.CheckForCollisions(TheCollisions, NumCollisions))
	{
		for(i = 0; i < NumCollisions; i++)
		{
			TheMainCollision = TheCollisions[i][0];

			for(int j = 1; j < int(TheCollisions[i].size());j++)
			{
				Cursor = TheCollisions[i][j];
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

	 for(int i = 0; i < int(MobileObjects.size()); i++)
	 {
		temp = MobileObjects[i];
		ThePond.RemoveObject(temp);
		delete temp;
	 }
	 MobileObjects.erase(MobileObjects.begin(), MobileObjects.end());
}

//////////////////////////////////
// void Draw()
//////////////////////////////////
// Notes:
//	Draw the game objects.
//////////////////////////////////
void GameWorld::Draw()
{  

	DrawGameField();

	for(int i = 0; i < int(MobileObjects.size()); i++)
	{
		MobileObjects[i]->Draw();
	}

}

//////////////////////////////////
// void DrawGameField()
//////////////////////////////////
// Notes:
//	Draws frogger background
///////////////////////////////////
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

///////////////////////////////////
// ResetGame()
///////////////////////////////////
// Notes:
//	Releases all resources and 
//	resets game.
///////////////////////////////////
void GameWorld::ResetGame()
{
	Destroy();
	Create();
}

///////////////////////////////////////
// int ReadGameData()
///////////////////////////////////////
// Notes:
//	Opens file and reads data in from
//	file and stores it in GameData
//	array
///////////////////////////////////////
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


