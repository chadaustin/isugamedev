#include <GL/glut.h>
#include "GameWorld.h"
#include "Input.h"


// Globals ///////////////////////////////////////////////////


Input GameInput;
GameWorld MazeTank;

bool CamMode = false;

int OldX = -1;
int OldY = -1;

/////////////////////////////////////////////////////////////

void Initialize()
{
    MazeTank.Init();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

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
   MazeTank.Update();
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

	glutMainLoop();
	return 0;
}


