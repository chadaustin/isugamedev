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

//boost smart pointers
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
#include "Collider.h"

#include "QuakeNav.h"


typedef ani::BodyPtr BodyPtr;
typedef boost::shared_ptr< ani::Operator<ani::Body> > BodyOperatorPtr;
typedef boost::shared_ptr< CollisionOperator<ani::Body> > CollisionBodyOperatorPtr;
typedef boost::shared_ptr< DriveNavigationOperator<ani::Body> > DriveNavigationBodyOperatorPtr;

// a place to store application data...
class App
{
public:
   App() : width( 0 ), height( 0 ), mainWin_contextID( -1 ), mJump( false )
   {
      stopWatch.pulse();
   }
   int width, height;
   int mainWin_contextID;
   cubeGeometry cube;
   StopWatch stopWatch;
   bool mJump;

   class Nav
   {
   public:
      Nav()
      {
         //mDynamicSystem = new ani::DynamicSystem<ani::Body, ani::RungeKuttaODEsolver<ani::Body> >;
         mDynamicSystem = new ani::DynamicSystem<ani::Body>;
         
         mAvatar.reset( new ani::Body );
         
         // Pounds to Kilograms, multiply Pounds by 0.45
         // Kilograms to Pounds, multiply Kilograms by 2.2 
         //mAvatar->setMass( 170.0f * 0.45f );
         mAvatar->setMass( 100.0f );
         mAvatar->setVolume( Vec3<float>( 1,1,1 ) );
         mAvatar->setPosition( Vec3<float>( 0,20,-20 ));
         
         mCollider.reset( new CollisionOperator<ani::Body> );
         mCollider->setElastic( 0.5f );
         
         mNavigator.reset( new DriveNavigationOperator<ani::Body> );
         
         BodyOperatorPtr gravity( new Gravity<ani::Body> );
         
         mDynamicSystem->add( sp_dynamic_cast< ani::Operator<ani::Body> >( gravity ) );
         mDynamicSystem->add( sp_dynamic_cast< ani::Operator<ani::Body> >( mNavigator ) );
         // goes last
         mDynamicSystem->add( sp_dynamic_cast< ani::Operator<ani::Body> >( mCollider ) );
         
         mDynamicSystem->add( mAvatar );
         
         std::cout<<"Nav setup\n"<<std::flush;
      }
      ~Nav()
      {
      }
      
      void step( float time )
      {
         mDynamicSystem->step( time );
      }

      // physics system
      DriveNavigationBodyOperatorPtr   mNavigator;
      CollisionBodyOperatorPtr         mCollider;
      BodyPtr                          mAvatar;
      ani::DynamicSystem<ani::Body>*   mDynamicSystem;
   };

   Nav mNav;
   QuakeNav mQuakeNav;
   bool mStop;
   bool mAccelerate;
   bool mTurnLeft, mTurnRight;

};
App app;

void drawGrid()
{
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
   glTranslatef( -app.mNav.mAvatar->position()[0], 0, -app.mNav.mAvatar->position()[2] - 20);
   
   
   glTranslatef( 0, -10, 0 );

   glPushMatrix();
      Matrix4f mat( Matrix4f::identity() );
      mat.makeIdent();
      kev::quat2mat( app.mNav.mAvatar->rotation(), mat );
      mat.setTrans( app.mNav.mAvatar->position() );
      glMultMatrixf( mat.data() );
      glScalef( app.mNav.mAvatar->volume()[0], app.mNav.mAvatar->volume()[1], app.mNav.mAvatar->volume()[2] );
      app.cube.render();
   glPopMatrix();
   
      
   drawGrid();
   
   glTranslatef( 5, 0, -20 );
	
   app.cube.render();
   
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
   
   app.mNav.step( app.stopWatch.timeInstant() );
   
   const Matrix4f& pointerMat = app.mQuakeNav.matrix();
   Vec3<float> pointerPos;

   if (app.mAccelerate == true)
   {
      Vec3<float> dir;
      kev::xformVec( dir, pointerMat, Vec3<float>(0.0f, 0.0f, -1000.0f) );
      //std::cout<<"accel "<<dir<<"\n"<<std::flush;
      
      app.mNav.mNavigator->force( dir );
   }
   else if (app.mJump == true )
   {
      app.mJump = false;
      app.mNav.mNavigator->force( Vec3<float>( 0,30000,0 ) );
   }
   else if (app.mStop == true)
   {
      //std::cout<<"stop\n"<<std::flush;
      app.mNav.mNavigator->stop();
   }

   float t = 1.0f;
   if (app.mTurnRight == true)
   {
      Vec3<float> q;
      q.set( 0.0f, -t, 0.0f );
      app.mNav.mNavigator->torque( q );
   }
   if (app.mTurnLeft == true)
   {
      Vec3<float> q;
      q.set( 0.0f, t, 0.0f );
      app.mNav.mNavigator->torque( q );
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

	case 'a':
      {
         app.mTurnLeft = true;
      }
   break;
        
	case 's':
      app.mAccelerate = false;
      app.mStop = true;
      break;

   case 'd':
      {
         app.mTurnRight = true;
      }
      break;

   case 'w':
      app.mAccelerate = true;
      app.mStop = false;
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
   case 'w':
      app.mAccelerate = false;
      app.mStop = false;
      break;
	case 'a':
      app.mTurnLeft = false;
      break;
   case 'd':
      app.mTurnRight = false;
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
		app.mJump = true;
      break;
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

