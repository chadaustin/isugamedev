// Levi VanOort -- lvanoort@aol.com 2/4/2002

#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "MyObject.h"
#include "collisiondetection.h"
#include <vector>

using namespace std;

//////////////////////////////////////////////////
// GameWorld
//////////////////////////////////////////////////
// Game world is basicly the global object that
// controls all the objects in the game world
//////////////////////////////////////////////////

class GameWorld
{
public:

	//////////////////////////////////////
	//Create
	//////////////////////////////////////
	// Notes:
	//	This creates a GameWorld.  This is
	//	where all initializations should go
	//	Objects, CollisionDetection, etc...
	//////////////////////////////////////
	GameWorld();

	//////////////////////////////////////
	// Destroy
	//////////////////////////////////////
	// Notes:
	//	Releases all objects.
	//////////////////////////////////////
	~GameWorld();

	//////////////////////////////////////
	//Update
	//////////////////////////////////////
	// Notes:
	//	This function is called and updates
	//	all gameworld objects
	//////////////////////////////////////
	void Update();

	//////////////////////////////////////
	// Draw
	//////////////////////////////////////
	// Notes:
	//	Draws all objects to screen currently
	//  in gameworld to screen.
	//////////////////////////////////////
	void Draw();

	void ResetGame();
private:
	CollisionDetection TheGame;
	vector<MyObject*> Collisions[30];

	vector<MyObject*> GameObjects;
	vector<MyObject*> AddObjectsQueue;
	vector<MyObject*> RemoveObjectsQueue;

	MyObject* PaddlePointer;


	void GameRemoveObject(MyObject*& TheObject);
	void AddToRemoveQueue(MyObject*& TheObject);

	///////////////////////////////////////////////////////////////////////
	// GameResponse
	///////////////////////////////////////////////////////////////////////
	// Certain collisions between objects can't be handled by the Objects
	// themselves because they have no knowledge of the game world.  
	// An Example:
	// When collisions cause objects to no longer exsist in Gameworld
	// this will need to be handled by the GameWorld. 
	//
	// This function handles all of these special cases.
	//////////////////////////////////////////////////////////////////////
	void GameResponse(MyObject*&, MyObject*&);	
};

#endif