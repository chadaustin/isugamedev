#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "MyObject.h"
#include "MyObjectStore.h"
#include "collisiondetection.h"

class GameWorld
{
public:
	GameWorld();

	~GameWorld();

	//////////////////////////////////////
	//Create
	//////////////////////////////////////
	// Notes:
	//	This creates a GameWorld.  This is
	//	where all initializations should go
	//	Objects, Maze, etc...
	//////////////////////////////////////
	void Create();

	//////////////////////////////////////
	//Update
	//////////////////////////////////////
	// Notes:
	//	This function is called and updates
	//	all gameworld objects
	//////////////////////////////////////
	void Update();

	//////////////////////////////////////
	// Destroy
	//////////////////////////////////////
	// Notes:
	//	Releases all objects
	//////////////////////////////////////
	void Destroy();

	void Register();

	//////////////////////////////////////
	// Draw
	//////////////////////////////////////
	// Notes:
	//	Draws all objects to screen
	//////////////////////////////////////
	void Draw();

private:
	CollisionDetection ThePond;
	MyObjectStore MobileObjects;

	int MazeX, MazeY;
	int GameData[100];

	void DrawGameField();
	void ResetGame();
	int ReadGameData();
	
};

#endif