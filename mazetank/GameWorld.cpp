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
#include "SoundManager.h"
#include "SoundEffectManager.h"
#include "Jukebox.h"
#include "WallObject.h"
#include "FloorObject.h"
#include "BuildMaze.h"
#include "SkyDome.h"
#include "Explosion.h"

extern Input GameInput;
extern GLuint clouds[1];
sound::SoundManager* GameSound;
vector<Explosion> TheExplosions;

GameWorld::GameWorld()
{
 
}

GameWorld::~GameWorld()
{
	for(int i = 0; i < TheGameObjects.size(); i++)
		delete TheGameObjects[i];

	TheGameObjects.erase(TheGameObjects.begin(), TheGameObjects.end());

   delete GameSound;
}

void GameWorld::Init()
{
	GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	///////////////////////////////////////
	// Initilize player object
	///////////////////////////////////////
	Player1 = new TankObject;

	Player1->Init();
	Player1->SetObjectAngle(0.0);
	Player1->SetCurrentObjectType(CAMTANK);
	float Position[3] = {-80.0, -80.0, 0.0};
	Player1->SetPosition(Position);
	Player1->SetVelocity(0.0);
	TheGameObjects.push_back(Player1);
	///////////////////////////////////////

	//////////////////////////////////////
	// Initlize the Nonplayer Object
	///////////////////////////////////////
	GameObject* NonPlayer = new TankObject;

	NonPlayer->Init();
	NonPlayer->SetObjectAngle(0.0);
	NonPlayer->SetCurrentObjectType(NPCTANK);
	float Position2[3] = {80.0, 80.0, 0.0};
	NonPlayer->SetPosition(Position2);
	NonPlayer->SetVelocity(0.0);
	TheGameObjects.push_back(NonPlayer);
	///////////////////////////////////////

	//////////////////////////////////////
	// Initlize the Nonplayer2 Object
	//////////////////////////////////////
	GameObject* NonPlayer2 = new TankObject;

	NonPlayer2->Init();
	NonPlayer2->SetObjectAngle(0.0);
	NonPlayer2->SetCurrentObjectType(NPCTANK);
	float Position22[3] = {-80.0, 80.0, 0.0};
	NonPlayer2->SetPosition(Position22);
	NonPlayer2->SetVelocity(0.0);
	TheGameObjects.push_back(NonPlayer2);

	//////////////////////////////////////
	// Initlize the Nonplayer3 Object
	//////////////////////////////////////
	GameObject* NonPlayer3 = new TankObject;

	NonPlayer3->Init();
	NonPlayer3->SetObjectAngle(0.0);
	NonPlayer3->SetCurrentObjectType(NPCTANK);
	float Position23[3] = {80.0, -80.0, 0.0};
	NonPlayer3->SetPosition(Position23);
	NonPlayer3->SetVelocity(0.0);
	TheGameObjects.push_back(NonPlayer3);
	////////////////////////////////////////
	// Initilize the floor
	////////////////////////////////////////
	GameObject* Floor = new FloorObject;
	////////////////////////////////////////

	//////////////////////////////////////////
	// Initilize the chase camera
	/////////////////////////////////////////
	GameCamera = new Camera;
	float CamDist[3] = {10.0, 0.0, -4.0};
	GameCamera->SetDistanceFromObjectCenter(CamDist);
	GameCamera->SetPitch(-8.0);
	GameCamera->SetYaw(0.0);
	GameCamera->SetRoll(0.0);
	GameCamera->Move(80.0, 80.0);
	/////////////////////////////////////////

	/////////////////////////////////////////
	// Build the maze
	/////////////////////////////////////////
	BuildMaze(TheGameObjects);

	////////////////////////////////////////////
	// Generate the sky dome
	///////////////////////////////////////////
	GenerateDome(200.0f, 5.0f, 5.0f, 1.0f, 1.0f);


	/////////////////////////////////////////
	// Initialize the Game Input
	//////////////////////////////////////////
	GameInput.SetCamera(GameCamera);

   /////////////////////////////////////////
   //Initialize GameSound
   /////////////////////////////////////////
   GameSound = new sound::SoundManager;

   GameSound->getJukebox()->addTrack("music/BSide.ogg");
   GameSound->getJukebox()->play();

   GameSound->getSoundEffectManager()->playSound("music/entering1.wav");

   ///////////////////////////////////////////
   // Initialize Shadows
   ///////////////////////////////////////////
   GLfloat floorPlane[4] = {0.0, 0.0, 1.0, 0.0};
   MyShadows.SetFloorObject(Floor);
   int LightHandle = MyShadows.AddLight(light_position);

   MyShadows.SetTheGroundPlane(floorPlane);

   ////////////////////////////////////////////
   // Initialize AI
   ////////////////////////////////////////////
   AIEngine NPCAI, NPCAI2, NPCAI3;
   NPCAI.Init();
   NPCAI.SetNPCTank(NonPlayer);
   NPCAI.SetPlayer(Player1);
   TheNPCAI.push_back(NPCAI);

   NPCAI2.Init();
   NPCAI2.SetNPCTank(NonPlayer2);
   NPCAI2.SetPlayer(Player1);
   TheNPCAI.push_back(NPCAI2);

   NPCAI3.Init();
   NPCAI3.SetNPCTank(NonPlayer3);
   NPCAI3.SetPlayer(Player1);
   TheNPCAI.push_back(NPCAI3);
}

void GameWorld::Update(int dt)
{
   float TankPosition[3];
   float OldTankPosition[3];
   float TankAngle;

   //////////////////////////////////////////////
   // Update the sound engine and physics engine
   //////////////////////////////////////////////
   GameSound->getJukebox()->update();

   int i;
   for(i = 0; i < TheNPCAI.size(); i++)
		TheNPCAI[i].Update(TheGameObjects,dt);

   GamePhysics.Update(TheGameObjects, dt);
   GameInput.Update(TheGameObjects);
   ///////////////////////
   // update camera
   ///////////////////////
   Player1->GetPosition(TankPosition);
   Player1->GetOldPosition(OldTankPosition);
   Player1->GetObjectAngle(TankAngle);

   GameCamera->Move(OldTankPosition[0]-TankPosition[0], OldTankPosition[1]-TankPosition[1]);
   GameCamera->SetObjectYaw(-TankAngle);
   GameCamera->Update(dt);
   //////////////////////////////////////

   for(i = 0; i < TheExplosions.size(); i++)
   {
		if(TheExplosions[i].ToDelete())
			TheExplosions.erase(TheExplosions.begin()+i);
   }


}

void GameWorld::Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GameCamera->Apply();

	MyShadows.DrawShadows(TheGameObjects);

	//////////////////////////////////////////////
	// Enable Back Face culling and Draw all the
	// game objects
	//////////////////////////////////////////////
	glEnable(GL_CULL_FACE);
	int i;
	for(i = 0; i < TheGameObjects.size(); i++)
		TheGameObjects[i]->Draw();

	for(i = 0; i < TheExplosions.size(); i++)
		TheExplosions[i].Draw();

	////////////////////////////////////////////////////
	// Disable Back Face culling so we can actually see
	// the sky dome from the inside of it.
	////////////////////////////////////////////////////
	glDisable(GL_CULL_FACE);
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glTranslatef(0.0, 0.0, 60.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, clouds[0]);
		RenderSkyDome();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
	glPopMatrix();

   glutSwapBuffers();
}

void GameWorld::AddObjectToGame(GameObject* TheGameObject)
{
	TheGameObjects.push_back(TheGameObject);
}