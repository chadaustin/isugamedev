/////////////////////////////////////
// Copyright Levi VanOort 4-19-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// BulletObject.cpp
/////////////////////////////////////

#include <GL/glut.h>
#include <stdlib.h>
#include "BulletObject.h"

BulletObject::BulletObject()
{
	this->SetCurrentObjectType(BULLET);
	this->SetAngularVelocity(0.0);
	this->SetObjectAngle(0.0);
}

BulletObject::~BulletObject()
{

}

void BulletObject::Init()
{

}

void BulletObject::GetGraphicsPointer(GraphicsObject *& TheGraphics)
{
	TheGraphics = NULL;
}

void BulletObject::Draw()
{
	float Translate[3];
	float Rotate;

	this->GetPosition(Translate);
	this->GetObjectAngle(Rotate);

	glPushMatrix();

		glTranslatef(Translate[0], Translate[1], Translate[2]);	
		glRotatef(Rotate, 0.0, 0.0, 1.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);

		glScalef(0.2, 0.2, 0.2);

		glutSolidSphere(1.0, 10, 10);

	glPopMatrix();
}