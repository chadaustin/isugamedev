#include "PhysicsEngine.h"
#include <math.h>
#include <gl/glut.h>

#define PI 3.1415926535

PhysicsEngine::PhysicsEngine()
{
	Stoptime = 0;
	Starttime = 0;
	dt = 0;

	CurrentCamera = NULL;
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
		}

	}
}

void PhysicsEngine::CameraTruckUpdate(GameObject* &TruckObject)
{
	float ObjectPosition[3];
	float ObjectVelocity = 0.0;
	float ObjectAngle;

	TruckObject->GetVelocity(ObjectVelocity);	
	ObjectVelocity *= dt;
	TruckObject->GetPosition(ObjectPosition);
	TruckObject->GetObjectAngle(ObjectAngle);

	float AngleInRadians = (ObjectAngle * PI)/180;

	float NewPosition[3];

	float MoveX = ObjectVelocity*cos(AngleInRadians);
	float MoveY = ObjectVelocity*sin(AngleInRadians);

	NewPosition[0] = ObjectPosition[0] + MoveX;
	NewPosition[1] = ObjectPosition[1] + MoveY;
	NewPosition[2] = ObjectPosition[2];

	TruckObject->SetPosition(NewPosition);

	//////////////////
	// Update Camera
	//////////////////
	if(CurrentCamera != NULL)
	{
		CurrentCamera->Move(-MoveX, -MoveY);

		CurrentCamera->SetYaw(-ObjectAngle);
	}

}