//////////////////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort lvanoort@aol.com Released under MIT.
// 
// WheelObject.h
// 4-4-2002
//////////////////////////////////////////////////////////////////// 


#ifndef __WHEELOBJECT_H__
#define __WHEELOBJECT_H__

class WheelObject : public GameObject
{
public:
	WheelObject()
	{
		TireRotate = 0.0;
	}

	~WheelObject()
	{ }

	void Draw()
	{
	
		glPushMatrix();
		glRotatef(TireRotate, 0.0, 1.0, 0.0);

		if(ColorEnabled)
			glColor3f(1.0,1.0,1.0);

		glRotatef(90.0, 1.0, 0.0, 0.0);
		glutSolidTorus(.05, .25, 20, 15);

		if(ColorEnabled)
			glColor3f(1.0, 1.0, 0.0);
		glRotatef(90.0, 1, 0, 0);
		glutSolidCone(.03, .25, 10, 10);

		if(ColorEnabled)
			glColor3f(1.0, 0.0, 1.0);
		glRotatef(90.0, 0, 1, 0);
		glutSolidCone(.03, .25, 10, 10);

		if(ColorEnabled)
			glColor3f(0.0, 1.0, 1.0);
		glRotatef(90.0, 0, 1, 0);
		glutSolidCone(.03, .25, 10, 10);

		if(ColorEnabled)
			glColor3f(1.0, 0.0, 0.0);
		glRotatef(90.0, 0, 1, 0);
		glutSolidCone(.03, .25, 10, 10);
		glPopMatrix();
	}
};
#endif