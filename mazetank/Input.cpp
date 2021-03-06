/////////////////////////////////////
// Copyright Levi VanOort 4-19-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// Input.h
/////////////////////////////////////

#include "Input.h"
#include "GraphicsObject.h"
#include "GameObject.h"
#include "BulletObject.h"
#include "SoundManager.h"
#include "GameWorld.h"
#include <math.h>

extern sound::SoundManager* GameSound;
extern GameWorld MazeTank;

Input::Input()
{

   MULTX = 0.3;
   MULTZ = 0.2;
}

void Input::SetCamera(Camera* TheCamera)
{
   ChaseCamera = TheCamera;
}

void Input::Update(vector<GameObject*> &TheObjects)
{
	ObjectType ObjectName;
	bool Found = false;

	int i = 0;
   while(i < TheObjects.size() && !Found)
   {
		TheObjects[i]->GetCurrentObjectType(ObjectName);
		if(ObjectName == CAMTANK)
		{
			Player1 = TheObjects[i];
			Found = true;
		}
		i++;
   }

   if(!Found)
	   Player1 = NULL;
}

void Input::Turn(float Angles)
{
	if(Player1 != NULL)
		Player1->SetAngularVelocity(Angles);
}

void Input::Accel(float Velocity)
{
	if(Player1 != NULL)
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
	if(Player1 != NULL)
	{
		GraphicsObject* TurretPointer;
		Player1->GetGraphicsPointer(TurretPointer);

		float Rotate[3];
		TurretPointer->GetRotate(Rotate);


		Rotate[0] += -1*ChangeY*MULTZ;
		Rotate[2] += -1*ChangeX*MULTX;
		////////////////////////////////////////////////////
		// If we get beyond turret rotate values clamp them
		// to the ends
		////////////////////////////////////////////////////
		if(Rotate[0] < -70)
			Rotate[0] = -70;

		if(Rotate[0] > -1)
			Rotate[0] = -1;

		TurretPointer->SetRotate(Rotate); 
	}
   
}

void Input::ShootBullet()
{	

	if(Player1 != NULL)
	{
		float TankRotation;
		float TurretRotations[3];
		GameObject* Bullet = new BulletObject;

		Bullet->SetCurrentObjectType(PLAYERBULLET);

		GraphicsObject* TheTurret;

		Player1->GetObjectAngle(TankRotation);
		Player1->GetGraphicsPointer(TheTurret);

		TheTurret->GetRotate(TurretRotations);

		/////////////////////////////////////////////////////////
		//Calculate the angle that the bullet should take off at
		/////////////////////////////////////////////////////////
		float Position[3];

		Player1->GetPosition(Position);

		Position[2] = 1.5;

		Bullet->SetPosition(Position);
		Bullet->SetObjectAngle(TankRotation+TurretRotations[2]);
		Bullet->SetObjectZAngle(TurretRotations[0]);
		Bullet->SetVelocityZ(0.04);
		/////////////////////////////////////////////////////////
		Bullet->SetVelocity(0.03);

		MazeTank.AddObjectToGame(Bullet);
		GameSound->getSoundEffectManager()->playSound("music/EXP2.WAV");
	}
   
}

void Input::Honk()
{
 //  GameSound->getSoundEffectManager()->playSound("music/car2.wav");
}