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

	this->SetObjectSphere(0.2);
   this->ResetCollisions();
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


 /*  float radius;

   this->GetObjectSphere(radius);

	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(Translate[0], Translate[1], Translate[2]);
		glLineWidth(1.0);
		glDisable(GL_DEPTH);
		glDisable(GL_LIGHTING);

      glutSolidSphere(radius, 10, 10);
		glLineWidth(1.0);
		glEnable(GL_DEPTH);
		glEnable(GL_LIGHTING);
	glPopMatrix();*/
}