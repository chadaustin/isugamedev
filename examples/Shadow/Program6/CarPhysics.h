#ifndef __CARPHYSICS_H__
#define __CARPHYSICS_H__

#include "GameObject.h"
#include "Camera.h"
#include <math.h>

class CarPhysics
{
public:
	CarPhysics();

	~CarPhysics();

	void SetWheelbase(float TheWheelbase);

	void SetCarTires(GameObject* Tires);

	void SetVehicle(GameObject* TheVehicle);
	
	void SetAccel(float TheAccel);

	void IncrementAccel(float IncrementAmount);

	void IncrementWheelAngle(float IncrementAmount);

	void SetWheelAngle(float TheAngle);

	void AttachCamera(Camera* CameraToAttach);

	void DetachCamera();

	void Update();

private:
	GameObject* TheTruck, *TheTires;
	int dt, Starttime, Stoptime;
	float WheelAngle, Accel, OldVelocity, Velocity, Wheelbase, TruckAngle;
	Camera* TheCamera;
	bool CameraAttached;

};
#endif