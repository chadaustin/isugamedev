#include "CollisionResponse.h"

void CollisionResponse::ResponseToCollisions(vector<GameObject*> &TheGameObjects)
{
   ObjectType MainObjectName;

   vector<GameObject*> Collisions;
 
   for(int i = 0; i < TheGameObjects.size(); i++)
   {
      if(TheGameObjects[i]->IsCollision())
      {
         TheGameObjects[i]->GetCurrentObjectType(MainObjectName);
         TheGameObjects[i]->GetCollisions(Collisions);

         if(Collisions.size() > 0)
         {
            for(int j = 0; j < Collisions.size(); j++)
            {
               switch(MainObjectName)
               {
               case BULLET:
                     BulletResponse(Collisions[j]);
                     break;

               case CAMTANK:
                     PlayerResponse(Collisions[j]);
                     break;

               case NPCTANK:
                     NPCResponse(Collisions[j]);
                     break;
               }

            }
         }
         else
         {
            //////////////////////////////////////////////////////////////
            // special case to remove bullets when they get below gound
            // plane
            /////////////////////////////////////////////////////////////
            if(MainObjectName == BULLET)
               AddToRemoveQueue(TheGameObjects[i]);
         }
      }
   }
}

void CollisionResponse::RemoveObjects(vector<GameObject*> &TheGameObjects)
{
   //////////////////////////////////////////////
	// Actually remove the objects from the game
	//////////////////////////////////////////////
   int i;
	for(i = 0; i < ToRemove.size(); i++)
	{
		for(int j = 0; ToRemove[i] != TheGameObjects[j]; j++);

		delete ToRemove[i];
		TheGameObjects.erase(TheGameObjects.begin()+j);
	}

   ToRemove.clear();

   for(i = 0; i < TheGameObjects.size(); i++)
   {
      TheGameObjects[i]->ResetCollisions();
   }
}

void CollisionResponse::BulletResponse(GameObject* &TheGameObject)
{
   ObjectType ResponseObjectName;

   TheGameObject->GetCurrentObjectType(ResponseObjectName);

   switch(ResponseObjectName)
   {
   case BULLET:
      AddToRemoveQueue(TheGameObject);
      break;

   case NPCTANK:
      AddToRemoveQueue(TheGameObject);
      break;

   case CAMTANK:
      break;
   }
}

void CollisionResponse::PlayerResponse(GameObject* &TheGameObject)
{
   ObjectType ResponseObjectName;

   TheGameObject->GetCurrentObjectType(ResponseObjectName);

   switch(ResponseObjectName)
   {
   case BULLET:
      break;

   case NPCTANK:
      break;

   case CAMTANK:
      break;
   }
}

void CollisionResponse::NPCResponse(GameObject* &TheGameObject)
{
   ObjectType ResponseObjectName;

   TheGameObject->GetCurrentObjectType(ResponseObjectName);

   switch(ResponseObjectName)
   {
   case BULLET:
      break;

   case NPCTANK:
      break;

   case CAMTANK:
      break;
   }
}

void CollisionResponse::AddToRemoveQueue(GameObject* &TheGameObject)
{
   bool Add = true;

   for(int i = 0; i < ToRemove.size(); i++)
   {
      if(TheGameObject == ToRemove[i])
         Add = false;
   }

   if(Add)
      ToRemove.push_back(TheGameObject);
}
