/////////////////////////////////////
// Copyright Levi VanOort 4-21-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// GameObject.h
/////////////////////////////////////

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "GraphicsObject.h"

enum ObjectType{CAMTANK = 0, BULLET};

class GameObject
{
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void GetGraphicsPointer(GraphicsObject*&) = 0;

	//////////////////////////////////
	// All the Common set functions
	//////////////////////////////////
	void SetSize(float Size[3])
	{
		for(int i = 0; i < 3; i++)
			ObjectSize[i] = Size[i];
	}
	void SetPosition(float Position[3])
	{
		for(int i = 0; i < 3; i++)
			ObjectPosition[i] = Position[i];
	}
	void SetCurrentObjectType(ObjectType TheType)
	{
		ObjectName = TheType;
	}
	void SetVelocity(float Velocity)
	{
		ObjectVelocity = Velocity;
	}	
   void SetAngularVelocity(float Angle)
   {
      ObjectAngleVelocity = Angle;
   }
	void SetObjectAngle(float Angle)
	{
		ObjectAngle = Angle;
	}
   void SetObjectZAngle(float Angle)
   {
      ObjectZAngle = Angle;
   }
   void SetVelocityZ(float Velocity)
   {
      ObjectVelocityZ = Velocity;
   }
	////////////////////////////////////


	//////////////////////////////////////
	// All the Common get functions
	//////////////////////////////////////
	void GetSize(float Size[3])
	{
		for(int i = 0;i < 3; i++)
			Size[i] = ObjectSize[i];
	}
	void GetPosition(float Position[3])
	{
		for(int i = 0; i < 3; i++)
			Position[i] = ObjectPosition[i];
	}
	void GetCurrentObjectType(ObjectType& TheType)
	{
		TheType = ObjectName;
	}
	void GetVelocity(float& Velocity)
	{
		Velocity = ObjectVelocity;
	}
   void GetAngularVelocity(float& Angle)
   {
      Angle = ObjectAngleVelocity;
   }
	void GetObjectAngle(float& Angle)
	{
		Angle = ObjectAngle;
	}
   void GetObjectZAngle(float& Angle)
   {
      Angle = ObjectAngle;
   }
   void GetVelocityZ(float& Velocity)
   {
      Velocity = ObjectVelocityZ;
   }
	/////////////////////////////////////////


protected:
	float ObjectSize[3];
	float ObjectPosition[3];
	float ObjectVelocity;
	float ObjectAngle;
	float ObjectAngleVelocity;
   float ObjectZAngle;
   float ObjectVelocityZ;
	ObjectType ObjectName;

};
#endif