#ifndef __FROGOBJECT_H__
#define __FROGOBJECT_H__

#include "MyObject.h"

// This was designed when maze was 2D array may need to change
// with update to RB tree implementation.


class FrogObject : public MyObject
{
public:
	FrogObject();
	~FrogObject();
	void SetGameCoordinates(int x, int y);
	void SetSize(int x, int y);
	void SetState(State TheState);
	void SetVelocityX(int Vel);
	void SetVelocityY(int Vel);

	void GetGameCoordinates(int& x, int& y);
	void GetSize(int& x, int& y);
	void GetState(State& TheState);
	void GetVelocityX(int& Vel);
	void GetVelocityY(int& Vel);
	ObjectName GetObjectName();

	///////////////////////////////////////////////////
    // Moved()
	///////////////////////////////////////////////////
	// Notes: If function returns true x and y contain 
	// distanced moved.
	///////////////////////////////////////////////////
	bool Moved(int&x, int&y);

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
	int GameX, GameY;
	int ObjectSizeX, ObjectSizeY;
	State ObjectState;
	int MoveX, MoveY;
	bool Move;
	int VelocityX;
	int VelocityY;
	ObjectName Name;
};

#endif