#include "GameWorld.h"
#include "GameObject.h"
#include "TankObject.h"
#include "Camera.h"
#include "Input.h"
#include "SoundManager.h"
#include "SoundEffectManager.h"
#include "Jukebox.h"

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
   GameObject* Player1 = new TankObject;

   Player1->Init();
   Player1->SetObjectAngle(0.0);
   Player1->SetCurrentObjectType(CAMTANK);
   float Position[3] = {0.0, 0.0, 0.0};
   Player1->SetPosition(Position);
   Player1->SetVelocity(0.0);
   TheGameObjects.push_back(Player1);

   GameCamera = new Camera;
   float CamDist[3] = {10.0, 0.0, -4.0};
   GameCamera->SetDistanceFromObjectCenter(CamDist);
   GameCamera->SetPitch(-8.0);
   GameCamera->SetYaw(0.0);
   GameCamera->SetRoll(0.0);

   GamePhysics.SetCamera(GameCamera);
   TheFloor.Init();

   GameInput.SetCamera(GameCamera);
   GameInput.SetGameObjects(TheGameObjects);

   /////////////////////////////////////////
   //Initialize GameSound
   /////////////////////////////////////////
//   GameSound = new sound::SoundManager;

//   GameSound->getJukebox()->addTrack("music/track1.ogg");
//   GameSound->getJukebox()->play();
}

void GameWorld::Update()
{
//   GameSound->getJukebox()->update();
   GamePhysics.Update(TheGameObjects);
}

void GameWorld::Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GameCamera->Apply();

	for(int i = 0; i < TheGameObjects.size(); i++)
		TheGameObjects[i]->Draw();

   TheFloor.Draw();
   
   glutSwapBuffers();
}

void GameWorld::AddObjectToGame(GameObject* TheGameObject)
{
	TheGameObjects.push_back(TheGameObject);
}