#ifndef __MYOBJECT_H__
#define __MYOBJECT_H__

enum ObjectName{FROG = 0, AUTO, LOG, LILY};
enum State{ALIVE = 0, COLLISION, LOGRIDING};

class MyObject
{
public:
	virtual void SetGameCoordinates(int x, int y) = 0;
	virtual void SetSize(int x, int y) = 0;
	virtual void SetState(State TheState) = 0;
	virtual void SetVelocityX(int Vel) = 0;
	virtual void SetVelocityY(int Vel) = 0;

	virtual void GetGameCoordinates(int& x, int& y) = 0;
	virtual void GetSize(int& x, int& y) = 0;
	virtual void GetState(State& TheState) = 0;
	virtual void GetVelocityX(int& Vel) = 0;
	virtual void GetVelocityY(int& Vel) = 0;
	virtual ObjectName GetObjectName() = 0;

	virtual bool Moved(int& x, int& y) = 0;

	virtual void CollisionResponse(MyObject* CollisionObject) = 0;

	virtual void Update()= 0;

	virtual void Draw()=0;


};
#endif