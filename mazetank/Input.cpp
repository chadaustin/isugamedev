#include "Input.h"
#include "GraphicsObject.h"

Input::Input()
{

   MULTX = 0.5;
   MULTZ = 0.5;
}

void Input::SetCamera(Camera* TheCamera)
{
   ChaseCamera = TheCamera;
}

void Input::SetGameObjects(vector<GameObject*> TheGameObjects)
{
   ObjectType ObjectName;

   for(int i = 0; i < TheGameObjects.size(); i++)
   {
      TheGameObjects[i]->GetCurrentObjectType(ObjectName);
      
      if(ObjectName == CAMTANK)
         Player1 = TheGameObjects[i];
   }
}

void Input::Turn(float Angles)
{
   Player1->SetAngularVelocity(Angles);
}

void Input::Accel(float Velocity)
{
   Player1->SetVelocity(Velocity);
}

void Input::LookAround(int ChangeX, int ChangeY)
{
      ChaseCamera->LookAround(ChangeX, ChangeY);
}

void Input::SnapCamera()
{
	ChaseCamera->SnapBack();
}

void Input::TurretRotate(int ChangeX, int ChangeY)
{
	GraphicsObject* TurretPointer;
	Player1->GetGraphicsPointer(TurretPointer);

	float Rotate[3];
	TurretPointer->GetRotate(Rotate);

	Rotate[2] += -1*ChangeX*MULTX;
	Rotate[0] += -1*ChangeY*MULTZ;

	TurretPointer->SetRotate(Rotate);
 
}