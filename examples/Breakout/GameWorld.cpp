// Levi VanOort -- lvanoort@aol.com -- 2/4/2002

#include "GameWorld.h"
#include "collisiondetection.h"
#include "MyObject.h"
#include "BlockObject.h"
#include "PaddleObject.h"
#include "BallObject.h"
#include "WallObject.h"
#include "PowerupObject.h"
#include "BulletObject.h"

#include <vector>
#include <time.h>
#include <stdlib.h>

extern bool LeftButtonPressed;
extern int NumberOfBalls;
extern int NumberOfBlocks;
extern int level;
extern int Score;

using namespace std;


GameWorld::GameWorld()
{
	ResetGame();
}

///////////////////////////////////////////
// Lets clean up all of the memory that we
// used
////////////////////////////////////////////
GameWorld::~GameWorld()
{
   Destroy();
}

///////////////////////////////////////////
// Lets clean up all of the memory that we
// used
////////////////////////////////////////////
void GameWorld::Destroy()
{
	int i;

	for(i = 0; i < GameObjects.size(); i++)
	{
		TheGame.RemoveObject(GameObjects[i]);
		delete GameObjects[i];
	}

	GameObjects.clear();
	AddObjectsQueue.clear();
	RemoveObjectsQueue.clear();
}

void GameWorld::Update()
{
	int i;
	float x,y;
	State PaddleState;

	//////////////////////////////////////////////////////////////////
	// If we are in shoot mode and LeftMouse button has been pressed
	// create a new bullet
	//////////////////////////////////////////////////////////////////
	PaddlePointer->GetState(PaddleState);
	if(LeftButtonPressed && PaddleState == SHOOTPADDLE)
	{
			MyObject* NewBullet = new BulletObject;

			float PaddleX, PaddleY, PaddleSizeX, PaddleSizeY;

			PaddlePointer->GetGameCoordinates(PaddleX, PaddleY);
			PaddlePointer->GetSize(PaddleSizeX, PaddleSizeY);

			NewBullet->SetGameCoordinates(PaddleX+PaddleSizeX/2, PaddleY+PaddleSizeY+5);
			NewBullet->SetVelocityY(float(-0.3));

			AddObjectsQueue.push_back(NewBullet);
			LeftButtonPressed = false;
	}

	/////////////////////////////////////
	// Remove all Objects from game
	// that have been queued for removal
	//////////////////////////////////////
	for(i = 0; i < RemoveObjectsQueue.size(); i++)
	{
		TheGame.RemoveObject(RemoveObjectsQueue[i]);
		GameRemoveObject(RemoveObjectsQueue[i]);
	}
	RemoveObjectsQueue.clear();

	//////////////////////////////////////
	// Add all Objects  to game
	// that have been queued for addition
	////////////////////////////////////////
	for(i = 0; i < AddObjectsQueue.size(); i++)
	{
		TheGame.AddObject(AddObjectsQueue[i]);
		GameObjects.push_back(AddObjectsQueue[i]);
	}
	AddObjectsQueue.clear();

	/////////////////////////////////////////
	// Update and move all objects
	// Since we are going through all
	// objects in game this is a good place
	// to queue DEAD object for removal.
	/////////////////////////////////////////
	for(i = 0; i < GameObjects.size(); i++)
	{
		State TheState;
		GameObjects[i]->Update();
		GameObjects[i]->GetGameCoordinates(x,y);
		GameObjects[i]->GetState(TheState);

		TheGame.Move(GameObjects[i], x, y);
		if(TheState == DEAD)
		{
			GameWorld::AddToRemoveQueue(GameObjects[i]);
			if(GameObjects[i]->GetObjectName() == BALL)
				NumberOfBalls--;
		}

	}

	MyObject* CollisionOne;
	MyObject* CollisionTwo;
	int Size;
	
	////////////////////////////////////////////////////
	// Check for Collisions and give each object and the
	// Game world a chance to respond to the collision
	/////////////////////////////////////////////////////
	if(TheGame.CheckForCollisions(Collisions, Size))
	{
		for(int a = 0; a < Size; a++)
		{
			CollisionOne = Collisions[a][0];
			for(int b = 1; b < Collisions[a].size(); b++)
			{
				CollisionTwo = Collisions[a][b];
				CollisionTwo->CollisionResponse(CollisionOne);
			    CollisionOne->CollisionResponse(CollisionTwo);

				GameResponse(CollisionOne, CollisionTwo);	
			}
		}
		for(int c = 0; c < Size; c++)
			Collisions[c].clear();
	}

	////////////////////////////////////////////////
	// If there are no active balls in game world
	// reset game
	////////////////////////////////////////////////
	if(NumberOfBalls == 0 || NumberOfBlocks == 0)
	{
		if(NumberOfBlocks == 0)
		{
			if(level == 3)
				level =0;
			else
				level++;
		}

		if(NumberOfBalls == 0)
			Score = 0;

      Destroy();
		ResetGame();
	}


}

void GameWorld::Draw()
{
	int i;

	/////////////////////////////////////////
	// Go through each object and tell it to 
	// draw itself
	////////////////////////////////////////
	for(i = 0; i < GameObjects.size(); i++)
		GameObjects[i]->Draw();

}

void GameWorld::GameResponse(MyObject*& CollisionOne, MyObject*& CollisionTwo)
{
	State CollisionState[2];
	ObjectName CollisionName[2];
	MyObject* TheCollisions[2];
	MyObject* TheNewObject;

	CollisionOne->GetState(CollisionState[0]);
	CollisionTwo->GetState(CollisionState[1]);

	CollisionName[0] = CollisionOne->GetObjectName();
	CollisionName[1] = CollisionTwo->GetObjectName();

	TheCollisions[0] = CollisionOne;
	TheCollisions[1] = CollisionTwo;

	for(int i = 0; i < 2; i++)
	{
		if(CollisionState[i] == DEAD)
		{
			////////////////////////////////////////
			// On DEATH of a Block see if we need to 
			// add a new powerup or ball to game
			////////////////////////////////////////
			if(CollisionName[i] == BLOCK)
			{
				int Myrand = rand()%15;
				if(Myrand == 8)
				{		
					TheNewObject = new PowerupObject;
					float XPos, YPos;

					TheCollisions[i]->GetGameCoordinates(XPos, YPos);
					TheNewObject->SetSize(20,20);
					TheNewObject->SetVelocityY(float(0.1));
					TheNewObject->SetGameCoordinates(XPos, YPos+10);

					AddObjectsQueue.push_back(TheNewObject);
				}

				else if(Myrand == 4)
				{		
					TheNewObject = new BallObject;
					float XPos, YPos;

					TheCollisions[i]->GetGameCoordinates(XPos, YPos);
					TheNewObject->SetState(NORMAL);
					TheNewObject->SetSize(20,20);
					TheNewObject->SetVelocityY(float(0.3));
					TheNewObject->SetGameCoordinates(XPos, YPos);
					
					AddObjectsQueue.push_back(TheNewObject);
				}
				
				////////////////////////////////////////////////
				// Since a BLOCK has died lets Blink the PADDLE
				////////////////////////////////////////////////
				State CurPaddleState;
				PaddlePointer->GetState(CurPaddleState);
				
				if(CurPaddleState == NORMAL)
					PaddlePointer->SetState(BLINKPADDLE);

				NumberOfBlocks--;
				Score++;
			}
			//////////////////////////////////////////////////
			// On Death of any Object Queue it to be removed
			// during next update cycle
			//////////////////////////////////////////////////
			GameWorld::AddToRemoveQueue(TheCollisions[i]);
		}
	}

}

////////////////////////////////////////////
// GameRemoveObject
///////////////////////////////////////////
// This function removes objects from game
// and released memory back to heap
// *Should only be called when game resets
//  or when Objects Queued for removal 
//  is processed at begin of Update Function
///////////////////////////////////////////
void GameWorld::GameRemoveObject(MyObject*& TheObject)
{
		TheGame.RemoveObject(TheObject);

      int i;
		for(i = 0; (GameObjects[i] != TheObject) && (i < GameObjects.size()); i++);

		if(i < GameObjects.size())
		{
			GameObjects.erase(GameObjects.begin() + i);
			delete TheObject;
			TheObject = NULL;
		}

}

//////////////////////////////////
// AddToRemoveQueue
///////////////////////////////////
// This function adds an object to be
// removed to the RemoveQueue and 
// can be used anywhere in the 
// GameWorld code.
//////////////////////////////////
void GameWorld::AddToRemoveQueue(MyObject*& TheObject)
{
	int index;

	for(index = 0; (index < RemoveObjectsQueue.size()) &&
		(TheObject != RemoveObjectsQueue[index]); index++);
	if(index >= RemoveObjectsQueue.size())
		RemoveObjectsQueue.push_back(TheObject);
}

//////////////////////////////////
// ResetGame
//////////////////////////////////
// Called to reset the current game
// *Be sure to release all memory
// back to heap before you can this
// function
//////////////////////////////////
void GameWorld::ResetGame()
{
	MyObject* temp;
	int levi;
	int i;

	NumberOfBalls = 0;
	NumberOfBlocks = 0;

	if(level == 1)
	{
	   for(levi = 0; levi < 3; levi++)
	   {
			for(i = 0; i < 12; i++)
			{
				temp = new BlockObject;
				temp->SetGameCoordinates(10+(50*i+i), 450+20*levi+levi);
				temp->SetSize(50, 20);
				TheGame.AddObject(temp);
				GameObjects.push_back(temp);
			}
	   }
	 }

	if(level == 2)
	{
	   for(levi = 0; levi < 3; levi++)
	   {
			for(i = 0; i < 12; i++)
			{
				temp = new BlockObject;
				temp->SetGameCoordinates(10+(50*i+i), 450+20*levi+levi);
				temp->SetSize(50, 20);
				TheGame.AddObject(temp);
				GameObjects.push_back(temp);
			}
	   }

	   for(i = 0; i < 4; i++)
	   {
		   temp = new WallObject;
		   temp->SetGameCoordinates(40+(160*i+i), 400);
		   TheGame.AddObject(temp);
		   GameObjects.push_back(temp);
	   }
	}

	if(level == 3)
	{
	   for(levi = 0; levi < 3; levi++)
	   {
			for(i = 0; i < 12; i++)
			{
				temp = new BlockObject;
				temp->SetGameCoordinates(10+(50*i+i), 450+20*levi+levi);
				temp->SetSize(50, 20);
				TheGame.AddObject(temp);
				GameObjects.push_back(temp);
			}
	   }

		for(levi = 0; levi < 2; levi++)
		{
		   for(i = 0; i < 5-levi; i++)
		   {
			   temp = new WallObject;
			   temp->SetGameCoordinates(40+(130*i+i)+levi*80, 400+levi*150);
			   TheGame.AddObject(temp);
			   GameObjects.push_back(temp);
		   }
		}
	}

	temp = new PaddleObject;
	PaddlePointer = temp;
	temp->SetGameCoordinates(100,30);
	temp->SetSize(100, 20);
	TheGame.AddObject(temp);
	GameObjects.push_back(temp);

	temp = new BallObject;
	temp->SetGameCoordinates(200,100);
	temp->SetVelocityX(0.0);
	temp->SetVelocityY(0.0);
	TheGame.AddObject(temp);
	GameObjects.push_back(temp);
}


	
