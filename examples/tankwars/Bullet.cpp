// Bullet.cpp: implementation of the Bullet class.
//
//////////////////////////////////////////////////////////////////////

#include "Bullet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Bullet::Bullet()
{
	xPos = 0;
	xPos = 0;
	yPos = 3.5;
	zPos = 0;
	angle = 0;
	speed = 1.5;
	extents = 0.25;

	next = NULL;

}

Bullet::~Bullet()
{
	delete next;
	//delete [] weaponTex;
}

void Bullet::draw()
{
	glTranslatef(xPos, yPos, zPos);

	glRotatef(angle, 0.0, 1.0, 0.0);
glBindTexture(GL_TEXTURE_2D, weaponTex[0]);
	glBegin(GL_QUADS);	// face in the z+ direction
		glNormal3f( 0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( -0.25, -0.25, 0.25);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.25, -0.25, 0.25);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.25, 0.25, 0.25);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( -0.25, 0.25, 0.25);
	glEnd();

	glBegin(GL_QUADS);	// face in x+ direction
		glNormal3f( 1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.25, -0.25, 0.25);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.25, -0.25, -0.25);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.25, 0.25, -0.25);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.25, 0.25, 0.25);
	glEnd();

	glBegin(GL_QUADS);	// face in the z- direction
		glNormal3f( 0.0, 0.0, -1.0);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.25, -0.25, -0.25);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( -0.25, -0.25, -0.25);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( -0.25, 0.25, -0.25);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.25, 0.25, -0.25);
	glEnd();

	glBegin(GL_QUADS);	// face in the y+ direction
		glNormal3f( 0.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.25, 0.25, 0.25);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.25, 0.25, -0.25);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( -0.25, 0.25, -0.25);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( -0.25, 0.25, 0.25);
	glEnd();

	glBegin(GL_QUADS);	// face in the y- direction
		glNormal3f( 0.0, -1.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.25, -0.25, 0.25);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.25, -0.25, -0.25);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( -0.25, -0.25, -0.25);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( -0.25, -0.25, 0.25);
	glEnd();

	glBegin(GL_TRIANGLES);	// z+ and x- direction
		glNormal3f(-1.0, 0.0, 5.0);
		glVertex3f(-0.25, -0.25, 0.25);
		glVertex3f(-0.25, 0.25, 0.25);
		glVertex3f(-1.5, 0, 0);
	glEnd();

	glBegin(GL_TRIANGLES);	// y+ and x- direction
		glNormal3f(-1.0, 5.0, 0.0);
		glVertex3f(-0.25, 0.25, 0.25);
		glVertex3f(-0.25, 0.25, -0.25);
		glVertex3f(-1.5, 0, 0);
	glEnd();

	glBegin(GL_TRIANGLES);	// z- and x- direction
		glNormal3f(-1.0, 0.0, -5.0);
		glVertex3f(-0.25, 0.25, -0.25);
		glVertex3f(-0.25, -0.25, 0.25);
		glVertex3f(-1.5, 0, 0);
	glEnd();

	glBegin(GL_TRIANGLES);	// y- and x- direction
		glNormal3f(-1.0, -5.0, 0.0);
		glVertex3f(-0.25, -0.25, -0.25);
		glVertex3f(-0.25, -0.25, 0.25);
		glVertex3f(-1.5, 0, 0);
	glEnd();

	return;
}