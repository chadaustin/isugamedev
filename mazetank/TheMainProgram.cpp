/////////////////////////////////////
// Copyright Levi VanOort 4-19-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// TheMainProgram.cpp
/////////////////////////////////////

#include <GL/glut.h>
#include "GameWorld.h"
#include "Input.h"
#include "BMPLoader.h"
#include <iostream>

using namespace std;


// Globals ///////////////////////////////////////////////////


Input GameInput;
GameWorld MazeTank;

bool CamMode = false;

int OldX = -1;
int OldY = -1;

int dt = 0;
int Starttime, Stoptime;
GLuint gamefloor[1];

/////////////////////////////////////////////////////////////

void Initialize()
{
	GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
    MazeTank.Init();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	 glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

	if(LOAD_TEXTUREBMP_SUCCESS == loadOpenGL2DTextureBMP("Textures/concrete.bmp", &gamefloor[0]))
		cout << "Success" << endl;

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

}

void MyMouse(int button, int state,int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		GameInput.ShootBullet();
}

void MouseMotion(int x, int y)
{

	int CenterX = glutGet(GLUT_WINDOW_WIDTH)/2;
	int CenterY = glutGet(GLUT_WINDOW_HEIGHT)/2;

	if(OldX == -1)
	{
		OldX = x;
		OldY = y;
	}


	if(CamMode)
		GameInput.LookAround(x - OldX, y - OldY);

	else
		GameInput.TurretRotate(x - OldX, y - OldY);


	if(x > CenterX + 50 || x < CenterX - 50 ||
		y > CenterY + 50 || y < CenterY - 50)

	{
		int tempx = glutGet(GLUT_WINDOW_WIDTH);
		int tempy = glutGet(GLUT_WINDOW_HEIGHT);

		glutWarpPointer(CenterX, CenterY);
		OldX = -1;
		OldY = -1;
	}

	else
	{
		OldX = x;
		OldY = y;
	}
}

void MyKeyboard(unsigned char key, int x, int y)
{

	switch(key)
   {
	case ' ':
		CamMode = true;
		break;

	case 27:
		exit(0);
		break;

   case 'd':
      GameInput.Turn(-0.03);
      break;

   case 'a':
      GameInput.Turn(0.03);
      break;

   case 'w':
      GameInput.Accel(0.017);
      break;

   case 's':
      GameInput.Accel(-0.017);
      break;

   case 'h':
      GameInput.Honk();
      break;

	}

}



void MyKeyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
	case ' ':
		CamMode = false;
		GameInput.SnapCamera();
		break;

   case 'd':
      GameInput.Turn(0.0);
      break;

   case 'a':
      GameInput.Turn(0.0);
      break;

   case 'w':
      GameInput.Accel(0.0);
      break;

   case 's':
      GameInput.Accel(0.0);
      break;
	}

}

void update()
{
	///////////////////////////////////////////
	// Timer used to move objects so
	// game will be same speed on all machines
	///////////////////////////////////////////
	Stoptime = glutGet(GLUT_ELAPSED_TIME);
	dt = Stoptime - Starttime;
	Starttime = Stoptime;
 
	if(dt > 200)
		dt = 200;
   
   if(dt < 0)
      dt *= -1;

   MazeTank.Update(dt);
	glutPostRedisplay();
}

void display()
{
   MazeTank.Draw();
}

void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)h/(GLfloat)w, 0.1, 500.0);
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100,50);
	glutCreateWindow("Final Project");
	Initialize();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(MyKeyboard);
	glutKeyboardUpFunc(MyKeyboardUp);

	glutPassiveMotionFunc(MouseMotion);
	glutMouseFunc(MyMouse);

	glutSetCursor(GLUT_CURSOR_NONE);
	glutIdleFunc(update);
	
	glutIgnoreKeyRepeat(1);

   Starttime = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
	return 0;
}


