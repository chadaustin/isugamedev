

#ifdef WIN32
   #include <windows.h>  // make the app win32 friendly. :)
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#include <GL/glaux.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>


//global definitions

#define EMPTY 0
#define BRICK  1
#define LADDER  2
#define WIRE  3
#define MONEY  4
#define GUY  5

#include "level.h"
#include "player.h"
#include "textures.h"
#include "badguy.h"


#ifdef WIN32
      void msleep( float msec )
      {
         ::Sleep( (int) msec );
      }
#else
      #include <unistd.h>
      void msleep( float msec )
      {
         ::usleep( (int)(msec * 1000.0f) );
      } 
#endif
      
//: get the current time
//  useful for profiling, or doing time based animation
//  returns - number in seconds...
#ifndef WIN32
   #include <sys/time.h>
   inline double getTime()
   {
      struct timeval tv;
      gettimeofday( &tv, 0 );

      // compose sec with microsec for sec.millisec
      return static_cast<double>( tv.tv_sec )
          + ( static_cast<double>( tv.tv_usec )
                 / 1000000.0 );
   }
#else
   #include <windows.h>  // windows time routines...
   #include <sys/types.h>
   #include <sys/timeb.h>
   inline double getTime()
   {
      struct _timeb tv;
      _ftime( &tv );

      // compose sec with millisec for sec.millisec
      return static_cast<double>( tv.time )
	      + ( static_cast<double>( tv.millitm ) 
	        / 1000.0 );
   }
#endif



// a place to store application data...
class App
{
public:
   App() : width( 0 ), height( 0 ), mainWin_contextID( -1 )
   {
   }
   int width, height;
   int mainWin_contextID;

};
App app;


bool won=false,lost=false;
level l;
player u(30,450,0,false);
badguy badguy1(30,150,0,false);
COGLTexture win,lose;
double lasttime = getTime(), currenttime = getTime();
double timechange = 0.0;


void initTexture(){
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	win.LoadFromFile("Data/win.bmp");
	lose.LoadFromFile("Data/lose.bmp");

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

}

void winOrLose(){
	l.isMoney(u.getPos(), u.getHeight()/30);
	if(won==true || lost==true){
		msleep(3000);
		exit(0);
	}
	if(l.getAmount()==0){
		won=true;
	}
	if((badguy1.getPos()-u.getPos()>=-10 && badguy1.getPos()-u.getPos()<=10) && badguy1.getHeight()==u.getHeight()){
		lost=true;
	}
}

void winner(){
	

	glEnable(GL_TEXTURE_2D);
	win.SetActive();
	glBegin( GL_QUADS );
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(100, 100,0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(400, 100,0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(400, 300,0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(100, 300,0);
	glEnd();

	glutPostRedisplay();
}

void looser(){
	glEnable(GL_TEXTURE_2D);
	lose.SetActive();
	glBegin( GL_QUADS );
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(100, 100,0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(400, 100,0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(400, 300,0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(100, 300,0);
	glEnd();

	glutPostRedisplay();
}

//////////////////////////////////////////////////
// This is called on a glutPostRedisplay
//////////////////////////////////////////////////
static void OnRedisplay()
{ 
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glEnable( GL_TEXTURE_2D);
 
	// set up the projection matrix
	glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluOrtho2D( 0,640,0,480 );
                           
	// initialize your matrix stack used for transforming your models
    glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();      

	// !!!TODO!!!: replace the following with your own opengl commands!

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	glColor3f(1,0,0);
	winOrLose();
	badguy1.findPlayer(u);
	badguy1.findLadder(l);
	badguy1.update( timechange );

	u.draw();
	l.draw();
	badguy1.draw();
	if(won){
		winner();
	}
	if(lost){
		looser();
	}


	glutSwapBuffers();
         
         // update the last time
         lasttime = currenttime;
         currenttime = getTime();
         timechange = currenttime - lasttime;
}





////////////////////////////////
// This is called on a Down Keypress        
////////////////////////////////
static void OnKeyboardDown( unsigned char k, int x, int y )
{ 
	if(won==true || lost==true)
		exit(0);
	switch (k)
	{
   // If user pressed 'q' or 'ESC', then exit the app.
   // this is really ungraceful, but necessary since GLUT does a while(1)
   // as it's control loop.  There is no GLUT method to exit, unfortunately.
	case 'q':
	case 27:
		exit( 0 );
		break;

	case 'a':

	   
		// !!!TODO!!!: add handler for when UP is pressed
		break;

	case 'z':
		// !!!TODO!!!: add handler for when DOWN is pressed
		break;

      
	default:
		// do nothing if no key is pressed
		break;
	}
}
////////////////////////////////
// This is called on an Up Keypress        
////////////////////////////////
static void OnKeyboardUp( unsigned char k, int x, int y ) 
{
	switch (k)
	{
	case 'a':
		break;

	case 'z':
		// !!!TODO!!!: add handler for when DOWN is released
		break;
   
	default:
		// do nothing if no key is pressed
		break;
	}
}

////////////////////////////////
// This is called on a Down Keypress 
// of a "special" key such as the grey arrows.
////////////////////////////////
static void OnSpecialKeyboardDown(int k, int x, int y) 
{
	int pos, h,temp, templ, tempw;
	
	if(!u.isFalling()){
		switch (k)
		{
		case GLUT_KEY_UP:
			pos = u.getPos();
			h = u.getHeight();
			temp = (h)/30;
			if(l.checkRegistry(pos+5, temp)==LADDER || l.checkRegistry(pos, temp)==LADDER && l.checkRegistry(pos, temp+1)!=BRICK){
				u.setHeight(h+10);
				if(u.getTexState()==2)
					u.setTexState(3);
				else
					u.setTexState(2);
			}
			break;
		case GLUT_KEY_DOWN:
			pos = u.getPos();
			h = u.getHeight();
			templ = (h-1)/30;
			tempw = (h)/30;
			if(l.checkRegistry(pos, templ)==LADDER){
				u.setTexState(4);
				u.setHeight(h-10);
				
			}
			if(h%30==0){
				if(l.checkRegistry(pos, templ+1)==WIRE){
					u.setFalling();
					u.setHeight(h-5);
					u.setTexState(4);

				}
			}
			break;
		case GLUT_KEY_LEFT:
			pos = u.getPos();
			h = u.getHeight();
			temp = h/30;
			if(pos == 0 || l.checkRegistry(pos-5, temp)==BRICK){
				break;
			}else if(l.checkRegistry(pos-5, temp-1)==LADDER || l.checkRegistry(pos, temp-1)==LADDER || l.checkRegistry(pos, temp)==LADDER || l.checkRegistry(pos-5, temp)==LADDER || (l.checkRegistry(pos-5, temp-1)==BRICK && h%30==0)){
				u.setPos(pos-5);
				if(u.getTexState()==0)
					u.setTexState(1);
				else
					u.setTexState(0);

			}else if(l.checkRegistry(pos-5, temp)==WIRE && h%30==0){
				u.setPos(pos-5);
				if(u.getTexState()==4)
					u.setTexState(5);
				else
					u.setTexState(4);

			}else{
				u.setFalling();
				u.setPos(pos-5);
				u.setHeight(h-5);
			}

			
			break;

		case GLUT_KEY_RIGHT:
			pos = u.getPos();
			h = u.getHeight();
			temp = h/30;
			if(pos==640 || l.checkRegistry(pos+10, temp)==BRICK){
				break;
			}else if(l.checkRegistry(pos+5, temp-1)==LADDER || l.checkRegistry(pos+5, temp)==LADDER || (l.checkRegistry(pos+5, temp-1)==BRICK && h%30==0)){
				u.setPos(pos+5);
				if(u.getTexState()==0)
					u.setTexState(1);
				else
					u.setTexState(0);
			}else if((l.checkRegistry(pos+10, temp)==WIRE && h%30==0)){
				u.setPos(pos+5);
				if(u.getTexState()==4)
					u.setTexState(5);
				else
					u.setTexState(4);
			}else{
				u.setFalling();
				u.setPos(pos+5);
				u.setHeight(h-5);
			}
			break;

		default:
			// do nothing if no special key pressed
			break;
		}
	}		
}
////////////////////////////////
// This is called on a Up Keypress        
////////////////////////////////
static void OnSpecialKeyboardUp( int k, int x, int y ) 
{
   switch (k)
   {
   case GLUT_KEY_UP:
      // !!!TODO!!!: add handler for when UP is released
      break;
   case GLUT_KEY_DOWN:
      // !!!TODO!!!: add handler for when DOWN is released
      break;
   default:
      // do nothing if no special key pressed
      break;
   }
}

////////////////////////////////
// This is called when mouse changes position
// x and y are the screen position 
// in your 2D window's coordinate frame
////////////////////////////////
static void OnMousePos( int x, int y ) 
{
   // !!!TODO!!!: do something based on mouse position
}

////////////////////////////////
// This is called when mouse clicks
////////////////////////////////
static void OnMouseClick( int a, int b, int c, int d )
{
   // !!!TODO!!!: Need mouse interaction?
   //             read the glut docs/manpage to find out how to query 
   //             which button was pressed...
   //             you may have to get this from the glut website 
   //             (use www.google.com to search for it)
}


//////////////////////////////////////////////////
// This is called repeatedly, as fast as possible
//////////////////////////////////////////////////
static void OnIdle()
{
	int h;
	// According to the GLUT specification, the current window is
	// undefined during an idle callback.  So we need to explicitly change
	// it if necessary
	if ( glutGetWindow() != app.mainWin_contextID )
			glutSetWindow( app.mainWin_contextID );

	// tell glut to call redisplay (which then calls OnRedisplay)
	if(u.isFalling()){
		h = u.getHeight();
		u.setHeight(h-5);
		if(l.checkRegistry(u.getPos(), (u.getHeight()-1)/30)==BRICK || (l.checkRegistry(u.getPos(), (u.getHeight())/30)==WIRE && (u.getHeight()%30==0 )) || u.getHeight()<=0 || l.checkRegistry(u.getPos(), (u.getHeight()-1)/30)==LADDER)
			u.setNotFalling();
		glutPostRedisplay();
	}else{
		glutPostRedisplay();	
	}
}


/////////////////////////////////////////////
// This is called on a Resize of the glut window
/////////////////////////////////////////////
static void OnReshape( int width, int height ) 
{
   // save these params in case your app needs them
   app.width = width;
   app.height = height;
   
   // set your viewport to the extents of the window
   glViewport( 0, 0, width, height );
   
   // let the app run idle, while resizing, 
   // glut does not do this for us automatically, so call OnIdle explicitly.
   OnIdle();
}

// Initialize the application
// initialize the state of your app here if needed...
static int OnApplicationInit()
{
	// Don't put open GL code here, this func may be called at anytime
	// even before the API is initialized 
	// (like before a graphics context is obtained)




   
	// !!!TODO!!!: put your initialization code here.

	l.loadlevel();
	l.init();
	return 0;
}


void main( int argc, char* argv[] )
{
    // Initialize the application
    // initialize the state of your app here if needed...
    OnApplicationInit();
   
    // Set the window's initial size
    ::glutInitWindowSize( 640, 480 );
    ::glutInit( &argc, argv );
  
    // Set to double buffer to reduce flicker
    ::glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    
    // Set the window title
    app.mainWin_contextID = ::glutCreateWindow( "Simple Load Runner" );
    
    std::cout<<"\n"<<std::flush;
    std::cout<<"Load Runner 2d" << std::endl << "by Josh Brown" 
		<< std::endl << "browner@iastate.edu"<< std::endl<<std::flush;
    std::cout<<"\n"<<std::flush;
    
   // display callbacks.
   ::glutReshapeFunc( OnReshape );
   ::glutIdleFunc( OnIdle );
   ::glutDisplayFunc( OnRedisplay );

   // tell glut to not call the keyboard callback repeatedly 
   // when holding down a key. (uses edge triggering, like the mouse)
 //  ::glutIgnoreKeyRepeat( 1 );

	// Initialize the textures
	initTexture();
	l.initTexture();
	u.initTexture();
	badguy1.initTexture();
   // keyboard callback functions.
   ::glutKeyboardFunc( OnKeyboardDown );
   ::glutKeyboardUpFunc( OnKeyboardUp );
   ::glutSpecialFunc( OnSpecialKeyboardDown );
   ::glutSpecialUpFunc( OnSpecialKeyboardUp );

   // mouse callback functions...
   ::glutMouseFunc( OnMouseClick );
   ::glutMotionFunc( OnMousePos );
   ::glutPassiveMotionFunc( OnMousePos );

    // start the application loop, your callbacks will now be called
    // time for glut to sit and spin.
    ::glutMainLoop();
}



