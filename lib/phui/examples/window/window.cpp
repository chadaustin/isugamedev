#include <GL/glut.h>
#include <phui/phui.h>

static int gWidth  = 640;
static int gHeight = 480;
static int mainWin_contextID;

//-----------------------------------------------------------------------------

void OnRedisplay()
{
   glClearColor( 0, 0, 0, 1 );
   glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

   // setup projection
   glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluPerspective( 80.0f, (float)gWidth / (float)gHeight, 0.01f, 1000.0f );

   // setup modelview
   glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();

   // draw a teapot
   glPushMatrix();
      glTranslatef( 0, 0, -50 );
      glutSolidTeapot( 25 );
   glPopMatrix();

   // draw a window
   // ui->draw();

   glutSwapBuffers();
}

void OnReshape( int width, int height )
{
   gWidth = width;
   gHeight = height;

   glViewport( 0, 0, gWidth, gHeight );
}

void OnIdle()
{
   // According to the GLUT specification, the current window is
   // undefined during an idle callback.  So we need to explicitly change
   // it if necessary
   if ( glutGetWindow() != mainWin_contextID )
      glutSetWindow( mainWin_contextID );

   // tell glut to call redisplay (which then calls OnRedisplay)
   glutPostRedisplay();
}

void OnKeyboardDown( unsigned char key, int x, int y )
{
   // ESC or q
   if ( key == 27 || key == 'q' )
   {
      exit(0);
   }
}

int main( int argc, char** argv )
{
   glutInitWindowSize( gWidth, gHeight );
   glutInit( &argc, argv );
   glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
   mainWin_contextID = glutCreateWindow( "Window Example" );

   // callbacks
   glutDisplayFunc( OnRedisplay );
   glutReshapeFunc( OnReshape );
   glutIdleFunc( OnIdle );
   glutKeyboardFunc( OnKeyboardDown );

   glutMainLoop();
}
