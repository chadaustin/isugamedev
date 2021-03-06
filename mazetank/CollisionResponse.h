/////////////////////////////////////
// Copyright Levi VanOort 4-28-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// CollisionResponse.h
/////////////////////////////////////

#ifndef __COLLISIONRESPONSE_H
#define __COLLISIONRESPONSE_H

#include "GameObject.h"
#include <vector>

using namespace std;

class CollisionResponse
{
public:

   void ResponseToCollisions(vector<GameObject*> &TheGameObjects);

   void RemoveObjects(vector<GameObject*> &TheGameObjects);

private:
   vector<GameObject*> ToRemove;

   void PlayerBulletResponse(GameObject* &TheGameObject);
   void NPCBulletResponse(GameObject* &TheGameObject);
   void PlayerResponse(GameObject* MainObject, GameObject* &TheGameObject);
   void NPCResponse(GameObject* MainObject, GameObject* &TheGameObject);
   void AddToRemoveQueue(GameObject* &TheGameObject);
   void WallResponse(GameObject* &TheGameObject);
};

#endif
