/////////////////////////////////////
// Copyright Levi VanOort 5-1-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// WallObject.cpp
/////////////////////////////////////

#include <GL/glut.h>
#include <stdlib.h>
#include "WallObject.h"

WallObject::WallObject()
{
	this->SetCurrentObjectType(WALL);
	this->SetAngularVelocity(0.0);
	this->SetObjectAngle(0.0);

	this->SetObjectSphere(0.6);
   this->ResetCollisions();
}

WallObject::~WallObject()
{

}

void WallObject::Init()
{

}

void WallObject::GetGraphicsPointer(GraphicsObject *& TheGraphics)
{
	TheGraphics = NULL;
}

void WallObject::Draw()
{
	float Translate[3];
	float Rotate;

	this->GetPosition(Translate);
	this->GetObjectAngle(Rotate);

	glPushMatrix();

		glTranslatef(Translate[0], Translate[1], Translate[2]);	
		glRotatef(Rotate, 0.0, 0.0, 1.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);

		glutSolidCube(1.0);

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