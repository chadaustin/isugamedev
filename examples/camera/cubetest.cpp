// simple glut application: look for the !!!TODO!!!s, and fill in your code 
//                          there as needed
// kevin meinert - kevn@vrac.iastate.edu
// Public domain
//

#ifdef WIN32
   #include <windows.h>  // make the app win32 friendly. :)
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include "camera.h"
#include "c:/gamedev/tank/Vec3.h"

int temp;

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

camera camera;


void drawBox(){
	glColor3f(1.0f,0.0f,0.0f);
	glTranslatef(0,0,-50);
	glBegin(GL_QUADS);
		// Front Face
		glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		// Back Face
		glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		// Top Face
		glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		// Bottom Face
		glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		// Right face
		glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		// Left Face
		glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
	glEnd();
}
	


void drawGrid()
{
   glColor3f(1,1,1);
   glBegin( GL_LINES );
      for ( int x = -1000; x < 1000; ++x)
      {
         glVertex3f( -1000, 0, x );
         glVertex3f(  1000, 0, x );
         glVertex3f( x, 0, -1000 );
         glVertex3f( x, 0,  1000 );
      }
   glEnd();
}

void drawCamera(){
	glLoadIdentity();
	
	glMultMatrixf( camera.getMat().data() );

}


//////////////////////////////////////////////////
// This is called on a glutPostRedisplay
//////////////////////////////////////////////////
static void OnRedisplay()
{ 
   glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
   glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
   
   
   // set up the projection matrix
   glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective( 80.0f, app.width / app.height, 0.01f, 1000.0f );
                           
   // initialize your matrix stack used for transforming your models
    glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();      

   // !!!TODO!!!: replace the following with your own opengl commands!
   drawCamera();

   drawGrid();
   drawBox();
   // !!!TODO!!!: ////////////////////////////////////////
   
   // swaps the front and back frame buffers.
   // hint: you've been drawing on the back, offscreen, buffer.  
   // This command then brings that framebuffer onscreen.
   glutSwapBuffers();
}

//////////////////////////////////////////////////
// This is called repeatedly, as fast as possible
//////////////////////////////////////////////////
static void OnIdle()
{
   // According to the GLUT specification, the current window is
   // undefined during an idle callback.  So we need to explicitly change
   // it if necessary
   if ( glutGetWindow() != app.mainWin_contextID )
           glutSetWindow( app.mainWin_contextID );

   // tell glut to call redisplay (which then calls OnRedisplay)
   glutPostRedisplay();
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

////////////////////////////////
// This is called on a Down Keypress        
////////////////////////////////
static void OnKeyboardDown( unsigned char k, int x, int y )
{ 

    Vec3<float> temp;
    switch (k)
    {
    // If user pressed 'q' or 'ESC', then exit the app.
    // this is really ungraceful, but necessary since GLUT does a while(1)
    // as it's control loop.  There is no GLUT method to exit, unfortunately.
    case 27:
      exit( 0 );
      break;

    case 'w':
        // !!!TODO!!!: add handler for when a is pressed

	    temp = camera.getPos();
	    temp[1]-=1.5;
	    camera.setPos(temp);
	    break;

    case 'x':
	    // !!!TODO!!!: add handler for when z is pressed
        temp=camera.getPos();
	    temp[1]+=1.5;
	    camera.setPos(temp);
	  
	    break;
	case 'a':
		temp=camera.getPos();
		temp[0]+=1.5;
		camera.setPos(temp);
		break;
	case 'd':
		temp=camera.getPos();
		temp[0]-=1.5;
		camera.setPos(temp);
		break;
	case 'q':
		temp=camera.getPos();
		temp[2]+=1.5;
		camera.setPos(temp);
		break;
	case 'z':
		temp=camera.getPos();
		temp[2]-=1.5;
		camera.setPos(temp);
		break;
	case 'g':
		std::cout << camera.getMat() << std::endl;
		break;

		      
	default:
      // do nothing if no key is pressed
      break;
   }
}
////////////////////////////////
// This is called on a Up Keypress        
////////////////////////////////
static void OnKeyboardUp( unsigned char k, int x, int y ) 
{
   switch (k)
   {
   case 'a':
      // !!!TODO!!!: add handler for when UP is released
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
   switch (k)
   {
   case GLUT_KEY_UP:
      
		camera.setTilt(10);

      break;
   case GLUT_KEY_DOWN:
	   camera.setTilt(-10);
      // !!!TODO!!!: add handler for when DOWN is pressed
      break;
   case GLUT_KEY_LEFT:
	  camera.spin(-10, 0, 1, 0);
	  break;
   case GLUT_KEY_RIGHT:
	  camera.spin(10, 0 , 1, 0);
	  break;
   default:
      // do nothing if no special key pressed
      break;
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


// Initialize the application
// initialize the state of your app here if needed...
static void OnApplicationInit()
{
   // Don't put open GL code here, this func may be called at anytime
   // even before the API is initialized 
   // (like before a graphics context is obtained)
   
   
   // !!!TODO!!!: put your initialization code here.
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
    app.mainWin_contextID = ::glutCreateWindow( "GLUT application" );
    
    std::cout<<"\n"<<std::flush;
    std::cout<<"YourApp - by YourName - you@your.address.com\n"<<std::flush;
    std::cout<<"       usage:  some params\n"<<std::flush;
    std::cout<<"               some more params\n"<<std::flush;
    std::cout<<"\n"<<std::flush;
    
   // display callbacks.
   ::glutReshapeFunc( OnReshape );
   ::glutIdleFunc( OnIdle );
   ::glutDisplayFunc( OnRedisplay );

   // tell glut to not call the keyboard callback repeatedly 
   // when holding down a key. (uses edge triggering, like the mouse)
//   ::glutIgnoreKeyRepeat( 1 );

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



