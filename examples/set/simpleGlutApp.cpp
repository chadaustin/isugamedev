

#ifdef WIN32
   #include <windows.h>  // make the app win32 friendly. :)
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include "card.h"
#include "deck.h"

int mouseX, mouseY;


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
double timechange = 0.0;
double lasttime = getTime(), currenttime = getTime();
int count=0;
int i,j;
deck dek;


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



	count=0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	dek.draw();
   
   count=0;
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
   mouseX = x;
   mouseY = app.height-y;
}

////////////////////////////////
// This is called when mouse clicks
////////////////////////////////
static void OnMouseClick( int button, int state, int x, int y )
{
   int temp; // temp card place 
   // !!!TODO!!!: Need mouse interaction?
   //             read the glut docs/manpage to find out how to query 
   //             which button was pressed...
   //             you may have to get this from the glut website 
   //             (use www.google.com to search for it)
   if (button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
      if((temp=dek.isACard(mouseX, mouseY))!=-1)
         std::cout << temp << std::endl;
         dek.selectCard(temp);
   }
}


//////////////////////////////////////////////////
// This is called repeatedly, as fast as possible
//////////////////////////////////////////////////
static void OnIdle()
{
//	int h;
	// According to the GLUT specification, the current window is
	// undefined during an idle callback.  So we need to explicitly change
	// it if necessary
	if ( glutGetWindow() != app.mainWin_contextID )
			glutSetWindow( app.mainWin_contextID );

	// tell glut to call redisplay (which then calls OnRedisplay)
	glutPostRedisplay();	
	
}

/**
 * Sets up OpenGL so that everything's ready for us to draw a new frame.
 */
void ResetDisplay()
{
   // clear the screen with black
   glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
   glClear( GL_COLOR_BUFFER_BIT );

   // setup the projection matrix so OpenGL knows we want to do 2D graphics
   glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluOrtho2D( 0.0f, 640.0f, 0.0f, 480.0f );

   // reset the modelview matrix to the identity matrix
   glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();
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
   ResetDisplay();
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
    std::cout<<"set - by the Iowa State Game Developers" << std::endl << "by Josh Brown (contribution: 100%)" 
		<< std::endl << "browner@iastate.edu"<< std::endl<<std::flush;
    std::cout<<"\n"<<std::flush;
    
   // display callbacks.
   ::glutReshapeFunc( OnReshape );
   ::glutIdleFunc( OnIdle );
   ::glutDisplayFunc( OnRedisplay );

   // tell glut to not call the keyboard callback repeatedly 
   // when holding down a key. (uses edge triggering, like the mouse)
 //  ::glutIgnoreKeyRepeat( 1 );

   // keyboard callback functions.
   ::glutKeyboardFunc( OnKeyboardDown );
   ::glutKeyboardUpFunc( OnKeyboardUp );
   ::glutSpecialFunc( OnSpecialKeyboardDown );
   ::glutSpecialUpFunc( OnSpecialKeyboardUp );

   // mouse callback functions...
   ::glutMouseFunc( OnMouseClick );
   ::glutMotionFunc( OnMousePos );
   ::glutPassiveMotionFunc( OnMousePos );

   dek.init();
   
    // start the application loop, your callbacks will now be called
    // time for glut to sit and spin.
    ::glutMainLoop();
}



