
#ifdef _MSC_VER
  // disable 'identifier was truncated to 255 characters in debug information' warning
  #pragma warning(disable: 4786)
#endif

#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>

#include "TankGame.h"
#include "AudioSystemFactory.h"
#include "GeodeCache.h"

//: App width/height
static float sWidth = 640.0f;
static float sHeight = 640.0f;

static TankGame *game = new TankGame();
static IAudioSystem* audioSystem;
static int mainWin_contextID;

// Provide functionality to automatically use different lights.
// Leave the first light (0) alone.
static int nextLightNum = 0;

int GetNextLightNum()
{
   return (nextLightNum++ % 7) + 1;
}

//------------------------------------------------------------------------------

//: This is called repeatedly, as fast as possible
static void
OnIdle()
{
   // Update the state of the game
   game->update();
     
   // According to the GLUT specification, the current window is
   // undefined during an idle callback.  So we need to explicitly change
   // it if necessary
   if ( glutGetWindow() != mainWin_contextID )
           glutSetWindow( mainWin_contextID );

   // tell glut to call redisplay (which then calls OnRedisplay)
   glutPostRedisplay();
}

//------------------------------------------------------------------------------

//: This is called on a glutPostRedisplay
static void
OnRedisplay()
{ 
   // when using multidisplays we'll need to actually 
   // set this to a different number for each windows opened.
   ContextManager::instance().setContext( mainWin_contextID );

   // Make sure GL is in the correct state
   glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
   glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
   glEnable( GL_DEPTH_TEST );
   glFrontFace( GL_CCW );
   glCullFace( GL_BACK );
   glEnable( GL_CULL_FACE );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
   glEnable( GL_COLOR_MATERIAL ); // enable materials
   glEnable( GL_TEXTURE_2D );
   
   // set up the projection matrix
   glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluPerspective( 80.0f, sWidth / sHeight, 0.01f, 1000.0f );

   // initialize your matrix stack used for transforming your models
   glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();
      glPushMatrix();
         // Draw the game!
         game->draw( game->getPlayer( 0 ) );
      glPopMatrix();

   // swaps the front and back frame buffers.
   // hint: you've been drawing on the back, offscreen, buffer.
   // This command then brings that framebuffer onscreen.
   glFlush();
   glutSwapBuffers();
}

//------------------------------------------------------------------------------

//: Initialize the application
//  initialize the state of your app here if needed...
static void
OnApplicationInit()
{
   // Don't put open GL code here, this func may be called at anytime
   // even before the OpenGL API is initialized 
   // (like before a graphics context is obtained)
   // can cause really bad things to happen...

   // Create the new player
   Player *p = new Player();
   Vec3<float> initial_tank_pos( 0, 0, -30 );
   p->getTank()->setPos( initial_tank_pos );
   p->getCamera().setTargetPos( p->getTank()->matrix() );
   game->addPlayer( p );

   // Init the game engine
   game->init();

   Light light;
   light.setNumber(0);
   light.setPos(0.0f, 0.0f, 0.0f, 1.0f);
   light.setColor( Light::diffuse, 1.0f, 1.0f, 1.0f );
   light.on();
   game->getWorld().setLight( light );

   //Load our tank model
   safe_ptr<Geode> geom = NULL;
   GeodeCache::instance().load( geom, "models/ship.obj" );

   Entity *entity = new Entity();
   entity->setGeode( geom );

   //Put the tank in the world
   game->getWorld().add( entity );
}

//------------------------------------------------------------------------------

//: This is called on a resize of the glut window
static void OnReshape( int width, int height ) 
{
   // save these params in case your app needs them
   sWidth = static_cast<float>( width );
   sHeight = static_cast<float>( height );
   
   // set your viewport to the extents of the window
   glViewport( 0, 0, width, height );
   
   // let the app run idle, while resizing, 
   // glut does not do this for us automatically, so call OnIdle explicitly.
   OnIdle();
}

//------------------------------------------------------------------------------

//: This is called on a down keypress
static void OnKeyboardDown( unsigned char k, int x, int y )
{ 
   switch (k)
   {
   // If user pressed 'ESC', then exit the app->
   // this is really ungraceful, but necessary since GLUT does a while(1)
   // as it's control loop.  There is no GLUT method to exit, unfortunately.
   case 27:
      delete game;
      exit( 0 );
      break;

   case ' ':
   {
      Bullet *bullet = new Bullet();
      bullet->setPos( game->getPlayer( 0 )->getTank()->getBarrelEndPos() );
      bullet->setRot( game->getPlayer( 0 )->getTank()->rotation() );
      bullet->setRotVel( 5.0f );
      bullet->setVel( game->getPlayer( 0 )->getTank()->getForward() * 50.0f );
      game->getBullets().push_back( bullet );
      break;
   }
   case 'q':
      game->getPlayer( 0 )->getCamera().setFollowDistVel( 40 );
      break;

   case 'e':
      game->getPlayer( 0 )->getCamera().setFollowDistVel( -40 );
      break;

   case 'w':
      game->getPlayer( 0 )->getCamera().setPitchVel( 40 );
      break;

   case 's':
      game->getPlayer( 0 )->getCamera().setPitchVel( -40 );
      break;

   case 'a':
      game->getPlayer( 0 )->getCamera().setYawVel( 40 );
      break;

   case 'd':
      game->getPlayer( 0 )->getCamera().setYawVel( -40 );
      break;
      
   default:
      // do nothing if no key is pressed
      break;
   }
}

//------------------------------------------------------------------------------

//: This is called on an up keypress
static void OnKeyboardUp( unsigned char k, int x, int y )
{
   switch ( k )
   {
   case 'q':
   case 'e':
      game->getPlayer( 0 )->getCamera().setFollowDistVel( 0 );
      break;
   case 'w':
   case 's':
      game->getPlayer( 0 )->getCamera().setPitchVel( 0 );
      break;
   case 'a':
   case 'd':
      game->getPlayer( 0 )->getCamera().setYawVel( 0 );
      break;

   default:
      // do nothing if no key is pressed
      break;
   }
}

//------------------------------------------------------------------------------

//: This is called on a down keypress of a "special" key such as the grey arrow
//  keys.
static void OnSpecialKeyboardDown( int k, int x, int y )
{
   switch ( k )
   {
   case GLUT_KEY_UP:
      game->getPlayer( 0 )->getTank()->setVelocity( 0.0f, 0.0f, -40.0f );
      break;
   case GLUT_KEY_DOWN:
      game->getPlayer( 0 )->getTank()->setVelocity( 0.0f, 0.0f, 40.0f );
      break;
   case GLUT_KEY_RIGHT:
      game->getPlayer( 0 )->getTank()->setAngVel( -3.0f );
      break;
   case GLUT_KEY_LEFT:
      game->getPlayer( 0 )->getTank()->setAngVel( 3.0f );
      break;
   default:
      // do nothing on any other special key
      break;
   }
}


//------------------------------------------------------------------------------

//: This is called on an up keypress of a "special" key
static void OnSpecialKeyboardUp( int k, int x, int y )
{
   switch (k)
   {
   case GLUT_KEY_UP:
   case GLUT_KEY_DOWN:
   {
      game->getPlayer( 0 )->getTank()->setVelocity( 0.0f, 0.0f, 0.0f );
      break;
   }
   case GLUT_KEY_RIGHT:
   case GLUT_KEY_LEFT:
      game->getPlayer( 0 )->getTank()->setAngVel( 0.0f );
      break;
   default:
      // do nothing on any other special key
      break;
   }
}

//------------------------------------------------------------------------------

int
main( int argc, char **argv )
{
   // Initialize the application
   // initialize the state of your app here if needed...
   OnApplicationInit();

   audioSystem = CreateAudioSystem();
   if (!audioSystem) {
      exit(EXIT_FAILURE);
   }

   // Set the window's initial size
   ::glutInitWindowSize( (int)sWidth, (int)sHeight );
   ::glutInit( &argc, argv );

   // Set to double buffer to reduce flicker
   ::glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );

   // Set the window title
   mainWin_contextID = ::glutCreateWindow( "Space Tank" );

   std::cout<<"\n"<<std::flush;
   std::cout<<"SpaceTank - by isugamedev - gamedev@iastate.edu\n"<<std::flush;
   std::cout<<"       usage:  \n"<<std::flush;
   std::cout<<"               \n"<<std::flush;
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
//   ::glutMouseFunc( OnMouseClick );
//   ::glutMotionFunc( OnMousePos );
//   ::glutPassiveMotionFunc( OnMousePos );

    // start the application loop, your callbacks will now be called
    // time for glut to sit and spin.
    ::glutMainLoop();

    // shut down the audio system
    delete audioSystem;

    // the C++ standard implicitly does 'return 0' if control reaches the
    // end of main() but VC++, of course, doesn't support this
    return 0;
}

//------------------------------------------------------------------------------


#ifdef _WIN32
#ifndef _CONSOLE

int WINAPI WinMain(
  HINSTANCE /*instance*/,
  HINSTANCE /*prev_instance*/,
  LPSTR     /*command_line*/,
  int       /*show_command*/)
{
  return main(__argc, __argv);
}

#endif
#endif
