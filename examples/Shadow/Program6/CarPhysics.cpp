#include "CarPhysics.h"

CarPhysics::CarPhysics()
{
	dt = 0;
	Starttime = glutGet(GLUT_ELAPSED_TIME);
	Stoptime = 0;
	WheelAngle = 0.0;
	Wheelbase = 0.0;

	Accel = 0;
	OldVelocity = 0.0;
	Velocity =0.0;

	TruckAngle = 0.0;
	CameraAttached = false;
}

CarPhysics::~CarPhysics()
{	}

void CarPhysics::SetWheelbase(float TheWheelbase)
{	Wheelbase = TheWheelbase; }

void CarPhysics::SetVehicle(GameObject* TheVehicle)
{	TheTruck = TheVehicle; }

void CarPhysics::SetCarTires(GameObject* Tires)
{	TheTires = Tires;}
	
void CarPhysics::SetAccel(float TheAccel)
{	Accel = TheAccel; }

void CarPhysics::IncrementAccel(float IncrementAmount)
{	Accel += IncrementAmount; }

void CarPhysics::IncrementWheelAngle(float IncrementAmount)
{	
	WheelAngle += IncrementAmount; 
	TheTruck->wheelturn = WheelAngle;
}

void CarPhysics::SetWheelAngle(float TheAngle)
{	WheelAngle = TheAngle; }

void CarPhysics::AttachCamera(Camera* CameraToAttach)
{	
	TheCamera = CameraToAttach;
	CameraAttached = true;
}

void CarPhysics::DetachCamera()
{
	TheCamera = NULL;
	CameraAttached = false;
}

void CarPhysics::Update()
{
	double pi = 3.1415926535;
	///////////////////////////////////////////
	// Timer used to move objects so
	// game will be same speed on all machines
	///////////////////////////////////////////
	Stoptime = glutGet(GLUT_ELAPSED_TIME);
	dt = Stoptime - Starttime;
	Starttime = glutGet(GLUT_ELAPSED_TIME);

	if(dt > 50)
		dt = 50;

	Velocity = Accel * dt + OldVelocity;
	if(Accel != 0.0)
		Accel = 0.0;
	OldVelocity = Velocity;

	double AngleInRadians = (WheelAngle * pi)/180;
	double TheRadius;
	double TurnAngle;

	if(AngleInRadians == 0.0)
	{
		AngleInRadians = 0.0001;
	}
	TheRadius = Wheelbase/sin(AngleInRadians);
	TurnAngle = (Velocity * dt)/TheRadius;

	//Find Old Position in terms of new turn radius
	double OldX = TheRadius*sin(TruckAngle);
	double OldY = TheRadius*cos(TruckAngle);

	TruckAngle += TurnAngle;

	//Find New Truck Position 
	double NewX = TheRadius*sin(TruckAngle);
	double NewY = TheRadius*cos(TruckAngle);

	//Translate truck to new position
	TheTruck->translate[0] += (NewX-OldX);
	TheTruck->translate[1] += (NewY-OldY);

	/////////////////////////////////////
	//Update rotation of truck
	//Convert to degrees
	/////////////////////////////////////
	double TheDegrees = (180.0*TruckAngle)/pi;
	if(TheDegrees > 360)
		TheDegrees = TheDegrees - 360;
	if(TheDegrees < 0)
		TheDegrees = 360 + TheDegrees;

	TheTruck->ZRotate(-TheDegrees);

	if(CameraAttached)
	{
		TheCamera->XTrans(-1*(NewX-OldX));
		TheCamera->YTrans(-1*(NewY-OldY));
	}

	/////////////////////////////////////////////
	// Code to make tire revolve at correct speed
	/////////////////////////////////////////////
	float WheelTurnAngle = (Velocity * dt)/0.25;
	double WheelDegrees = (180.0*WheelTurnAngle)/pi;
	if(WheelDegrees > 360)
		WheelDegrees = WheelDegrees - 360;
	if(WheelDegrees < 0)
		WheelDegrees = 360 + WheelDegrees;

	TheTires->TireRotate += WheelDegrees;
	//////////////////////////////////////////////
}
