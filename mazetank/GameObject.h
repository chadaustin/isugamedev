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
#include <vector>

enum ObjectType{CAMTANK = 0, BULLET, NPCTANK, WALL};

class GameObject
{
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void GetGraphicsPointer(GraphicsObject*&) = 0;

	//////////////////////////////////
	// All the Common set functions
	//////////////////////////////////
	void SetPosition(float Position[3])
	{
		for(int i = 0; i < 3; i++)
      {
         ObjectOldPosition[i] = ObjectPosition[i];
			ObjectPosition[i] = Position[i];
      }
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
   void SetObjectSphere(float Radius)
   {
      ObjectSphere = Radius;
   }
	////////////////////////////////////


	//////////////////////////////////////
	// All the Common get functions
	//////////////////////////////////////
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
      Angle = ObjectZAngle;
   }
   void GetVelocityZ(float& Velocity)
   {
      Velocity = ObjectVelocityZ;
   }
   void GetObjectSphere(float& Radius)
   {
      Radius = ObjectSphere;
   }
   void GetOldPosition(float OldPosition[3])
   {
      for(int i = 0; i < 3; i++)
         OldPosition[i] = ObjectOldPosition[i];
   }
	/////////////////////////////////////////

   ////////////////////////////////////////////////
   // Common Functions used for collision detection
   ////////////////////////////////////////////////
   void AddCollision(GameObject* &CollidedObject)
   {
      TheCollisions.push_back(CollidedObject);
      ACollision = true;
   }

   void ResetCollisions()
   {
      TheCollisions.clear();
      ACollision = false;
   }

   void AddCollision()
   {
      ACollision = true;
   }

   void GetCollisions(std::vector<GameObject*> &Collisions)
   {
      for(int i = 0; i < TheCollisions.size(); i++)
         Collisions.push_back(TheCollisions[i]);
   }

   bool IsCollision()
   {
      return ACollision;
   }
   //////////////////////////////////////////////////
protected:
	float ObjectPosition[3];
   float ObjectOldPosition[3];
	float ObjectVelocity;
	float ObjectAngle;
	float ObjectAngleVelocity;
   float ObjectZAngle;
   float ObjectVelocityZ;
	float ObjectBox[3];
   float ObjectSphere;
	ObjectType ObjectName;
   bool ACollision;

   std::vector<GameObject*> TheCollisions;

};
#endif