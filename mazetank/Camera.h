/////////////////////////////////////
// Copyright Levi VanOort 4-19-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// Camera.h
/////////////////////////////////////
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GL/glut.h>
#include <vector>

using namespace std;

class Camera
{
public:
	Camera();

	~Camera();

	///////////////////////////////////////////////////////
	// void SetDistanceFromObjectCenter(float Distance[3]);
	//////////////////////////////////////////////////////
	// Pre: None
	// Post: The Camera is set to a point x,y,z from object,
	// Notes:
	//
	///////////////////////////////////////////////////////
	void SetDistanceFromObjectCenter(float Distance[3]);

	////////////////////////////////////
	// void SetObjectPitch(float InDegrees);
	////////////////////////////////////
	// Pre: None
	// Post: Camera Pitch is set to given value
   //       around Object Center
	// Notes:
	////////////////////////////////////
	void SetObjectPitch(float InDegrees);

	////////////////////////////////////
	// void SetObjectYaw(float InDegrees)
	////////////////////////////////////
	// Pre: None
	// Post: Camera Yaw is set to given value
   //       around Object Center
	// Notes:
	//
	/////////////////////////////////////
	void SetObjectYaw(float InDegrees);

	/////////////////////////////////////
	// void SetObjectRoll(float InDegrees)
	/////////////////////////////////////
	// Pre: None
	// Post: Camera Roll is set to given value
   //       around Object Center
	// Notes:
	//
	/////////////////////////////////////
	void SetObjectRoll(float InDegrees);

	////////////////////////////////////
	// void SetPitch(float InDegrees);
	////////////////////////////////////
	// Pre: None
	// Post: Camera Pitch is set to given value
	// Notes:
	////////////////////////////////////
	void SetPitch(float InDegrees);

	////////////////////////////////////
	// void SetYaw(float InDegrees)
	////////////////////////////////////
	// Pre: None
	// Post: Camera Yaw is set to given value
	// Notes:
	//
	/////////////////////////////////////
	void SetYaw(float InDegrees);

	/////////////////////////////////////
	// void SetRoll(float InDegrees)
	/////////////////////////////////////
	// Pre: None
	// Post: Camera Roll is set to given value
	// Notes:
	//
	/////////////////////////////////////
	void SetRoll(float InDegrees);

	//////////////////////////////////////////
	// void SnapBack()
	//////////////////////////////////////////
	// Pre: Pitch, Yaw, and Roll have been set
	// Post: LookAround is set back to current
	//		 Pitch, Yaw, and Roll
	// Notes:
	//
	///////////////////////////////////////
	void SnapBack();

	////////////////////////////////////////
	// void Move(float X, float Y)
	////////////////////////////////////////
	// Pre: Distance From Object has been set
	// Post: Camera moves given X and Y
	// Notes:
	//
	////////////////////////////////////////
	void Move(float X, float Y);

	////////////////////////////////////////////
	// void RotateAroundObject(float InDegrees)
	////////////////////////////////////////////
	// Pre: Yaw has been set
	// Post: Yaw is updated by given value
	// Notes:
	//
	/////////////////////////////////////////////
	void RotateAroundObject(float InDegrees);

	////////////////////////////////////////////
	// void LookAround(int ChangeX, int ChangeY)
	////////////////////////////////////////////
	// Pre: Yaw and Pitch have been set
	// Post: Converts Change
	// Notes:
	//
	////////////////////////////////////////////
	void LookAround(int ChangeX, int ChangeY);

	///////////////////////////////////////////
	// void Apply()
	///////////////////////////////////////////
	// Pre: Yaw, Pitch and Roll have been set
	// Post: All camera translations and rotations
	//		 have been applied
	// Notes: Must been called every display
	//			cycle
	///////////////////////////////////////////
	void Apply();

   void Update(int dt);

private:
	float CamDistance[3];

	float CurrentRotates[3];
	float LookAroundRotates[3];

	float MovementTranslations[3];
   float CamOrient[3];

	float MULTX;
	float MULTZ;

   double MinMoveX, MinMoveY;
   double DestX, DestY;

};
#endif