#include <gl/glut.h>
#include "TruckObject.h"
#include "FloorObject.h"
#include "Camera.h"
#include "Shadow.h"
#include "WheelObject.h"
#include <iostream>
#include <vector>
#include "CarPhysics.h"
#include "SkyDome.h"
#include "BMPLoader.h"

using namespace std;

int const NUMBERLIGHTS = 2;

Camera* MyCamera = new Camera;

//The Floor is a special case
GameObject* TheFloor;
//////////////////////////////

Shadow MyShadows;
vector <GameObject*> TheObjects;
GameObject* TheTruck;
CarPhysics TheTruckPhysics;

GLuint clouds[1];
GLuint grass[1];

LightPosition MyLights[NUMBERLIGHTS];

//GLfloat light_position[] = {0.0, 10.0, 10.0, 1.0};
//GLfloat light_position2 [] = {0.0, -10.0, 10.0, 1.0};
GLfloat mat_diffuse[4] = {1.0, 0.5, 0.5, 1.0};
GLfloat floorPlane[4] = {0.0, 0.0, 1.0, 0.0};

void init()
{
	MyLights[0].ThePosition[0] = 0.0;
	MyLights[0].ThePosition[1] = 10.0;
	MyLights[0].ThePosition[2] = 10.0;
	MyLights[0].ThePosition[3] = 1.0;

	MyLights[1].ThePosition[0] = 0.0;
	MyLights[1].ThePosition[1] = -10.0;
	MyLights[1].ThePosition[2] = 10.0;
	MyLights[1].ThePosition[3] = 1.0;
	///////////////////////////////////////////////////////////
	//Initialize all of the lights
	////////////////////////////////////////////////////////////
	GLfloat mat_specular[] = {0.256777, 0.137622, 0.086014, 1.0};
	GLfloat mat_shininess[] = {12.8};

	GLfloat white_light[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat lmodel_ambient[] = {0.19125, 0.0735, 0.0225, 1.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glLightfv(GL_LIGHT0, GL_POSITION, MyLights[0].ThePosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glLightfv(GL_LIGHT1, GL_POSITION, MyLights[1].ThePosition);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	//////////////////////////////////////////////////////////////

	TheFloor = new FloorObject;

	TheTruck = new TruckObject;
	GameObject* Truck2 = new TruckObject;

	///////////////////////////////////////
	//This initializes all the physics for
	//putting the truck in motion
	///////////////////////////////////////
	TheTruckPhysics.SetVehicle(TheTruck);
	TheTruckPhysics.SetWheelbase(2.6);
	TheTruckPhysics.AttachCamera(MyCamera);
	TheTruckPhysics.SetCarTires(TheTruck->Tires);
	/////////////////////////////////////////

	TheObjects.push_back(TheTruck);
	TheObjects.push_back(Truck2);

	Truck2->YTranslate(10.0);

	///////////////////////////////////////
	//Initialize all of the parameters
	//that the shadow needs setup
	///////////////////////////////////////
	MyShadows.SetTheGroundPlane(floorPlane);
	for(int j = 0; j < NUMBERLIGHTS; j++)
	{
		MyShadows.AddLight(MyLights[j].ThePosition);
	}
	MyShadows.SetFloorObject(TheFloor);

	for(int i = 0; i < TheObjects.size(); i++)
		MyShadows.AddAObject(TheObjects[i]);

	/////////////////////////////////////////

	//////////////////////////////////////////
	//Initialize Camera parameteres
	/////////////////////////////////////////
	MyCamera->YRotate(-2.0);
	MyCamera->XTrans(-7.0);
	/////////////////////////////////////////

	///////////////////////////////////
	//Load textures
	//////////////////////////////////
	glEnable(GL_TEXTURE_2D);
	loadOpenGL2DTextureBMP("nebula.bmp", &clouds[0],  GL_RGB);
	loadOpenGL2DTextureBMP("marbteal.bmp", &grass[0],  GL_RGB);
	//////////////////////////////////

	GenerateDome(300.0f, 5.0f, 5.0f, 1.0f, 1.0f);

    glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

}

void MoveTheTruck(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		TheTruckPhysics.IncrementAccel(-0.0001);
		break;
	case GLUT_KEY_DOWN:
		TheTruckPhysics.IncrementAccel(0.0001);
		break;
	case GLUT_KEY_LEFT:
		TheTruckPhysics.IncrementWheelAngle(3.0);
		break;
	case GLUT_KEY_RIGHT:
		TheTruckPhysics.IncrementWheelAngle(-3.0);
		break;
	}
}

void MyKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
		MyCamera->YRotate(-1.0);
		break;

	case 's':
		MyCamera->YRotate(1.0);
		break;

	case 'a':
		MyCamera->ZRotate(1.0);
		break;

	case 'd':
		MyCamera->ZRotate(-1.0);
		break;

	case 'i':
		MyCamera->XTrans(1.0);
		break;

	case 'j':
		MyCamera->YTrans(1.0);
		break;

	case 'k':
		MyCamera->XTrans(-1.0);
		break;

	case 'l':
		MyCamera->YTrans(-1.0);
		break;

	case 'f':
		MyLights[0].ThePosition[0] += 1.0;
		break;

	case 't':
		MyLights[0].ThePosition[1] += 1.0;
		break;

	case 'g':
		MyLights[0].ThePosition[1] -= 1.0;
		break;
		
	case 'h':
		MyLights[0].ThePosition[0] -= 1.0;
		break;
	}
}

void mydisplay()
{
	int i;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	MyCamera->Process();
	glLightfv(GL_LIGHT0, GL_POSITION, MyLights[0].ThePosition);
	glLightfv(GL_LIGHT1, GL_POSITION, MyLights[1].ThePosition);

	///////////////////////////////////////////
	// Draw sphere to represent light position
	///////////////////////////////////////////
	for(i = 0; i < NUMBERLIGHTS; i++)
	{
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(MyLights[i].ThePosition[0], MyLights[i].ThePosition[1], MyLights[i].ThePosition[2]);
		glColor3f(1.0, 1.0, 0.0);
		glutSolidSphere(.5, 10, 10);
		glPopMatrix();
	}
	///////////////////////////////////////////

	////////////////////////////
	//Draw reflection
	////////////////////////////
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	glPushMatrix();
	glScalef(1.0, 1.0, -1.0);
	glEnable(GL_NORMALIZE);
	for(i = 0; i < TheObjects.size(); i++)
	{
		TheObjects[i]->EnableColor();
		TheObjects[i]->Draw();
	}
	glDisable(GL_NORMALIZE);
	glPopMatrix();
	/////////////////////////

	///////////////////////////////
	//Draw Shadows here
	///////////////////////////////
	for(i = 0; i < NUMBERLIGHTS; i++)
	{
		MyShadows.SetLightPosition(i, MyLights[i].ThePosition);
	}
	MyShadows.DrawShadows();
	///////////////////////////////
	
	///////////////////////////////////////////
	// Draw the skydome
	//////////////////////////////////////////
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glTranslatef(0.0, 0.0, 80.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, clouds[0]);

	// These two lines allow for wireframe mode
//	glDisable(GL_TEXTURE_2D);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	///////////////////////////////////////////
	RenderSkyDome();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//////////////////////////////////////////

	//////////////////////////////
	// Update each object
	//////////////////////////////
	for(i = 0; i < TheObjects.size(); i++)
	{
		TheObjects[i]->EnableColor();
		TheObjects[i]->Draw();
	}
	///////////////////////////////


	glutSwapBuffers(); 
}

void update()
{
	////////////////////////
	// Update Truck Physics
	////////////////////////
	TheTruckPhysics.Update();
	////////////////////////
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0, (GLfloat)h/(GLfloat)w, 0.1, 500.0);
}


int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,50);
	glutCreateWindow("Moving Model");
	init();
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MoveTheTruck);
	
	glutMainLoop();
	return 0;
}
