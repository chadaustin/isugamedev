/////////////////////////////////////
// Copyright Levi VanOort 4-19-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// FloorGraphics.h
/////////////////////////////////////
#ifndef __FLOORGRAPHICS_H__
#define __FLOORGRAPHICS_H__

#include "GraphicsObject.h"

extern GLuint gamefloor[1];

class FloorGraphics:public GraphicsObject
{
public:
	FloorGraphics()
	{
		ambient[0] = 0.2;
		ambient[1] = 0.2;
		ambient[2] = 0.2;
		ambient[3] = 1.0;

		diffuse[0] = 0.5;
		diffuse[1] = 0.5;
		diffuse[2] = 0.5;
		diffuse[3] = 1.0;

		specular[0] = 0.0;
		specular[1] = 0.0;
		specular[2] = 0.0;
		specular[3] = 1.0;

		shininess = 65.0;

	}

	void Draw()
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);	

		DrawFloor(100.0, 100.0, 1.0);
	}

	void Init()
	{

	}
private:
	void DrawFloor(float SizeX, float SizeY, float Spacing)
   {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, gamefloor[0]);

	   glNormal3f(0.0, 0.0, 1.0);
	   bool first = false;
	   float x,y,LastX;

	   for(x = -SizeX; x <= SizeX; x+= Spacing)
	   {	
		   glBegin(GL_QUAD_STRIP);
		   bool Toggle = true;

		   for(y = -SizeY; y <= SizeY; y+= Spacing)
		   {
			   
			   if(!(x == -SizeX))
			   {
				   if(Toggle)
				   {
					   glTexCoord2f(0,0); glVertex3f(LastX, y, 0.0);
					   glTexCoord2f(0,1); glVertex3f(x, y, 0.0);
					   Toggle = false;
				   }
				   else
				   {
					   glTexCoord2f(1,0); glVertex3f(LastX, y, 0.0);
					   glTexCoord2f(1,1); glVertex3f(x, y, 0.0);
					   Toggle = true;
				   }
			   }
			   
		   }
		   glEnd();
		   LastX = x;
	   
	   }

	glDisable(GL_TEXTURE_2D);
   }
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;

};
#endif
