#include <GL/glut.h>
#include "GameWorld.h"
#include "Input.h"

Input GameInput;
GameWorld MazeTank;


///////////////////////////////

void Initialize()
{
    MazeTank.Init();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

}



void MouseMotion(int x, int y)
{
   GameInput.TurretRotate(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
}

void KeyboardInput(int key, int x, int y)
{
   switch(key)
   {
   case GLUT_KEY_RIGHT:
      GameInput.Turn(-0.02);
      break;

   case GLUT_KEY_LEFT:
      GameInput.Turn(0.02);
      break;

   case GLUT_KEY_UP:
      GameInput.Accel(0.017);
      break;

   case GLUT_KEY_DOWN:
      GameInput.Accel(-0.017);
      break;
   }
}

void KeyboardInputUp(int key, int x, int y)
{
   switch(key)
   {
   case GLUT_KEY_RIGHT:
      GameInput.Turn(0.0);
      break;

   case GLUT_KEY_LEFT:
      GameInput.Turn(0.0);
      break;

   case GLUT_KEY_UP:
      GameInput.Accel(0.0);
      break;

   case GLUT_KEY_DOWN:
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
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100,50);
	glutCreateWindow("Final Project");
	Initialize();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(KeyboardInput);
   glutSpecialUpFunc(KeyboardInputUp);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(update);
	
   glutIgnoreKeyRepeat(1);

	glutMainLoop();
	return 0;
}


