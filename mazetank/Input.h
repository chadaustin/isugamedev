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

	void Update(vector<GameObject*> &TheObjects);

	void Turn(float Angles);

	void Accel(float Velocity);

	void LookAround(int ChangeX, int ChangeY);

	void TurretRotate(int ChangeX, int ChangeY);

	void SnapCamera();

	void ShootBullet();

   void Honk();
private:

   GameObject* Player1;
   Camera* ChaseCamera;

   float MULTX, MULTZ;
};
#endif

