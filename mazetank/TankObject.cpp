#include "TankObject.h"

TankObject::TankObject()
{
	Body = new TankGraphics;
	Turret = new TurretGraphics;

	this->SetCurrentObjectType(CAMTANK);
	this->SetAngularVelocity(0.0);
	this->SetObjectAngle(0.0);

	float Position[3];

	Position[0] = 3.0;
	Position[1] = 2.2;
	Position[2] = 1.9;

	this->SetObjectBoundingBox(Position);
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

	float size[3];
	this->GetObjectBoundingBox(size);

	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(Translate[0]-1.9, Translate[1]-1.1, Translate[2]-0.2);
		glLineWidth(1.0);
		glDisable(GL_DEPTH);
		glDisable(GL_LIGHTING);

		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(size[0], 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, size[1], 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, size[2]);
		glEnd();
		glLineWidth(1.0);
		glEnable(GL_DEPTH);
		glEnable(GL_LIGHTING);
	glPopMatrix();

}

