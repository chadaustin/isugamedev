#include <gl/glut.h>


#include "FloorGraphics.h"
#include "GraphicsObject.h"
#include "TankGraphics.h"
#include "TurretGraphics.h"
#include "GameObject.h"
#include "TankObject.h"
#include "Camera.h"
#include "PhysicsEngine.h"

vector<GameObject*> TheObjects;

Camera* MyCamera = new Camera;
GraphicsObject* MyFloor = new FloorGraphics;
GameObject* MyTank = new TankObject;

PhysicsEngine MyPhysics;

int OldX = -1;
int OldY = -1;

float ZRotate = 0.0;


///////////////////////////////

void Initialize()
{
	float dist[3] = {10.0, 0.0, -6.0};

	float temp[3] = {0.0, 0.0, 2.0};

	MyTank->Init();
	MyTank->SetObjectAngle(0.0);
	MyTank->SetPosition(temp);
	MyTank->SetVelocity(0.0);

	TheObjects.push_back(MyTank);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

	MyCamera->SetDistanceFromObjectCenter(dist);
	MyCamera->SetPitch(-2.0);

	MyPhysics.SetCamera(MyCamera);
}

void MyKeyBoard(unsigned char key,int x, int y)
{
	float temp;
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

}

void MouseMotion(int x, int y)
{
	if(OldX != -1)
		MyCamera->LookAround(OldY-y, -1*(OldX-x));

	OldX = x;
	OldY = y;
}



void update()
{
	MyPhysics.Update(TheObjects);
	glutPostRedisplay();
}

void display()
{

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	MyCamera->Apply();


	glPushMatrix();
	glTranslatef(-30.0, -30.0, 2.0);
	glutSolidCube(3.0);
	glPopMatrix();

	for(int i = 0; i < TheObjects.size(); i++)
		TheObjects[i]->Draw();

	MyFloor->Draw();


   glPushMatrix();
   glLineWidth(10);
   glScalef(10,10,10);
   glDisable(GL_DEPTH);
   glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
	glEnd();
   glEnable(GL_LIGHTING);
   glEnable(GL_DEPTH);
   glLineWidth(1);
   glPopMatrix();

	glutSwapBuffers();

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


