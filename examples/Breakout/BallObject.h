// Levi VanOort -- lvanoort@aol.com 2/4/2002

#ifndef __BALLOBJECT_H__
#define __BALLBJECT_H__

class BallObject: public MyObject
{
public:

	BallObject();
	virtual ~BallObject();

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
	float LastX, LastY;
	bool responded;
	float AngleCoefficient;
	bool SegmentIntersection(float X1, float Y1, 
							 float X2, float Y2,
							 float X3, float Y3, 
							 float X4, float Y4);
	void ReflectOffObject(MyObject* TheObject);

	State CurrentState;
	ObjectName TheObjectName;
	int StartStateTimer, KillerBalltime;

};
#endif
