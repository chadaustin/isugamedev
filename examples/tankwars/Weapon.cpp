// Weapon.cpp: implementation of the Weapon class.
//
//////////////////////////////////////////////////////////////////////

#include "Weapon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Weapon::Weapon()
{

}

Weapon::~Weapon()
{

}

void Weapon::initialize(GLfloat x, GLfloat z, GLfloat theta)
{
	angle = theta;

	theta = theta * 3.14159 / 180;

	x = x - 4.5 * cos(theta);
	z = z + 4.5 * sin(theta);

	xPos = x;
	zPos = z;

	return;
}

void Weapon::draw()
{
	glTranslatef(xPos, yPos, zPos);

	glRotatef(angle, 0.0, 1.0, 0.0);

	return;
}

void Weapon::move(GLint dir)
{

	GLfloat changeX, changeZ, angleRads;

	angleRads = angle * 3.14159 / 180;

	changeX = cos(angleRads) * speed;
	changeZ = sin(angleRads) * speed;

	xPos += dir * changeX;
	zPos -= dir * changeZ;

	return;
}