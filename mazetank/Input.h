/////////////////////////////////////
// Copyright Levi VanOort 4-23-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// Input.h
/////////////////////////////////////
#ifndef __INPUT_H__
#define __INPUT_H__

#include "GameObject.h"
#include "Camera.h"
#include <vector>

using namespace std;

class Input
{
public:

   Input();

   void SetCamera(Camera* TheCamera);

   void SetGameObjects(vector<GameObject*> TheGameObjects);

   void Turn(float Angles);

   void Accel(float Velocity);

   void LookAround(int X, int Y);

private:

   GameObject* Player1;
   Camera* ChaseCamera;
   int OldX, OldY;
};
#endif

