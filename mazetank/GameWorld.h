/////////////////////////////////////
// Copyright Levi VanOort 4-19-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// GameWorld.h
/////////////////////////////////////
#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include <GL/glut.h>
#include <vector>
#include "Camera.h"
#include "GameObject.h"
#include "PhysicsEngine.h"
#include "Shadow.h"
using namespace std;

class GameWorld
{
public:

   GameWorld();

   ~GameWorld();

   void Init();

   void Update(int dt);

   void Draw();

   void AddObjectToGame(GameObject* TheGameObject);

private:

   vector<GameObject*> TheGameObjects;
   PhysicsEngine GamePhysics;
   Camera* GameCamera;
   GameObject* Player1;

   Shadow MyShadows;

};
#endif



