// Levi VanOort -- lvanoort@aol.com 2/4/2002

#include <GL/glut.h>
#include <stdio.h>
#include "GameWorld.h"
#include "BMPLoader.h"

using namespace std;

//Globals/////////////////////////////////////////////////
int WindowSizeX = 640;
int WindowSizeY = 640;

GameWorld BreakOut;

int MouseX = WindowSizeX/2;
int MouseY = 30;
int LastX = MouseX;

bool LeftButtonPressed = false;
int NumberOfBalls = 0;
int level = 1;
int NumberOfBlocks = 0;
int Score = 0;
bool drawtextures = true;

#define NEWGAME 10
#define QUIT 11
#define ONE 12
#define TWO 13
#define THREE 14

GLuint ball[1];
GLuint block[1];
GLuint paddle[4];
GLuint wall[1];
GLuint powerup[1];
GLuint bullet[1];

int dt = 0;
int Starttime = glutGet(GLUT_ELAPSED_TIME);
int Stoptime = 0;
///////////////////////////////////////////////////////

void MainMenu(int value)
{
	switch(value)
	{
	case NEWGAME:
		Score = 0;
		BreakOut.~GameWorld();
		BreakOut.ResetGame();
		break;
	case QUIT:
		BreakOut.~GameWorld();
		exit(0);
		break;
	}
}

void LevelSubMenu(int value)
{
	switch(value)
	{
	case ONE:	
		level = 1;
		Score = 0;
		BreakOut.~GameWorld();
		BreakOut.ResetGame();
		break;
	case TWO:
		level = 2;
		Score = 0;
		BreakOut.~GameWorld();
		BreakOut.ResetGame();
		break;
	case THREE:
		level = 3;
		Score = 0;
		BreakOut.~GameWorld();
		BreakOut.ResetGame();
		break;
	}
}

void renderBitmapString(float x, float y,void *font, char *string) 
{ 
  char *c;

  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++) 
    glutBitmapCharacter(font, *c);
} 



void init(void)
{

	glEnable(GL_TEXTURE_2D);
	//Load in all textures
	loadOpenGL2DTextureBMP("bullet.bmp", &bullet[0],  GL_RGB);
	loadOpenGL2DTextureBMP("ball.bmp", &ball[0],  GL_RGB);
	loadOpenGL2DTextureBMP("block.bmp", &block[0],  GL_RGB);
	loadOpenGL2DTextureBMP("paddle.bmp", &paddle[0],  GL_RGB);
 	loadOpenGL2DTextureBMP("paddle2.bmp", &paddle[1],  GL_RGB);
 	loadOpenGL2DTextureBMP("paddle3.bmp", &paddle[2],  GL_RGB);
 	loadOpenGL2DTextureBMP("paddle4.bmp", &paddle[3],  GL_RGB);
	loadOpenGL2DTextureBMP("brick2.bmp", &wall[0],  GL_RGB);
	loadOpenGL2DTextureBMP("powerup.bmp", &powerup[0],  GL_RGB);

	////////////////////////////////////////////////////////////
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

	glutSetCursor(GLUT_CURSOR_NONE);

	int LevelSubMenuHandle = glutCreateMenu(LevelSubMenu);


	glutCreateMenu(MainMenu);

	glutAddSubMenu("Level", LevelSubMenuHandle);

	glutAddMenuEntry("New Game", NEWGAME);
	glutAddMenuEntry("Quit",QUIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutSetMenu(LevelSubMenuHandle);
	glutAddMenuEntry("1", ONE);
	glutAddMenuEntry("2", TWO);
	glutAddMenuEntry("3", THREE);

}

void mydisplay();

void update()
{
	///////////////////////////////////////////
	// Timer used to move objects so
	// game will be same speed on all machines
	///////////////////////////////////////////
	Stoptime = glutGet(GLUT_ELAPSED_TIME);
	dt = Starttime - Stoptime;
	Starttime = glutGet(GLUT_ELAPSED_TIME);

	////////////////////////////////////////////////
	// In case time change gets to large set 
	// it to resonable value to make game playable
	////////////////////////////////////////////////
	if(dt > 50)
		dt = 50;

	//////////////////////////////////////
	// Update the GameWorld and redraw
	//////////////////////////////////////
	BreakOut.Update();

	glutPostRedisplay();

}

void MyKeyboard(unsigned char key, int x, int y)
{
	if(int(key) == 27)
	{
		BreakOut.~GameWorld();
		exit(0);
	}
	if(key == 't' || key == 'T')
	{
		if(drawtextures)
			drawtextures = false;
		else
			drawtextures = true;
	}
}

void PaddleMotion(int x, int y)
{

	MouseX = MouseX - (LastX - x);

	if (x <= WindowSizeX/2-50 || x >= WindowSizeX/2+50)
	{
		glutWarpPointer(WindowSizeX/2, y);
		LastX = WindowSizeX/2;
	}
	else if ( y < WindowSizeY/2-50 || y > WindowSizeY/2+50 )
	{
		glutWarpPointer(x, WindowSizeY/2);
		LastX = x;
	}

	else	
		LastX = x;
}

void MouseButtonPress(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		LeftButtonPressed = true;
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		LeftButtonPressed = false;
}

	

void mydisplay()
{ 
	char temp[100];

	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0,1.0,1.0);

   sprintf(temp, "%d", Score);
	renderBitmapString(10,620, GLUT_BITMAP_HELVETICA_18, "Score");
	renderBitmapString(90,620, GLUT_BITMAP_HELVETICA_18, temp);

//	glEnable(GL_TEXTURE_2D);

	BreakOut.Draw();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei) WindowSizeX, (GLsizei) WindowSizeY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble) WindowSizeX, 0.0, (GLdouble) WindowSizeY);
}


int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WindowSizeX,WindowSizeY);
	glutInitWindowPosition(100,50);
	glutCreateWindow("BreakOut");
	init();
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
	glutPassiveMotionFunc(PaddleMotion);
	glutMouseFunc(MouseButtonPress);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}
