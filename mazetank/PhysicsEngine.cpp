#include "PhysicsEngine.h"
#include <math.h>
#include <GL/glut.h>

#define PI 3.1415926535

PhysicsEngine::PhysicsEngine()
{
	Stoptime = 0;
	Starttime = 0;
	dt = 0;

	CurrentCamera = NULL;
   GRAVITY = -.00001981;
}

PhysicsEngine::~PhysicsEngine()
{

}
void PhysicsEngine::Init()
{

}

void PhysicsEngine::Update(vector<GameObject*> &TheObjects)
{

	ObjectType ObjectName;

	///////////////////////////////////////////
	// Timer used to move objects so
	// game will be same speed on all machines
	///////////////////////////////////////////
	Stoptime = glutGet(GLUT_ELAPSED_TIME);
	dt = Stoptime - Starttime;
	Starttime = glutGet(GLUT_ELAPSED_TIME);

	if(dt > 50)
		dt = 50;	

	for(int i = 0; i < TheObjects.size(); i++)
	{
		////////////////////////
		//Lets get object name
		////////////////////////
		TheObjects[i]->GetCurrentObjectType(ObjectName);

		switch(ObjectName)
		{
		case CAMTANK:
			CameraTruckUpdate(TheObjects[i]);
			break;

		case BULLET:
			//BulletUpdate(TheObjects[i]);
			break;
		}

	}

	CollisionDetection(TheObjects);
}

void PhysicsEngine::CameraTruckUpdate(GameObject* &TruckObject)
{
	float ObjectPosition[3];
	float ObjectVelocity = 0.0;
	float ObjectAngle;
	float ObjectAngularVelocity;

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
	if(CurrentCamera != NULL)
	{
		CurrentCamera->Move(-MoveX, -MoveY);
		CurrentCamera->SetObjectYaw(-ObjectAngle);
	}

}

void PhysicsEngine::BulletUpdate(GameObject* &BulletObject)
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

	vector<GameObject*> ToRemove;

	int i;
	for(i = 0; i < TheObjects.size(); i++)
	{
		TheObjects[i]->GetPosition(Position);

		if(Position[2] < -2)
		{
			ToRemove.push_back(TheObjects[i]);
		}
	}

	int j;


	for(i = 0; i < TheObjects.size(); i++)
	{
		for(j = i+1; j < TheObjects.size(); j++)
		{
			if(CheckForCollision(TheObjects[i], TheObjects[j]))
			{
				int temp = 1;
				//Respond to collision;
			}
		}
	}
	

	//////////////////////////////////////////////
	// Actually remove the objects from the game
	//////////////////////////////////////////////
	for(i = 0; i < ToRemove.size(); i++)
	{
		for(j = 0; ToRemove[i] != TheObjects[j]; j++);

		delete ToRemove[i];
		TheObjects.erase(TheObjects.begin()+j);
	}
}

bool PhysicsEngine::CheckForCollision(GameObject* ObjectOne, GameObject* ObjectTwo)
{
	float OneTop[3];
	float OneBottom[3];

	float TwoTop[3];
	float TwoBottom[3];

//	ObjectOne->GetObjectBoundingBox(OneTop, OneBottom);
//	ObjectTwo->GetObjectBoundingBox(TwoTop, TwoBottom);

	if(OneTop[0] > TwoBottom[0] || OneTop[1] > TwoBottom[1] || OneTop[2] < TwoBottom[2]
		|| TwoTop[0] > OneBottom[0] || TwoTop[1] > OneBottom[1] || TwoTop[2] < OneBottom[2])
		return false;
	else
		return true;
}