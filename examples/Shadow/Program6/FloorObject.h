#ifndef __FLOOROBJECT_H__
#define __FLOOROBJECT_H__

#include <gl/glut.h>

class FloorObject : public GameObject
{
private:
	void DrawFloor(float SizeX, float SizeY, float Spacing)
	{
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
						glTexCoord2f(1,0); glVertex3f(x, y, 0.0);
						Toggle = false;
					}
					else
					{
						glTexCoord2f(0,1); glVertex3f(LastX, y, 0.0);
						glTexCoord2f(1,1); glVertex3f(x, y, 0.0);
						Toggle = true;
					}
				}
			
			}
			glEnd();
			LastX = x;
		}
	}
public:
	FloorObject()
	{
		for(int i = 0; i < 3; i++)
		{
			scale[i] = 1.0;
			translate[i] = 0.0;
			rotate[i] = 0.0;
		}
		color[0] = 0.0;
		color[1] = 1.0;
		color[2] = 0.0;
		color[3] = 1.0;
	}

	~FloorObject()
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

		DrawFloor(30.0, 30.0, 1.0);

		glPopMatrix();
	}
};
#endif