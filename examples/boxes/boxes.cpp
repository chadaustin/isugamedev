/**
 * A simple, introductory GLUT app that draws a box on the screen.
 *
 * On Windows, make sure you link with glut.lib, opengl32.lib and glu32.lib
 * 
 * Compile on linux with the command:
 * g++ -o boxes -lGL -lGLU -lglut boxes.cpp
 *
 * Author: Ben Scott <bscott@iastate.edu>
 * Public domain
 */
#include <GL/glut.h>

// global variables that controls the position of the square
int xpos = 0;
int ypos = 0;

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

/**
 * Called by glut whenever we need to redisplay the window. Note that I've also
 * setup glut to call this function whenever it has nothing else to do by
 * registering this function as the Idle function in main(..).
 */
void MyDisplay()
{
   // make sure everything is setup correctly to draw!
   ResetDisplay();

   // tell openGL that we want to draw a red square
   glColor3f( 1.0f, 0.0f, 0.0f );
   glBegin( GL_QUADS );
      glVertex2i( xpos + 100, ypos + 100 );
      glVertex2i( xpos + 200, ypos + 100 );
      glVertex2i( xpos + 200, ypos + 200 );
      glVertex2i( xpos + 100, ypos + 200 );
   glEnd();

   // we've been drawing the the back buffer that is not currently visible on
   // the screen. tell glut to swap the back and front buffers to make our new
   // square visible!
   glutSwapBuffers();
}

//------------------------------------------------------------------------------

/**
 * Called by GLUT whenever a key that can be represented as a char has been
 * pressed.
 */
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

   // ESC (char code 27) quits this application
   else if ( key == 27 ) {
      exit( 0 );
   }
}

//------------------------------------------------------------------------------

int main( int argc, char** argv )
{
   // initialize glut and tell it what our window should be like
   glutInit( &argc, argv );
   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
   glutInitWindowSize( 640, 480 );
   glutInitWindowPosition( 100, 100 );
   glutCreateWindow( "i love glut!" );

   // register callbacks to receive events from the OS
   glutDisplayFunc( MyDisplay );
   glutIdleFunc( MyDisplay );
   glutKeyboardFunc( MyKeyPress );

   // start the application loop, your callbacks will now be called.
   // glutMainLoop() will NEVER return
   glutMainLoop();
}
