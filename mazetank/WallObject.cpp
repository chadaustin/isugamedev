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

	ambient[0] = 0.2;
	ambient[1] = 0.2;
	ambient[2] = 0.2;
	ambient[3] = 1.0;

	diffuse[0] = 0.63;
	diffuse[1] = 0.65;
	diffuse[2] = 0.73;
	diffuse[3] = 1.0;

	specular[0] = 0.0;
	specular[1] = 0.0;
	specular[2] = 0.0;
	specular[3] = 1.0;

	shininess = 40.0;

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

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);

		glTranslatef(Translate[0], Translate[1], Translate[2]);	
		glRotatef(Rotate, 0.0, 0.0, 1.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);

		glutSolidCube(1.0);

	glPopMatrix();

}