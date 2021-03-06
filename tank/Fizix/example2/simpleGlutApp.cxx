// Kevin Meinert
// simple glut application: look for the !!!TODO!!!s, and fill in your code 
//                          there as needed
//

#ifdef WIN32
   #include <windows.h>  // make the app win32 friendly. :)
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>

#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr_dyncast.hpp>

#include "cubeGeometry.h"
#include "StopWatch.h"

#include <Quat.h>
#include <Matrix4f.h>
#include <Vec3.h>
#include <Defines.h>
#include <extend.h>

// particle system
#include "Fizix/Body.h"
#include "Fizix/Operator.h"
#include "Fizix/EulerODEsolver.h"
#include "Fizix/RungeKuttaODEsolver.h"
#include "Fizix/DynamicSystem.h"
#include "Fizix/systems/Torch.h"

#include "QuakeNav.h"

// a place to store application data...
class App
{
public:
   App() : width( 0 ), height( 0 ), mainWin_contextID( -1 )
   {
      stopWatch.pulse();
   }
   int width, height;
   int mainWin_contextID;
   cubeGeometry cube;
   StopWatch stopWatch;
   QuakeNav mQuakeNav;
   
   void drawSystem()
   {
      
         for (int x = 0; x < torch->entities().size(); ++x)
         {
            boost::shared_ptr<ani::FireParticle> ent( torch->entities()[x] );
            const Vec3<float>& pos = ent->position();
            const ColorRGBA& col = ent->color(); 
            glColor4f( col[0], col[1], col[2], col[3] );
            //glPushMatrix();
            //glTranslatef( pos[0], pos[1], pos[2] );
            
            glBegin( GL_TRIANGLES );
            glNormal3f( 0,0,1 );
            glVertex3f( pos[0], pos[1], pos[2] );
            glVertex3f( pos[0]+1, pos[1], pos[2] );
            glVertex3f( pos[0]+1, pos[1]+1, pos[2] );
            glEnd();

            //glPopMatrix();
            //glVertex3f( pos[0], pos[1], pos[2] );
            //std::cout<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<"\n"<<std::flush;
         }
   }   
   
   boost::shared_ptr< ani::Torch<ani::FireParticle> > torch;
};
App app;

void drawGrid()
{
   int extent = 1000;

   glPushAttrib( GL_ENABLE_BIT );
      glDisable( GL_LIGHTING );
      glColor3f( 0.1f, 0.3f, 0.7f );
      glBegin( GL_LINES );
         for ( int x = -extent; x < extent; x += 5)
         {
            glVertex3f( -extent, 0, x );
            glVertex3f(  extent, 0, x );
            glVertex3f( x, 0, -extent );
            glVertex3f( x, 0,  extent );
         }
      glEnd();
   glPopAttrib();
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

   //glTranslatef( 0, 0, -10 );
   
   const Matrix4f& pointerMat = app.mQuakeNav.matrix();
   glMultMatrixf( pointerMat.data() );
   
   glTranslatef( 0, -10, 0 );

      
   drawGrid();
   
   
   
   glTranslatef( 5, 0, -20 );
   
   app.cube.render();

   glTranslatef( 0, 3, 0 );
   app.drawSystem();
   
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
   app.stopWatch.pulse();
   
   app.torch->step( app.stopWatch.timeInstant() );

   static int output_cnt = 0;
   output_cnt++;
   if (output_cnt % 30 == 4)
   {
      std::cout<<"fps: "<<app.stopWatch.fpsAverage()<<" ... "<<app.torch->entities().size()<<" ents in system\n"<<std::flush;;
   }   
   
   ////////////////////////////
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
   switch (k)
   {
   // If user pressed 'q' or 'ESC', then exit the app.
   // this is really ungraceful, but necessary since GLUT does a while(1)
   // as it's control loop.  There is no GLUT method to exit, unfortunately.
   case 'q':
   case 27:
      exit( 0 );
      break;

      case 'i':
      app.mQuakeNav.applyZtrans( -10 );
      break;
      
      case 'k':
      app.mQuakeNav.applyZtrans( 10 );
      break;


      case 'j':
      app.mQuakeNav.applyYrot( kev::deg2rad( -45.0f ) );
      break;
      
      case 'l':
      app.mQuakeNav.applyYrot( kev::deg2rad( 45.0f ) );
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
   case 's':
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
   case GLUT_KEY_DOWN:
      // !!!TODO!!!: add handler for when DOWN is pressed
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
   
   
}


void main(int argc, char* argv[])
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
   ::glutIgnoreKeyRepeat( 1 );

   // keyboard callback functions.
   ::glutKeyboardFunc( OnKeyboardDown );
   ::glutKeyboardUpFunc( OnKeyboardUp );
   ::glutSpecialFunc( OnSpecialKeyboardDown );
   ::glutSpecialUpFunc( OnSpecialKeyboardUp );

   // mouse callback functions...
   ::glutMouseFunc( OnMouseClick );
   ::glutMotionFunc( OnMousePos );
   ::glutPassiveMotionFunc( OnMousePos );

   //::glutWarpPointer( app.width / 2, app.height / 2 );
   
    // start the application loop, your callbacks will now be called
    // time for glut to sit and spin.
    ::glutMainLoop();
}

