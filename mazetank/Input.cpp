#include "Input.h"
#include "GraphicsObject.h"

Input::Input()
{
   OldX = 0;
   OldY = 0;

   TurretOldX = 0;
   TurretOldY = 0;

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

void Input::LookAround(int X, int Y)
{
   int ChangeX = X - OldX;
   int ChangeY = Y - OldY;

   if(!(OldX == 0 && OldY == 0))
      ChaseCamera->LookAround(ChangeX, ChangeY);

   OldX = X;
   OldY = Y;

}

void Input::TurretRotate(int X, int Y)
{
   GraphicsObject* TurretPointer;
   Player1->GetGraphicsPointer(TurretPointer);
   
   int ChangeX = X - TurretOldX;
   int Changey = Y - TurretOldY;

   float Rotate[3];
   TurretPointer->GetRotate(Rotate);

   if(!(TurretOldX == 0 && TurretOldY == 0))
   {
      Rotate[2] = X*MULTX;
      Rotate[0] = Y*MULTZ;

      TurretPointer->SetRotate(Rotate);
   }

   TurretOldX = X;
   TurretOldY = Y;
}