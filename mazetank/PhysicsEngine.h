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
	void Update(vector<GameObject*> &TheObjects);

	void SetCamera(Camera* &TheCamera)
	{ CurrentCamera = TheCamera;}

private:
	Camera* CurrentCamera;
	int dt, Starttime, Stoptime;
   float GRAVITY;

	void CameraTruckUpdate(GameObject* &TruckObject);
	void BulletUpdate(GameObject* &BulletObject);

};
#endif