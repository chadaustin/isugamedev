#include "TankObject.h"

TankObject::TankObject()
{
	Body = new TankGraphics;
	Turret = new TurretGraphics;

	this->SetCurrentObjectType(CAMTANK);
	this->SetAngularVelocity(0.0);
	this->SetObjectAngle(0.0);
}

TankObject::~TankObject()
{
	delete Body;
	delete Turret;
}

void TankObject::Init()
{
	Body->Init();
   Turret->Init();

}

void TankObject::GetGraphicsPointer(GraphicsObject *& TheGraphics)
{
   TheGraphics = Turret;
}

void TankObject::Draw()
{
	float Translate[3];
	float Rotate;

	this->GetPosition(Translate);
	this->GetObjectAngle(Rotate);

	glPushMatrix();

		glTranslatef(Translate[0], Translate[1], Translate[2]);	
		glRotatef(Rotate, 0.0, 0.0, 1.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);

		glScalef(2.0, 2.0, 2.0);
		Body->Draw();

		////////////////////////////////////
		// Translate Turret to proper spot
		////////////////////////////////////
		glTranslatef(0.0, 0.5, 0.5);      
		Turret->Draw();

	glPopMatrix();

}

