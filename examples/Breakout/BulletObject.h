// Levi VanOort -- lvanoort@aol.com 2/4/2002

#ifndef __BULLETUPOBJECT_H__
#define __BULLETPOBJECT_H__


class BulletObject: public MyObject
{
public:

	BulletObject();
	virtual ~BulletObject();

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


	void CollisionResponse(MyObject* CollisionObject);

	void Update();

	void Draw();

private:
	float GameX, GameY;
	float SizeX, SizeY;
	float VelocityX, VelocityY;

	State CurrentState;
	ObjectName TheObjectName;
	
};
#endif
