/////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//			-- lvanoort@aol.com -- 
//				4/4/2002
//
// Frogger.cpp
/////////////////////////////////////////////////////
#include <stdlib.h>
#include <GL/glut.h>
#include "GameWorld.h"


//Globals
enum Movement{NONE = 0, LEFT, RIGHT, UP, DOWN};



// Global externals
int WindowSizeX = 663;
int WindowSizeY = 470;
int LaneSize = 36;
int FrogZone;
int CurrentLevel = 1;
Movement FrogMove = NONE;
///////////////////////


int start_clock_count = glutGet(GLUT_ELAPSED_TIME);
int temp = 0;

// Game Object
GameWorld Frogger;


void init()
{
	glClearColor(0.0,0.0,0.0, 0.0);
}


void update()
{
	while(glutGet(GLUT_ELAPSED_TIME)-start_clock_count < 30)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Frogger.Draw();
		glutSwapBuffers();
	}
	start_clock_count = glutGet(GLUT_ELAPSED_TIME);
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

		default : 
			break;
	}

}

void Input(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:
		exit(0);
		break;
	}
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WindowSizeX,WindowSizeY);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Frogger");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(FrogInput);
	glutKeyboardFunc(Input);
	glutIdleFunc(update);
	glutMainLoop();

	return 0;
}


