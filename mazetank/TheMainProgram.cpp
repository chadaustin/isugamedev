#include <gl/glut.h>
#include "GameWorld.h"

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

void MyKeyBoard(unsigned char key,int x, int y)
{
/*	float temp;
	switch(key)
	{
	case 'a':

		MyTank->GetObjectAngle(temp);
		MyTank->SetObjectAngle(temp+1.0);
		break;

	case 'd':

		MyTank->GetObjectAngle(temp);
		MyTank->SetObjectAngle(temp-1.0);
		break;

	case 'w':
		MyTank->GetVelocity(temp);
		MyTank->SetVelocity(temp+0.01);
		break;

	case 's':
		MyTank->GetVelocity(temp);
		MyTank->SetVelocity(temp-0.01);
		break;

	case 'f':
		ZRotate -= 1.0;
		MyCamera->RotateAroundObject(1.0);
		break;

	case 'h':
		ZRotate += 1.0;
		MyCamera->RotateAroundObject(-1.0);
		break;
		
	}
*/
}

void MouseMotion(int x, int y)
{
/*	if(OldX != -1)
		MyCamera->LookAround(OldY-y, -1*(OldX-x));

	OldX = x;
	OldY = y;*/
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
	glutKeyboardFunc(MyKeyBoard);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(update);
	
	glutMainLoop();
	return 0;
}


