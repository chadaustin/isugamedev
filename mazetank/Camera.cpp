#include "Camera.h"

Camera::Camera()
{
	MULTX = 2.0;
	MULTZ = 2.0;

	for(int i = 0; i < 3; i++)
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
	MovementTranslations[0] += X;
	MovementTranslations[1] += Y;
}

void Camera::RotateAroundObject(float InDegrees)
{
	CurrentRotates[2] += InDegrees;
}

void Camera::LookAround(int ChangeX, int ChangeY)
{
	LookAroundRotates[1] += ChangeX*MULTX;
	LookAroundRotates[2] += ChangeY*MULTZ;
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
