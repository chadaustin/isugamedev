/////////////////////////////////////
// Copyright Levi VanOort 5-3-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// AIEngine.cpp
/////////////////////////////////////
#include "AIEngine.h"
#include <math.h>

#include <iostream>

using namespace std;

#define PI 3.141592653

void AIEngine::Init()
{
	MovingAroundBlock = false;
	FacingOpponent = false;
	Rotate = true;
}

void AIEngine::SetNPCTank(GameObject* NPCTank)
{
	ToControl = NPCTank;
}

void AIEngine::SetPlayer(GameObject* Player1)
{
	ToKill = Player1;
}

void AIEngine::Update(vector<GameObject*> &TheObjects, int dt)
{
	//Verify that the NPCTank is still in the game
	bool NPCAlive = false;
	bool PlayerAlive = false;

	int i = 0;

	while((!NPCAlive || !PlayerAlive) && i < TheObjects.size())
	{
		if(TheObjects[i] == ToControl)
			NPCAlive = true;
		if(TheObjects[i] == ToKill)
			PlayerAlive = true;
		i++;
	}

	/////////////////////////////////////////////////
	// If both player and non player are still alive 
	// lets figure out which way to head.
	/////////////////////////////////////////////////
	if(NPCAlive && PlayerAlive)
	{

		float PlayerPosition[3];
		float NPCPosition[3];
		float NPCPositionOld[3];
		float NPCVelocity;

		ToKill->GetPosition(PlayerPosition);
		ToControl->GetPosition(NPCPosition);
		ToControl->GetVelocity(NPCVelocity);
		ToControl->GetOldPosition(NPCPositionOld);

		float Dist = sqrt(pow(PlayerPosition[0]-NPCPosition[0],2)+
						  pow(PlayerPosition[1]-NPCPosition[1],2)+
						  pow(PlayerPosition[2]-NPCPosition[2],2));

		if(MovingAroundBlock)
		{
			if(Rotate)
			{
				ToControl->SetAngularVelocity(0.03);
				Rotate = false;
			}
			else
			{
				ToControl->SetVelocity(0.017);
				MovingAroundBlock = false;
				Rotate = true;
			}

		}
		else
		{

			if(NPCPosition[0] == NPCPositionOld[0] &&
			   NPCPosition[1] == NPCPositionOld[1] &&
			   NPCVelocity > 0.0)
			{
				// Tank is trying to move but it ran into something
				MovingAroundBlock = true;
			}
			else
			{

				RotateToFaceOpponent();
			
				if(FacingOpponent)
				{
					////////////////////////////////////////////////////
					// We are facing the opponent so lets drive forward
					////////////////////////////////////////////////////
					ToControl->SetAngularVelocity(0.0);
					ToControl->SetVelocity(0.017);
				
				}
			}
		}
	}
}

void AIEngine::RotateToFaceOpponent()
{
	////////////////////////////////////////////
	// Stop the Non player while be are rotating
	////////////////////////////////////////////
	ToControl->SetVelocity(0.0);	

	///////////////////////////////////////////////
	// Get Required info from each of the objects
	///////////////////////////////////////////////
	float PlayerPosition[3];
	ToKill->GetPosition(PlayerPosition);

	float NPCPosition[3];
	ToControl->GetPosition(NPCPosition);

	float NPCRotation;
	ToControl->GetObjectAngle(NPCRotation);
	///////////////////////////////////////////////

	/////////////////////////////////////////
	// Convert NPCRotation to a angle between 
	// 0 and 360
	/////////////////////////////////////////
	while(NPCRotation > 360)
		NPCRotation = NPCRotation - 360;

	while(NPCRotation < 0)
		NPCRotation = 360 - (NPCRotation*-1);

	double CurrentOrientationInRadians = (NPCRotation * PI)/180;

	float x = PlayerPosition[0] - NPCPosition[0];
	float y = PlayerPosition[1] - NPCPosition[1];

	////////////////////////////////////////////
	// Calculate which way we need to face to
	// be pointed towards our opponent
	////////////////////////////////////////////

	double PlayerAngleFromNPC;
	if(y < 0)
		PlayerAngleFromNPC = 4.71239 - tanh(x/y);

	else if(y > 0)
		PlayerAngleFromNPC = 1.5708 - tanh(x/y) ;
	else
		PlayerAngleFromNPC = 4.71239;

	if(CurrentOrientationInRadians - PlayerAngleFromNPC < 0.1 &&
		CurrentOrientationInRadians - PlayerAngleFromNPC > -0.1)
	{
		FacingOpponent = true;
	}
	else
	{
		FacingOpponent = false;
		////////////////////////////////////////////////
		// Find which way is the shortest way to rotate
		// to face opponent
		////////////////////////////////////////////////
		float clockwise = CurrentOrientationInRadians - PlayerAngleFromNPC;
		float counterclockwise = PlayerAngleFromNPC - CurrentOrientationInRadians;

		if(CurrentOrientationInRadians < PlayerAngleFromNPC)
		{
			if(2*PI+CurrentOrientationInRadians - PlayerAngleFromNPC < 
				PlayerAngleFromNPC - CurrentOrientationInRadians)
				ToControl->SetAngularVelocity(-0.03);
			else
				ToControl->SetAngularVelocity(0.03);
		}
		else
		{
			if(2*PI+PlayerAngleFromNPC - CurrentOrientationInRadians < 
				CurrentOrientationInRadians - PlayerAngleFromNPC)
				ToControl->SetAngularVelocity(0.03);
			else
				ToControl->SetAngularVelocity(-0.03);
		}
	}

}

