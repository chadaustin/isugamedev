//////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//				lvanoort@aol.com 
//
// MyObject.h
// 4-5-2002
//////////////////////////////////////////////////////
#ifndef __MYOBJECT_H__
#define __MYOBJECT_H__

enum ObjectName{FROG = 0, AUTO, LOG, LILY};
enum State{ALIVE = 0, COLLISION, LOGRIDING};

class MyObject

{
public:
   virtual ~MyObject() {}

	virtual void SetGameCoordinates(float x, float y) = 0;
	virtual void SetSize(float x, float y) = 0;
	virtual void SetState(State TheState) = 0;
	virtual void SetVelocityX(float Vel) = 0;
	virtual void SetVelocityY(float Vel) = 0;


	virtual void GetGameCoordinates(float& x, float& y) = 0;
	virtual void GetSize(float& x, float& y) = 0;
	virtual void GetState(State& TheState) = 0;
	virtual void GetVelocityX(float& Vel) = 0;
	virtual void GetVelocityY(float& Vel) = 0;
	virtual ObjectName GetObjectName() = 0;


	virtual bool Moved(float& x, float& y) = 0;

	virtual void CollisionResponse(MyObject* CollisionObject) = 0;
	virtual void Update()= 0;
	virtual void Draw()=0;
};

#endif


