/////////////////////////////////////
// Copyright Levi VanOort 4-28-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// CollisionResponse.cpp
/////////////////////////////////////
#include "CollisionResponse.h"
#include "SoundManager.h"
#include "Explosion.h"

extern sound::SoundManager* GameSound;
extern vector<Explosion> TheExplosions;

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
               case PLAYERBULLET:
                     PlayerBulletResponse(Collisions[j]);
                     break;

			   case NPCBULLET:
				     NPCBulletResponse(Collisions[j]);

               case CAMTANK:
                     PlayerResponse(TheGameObjects[i], Collisions[j]);
                     break;

               case NPCTANK:
                     NPCResponse(TheGameObjects[i], Collisions[j]);
                     break;
               case WALL:
                     WallResponse(Collisions[j]);
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
            if(MainObjectName == PLAYERBULLET || MainObjectName == NPCBULLET)
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
   int j;
	for(i = 0; i < ToRemove.size(); i++)
	{
		for(j = 0; ToRemove[i] != TheGameObjects[j]; j++);

		delete ToRemove[i];
		TheGameObjects.erase(TheGameObjects.begin()+j);
	}

   ToRemove.clear();

   for(i = 0; i < TheGameObjects.size(); i++)
   {
      TheGameObjects[i]->ResetCollisions();
   }
}

void CollisionResponse::PlayerBulletResponse(GameObject* &TheGameObject)
{
   ObjectType ResponseObjectName;
   Explosion TheExplosion;

   TheGameObject->GetCurrentObjectType(ResponseObjectName);

   switch(ResponseObjectName)
   {
   case NPCTANK:
		float Position[3];
		TheGameObject->GetPosition(Position);
		AddToRemoveQueue(TheGameObject);

		GameSound->getSoundEffectManager()->playSound("music/EXP0.WAV");
		TheExplosion.SetPosition(Position);
		TheExplosions.push_back(TheExplosion);
		
      break;

   case CAMTANK:
      break;

   case WALL:
      break;
   }
}
void CollisionResponse::NPCBulletResponse(GameObject* &TheGameObject)
{
   ObjectType ResponseObjectName;

   TheGameObject->GetCurrentObjectType(ResponseObjectName);

   switch(ResponseObjectName)
   {
   case NPCTANK:
      break;

   case CAMTANK:
      AddToRemoveQueue(TheGameObject);
	  GameSound->getSoundEffectManager()->playSound("music/EXP0.WAV");
      break;

   case WALL:
      break;
   }
}

void CollisionResponse::PlayerResponse(GameObject* MainObject, GameObject* &TheGameObject)
{
   ObjectType ResponseObjectName;
   float Position[3];

   TheGameObject->GetCurrentObjectType(ResponseObjectName);

   switch(ResponseObjectName)
   {
   case NPCTANK:
      MainObject->GetOldPosition(Position);
      MainObject->SetPosition(Position);
      MainObject->SetPosition(Position);
      break;

   case CAMTANK:
      break;

   case WALL:
      MainObject->GetOldPosition(Position);
      MainObject->SetPosition(Position);
      MainObject->SetPosition(Position);  
   }
}

void CollisionResponse::NPCResponse(GameObject* MainObject, GameObject* &TheGameObject)
{
   ObjectType ResponseObjectName;
   float Position[3];

   TheGameObject->GetCurrentObjectType(ResponseObjectName);

   switch(ResponseObjectName)
   {
   case NPCTANK:
      break;

   case CAMTANK:
      MainObject->GetOldPosition(Position);
      MainObject->SetPosition(Position);
      MainObject->SetPosition(Position);
      break;

   case WALL:
      MainObject->GetOldPosition(Position);
      MainObject->SetPosition(Position);
      MainObject->SetPosition(Position);
      break;
   }
}

void CollisionResponse::WallResponse(GameObject* &TheGameObject)
{
   ObjectType ResponseObjectName;

   TheGameObject->GetCurrentObjectType(ResponseObjectName);

   switch(ResponseObjectName)
   {
		case PLAYERBULLET:
		  AddToRemoveQueue(TheGameObject);
		  break;

		case NPCBULLET:
		  AddToRemoveQueue(TheGameObject);
		  break;

		case NPCTANK:
		  break;

		case CAMTANK:
		  break;

		case WALL:
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
