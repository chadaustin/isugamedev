/////////////////////////////////////
// Copyright Levi VanOort 4-19-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// Camera.cpp
/////////////////////////////////////
#include "Camera.h"

Camera::Camera()
{
	MULTX = 0.5;
	MULTZ = 0.5;

	int i;

	MinMoveX = .01;
	MinMoveY = .01;

	DestX = 0;
	DestY = 0;

	for(i = 0; i < 3; i++)
	{
		MovementTranslations[i] = 0.0;
		CamDistance[i] = 0.0;
		CurrentRotates[i] = 0.0;
		LookAroundRotates[i] = 0.0;
	}
}

Camera::~Camera()
{
}


void Camera::SetDistanceFromObjectCenter(float Distance[3])
{
	for(int i = 0; i < 3; i++)
		CamDistance[i] = Distance[i];
}

void Camera::SetObjectPitch(float InDegrees)
{
	CurrentRotates[1] = InDegrees;
}

void Camera::SetObjectRoll(float InDegrees)
{
	CurrentRotates[0] = InDegrees;
}

void Camera::SetObjectYaw(float InDegrees)
{
	CurrentRotates[2] = InDegrees;
}

void Camera::SetPitch(float InDegrees)
{
   CamOrient[1] = InDegrees;
}

void Camera::SetRoll(float InDegrees)
{
   CamOrient[0] = InDegrees;
}

void Camera::SetYaw(float InDegrees)
{
   CamOrient[2] = InDegrees;
}

void Camera::SnapBack()
{
	for(int i = 0; i < 3; i++)
		LookAroundRotates[i] = 0.0;
}

void Camera::Move(float X, float Y)
{
   DestX += X;
   DestY += Y;
}

void Camera::RotateAroundObject(float InDegrees)
{
	CurrentRotates[2] += InDegrees;
}

void Camera::LookAround(int ChangeX, int ChangeY)
{
	LookAroundRotates[2] += ChangeX*MULTX;
	LookAroundRotates[1] += ChangeY*MULTZ;
}

void Camera::Apply()
{
	gluLookAt(-10.0, 0.0, 0.0,
		       0.0, 0.0, 0.0,
			    0.0, 0.0, 1.0);

	glTranslatef(-10.0, 0.0, 0.0);

	glRotatef(LookAroundRotates[0] + CamOrient[0], 1.0, 0.0, 0.0);
	glRotatef(LookAroundRotates[1] + CamOrient[1], 0.0, 1.0, 0.0);
	glRotatef(LookAroundRotates[2] + CamOrient[2], 0.0, 0.0, 1.0);

   glTranslatef(CamDistance[0], CamDistance[1], CamDistance[2]);

	glRotatef(CurrentRotates[0], 1.0, 0.0, 0.0);
	glRotatef(CurrentRotates[1], 0.0, 1.0, 0.0);
	glRotatef(CurrentRotates[2], 0.0, 0.0, 1.0);

	glTranslatef(MovementTranslations[0], MovementTranslations[1], MovementTranslations[2]);

}

void Camera::Update(int dt)
{
   float delta = (float)dt / 1000.0f;
   float DistX = DestX - MovementTranslations[0];
   float DistY = DestY - MovementTranslations[1];


   MovementTranslations[0] += DistX*3*delta;
   MovementTranslations[1] += DistY*3*delta;
}