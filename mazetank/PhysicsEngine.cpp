/////////////////////////////////////
// Copyright Levi VanOort 4-21-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// PhysicsEngine.cpp
/////////////////////////////////////

#include "PhysicsEngine.h"
#include <math.h>
#include <GL/glut.h>

#define PI 3.1415926535

PhysicsEngine::PhysicsEngine()
{
	CurrentCamera = NULL;
   GRAVITY = -.00001981;
}

PhysicsEngine::~PhysicsEngine()
{

}
void PhysicsEngine::Init()
{

}

void PhysicsEngine::Update(vector<GameObject*> &TheObjects, int deltatime)
{

	ObjectType ObjectName;



	for(int i = 0; i < TheObjects.size(); i++)
	{
		////////////////////////
		//Lets get object name
		////////////////////////
		TheObjects[i]->GetCurrentObjectType(ObjectName);

		switch(ObjectName)
		{
		case CAMTANK:
			CameraTruckUpdate(TheObjects[i], deltatime);
			break;

		case BULLET:
			BulletUpdate(TheObjects[i], deltatime);
			break;
		}

	}

	CollisionDetection(TheObjects);
}

void PhysicsEngine::CameraTruckUpdate(GameObject* &TruckObject, int dt)
{
	float ObjectPosition[3];
	float ObjectVelocity = 0.0;
	float ObjectAngle;
	float ObjectAngularVelocity;

   ///////////////////////////////////////////////////////////
   // Collect all the information about the Camera Tank Object
   ///////////////////////////////////////////////////////////
	TruckObject->GetVelocity(ObjectVelocity);	
	ObjectVelocity *= dt;
	TruckObject->GetPosition(ObjectPosition);
	TruckObject->GetAngularVelocity(ObjectAngularVelocity);
	TruckObject->GetObjectAngle(ObjectAngle);

	float AngleInRadians = (ObjectAngle * PI)/180;
	float AngularVelocity = (ObjectAngularVelocity*PI)/180;

	AngleInRadians = AngleInRadians + AngularVelocity*dt;

	float NewPosition[3];

	float MoveX = ObjectVelocity*cos(AngleInRadians);
	float MoveY = ObjectVelocity*sin(AngleInRadians);

	NewPosition[0] = ObjectPosition[0] + MoveX;
	NewPosition[1] = ObjectPosition[1] + MoveY;
	NewPosition[2] = ObjectPosition[2];

   //////////////////////////////////////////////////
   // Set New tank angle based on Angular velocity
   // and change in time
   //////////////////////////////////////////////////
	ObjectAngle = (AngleInRadians * 180.0) / PI;

	TruckObject->SetPosition(NewPosition);
	TruckObject->SetObjectAngle(ObjectAngle);

	//////////////////
	// Update Camera
	//////////////////
/*	if(CurrentCamera != NULL)
	{
		CurrentCamera->Move(-MoveX, -MoveY);
		CurrentCamera->SetObjectYaw(-ObjectAngle);
	}*/

}

void PhysicsEngine::BulletUpdate(GameObject* &BulletObject, int dt)
{
   float ObjectPosition[3];
	float ObjectVelocity = 0.0;
	float ObjectAngle;
   float ObjectAngleZ;
   float ObjectVelocityZ;

   /////////////////////////////////////////////////
   // Collect all info about the current Bullet for
   // use in equations
   /////////////////////////////////////////////////
   BulletObject->GetVelocity(ObjectVelocity);
   ObjectVelocity *= dt;

   BulletObject->GetPosition(ObjectPosition);
   BulletObject->GetObjectAngle(ObjectAngle);
   BulletObject->GetObjectZAngle(ObjectAngleZ);
   BulletObject->GetVelocityZ(ObjectVelocityZ);
   
   
	float AngleInRadians = (ObjectAngle * PI)/180;
    float AngleZInRadians = ((ObjectAngleZ) * PI)/180;

    float MoveX = ObjectVelocity*cos(AngleInRadians);
	float MoveY = ObjectVelocity*sin(AngleInRadians);

   //////////////////////////////////////////////////////
   // Calculate the Z position
   //////////////////////////////////////////////////////
   float NewVelocity = ObjectVelocityZ * sin(-1*AngleZInRadians) + GRAVITY*dt;
   float MoveZ = NewVelocity*dt;
   
   float NewPosition[3];

   NewPosition[0] = ObjectPosition[0] + MoveX;
   NewPosition[1] = ObjectPosition[1] + MoveY;
   NewPosition[2] = ObjectPosition[2] + MoveZ;

   BulletObject->SetPosition(NewPosition);
   BulletObject->SetVelocityZ(NewVelocity);
}

void PhysicsEngine::CollisionDetection(vector<GameObject*> &TheObjects)
{
	float Position[3];
    ObjectType ObjectName;
	ObjectType ObjectName2;
	vector<GameObject*> ToRemove;

   ///////////////////////////////////////////////////////
   // Remove bullets once they get below the ground plane
   //////////////////////////////////////////////////////
	int i;
	for(i = 0; i < TheObjects.size(); i++)
	{
		TheObjects[i]->GetPosition(Position);
		TheObjects[i]->GetCurrentObjectType(ObjectName);

		if(Position[2] < 0 && ObjectName == BULLET)
		{
 			TheObjects[i]->AddCollision();
		}
	}

	int j;


   ////////////////////////////////////////
   // Check here for all the collisions
   ////////////////////////////////////////
	for(i = 0; i < TheObjects.size(); i++)
	{
		TheObjects[i]->GetCurrentObjectType(ObjectName);
		for(j = i+1; j < TheObjects.size(); j++)
		{
			TheObjects[j]->GetCurrentObjectType(ObjectName2);

			if(!(ObjectName == WALL && ObjectName2 == WALL))
			{
				if(CheckForCollision(TheObjects[i], TheObjects[j]))
				{
					TheObjects[i]->AddCollision(TheObjects[j]);
					TheObjects[j]->AddCollision(TheObjects[i]);
				}
			}
		}
	}

   ObjectsResponse.ResponseToCollisions(TheObjects);
   ObjectsResponse.RemoveObjects(TheObjects);
}

bool PhysicsEngine::CheckForCollision(GameObject* ObjectOne, GameObject* ObjectTwo)
{
   return SphereToSphereCollision(ObjectOne, ObjectTwo);
}

bool PhysicsEngine::SphereToSphereCollision(GameObject* ObjectOne, GameObject* ObjectTwo)
{
   float PositionOne[3];
   float PositionTwo[3];

   ObjectOne->GetPosition(PositionOne);
   ObjectTwo->GetPosition(PositionTwo);

   float Dist = sqrt(pow(PositionOne[0]-PositionTwo[0],2)+
                     pow(PositionOne[1]-PositionTwo[1],2)+
                     pow(PositionOne[2]-PositionTwo[2],2));

   float OneRadius;
   float TwoRadius;

   ObjectOne->GetObjectSphere(OneRadius);
   ObjectTwo->GetObjectSphere(TwoRadius);

   Dist = Dist - (OneRadius+TwoRadius);

   if(Dist > 0)
      return false;
   else
      return true;
}