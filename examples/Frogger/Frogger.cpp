#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "GameWorld.h"
#include <iostream.h>

//Globals
enum Movement{NONE = 0, LEFT, RIGHT, UP, DOWN};

Movement FrogMove = NONE;

int WindowSizeX = 663;
int WindowSizeY = 470;
int LaneSize = 36;
int FrogZone;
int CurrentLevel = 1;

DWORD start_clock_count = GetTickCount();
int temp = 0;

GameWorld Frogger;

void init()
{
	glClearColor(0.0,0.0,0.0, 0.0);
//	glShadeModel(GL_FLAT);
}

void update()
{
	while(GetTickCount()-start_clock_count < 30)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Frogger.Draw();
		glutSwapBuffers();
	}
	start_clock_count = GetTickCount();
	Frogger.Update();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Frogger.Draw();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei) WindowSizeX, (GLsizei) WindowSizeY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble) WindowSizeX, 0.0, (GLdouble) WindowSizeY);
}

void FrogInput(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT : 
			FrogMove = LEFT;
			break;

		case GLUT_KEY_RIGHT: 
			FrogMove = RIGHT;
			break;

		case GLUT_KEY_UP : 
			FrogMove = UP;
			FrogZone++;
			break;

		case GLUT_KEY_DOWN :
			if (FrogZone == 0)
				FrogMove = NONE;
			else
			{
				FrogMove = DOWN;
				FrogZone--;
			}
			break;

		default : NULL;
			break;
	}
}


int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WindowSizeX,WindowSizeY);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(FrogInput);
	glutIdleFunc(update);
	glutMainLoop();
	return 0;
}
