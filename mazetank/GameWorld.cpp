/////////////////////////////////////
// Copyright Levi VanOort 4-19-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// GameWorld.cpp
/////////////////////////////////////

#include "GameWorld.h"
#include "GameObject.h"
#include "TankObject.h"
#include "Camera.h"
#include "Input.h"
//#include "SoundManager.h"
//#include "SoundEffectManager.h"
//#include "Jukebox.h"
#include "WallObject.h"
#include "BuildMaze.h"

extern Input GameInput;
//sound::SoundManager* GameSound;

GameWorld::GameWorld()
{
 
}

GameWorld::~GameWorld()
{
	for(int i = 0; i < TheGameObjects.size(); i++)
		delete TheGameObjects[i];

	TheGameObjects.erase(TheGameObjects.begin(), TheGameObjects.end());

//   delete GameSound;
}

void GameWorld::Init()
{
   Player1 = new TankObject;

   Player1->Init();
   Player1->SetObjectAngle(0.0);
   Player1->SetCurrentObjectType(CAMTANK);
   float Position[3] = {0.0, 0.0, 0.0};
   Player1->SetPosition(Position);
   Player1->SetVelocity(0.0);
   TheGameObjects.push_back(Player1);

   GameObject* NonPlayer = new TankObject;

   NonPlayer->Init();
   NonPlayer->SetObjectAngle(0.0);
   NonPlayer->SetCurrentObjectType(NPCTANK);
   float Position2[3] = {40.0, 0.0, 0.0};
   NonPlayer->SetPosition(Position2);
   NonPlayer->SetVelocity(0.0);
   TheGameObjects.push_back(NonPlayer);

   GameCamera = new Camera;
   float CamDist[3] = {10.0, 0.0, -4.0};
   GameCamera->SetDistanceFromObjectCenter(CamDist);
   GameCamera->SetPitch(-8.0);
   GameCamera->SetYaw(0.0);
   GameCamera->SetRoll(0.0);

   BuildMaze(TheGameObjects);

   GamePhysics.SetCamera(GameCamera);
   TheFloor.Init();

   GameInput.SetCamera(GameCamera);
   GameInput.SetGameObjects(TheGameObjects);

   /////////////////////////////////////////
   //Initialize GameSound
   /////////////////////////////////////////
/*   GameSound = new sound::SoundManager;

   GameSound->getJukebox()->addTrack("music/BSide.ogg");
   GameSound->getJukebox()->play();

   GameSound->getSoundEffectManager()->playSound("music/entering1.wav");*/
}

void GameWorld::Update(int dt)
{
   float TankPosition[3];
   float OldTankPosition[3];
   float TankAngle;

//   GameSound->getJukebox()->update();
   GamePhysics.Update(TheGameObjects, dt);
   
   Player1->GetPosition(TankPosition);
   Player1->GetOldPosition(OldTankPosition);
   Player1->GetObjectAngle(TankAngle);

   // update camera
   GameCamera->Move(OldTankPosition[0]-TankPosition[0], OldTankPosition[1]-TankPosition[1]);
   GameCamera->SetObjectYaw(-TankAngle);
   GameCamera->Update(dt);

}

void GameWorld::Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GameCamera->Apply();

    TheFloor.Draw();

	for(int i = 0; i < TheGameObjects.size(); i++)
		TheGameObjects[i]->Draw();
 
   glutSwapBuffers();
}

void GameWorld::AddObjectToGame(GameObject* TheGameObject)
{
	TheGameObjects.push_back(TheGameObject);
}