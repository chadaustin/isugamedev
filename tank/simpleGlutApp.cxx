// Tank - isu game dev club
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

#include "Vec3.h"
#include "Matrix4f.h"
#include "Camera.h"
#include "Tank.h"
#include "glRenderLight.h"
#include "StopWatch.h"

// a place to store application data...
class App
{
public:
   App() : width( 0 ), height( 0 ), mainWin_contextID( -1 )
   {
      Vec3<float> initial_tank_pos( 0, 0, -30 );
      tank.setPos( initial_tank_pos );
      
      camera.follow( true );
      camera.setTargetPos( tank.matrix() );
      camera.setPitch( 45.0f );
      
      light.setPos(0.0f, 0.0f, 0.0f, 1.0f);
      light.setColor(Light::diffuse);
      light.on();
      stopWatch.pulse();
   }
   int width, height;
   int mainWin_contextID;
   Tank tank;
   Camera camera;
   Light light;
   StopWatch stopWatch;
};
App app;





void drawGrid()
{
   glPushAttrib( GL_ENABLE_BIT );
      glDisable( GL_LIGHTING );
      glColor3f( 0.7, 0.3, 0.1 );
      glBegin( GL_LINES );
         for ( int x = -1000; x < 1000; x += 5)
         {
            glVertex3f( -1000, 0, x );
            glVertex3f(  1000, 0, x );
            glVertex3f( x, 0, -1000 );
            glVertex3f( x, 0,  1000 );
         }
      glEnd();
      //glEnable( GL_LIGHTING );
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
   glDisable( GL_CULL_FACE );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
      
   // set up the projection matrix
   glMatrixMode( GL_PROJECTION );
        glLoadIdentity();                     
        gluPerspective( 80.0f, app.width / app.height, 0.01f, 1000.0f );
                           
   // initialize your matrix stack used for transforming your models
    glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();      

      app.camera.draw();
      
      glEnable( GL_LIGHTING );
      glRender( app.light );
  
      app.tank.draw();
   
      
   drawGrid();
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
   app.stopWatch.pulse();
   
   // According to the GLUT specification, the current window is
   // undefined during an idle callback.  So we need to explicitly change
   // it if necessary
   if ( glutGetWindow() != app.mainWin_contextID )
           glutSetWindow( app.mainWin_contextID );

   app.camera.setTargetPos( app.tank.matrix() );
   app.tank.update( app.stopWatch.timeInstant() );
   app.camera.update( app.stopWatch.timeInstant() );
   
   Vec3<float> lightOffset(-10.0f, 0.0f, 0.0f);
   lightOffset = app.camera.position() + lightOffset;
   app.light.setPos(lightOffset[0], lightOffset[1], lightOffset[2], 1.0f);

   
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

   case 'w':
      app.camera.setPitchVel( 1 );
      break;

   case 's':
      app.camera.setPitchVel( -1 );
      break;

   case 'a':
      app.camera.setYawVel( 1 );
      break;

   case 'd':
      app.camera.setYawVel( -1 );
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
   case 'w':
   case 's':
      app.camera.setPitchVel( 0 );
      break;
   case 'a':
   case 'd':
      app.camera.setYawVel( 0 );
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
   {
      app.tank.setVelocity( 0.0f, 0.0f, -40.0f );
      break;
   }
   case GLUT_KEY_DOWN:
   {
      app.tank.setVelocity( 0.0f, 0.0f, 40.0f );
      break;
   }
   case GLUT_KEY_RIGHT:
      app.tank.setAngVel( -3.0f );
      break;
   case GLUT_KEY_LEFT:
      app.tank.setAngVel( 3.0f );
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
   case GLUT_KEY_DOWN:
   {
      app.tank.setVelocity( 0.0f, 0.0f, 0.0f );
      break;
   }
   case GLUT_KEY_RIGHT:
   case GLUT_KEY_LEFT:
      app.tank.setAngVel( 0.0f );
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

    // start the application loop, your callbacks will now be called
    // time for glut to sit and spin.
    ::glutMainLoop();
}

