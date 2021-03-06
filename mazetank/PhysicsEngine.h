/////////////////////////////////////
// Copyright Levi VanOort 4-21-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// PhysicsEngine.h
/////////////////////////////////////

#ifndef __PHYSICSENGINE_H__
#define __PHYSICSENGINE_H__

#include "Camera.h"
#include "GameObject.h"
#include "CollisionResponse.h"
#include <vector>

using namespace std;

class PhysicsEngine
{
public:

	PhysicsEngine();

	~PhysicsEngine();

	void Init();

	//////////////////////////////////////////////////
	// void Update(vector<GameObject*> TheObjects)
	//////////////////////////////////////////////////
	// Pre: TheObjects is filled with pointers to all
	//		the objects in the game.
	//		TheCamera has been initialized
	// Post: TheObjects is updated, TheCamera is updated
	// Notes:
	//	To avoid issues created by trying to keep multiple
	//	lists of object pointers the plan is to keep one
	//	list that will get passed around.  
	//	
	//////////////////////////////////////////////////
	void Update(vector<GameObject*> &TheObjects, int dt);

private:
	float GRAVITY;

	CollisionResponse ObjectsResponse;

	void TankUpdate(GameObject* &TruckObject, int dt);
	void BulletUpdate(GameObject* &BulletObject, int dt);
	void CollisionDetection(vector<GameObject*> &TheObjects);
	bool CheckForCollision(GameObject* ObjectOne, GameObject* ObjectTwo);
	bool SphereToSphereCollision(GameObject* ObjectOne, GameObject* ObjectTwo);
	bool SortPredicate(GameObject* Lvalue, GameObject* Rvalue);

};
bool SortPredicate(GameObject* Lvalue, GameObject* Rvalue);
#endif