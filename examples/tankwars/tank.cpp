// tank.cpp: implementation of the tank class.
//
//////////////////////////////////////////////////////////////////////

#include "tank.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Tank::Tank(GLfloat x, GLfloat y, GLfloat z, GLfloat angleIn)
{
	xPos = x;
	yPos = y;
	zPos = z;
	speed = 0.3f;
	shotsLeft = 10;
	alive = true;
	hitPoints = 1;
	angle = angleIn;
	rotateSpeed = 2.2f;
	extents = 3.0;

}

Tank::~Tank()
{
	//delete [] treadTex;

}

void Tank::draw()
{

	glTranslatef(xPos, yPos, zPos);
	
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

// main body
glBindTexture(GL_TEXTURE_2D, treadTex[4]);
	glBegin(GL_QUADS);	// ass
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(3.0f, 1.0f, -2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(3.0f, 1.0f, 2.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(3.0f, 3.0f, 2.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(3.0f, 3.0f, -2.0f);
	glEnd();

	glBegin(GL_QUADS);	// front
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-3.0f, 1.0f, -2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-3.0f, 1.0f, 2.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-3.0f, 2.3f, 2.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-3.0f, 2.3f, -2.0f);
	glEnd();

	glBegin(GL_QUADS);	// top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(3.0f, 3.0f, -2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(3.0f, 3.0f, 2.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, 3.0f, 2.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 3.0f, -2.0f);
	glEnd();
glBindTexture(GL_TEXTURE_2D, treadTex[3]);
	glBegin(GL_QUADS);	// front panel
		glNormal3f( -4.0f, 8.0f, 0.0f );
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, 3.0f, 2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, 3.0f, -2.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-3.0f, 2.3f, -2.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-3.0f, 2.3f, 2.0f);
	glEnd();

glBindTexture(GL_TEXTURE_2D, treadTex[4]);
	glBegin(GL_POLYGON);	// right side
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-3.0f, 1.0f, -2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(3.0f, 1.0f, -2.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(3.0f, 3.0f, -2.0f);
		glTexCoord2f(0.5f, 1.0f);	glVertex3f(-1.0f, 3.0f, -2.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f(-3.0f, 2.3f, -2.0f);
	glEnd();

	glBegin(GL_POLYGON);	// left side
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-3.0f, 1.0f, 2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(3.0f, 1.0f, 2.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(3.0f, 3.0f, 2.0f);
		glTexCoord2f(0.5f, 1.0f);	glVertex3f(-1.0f, 3.0f, 2.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f(-3.0f, 2.3f, 2.0f);
	glEnd();

// Turret Box
glBindTexture(GL_TEXTURE_2D, treadTex[5]);
	glBegin(GL_QUADS); //front
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 3.0f, -1.5f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-0.5f, 3.0f, 1.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-0.5f, 4.0f, 1.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-0.5f, 4.0f, -1.5f);
	glEnd();

	glBegin(GL_QUADS); //ass
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(2.5f, 3.0f, -1.5f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.5f, 3.0f, 1.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.5f, 4.0f, 1.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(2.5f, 4.0f, -1.5f);
	glEnd();
glBindTexture(GL_TEXTURE_2D, treadTex[6]);
	glBegin(GL_QUADS); //top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 4.0f, -1.5f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-0.5f, 4.0f, 1.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.5f, 4.0f, 1.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(2.5f, 4.0f, -1.5f);
	glEnd();

glBindTexture(GL_TEXTURE_2D, treadTex[5]);
	glBegin(GL_QUADS); //left
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 3.0f, -1.5f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.5f, 3.0f, -1.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.5f, 4.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-0.5f, 4.0f, -1.5f);
	glEnd();

	glBegin(GL_QUADS); //right
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 3.0f, 1.5f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.5f, 3.0f, 1.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.5f, 4.0f, 1.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-0.5f, 4.0f, 1.5f);
	glEnd();

//Gun Barrel
glBindTexture(GL_TEXTURE_2D, treadTex[7]);	
	glBegin(GL_QUADS); //top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.5f, 0.0f);	glVertex3f(-0.5f, 3.8f, -0.2f);
		glTexCoord2f(0.625f, 0.0f);	glVertex3f(-0.5f, 3.8f, 0.2f);
		glTexCoord2f(0.625f, 1.0f);	glVertex3f(-4.5f, 3.8f, 0.2f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.5f, 3.8f, -0.2f);
	glEnd();

	glBegin(GL_QUADS); //bottom
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.325f, 0.0f);	glVertex3f(-0.5f, 3.2f, -0.2f);
		glTexCoord2f(0.5f, 0.0f);	glVertex3f(-0.5f, 3.2f, 0.2f);
		glTexCoord2f(0.5f, 1.0f);	glVertex3f(-4.5f, 3.2f, 0.2f);
		glTexCoord2f(0.375f, 1.0f);	glVertex3f(-4.5f, 3.2f, -0.2f);
	glEnd();

	glBegin(GL_QUADS); //left
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 3.3f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-0.5f, 3.7f, -0.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-4.5f, 3.7f, -0.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.5f, 3.3f, -0.5f);
	glEnd();

	glBegin(GL_QUADS); //right
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 3.3f, 0.5f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-0.5f, 3.7f, 0.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-4.5f, 3.7f, 0.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.5f, 3.3f, 0.5f);
	glEnd();

	glBegin(GL_QUADS);	// right/top
		glNormal3f(0.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-0.5f, 3.8f, -0.2f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-4.5f, 3.8f, -0.2f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.5f, 3.7f, -0.5f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 3.7f, -0.5f);
	glEnd();

	glBegin(GL_QUADS);	//right/bottom
		glNormal3f(0.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-0.5f, 3.2f, -0.2f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-4.5f, 3.2f, -0.2f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.5f, 3.3f, -0.5f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 3.3f, -0.5f);
	glEnd();

	glBegin(GL_QUADS);	//left/top
		glNormal3f(0.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-0.5f, 3.8f, 0.2f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-4.5f, 3.8f, 0.2f);		
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.5f, 3.7f, 0.5f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 3.7f, 0.5f);
	glEnd();

	glBegin(GL_QUADS);	// left/bottom
		glNormal3f(0.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-0.5f, 3.2f, 0.2f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-4.5f, 3.2f, 0.2f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.5f, 3.3f, 0.5f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 3.3f, 0.5f);
	glEnd();
glBindTexture(GL_TEXTURE_2D, treadTex[8]);
	glBegin(GL_POLYGON);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.3f, 0.0f);	glVertex3f(-4.5f, 3.2f, -0.2f);	
		glTexCoord2f(0.7f, 0.0f);	glVertex3f(-4.5f, 3.2f, 0.2f);
		glTexCoord2f(1.0f, 0.3f);	glVertex3f(-4.5f, 3.3f, 0.5f);	
		glTexCoord2f(1.0f, 0.7f);	glVertex3f(-4.5f, 3.7f, 0.5f);	
		glTexCoord2f(0.7f, 1.0f);	glVertex3f(-4.5f, 3.8f, 0.2f);	
		glTexCoord2f(0.3f, 1.0f);	glVertex3f(-4.5f, 3.8f, -0.2f);	
		glTexCoord2f(0.0f, 0.7f);	glVertex3f(-4.5f, 3.7f, -0.5f);
		glTexCoord2f(0.0f, 0.3f);	glVertex3f(-4.5f, 3.3f, -0.5f);
	glEnd();

// Left Tread
glBindTexture(GL_TEXTURE_2D, treadTex[9]);
	glBegin(GL_QUADS);	// top
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.7f, 1.0f);	glVertex3f(-3.5f, 1.8f, 2.0f);
		glTexCoord2f(0.7f, 0.0f);	glVertex3f(3.5f, 1.8f, 2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(3.5f, 1.8f, 3.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-3.5f, 1.8f, 3.5f);
	glEnd();

	glBegin(GL_QUADS);	// front top slant
		glNormal3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.7f, 0.0f);	glVertex3f(-3.5f, 1.8f, 2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-3.5f, 1.8f, 3.5f);
		glTexCoord2f(1.0f, 0.2f);	glVertex3f(-4.0f, 1.3f, 3.5f);
		glTexCoord2f(0.7f, 0.2f);	glVertex3f(-4.0f, 1.3f, 2.0f);
	glEnd();

	glBegin(GL_QUADS);	// back top slant
		glNormal3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.7f, 0.0f);	glVertex3f(3.5f, 1.8f, 2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(3.5f, 1.8f, 3.5f);
		glTexCoord2f(1.0f, 0.2f);	glVertex3f(4.0f, 1.3f, 3.5f);
		glTexCoord2f(0.7f, 0.2f);	glVertex3f(4.0f, 1.3f, 2.0f);
	glEnd();
	
	glBegin(GL_QUADS);	// front
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.3f, 1.0f);	glVertex3f(-4.0f, 1.3f, 3.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.0f, 1.3f, 2.0f);
		glTexCoord2f(0.0f, 0.8f);	glVertex3f(-4.0f, 0.8f, 2.0f);
		glTexCoord2f(0.3f, 0.8f);	glVertex3f(-4.0f, 0.8f, 3.5f);
	glEnd();

	glBegin(GL_QUADS);	// front bottom slant
		glNormal3f(-1.2f, -0.75f, 0.0f);
		glTexCoord2f(0.0f, 0.2f);	glVertex3f(-4.0f, 0.8f, 2.0f);
		glTexCoord2f(0.3f, 0.2f);	glVertex3f(-4.0f, 0.8f, 3.5f);
		glTexCoord2f(0.3f, 0.6f);	glVertex3f(-3.5f, 0.0f, 3.5f);
		glTexCoord2f(0.0f, 0.6f);	glVertex3f(-3.5f, 0.0f, 2.0f);
	glEnd();

	glBegin(GL_QUADS);	// back
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.3f, 1.0f);	glVertex3f(4.0f, 1.3f, 3.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(4.0f, 1.3f, 2.0f);
		glTexCoord2f(0.0f, 0.8f);	glVertex3f(4.0f, 0.8f, 2.0f);
		glTexCoord2f(0.3f, 0.8f);	glVertex3f(4.0f, 0.8f, 3.5f);
	glEnd();

	glBegin(GL_QUADS);	// rear bottom slant
		glNormal3f(1.2f, -0.75f, 0.0f);
		glTexCoord2f(0.0f, 0.2f);	glVertex3f(4.0f, 0.8f, 2.0f);
		glTexCoord2f(0.3f, 0.2f);	glVertex3f(4.0f, 0.8f, 3.5f);
		glTexCoord2f(0.3f, 0.6f);	glVertex3f(3.5f, 0.0f, 3.5f);
		glTexCoord2f(0.0f, 0.6f);	glVertex3f(3.5f, 0.0f, 2.0f);
	glEnd();
glBindTexture(GL_TEXTURE_2D, treadTex[10]);
	glBegin(GL_POLYGON); // outside 
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.1f, 0.0f);	glVertex3f(-3.5f, 0.0f, 3.5f);
		glTexCoord2f(0.9f, 0.0f);	glVertex3f(3.5f, 0.0f, 3.5f);
		glTexCoord2f(1.0f, 0.1f);	glVertex3f(4.0f, 0.8f, 3.5f);
		glTexCoord2f(1.0f, 0.2f);	glVertex3f(4.0f, 1.3f, 3.5f);
		glTexCoord2f(0.9f, 0.3f);	glVertex3f(3.5f, 1.8f, 3.5f);
		glTexCoord2f(0.1f, 0.3f);	glVertex3f(-3.5f, 1.8f, 3.5f);
		glTexCoord2f(0.0f, 0.2f);	glVertex3f(-4.0f, 1.3f, 3.5f);
		glTexCoord2f(0.0f, 0.1f);	glVertex3f(-4.0f, 0.8f, 3.5f);
	glEnd();

	glBegin(GL_POLYGON); // inside 
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.1f, 0.0f);	glVertex3f(-3.5f, 0.0f, 2.0f);
		glTexCoord2f(0.9f, 0.0f);	glVertex3f(3.5f, 0.0f, 2.0f);
		glTexCoord2f(1.0f, 0.1f);	glVertex3f(4.0f, 0.8f, 2.0f);
		glTexCoord2f(1.0f, 0.2f);	glVertex3f(4.0f, 1.3f, 2.0f);
		glTexCoord2f(0.9f, 0.3f);	glVertex3f(3.5f, 1.8f, 2.0f);
		glTexCoord2f(0.1f, 0.3f);	glVertex3f(-3.5f, 1.8f, 2.0f);
		glTexCoord2f(0.0f, 0.2f);	glVertex3f(-4.0f, 1.3f, 2.0f);
		glTexCoord2f(0.0f, 0.1f);	glVertex3f(-4.0f, 0.8f, 2.0f);
	 glEnd();


//Right Tread
glBindTexture(GL_TEXTURE_2D, treadTex[9]);
	glBegin(GL_QUADS);	// top
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-3.5f, 1.8f, -3.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(3.5f, 1.8f, -3.5f);
		glTexCoord2f(0.7f, 1.0f);	glVertex3f(3.5f, 1.8f, -2.0f);
		glTexCoord2f(0.7f, 0.0f);	glVertex3f(-3.5f, 1.8f, -2.0f);
	glEnd();

	glBegin(GL_QUADS);	// front top slant
		glNormal3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.2f);	glVertex3f(-3.5f, 1.8f, -3.5f);
		glTexCoord2f(0.7f, 0.2f);	glVertex3f(-3.5f, 1.8f, -2.0f);
		glTexCoord2f(0.7f, 0.0f);	glVertex3f(-4.0f, 1.3f, -2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-4.0f, 1.3f, -3.5f);
	glEnd();

	glBegin(GL_QUADS);	// back top slant
		glNormal3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.2f);	glVertex3f(3.5f, 1.8f, -3.5f);
		glTexCoord2f(0.7f, 0.2f);	glVertex3f(3.5f, 1.8f, -2.0f);
		glTexCoord2f(0.7f, 0.0f);	glVertex3f(4.0f, 1.3f, -2.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(4.0f, 1.3f, -3.5f);
	glEnd();
	
	glBegin(GL_QUADS);	// front
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.3f, 1.0f);	glVertex3f(-4.0f, 1.3f, -2.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.0f, 1.3f, -3.5f);
		glTexCoord2f(0.0f, 0.8f);	glVertex3f(-4.0f, 0.8f, -3.5f);
		glTexCoord2f(0.3f, 0.8f);	glVertex3f(-4.0f, 0.8f, -2.0f);
	glEnd();

	glBegin(GL_QUADS);	// front bottom slant
		glNormal3f(-1.2f, -0.75f, 0.0f);
		glTexCoord2f(0.0f, 0.2f);	glVertex3f(-4.0f, 0.8f, -3.5f);
		glTexCoord2f(0.3f, 0.2f);	glVertex3f(-4.0f, 0.8f, -2.0f);
		glTexCoord2f(0.3f, 0.6f);	glVertex3f(-3.5f, 0.0f, -2.0f);
		glTexCoord2f(0.0f, 0.6f);	glVertex3f(-3.5f, 0.0f, -3.5f);
	glEnd();

	glBegin(GL_QUADS);	// back
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.3f, 1.0f);	glVertex3f(4.0f, 1.3f, -2.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(4.0f, 1.3f, -3.5f);
		glTexCoord2f(0.0f, 0.8f);	glVertex3f(4.0f, 0.8f, -3.5f);
		glTexCoord2f(0.3f, 0.8f);	glVertex3f(4.0f, 0.8f, -2.0f);
	glEnd();

	glBegin(GL_QUADS);	// rear bottom slant
		glNormal3f(1.2f, -0.75f, 0.0f);
		glTexCoord2f(0.0f, 0.2f);	glVertex3f(4.0f, 0.8f, -3.5f);
		glTexCoord2f(0.3f, 0.2f);	glVertex3f(4.0f, 0.8f, -2.0f);
		glTexCoord2f(0.3f, 0.6f);	glVertex3f(3.5f, 0.0f, -2.0f);
		glTexCoord2f(0.0f, 0.6f);	glVertex3f(3.5f, 0.0f, -3.5f);
	glEnd();
glBindTexture(GL_TEXTURE_2D, treadTex[10]);
	glBegin(GL_POLYGON); // outside 
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.1f, 0.0f);	glVertex3f(-3.5f, 0.0f, -3.5f);
		glTexCoord2f(0.9f, 0.0f);	glVertex3f(3.5f, 0.0f, -3.5f);
		glTexCoord2f(1.0f, 0.1f);	glVertex3f(4.0f, 0.8f, -3.5f);
		glTexCoord2f(1.0f, 0.2f);	glVertex3f(4.0f, 1.3f, -3.5f);
		glTexCoord2f(0.9f, 0.3f);	glVertex3f(3.5f, 1.8f, -3.5f);
		glTexCoord2f(0.1f, 0.3f);	glVertex3f(-3.5f, 1.8f, -3.5f);
		glTexCoord2f(0.0f, 0.2f);	glVertex3f(-4.0f, 1.3f, -3.5f);
		glTexCoord2f(0.0f, 0.1f);	glVertex3f(-4.0f, 0.8f, -3.5f);
	glEnd();

	glBegin(GL_POLYGON); // inside 
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.1f, 0.0f);	glVertex3f(-3.5f, 0.0f, -2.0f);
		glTexCoord2f(0.9f, 0.0f);	glVertex3f(3.5f, 0.0f, -2.0f);
		glTexCoord2f(1.0f, 0.1f);	glVertex3f(4.0f, 0.8f, -2.0f);
		glTexCoord2f(1.0f, 0.2f);	glVertex3f(4.0f, 1.3f, -2.0f);
		glTexCoord2f(0.9f, 0.3f);	glVertex3f(3.5f, 1.8f, -2.0f);
		glTexCoord2f(0.1f, 0.3f);	glVertex3f(-3.5f, 1.8f, -2.0f);
		glTexCoord2f(0.0f, 0.2f);	glVertex3f(-4.0f, 1.3f, -2.0f);
		glTexCoord2f(0.0f, 0.1f);	glVertex3f(-4.0f, 0.8f, -2.0f);
	glEnd();
/*
	glBegin(GL_LINES);	// laser
		glVertex3f(-4.5, 3.5, 0.0);
		glVertex3f(-40.0, 3.5, 0.0);
	glEnd();
*/
	return;
}
	
void Tank::move(GLint dir)
{// dir is either -1 for going forward, or 1 for going in reverse
	GLfloat changeX, changeZ, angleRads;

	angleRads = angle * 3.14159f / 180.0f;

	changeX = cos(angleRads) * speed;
	changeZ = sin(angleRads) * speed;

	xPos += dir * changeX;
	zPos -= dir * changeZ;
		
	return;
}
	
void Tank::turn(GLint dir)
{// dir is either -1 for right turn or 1 for left turn

	angle += dir * rotateSpeed;

	return;
}
	
void Tank::deathDraw()
{
	return;
}


