/////////////////////////////////////
// Copyright Levi VanOort 5-4-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// Explosion.h
/////////////////////////////////////

#ifndef __EXPLOSION_H
#define __EXPLOSION_H

#include <GL/glut.h>

class Explosion
{
public:

	Explosion()
	{
		ExplosionFrame = 0.3;
	}

	void SetPosition(float ThePosition[3])
	{
		for(int i = 0; i < 2; i++)
			Position[i] = ThePosition[i];
	}

	void Draw()
	{
		glDisable(GL_LIGHTING);
		glPushMatrix();
			glTranslatef(Position[0], Position[1], 1.0);
			glColor3f(1.0, 0.0, 0.0);
			glutSolidSphere(ExplosionFrame, 10, 10);
		glPopMatrix();

		ExplosionFrame += 0.2;
		glEnable(GL_LIGHTING);
	}

	bool ToDelete()
	{
		if(ExplosionFrame > 2.0)
			return true;
		else 
			return false;
	}

private:
	float Position[2];
	float ExplosionFrame;

};
#endif