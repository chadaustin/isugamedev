//////////////////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort lvanoort@aol.com Released under MIT.
// 
// TruckObject.h
// 4-4-2002
//////////////////////////////////////////////////////////////////// 


#ifndef __TRUCKOBJECT_H__
#define __TRUCKOBJECT_H__

#include <gl/glut.h>
#include <vector>
#include "GameObject.h"
#include "WheelObject.h"

class TruckObject : public GameObject
{
public:
	TruckObject()
	{
		rotate[0] = 0.0;
		rotate[1] = 0.0;
		rotate[2] = 0.0;

		translate[0] = 0.0;
		translate[1] = 0.0;
		translate[2] = 0.0;

		wheelturn = 0.0;
		color[0] = 0.6;
		color[1] = 0.4;
		color[2] = 1.0;
		color[3] = 1.0;

		for(int i = 0; i < 3; i++)
			scale[i] = 1.0;

		Tires = new WheelObject;
	}

	~TruckObject()
	{

	}

	void Draw()
	{

		glPushMatrix();
		glScalef(scale[0], scale[1], scale[2]);
		glTranslatef(translate[0], translate[1], translate[2]);

		glRotatef(rotate[0], 1.0, 0.0, 0.0);
		glRotatef(rotate[1], 0.0, 1.0, 0.0);
		glRotatef(rotate[2], 0.0, 0.0, 1.0);

		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.2);

		if(ColorEnabled)
		{
			glColor4f(color[0], color[1], color[2], color[3]);
			Tires->EnableColor();
		}
		else
			Tires->DisableColor();

		glBegin(GL_QUADS);

			//Draw Drivers side
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.4);
			glVertex3f(0.4, 0.0, 0.4);
			glVertex3f(0.4, 0.0, 0.0);

			glVertex3f(0.2, 0.0, 0.4);
			glVertex3f(0.2, 0.0, 0.6);
			glVertex3f(1.0, 0.0, 0.6);
			glVertex3f(1.0, 0.0, 0.4);

			glVertex3f(1.0, 0.0, 0.0);
			glVertex3f(1.0, 0.0, 0.6);
			glVertex3f(1.8, 0.0, 0.6);
			glVertex3f(1.8, 0.0, 0.0);

			glVertex3f(1.8, 0.0, 0.0);
			glVertex3f(1.8,	0.0, 1.2);
			glVertex3f(2.6, 0.0, 1.2);
			glVertex3f(2.6, 0.0, 0.0);

			//Drivers outside box
			glVertex3f(2.6, 0.0, 0.0);
			glVertex3f(2.6, 0.0, 0.6);
			glVertex3f(3.0, 0.0, 0.6);
			glVertex3f(3.0, 0.0, 0.0);

			glVertex3f(3.0, 0.0, 0.4);
			glVertex3f(3.0, 0.0, 0.6);
			glVertex3f(3.6, 0.0, 0.6);
			glVertex3f(3.6, 0.0, 0.4);

			glVertex3f(3.6, 0.0, 0.0);
			glVertex3f(3.6, 0.0, 0.6);
			glVertex3f(4.05, 0.0, 0.6);
			glVertex3f(4.05, 0.0, 0.0);

			//Drivers inside box
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(2.6, 0.05, 0.0);
			glVertex3f(2.6, 0.05, 0.6);
			glVertex3f(3.0, 0.05, 0.6);
			glVertex3f(3.0, 0.05, 0.0);

			glVertex3f(3.0, 0.05, 0.4);
			glVertex3f(3.0, 0.05, 0.6);
			glVertex3f(3.6, 0.05, 0.6);
			glVertex3f(3.6, 0.05, 0.4);

			glVertex3f(3.6, 0.05, 0.0);
			glVertex3f(3.6, 0.05, 0.6);
			glVertex3f(4.05, 0.05, 0.6);
			glVertex3f(4.05, 0.05, 0.0);

			//Top of drivers side of box
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(2.6, 0.0, 0.6);
			glVertex3f(2.6, 0.05, 0.6);
			glVertex3f(4.0, 0.05, 0.6);
			glVertex3f(4.0, 0.0, 0.6);


			//Draw Drivers side
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 1.0, 0.4);
			glVertex3f(0.4, 1.0, 0.4);
			glVertex3f(0.4, 1.0, 0.0);

			glVertex3f(0.2, 1.0, 0.4);
			glVertex3f(0.2, 1.0, 0.6);
			glVertex3f(1.0, 1.0, 0.6);
			glVertex3f(1.0, 1.0, 0.4);

			glVertex3f(1.0, 1.0, 0.0);
			glVertex3f(1.0, 1.0, 0.6);
			glVertex3f(1.8, 1.0, 0.6);
			glVertex3f(1.8, 1.0, 0.0);

			glVertex3f(1.8, 1.0, 0.0);
			glVertex3f(1.8,	1.0, 1.2);
			glVertex3f(2.6, 1.0, 1.2);
			glVertex3f(2.6, 1.0, 0.0);

			//Drivers outside box
			glVertex3f(2.6, 1.0, 0.0);
			glVertex3f(2.6, 1.0, 0.6);
			glVertex3f(3.0, 1.0, 0.6);
			glVertex3f(3.0, 1.0, 0.0);

			glVertex3f(3.0, 1.0, 0.4);
			glVertex3f(3.0, 1.0, 0.6);
			glVertex3f(3.6, 1.0, 0.6);
			glVertex3f(3.6, 1.0, 0.4);

			glVertex3f(3.6, 1.0, 0.0);
			glVertex3f(3.6, 1.0, 0.6);
			glVertex3f(4.05, 1.0, 0.6);
			glVertex3f(4.05, 1.0, 0.0);

			//Drivers inside box
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(2.6, 0.95, 0.0);
			glVertex3f(2.6, 0.95, 0.6);
			glVertex3f(3.0, 0.95, 0.6);
			glVertex3f(3.0, 0.95, 0.0);

			glVertex3f(3.0, 0.95, 0.4);
			glVertex3f(3.0, 0.95, 0.6);
			glVertex3f(3.6, 0.95, 0.6);
			glVertex3f(3.6, 0.95, 0.4);

			glVertex3f(3.6, 0.95, 0.0);
			glVertex3f(3.6, 0.95, 0.6);
			glVertex3f(4.05, 0.95, 0.6);
			glVertex3f(4.05, 0.95, 0.0);

			//Top of drivers side of box
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(2.6, 0.95, 0.6);
			glVertex3f(2.6, 1.0, 0.6);
			glVertex3f(4.0, 1.0, 0.6);
			glVertex3f(4.0, 0.95, 0.6);		

			//Draw Top and bottom

			//Grill
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 1.0, 0.4);
			glVertex3f(0.0, 0.0, 0.4);
			glVertex3f(0.0, 0.0, 0.0);

			//Front angle of Hood
			glNormal3f(-0.707107, 0.0, 0.707107);
			glVertex3f(0.0, 1.0, 0.4);
			glVertex3f(0.2, 1.0, 0.6);
			glVertex3f(0.2, 0.0, 0.6);
			glVertex3f(0.0, 0.0, 0.4);

			//Top of Hood
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(0.2, 1.0, 0.6);
			glVertex3f(1.2, 1.0, 0.6);
			glVertex3f(1.2, 0.0, 0.6);
			glVertex3f(0.2, 0.0, 0.6);

			//Draw Windshield
			glNormal3f(-0.707107, 0.0, 0.707107);
			glVertex3f(1.2, 1.0, 0.6);
			glVertex3f(1.8, 1.0, 1.2);
			glVertex3f(1.8, 0.0, 1.2);
			glVertex3f(1.2, 0.0, 0.6);

			//Draw roof
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(1.8, 1.0, 1.2);
			glVertex3f(2.6, 1.0, 1.2);
			glVertex3f(2.6, 0.0, 1.2);
			glVertex3f(1.8, 0.0, 1.2);

			//Draw backwindow
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(2.6, 1.0, 1.2);
			glVertex3f(2.6, 1.0, 0.6);
			glVertex3f(2.6, 0.0, 0.6);
			glVertex3f(2.6, 0.0, 1.2);

			//Draw lip of box
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(2.6, 1.0, 0.6);
			glVertex3f(2.7, 1.0, 0.6);
			glVertex3f(2.7, 0.0, 0.6);
			glVertex3f(2.6, 0.0, 0.6);

			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(2.7, 1.0, 0.6);
			glVertex3f(2.7, 1.0, 0.55);
			glVertex3f(2.7, 0.0, 0.55);
			glVertex3f(2.7, 0.0, 0.6);

			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(2.7, 1.0, 0.55);
			glVertex3f(2.7, 0.0, 0.55);
			glVertex3f(2.6, 0.0, 0.55);
			glVertex3f(2.6, 1.0, 0.55);

			//Draw cab side of the box
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(2.6, 1.0, 0.55);
			glVertex3f(2.6, 1.0, 0.2);
			glVertex3f(2.6, 0.0, 0.2);
			glVertex3f(2.6, 0.0, 0.55);

			//Draw bottom of box
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(2.6, 1.0, 0.2);
			glVertex3f(3.0, 1.0, 0.2);
			glVertex3f(3.0, 0.0, 0.2);
			glVertex3f(2.6, 0.0, 0.2);

			glVertex3f(3.0, 0.78, 0.2);
			glVertex3f(3.6, 0.78, 0.2);
			glVertex3f(3.6, 0.22, 0.2);
			glVertex3f(3.0, 0.22, 0.2);

			glVertex3f(3.6, 1.0, 0.2);
			glVertex3f(4.0, 1.0, 0.2);
			glVertex3f(4.0, 0.0, 0.2);
			glVertex3f(3.6, 0.0, 0.2);

			//Draw wheel wells
			glNormal3f(-0.707107, 0.0, 0.707107);
			glVertex3f(3.0, 1.0, 0.2);
			glVertex3f(3.2, 1.0, 0.4);
			glVertex3f(3.2, 0.78, 0.4);
			glVertex3f(3.0, 0.78, 0.2);

			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(3.2, 1.0, 0.4);
			glVertex3f(3.4, 1.0, 0.4);
			glVertex3f(3.4, 0.78, 0.4);
			glVertex3f(3.2, 0.78, 0.4);

			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(3.2, 0.78, 0.4);
			glVertex3f(3.4, 0.78, 0.4);
			glVertex3f(3.4, 0.78, 0.2);
			glVertex3f(3.2, 0.78, 0.2);

			glNormal3f(0.707107, 0.0, 0.707107);
			glVertex3f(3.4, 1.0, 0.4);
			glVertex3f(3.6, 1.0, 0.2);
			glVertex3f(3.6, 0.78, 0.2);
			glVertex3f(3.4, 0.78, 0.4);

			glNormal3f(-0.707107, 0.0, 0.707107);
			glVertex3f(3.0, 0.0, 0.2);
			glVertex3f(3.2, 0.0, 0.4);
			glVertex3f(3.2, 0.22, 0.4);
			glVertex3f(3.0, 0.22, 0.2);

			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(3.2, 0.0, 0.4);
			glVertex3f(3.4, 0.0, 0.4);
			glVertex3f(3.4, 0.22, 0.4);
			glVertex3f(3.2, 0.22, 0.4);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(3.2, 0.22, 0.4);
			glVertex3f(3.4, 0.22, 0.4);
			glVertex3f(3.4, 0.22, 0.2);
			glVertex3f(3.2, 0.22, 0.2);

			glNormal3f(0.707107, 0.0, 0.707107);
			glVertex3f(3.4, 0.0, 0.4);
			glVertex3f(3.6, 0.0, 0.2);
			glVertex3f(3.6, 0.22, 0.2);
			glVertex3f(3.4, 0.22, 0.4);

			//Draw tail gate
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(4.0, 1.0, 0.0);
			glVertex3f(4.0, 1.0, 0.6);
			glVertex3f(4.0, 0.0, 0.6);
			glVertex3f(4.0, 0.0, 0.0);

			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(4.0, 1.0, 0.6);
			glVertex3f(4.05, 1.0, 0.6);
			glVertex3f(4.05, 0.0, 0.6);
			glVertex3f(4.0, 0.0, 0.6);

			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(4.05, 1.0, 0.6);
			glVertex3f(4.05, 1.0, 0.0);
			glVertex3f(4.05, 0.0, 0.0);
			glVertex3f(4.05, 0.0, 0.6);

			//Draw under of truck
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(4.05, 0.0, 0.0);
			glVertex3f(4.05, 1.0, 0.0);
			glVertex3f(3.6, 1.0, 0.0);
			glVertex3f(3.6, 0.0, 0.0);

			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(3.0, 0.0, 0.0);
			glVertex3f(3.0, 1.0, 0.0);
			glVertex3f(1.0, 1.0, 0.0);
			glVertex3f(1.0, 0.0, 0.0);

			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(1.0, 0.0, 0.0);
			glVertex3f(1.0, 1.0, 0.0);
			glVertex3f(1.0, 1.0, 0.4);
			glVertex3f(1.0, 0.0, 0.4);

			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(1.0, 0.0, 0.4);
			glVertex3f(1.0, 1.0, 0.4);
			glVertex3f(0.4, 1.0, 0.4);
			glVertex3f(0.4, 0.0, 0.4);

			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(0.4, 0.0, 0.4);
			glVertex3f(0.4, 1.0, 0.4);
			glVertex3f(0.4, 1.0, 0.0);
			glVertex3f(0.4, 0.0, 0.0);

			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(0.4, 0.0, 0.0);
			glVertex3f(0.4, 1.0, 0.0);
			glVertex3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);

		glEnd();

		glBegin(GL_TRIANGLES);

			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(0.0, 0.0, 0.4);
			glVertex3f(0.2, 0.0, 0.6);
			glVertex3f(0.2, 0.0, 0.4);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 1.0, 0.4);
			glVertex3f(0.2, 1.0, 0.6);
			glVertex3f(0.2, 1.0, 0.4);

			//Draw triangles in wheel wells
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(3.0, 0.0, 0.2);
			glVertex3f(3.2, 0.0, 0.4);
			glVertex3f(3.0, 0.0, 0.4);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(3.0, 0.05, 0.2);
			glVertex3f(3.2, 0.05, 0.4);
			glVertex3f(3.0, 0.05, 0.4);

			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(3.0, 0.95, 0.2);
			glVertex3f(3.2, 0.95, 0.4);
			glVertex3f(3.0, 0.95, 0.4);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(3.0, 1.0, 0.2);
			glVertex3f(3.2, 1.0, 0.4);
			glVertex3f(3.0, 1.0, 0.4);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(3.0, 0.22, 0.2);
			glVertex3f(3.2, 0.22, 0.4);
			glVertex3f(3.2, 0.22, 0.2);

			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(3.0, 0.78, 0.2);
			glVertex3f(3.2, 0.78, 0.4);
			glVertex3f(3.2, 0.78, 0.2);

			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(3.4, 0.0, 0.4);
			glVertex3f(3.6, 0.0, 0.2);
			glVertex3f(3.6, 0.0, 0.4);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(3.4, 0.05, 0.4);
			glVertex3f(3.6, 0.05, 0.2);
			glVertex3f(3.6, 0.05, 0.4);

			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(3.4, 0.95, 0.4);
			glVertex3f(3.6, 0.95, 0.2);
			glVertex3f(3.6, 0.95, 0.4);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(3.4, 1.0, 0.4);
			glVertex3f(3.6, 1.0, 0.2);
			glVertex3f(3.6, 1.0, 0.4);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(3.4, 0.22, 0.4);
			glVertex3f(3.6, 0.22, 0.2);
			glVertex3f(3.4, 0.22, 0.2);

			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(3.4, 0.78, 0.4);
			glVertex3f(3.6, 0.78, 0.2);
			glVertex3f(3.4, 0.78, 0.2);

		glEnd();

		glPushMatrix();
		glTranslatef(0.7, 0.08, 0.08);
		glRotatef(wheelturn, 0.0, 0.0, 1.0);
		Tires->Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.7, 0.92, 0.08);
		glRotatef(wheelturn, 0.0, 0.0, 1.0);
		Tires->Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(3.3, 0.08, 0.08);
		Tires->Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(3.3, 0.92, 0.08);
		Tires->Draw();
		glPopMatrix();


		glPopMatrix();

	
		glPopMatrix();
	}
};
#endif