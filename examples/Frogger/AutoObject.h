//////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//				lvanoort@aol.com 
//
// AutoObject.h
// 4-5-2002
//////////////////////////////////////////////////////
#ifndef __AUTOOBJECT_H__
#define __AUTOOBJECT_H__

#include "MyObject.h"

class AutoObject : public MyObject
{
public:
	AutoObject();
	~AutoObject();

	void SetGameCoordinates(float x, float y);
	void SetSize(float x, float y);
	void SetState(State TheState);
	void SetVelocityX(float Vel);
	void SetVelocityY(float Vel);

	void GetGameCoordinates(float& x, float& y);
	void GetSize(float& x, float& y);
	void GetState(State& TheState);
	void GetVelocityX(float& Vel);
	void GetVelocityY(float& Vel);
	ObjectName GetObjectName();

	///////////////////////////////////////////////////
    // Moved()
	///////////////////////////////////////////////////
	// Notes: If function returns true x and y contain 
	// distanced moved.
	///////////////////////////////////////////////////
	bool Moved(float&x, float&y);



	///////////////////////////////////////////////////
    // CollisionResponse()
	///////////////////////////////////////////////////
	// Notes: Function is responsible for responding
	// to Collision between self and CollisionObject
	///////////////////////////////////////////////////	
	void CollisionResponse(MyObject* CollisionObject);

	void Update();

	void Draw();

private:

	float GameX, GameY;
	float ObjectSizeX, ObjectSizeY;
	State ObjectState;
	float MoveX, MoveY;
	bool Move;
	ObjectName Name;
	float MoveDistanceX;
	float MoveDistanceY;
	float VelocityX;
	float VelocityY;
};

#endif