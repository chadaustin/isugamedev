#include <GL/glut.h>
#include <string>
#include "pong.h"
#include <math.h>
#include <iostream>

using namespace std;

/*	This code blatantly copies Ben Scott's Boxes Code	*/


/**
 * Sets up OpenGL so that everything's ready for us to draw a new frame.
 */

//Global Var
int inFullScreen = 1;	//Full Screen Flag
int hitSpot;			//used in AI
int slope;				//used in AI, too (bad place to put this, but I don't care
int GameOver = 0;
int MoveToCenter = 0;

int yourScore = 0;
int compScore = 0;

int MaxAng = 80;		//maximum rebound angle


//Initialize Box
float WindowWidth = 800;
float WindowHeight = 600;
int PaddleHeight = 40;
int PaddleWidth = 10;

//Used in FPS calculation
int frame = 0;
float fps;

//-----Computer's Aggressiveness---------------------------
//Measured in how many pixels out of screen range the
//computer player will chase the ball
int oppAggr = PaddleHeight;		//Computer's Aggressiveness

//----Computer's Speed-------------------------------------
int oppSpd = 10;


//So, this is crappy code, but it'll work for pong
int xpos = int(PaddleWidth * 2);
int ypos = int(WindowHeight / 2);
int cxpos = int(WindowWidth - (PaddleWidth * 2));
int cypos = int(WindowHeight / 2);

pongball ball;


void ResetDisplay()
{
   // clear the screen with black
   glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
   glClear( GL_COLOR_BUFFER_BIT );

   // setup the projection matrix so OpenGL knows we want to do 2D graphics
   glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      //gluOrtho2D( 0.0f, 640.0f, 0.0f, 480.0f );
	  gluOrtho2D( 0.0f, WindowWidth, 0.0f, WindowHeight);

   // reset the modelview matrix to the identity matrix
   glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();
}


/*
void renderBitmapString( float x, float y, void *font, char *string) 
{  
  char *c;
  glRasterPos2f(x,y);
  for (c=string; *c != '\0'; c++) 
  {
    glutBitmapCharacter(font, *c);
  }
}
*/

string IntToString(int n)
// postcondition: returns stringized form of n
{  if (n == 0)
  {
    return "0";   // special case for 0
  }
  int k;
  string reverse = "";    // will be correct, but in reverse
  string val = "";        // the string returned
  if (n < 0)                // start with "-" if n < 0
  {
    val = "-";
    n = -n;
  }
  while (n > 0)             // get each digit, catenate in reverse
  {
    reverse += char('0' + n % 10);
    n /= 10;
  }
  // now build the string to return by "unreversing"
  for (k = reverse.length() - 1; k >= 0; k--)
  {
    val += reverse[k];
  }
  return val;
}

void renderBitmapString (float x, float y, void *font, string s)
{
	glRasterPos2f(x,y);
	for (int i = 0; i < s.length(); ++i)
	{
		glutBitmapCharacter(font, s[i]);
	}
}

void MyDisplay()
{
	//do ball movement-------------------------------------------------
	ball.vel.x_component = ball.vel.magnitude * coss(ball.vel.angle);
	ball.vel.y_component = ball.vel.magnitude * sinn(ball.vel.angle);

	ball.x += ball.vel.x_component;
	ball.y += ball.vel.y_component;
	//-----------------------------------------------------------------


	//do computer AI (if you want to call it intelligent) -------------

	/* find out where the ball is going to hit the screen edge*/

	if (ball.vel.x_component > 0)
	{
		slope = ball.vel.y_component / ball.vel.x_component;
		hitSpot = slope * (WindowWidth - ball.x) + ball.y;
	

	/* if the ball is within the range of the screen, try to hit it */
		if (hitSpot >= 0 - PaddleHeight - oppAggr && hitSpot <= WindowHeight + PaddleHeight + oppAggr)
		{
			if (ball.y > cypos)
			{
				cypos += oppSpd;
			}
			else if (ball.y < cypos)
			{
				cypos -= oppSpd;
			}

			// prevent computer from walking off the screen
			if (cypos < -PaddleHeight)
			{
				cypos = -PaddleHeight;
			}

			if (cypos > WindowHeight + PaddleHeight)
			{
				cypos = WindowHeight + PaddleHeight;
			}
		// ----------------------------------------------------------
		
		}
	}

	else if (MoveToCenter == 1)
	{
		if (ball.vel.x_component < 0)
		{
			//move back to center of screen
			if (cypos - oppSpd > WindowHeight / 2)
			{
				cypos -= oppSpd;
			}
			else if (cypos + oppSpd < WindowHeight / 2)
			{
				cypos += oppSpd;
			}
		}

	}

	// prevent player from walking off the screen---------------
	if (ypos < -PaddleHeight)
	{
		ypos = -PaddleHeight;
	}

	if (ypos > WindowHeight + PaddleHeight)
	{
		ypos = WindowHeight + PaddleHeight;
	}

	//-----------------------------------------------------------------

	//do ball collisions with wall------------------------------------
	if (ball.x + ball.radius >= WindowWidth)
	{
		ball.vel.angle = (180 - ball.vel.angle) % 360;
		ball.x = WindowWidth - ball.radius - 1;
		++yourScore;
		//ball.vel.x_component = -ball.vel.x_component;	
	}

	if (ball.x - ball.radius <= 0)
	{
		ball.vel.angle = (180 - ball.vel.angle) % 360;
		ball.x = ball.radius + 1;		
		++compScore;
		//ball.vel.x_component = -ball.vel.x_component;
	}

	if (ball.y + ball.radius >= WindowHeight)
	{
		ball.vel.angle = (-ball.vel.angle) % 360;
		ball.y = WindowHeight - ball.radius - 1;
		//ball.vel.y_component = -ball.vel.y_component;
	}

	if (ball.y - ball.radius <= 0)
	{
		ball.vel.angle = (-ball.vel.angle ) % 360;
		ball.y = ball.radius + 1;
		//ball.vel.y_component = -ball.vel.y_component;
	}
	//-----------------------------------------------------------------

	//do ball collisions with paddle-----------------------------------
	if (ball.x - ball.radius - ball.vel.x_component < xpos + PaddleWidth)
	{
		if (ball.vel.x_component < 0)
		{
			slope = ball.vel.y_component / ball.vel.x_component;
			hitSpot = slope * ((xpos + PaddleWidth) - ball.x) + ball.y;

			if ((hitSpot - ball.radius >= ypos - PaddleHeight) && (hitSpot + ball.radius <= ypos + PaddleHeight))
			{
				ball.vel.angle = (MaxAng / PaddleHeight) * (hitSpot - ypos);

				ball.x = xpos + PaddleWidth + 1 + ball.radius;
				ball.y = hitSpot;
			}
		}
	}

	if (ball.x + ball.vel.x_component + ball.radius > cxpos - PaddleWidth)
	{
		if (ball.vel.x_component > 0)
		{
			slope = ball.vel.y_component / ball.vel.x_component;
			hitSpot = slope * ((cxpos - PaddleWidth) - ball.x) + ball.y;

			if ((hitSpot - ball.radius >= cypos - PaddleHeight) && (hitSpot + ball.radius <= cypos + PaddleHeight))
			{
				ball.vel.angle = (180 - ( (MaxAng / PaddleHeight) * (hitSpot - cypos) )) % 360;

				ball.x = cxpos - PaddleWidth - 1 - ball.radius;
				ball.y = hitSpot;
				
				//ball.vel.angle = (180 - ball.vel.angle) % 360;
				//slope = MaxAng / PaddleHeight;
				//ball.vel.angle = (180 - ((MaxAng / PaddleHeight) * (ypos - hitSpot)) + MaxAng) % 360;
			}
		}

	}


	
	//-----------------------------------------------------------------
	


   // make sure everything is setup correctly to draw!
   ResetDisplay();

   // tell openGL that we want to draw a red square
   
   //--Your Paddle-------------------------------------------
   glColor3f( 1.0f, 0.0f, 0.0f );
   glBegin( GL_QUADS );
		glVertex2i( xpos - PaddleWidth, ypos - PaddleHeight);
		glVertex2i( xpos + PaddleWidth, ypos - PaddleHeight);
		glVertex2i( xpos + PaddleWidth, ypos + PaddleHeight);
		glVertex2i( xpos - PaddleWidth, ypos + PaddleHeight);
   glEnd();
	//--------------------------------------------------------
   
   //--Computer's Paddle--------------------------------------
   glColor3f( 0.0f, 0.0f, 1.0f );
   glBegin( GL_QUADS );
		glVertex2i( cxpos - PaddleWidth, cypos - PaddleHeight);
		glVertex2i( cxpos + PaddleWidth, cypos - PaddleHeight);
		glVertex2i( cxpos + PaddleWidth, cypos + PaddleHeight);
		glVertex2i( cxpos - PaddleWidth, cypos + PaddleHeight);
   glEnd();
	//--------------------------------------------------------
   

	//Draw ball 
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
		glVertex2i(ball.x - ball.radius, ball.y - ball.radius);
		glVertex2i(ball.x + ball.radius, ball.y - ball.radius);
		glVertex2i(ball.x + ball.radius, ball.y + ball.radius);
		glVertex2i(ball.x - ball.radius, ball.y + ball.radius);
	glEnd();

  
   // we've been drawing the the back buffer that is not currently visible on
   // the screen. tell glut to swap the back and front buffers to make our new
   // square visible!

	renderBitmapString(300,20, GLUT_BITMAP_HELVETICA_18, "Score");
	renderBitmapString(200,20, GLUT_BITMAP_HELVETICA_18, IntToString(yourScore));
	renderBitmapString(400,20, GLUT_BITMAP_HELVETICA_18, IntToString(compScore));

	if (yourScore == 11 || compScore == 11)
	{
		//Game is over
		if (yourScore > compScore)
		{
			renderBitmapString(230,20, GLUT_BITMAP_HELVETICA_18, "You Win!!!");
			cout << "You Win!!!\n\n";
		}
		else
		{
			renderBitmapString(230,20, GLUT_BITMAP_HELVETICA_18, "You Lose, and you Suck.");
			cout << "You Lose, and you Suck.\n\n";
		}

		GameOver = 1;


		if (GameOver == 1)
		{
			//Score Report
			renderBitmapString(200,400,GLUT_BITMAP_HELVETICA_18, "==--------------");
			renderBitmapString(200,380,GLUT_BITMAP_HELVETICA_18, "== Score Report ");
			renderBitmapString(200,360,GLUT_BITMAP_HELVETICA_18, "== You:");
			renderBitmapString(240,360,GLUT_BITMAP_HELVETICA_18, IntToString(yourScore));
			renderBitmapString(200,340,GLUT_BITMAP_HELVETICA_18, "== CPU:");
			renderBitmapString(240,340,GLUT_BITMAP_HELVETICA_18, IntToString(compScore));
			renderBitmapString(200,320,GLUT_BITMAP_HELVETICA_18, "==--------------");
			renderBitmapString(200,300,GLUT_BITMAP_HELVETICA_18, "Press Enter to exit.");

			glutSwapBuffers();
	   
			
			exit(0);
		}


	}
	
	//----These are used for debugging!!!----
	//renderBitmapString(100,100,GLUT_BITMAP_HELVETICA_18, IntToString(ypos));
	//renderBitmapString(300,100,GLUT_BITMAP_HELVETICA_18, IntToString(ball.vel.angle));
	//---------------------------------------

	//----Try to lock game at 60 FPS----------------------------------------
	frame++;

   int time;
   int timebase = 0;
	time = glutGet(GLUT_ELAPSED_TIME);
	
	if (frame > 60)
	{
		if (time - timebase > 1000) 
		{
			time = glutGet(GLUT_ELAPSED_TIME);
			fps = frame * 1000.0 / (time - timebase);
	 		timebase = time;		
			frame = 0;
		}
		else
		{
			time = glutGet(GLUT_ELAPSED_TIME);
		}
	}
	//----------------------------------------------------------------------
	renderBitmapString(300,400,GLUT_BITMAP_HELVETICA_18, "FPS: ");
	renderBitmapString(330,400,GLUT_BITMAP_HELVETICA_18, IntToString(fps));



   glutSwapBuffers();

}

void MyKeyPress( unsigned char key, int mouseX, int mouseY )
{
   // w makes the box move up
   if ( key == 'w' ) {
      ypos += 5;
   }
   // s makes the box move down
   else if ( key == 's' ) {
      ypos -= 5;
   }
   // a makes the box move left
   else if ( key == 'a' ) {
      xpos -= 5;
   }
   // d makes the box move right
   else if ( key == 'd' ) {
      xpos += 5;
   }

   
   else if (key == 'f')
   {
	   if (inFullScreen == 0)
	   {
		   glutFullScreen();
		   inFullScreen = 1;
	   }
	   else if (inFullScreen == 1)
	   {
		   glutReshapeWindow(WindowWidth, WindowHeight);
		   glutPositionWindow(100,100);
		   inFullScreen = 0;
	   }	   
   }
   
   // ESC (char code 27) quits this application
   else if ( key == 27 ) {
      exit( 0 );
   }

}


void MyMouseFunc(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			xpos = x;
			ypos = WindowHeight - y;
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		else if (state == GLUT_UP)
		{
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}
}

void PongMouseHandler(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		ypos = WindowHeight - y;
	}
	
	glutSetCursor(GLUT_CURSOR_NONE);
}

void PongMotionFunc(int x, int y)
{
	glutSetCursor(GLUT_CURSOR_NONE);
	ypos = WindowHeight - y;
}
/*
void MyMouseFunc(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		xpos = x;
		ypos = WindowHeight - y;
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else 
	{
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}	
}
*/

void MyMotionFunc(int x, int y)
{
	xpos = x;
	ypos = WindowHeight - y;
}

void main(int argc, char **argv)
{
	// Initialize Glut
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WindowWidth,WindowHeight);
	glutCreateWindow("Lou Herard:  OpenGL Demo using GLUT");
	glutFullScreen();

	// Register Callbacks to interact with OS
	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyDisplay);
	glutKeyboardFunc(MyKeyPress);
	glutMouseFunc(PongMouseHandler);
	glutMotionFunc(PongMotionFunc);
	glutPassiveMotionFunc(PongMotionFunc);

	//Create Ball	
	ball.radius = 5;
	ball.x = WindowWidth / 2;
	ball.y = WindowHeight / 2;

	ball.vel.angle = 0;
	ball.vel.magnitude = 15;

	//glutFullScreen();

	glutMainLoop();

	cout << "==----------------\n";
	cout << "== Score Report\n";
	cout << "== You " << yourScore << endl;
	cout << "== CPU " << compScore << endl;
	cout << "==----------------\n";
	cin.get();
}
