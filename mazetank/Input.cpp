#include "Input.h"

Input::Input()
{
   OldX = 0;
   OldY = 0;
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