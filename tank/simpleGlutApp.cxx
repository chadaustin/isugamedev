// Tank - isu game dev club
// Public domain
//

#ifdef _WIN32
   #include <windows.h>  // make the app win32 friendly. :)
#endif

#ifdef _MSC_VER
  // disable 'identifier was truncated to 255 characters in debug information' warning
  #pragma warning(disable: 4786)
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <vector>
#include <stdlib.h>

// data types
#include "Vec3.h"
#include "Matrix4f.h"
#include "StopWatch.h"
#include "Light.h"
#include "Material.h"

// decoupled renderers
#include "glRenderLight.h"
#include "glRenderMaterial.h"

// application objects
#include "Camera.h"
#include "Tank.h"
#include "Bullet.h"
#include "World.h"
#include "ObjImporter.h"
#include "HUD.h"

// Provide functionality to automatically use different lights.
// Leave the first light (0) alone.
static int nextLightNum = 0;

int GetNextLightNum()
{
   return (nextLightNum++ % 7) + 1;
}

#include "unistd.h"

// a place to store application data...
class App
{
public:
   App() : width( 0 ), height( 0 ), mainWin_contextID( -1 )
   {
      
   }
   void init()
   {
      Vec3<float> initial_tank_pos( 0, 0, -30 );
      tank.setPos( initial_tank_pos );
      
      camera.follow( true );
      camera.setTargetPos( tank.matrix() );
      camera.setPitch( 45.0f );

      light.setNumber( 0 );
      light.setPos( 0.0f, 0.0f, 0.0f, 1.0f );
      light.setColor( Light::diffuse, 1.0f, 1.0f, 1.0f );
      light.on();
      
      kev::ObjImporter importer;
      std::vector< safe_ptr<GeoSet> > gset;
      
      //Load our tank model
      importer.load( gset, "models/ship.obj" );

      Entity *entity = new Entity();
      std::vector< safe_ptr<GeoSet> >::iterator itr;
      for (itr = gset.begin(); itr != gset.end(); itr++) 
      {
         entity->addGeoSet( *itr );
      }

      //Put the tank in the world
      world.add( entity );
      
      hud.init();
      
      // call this last to minimize integrator instability
      stopWatch.pulse();
   }
      
   float width, height;
   int mainWin_contextID;
   Tank tank;
   std::vector<Bullet *> bullets;
   Camera camera;
   Light light;
   StopWatch stopWatch;
   World world;
   HUD hud;
};
App* app = NULL;

/*----------------------------------------------------------------------------*/

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
   // when using multidisplays we'll need to actually 
   // set this to a different number for each windows opened.
   ContextManager::instance().setContext( app->mainWin_contextID );
   
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
      gluPerspective( 80.0f, app->width / app->height, 0.01f, 1000.0f );
                           
   // initialize your matrix stack used for transforming your models
   glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();      

      app->camera.draw();
      
      glEnable( GL_LIGHTING );
      kev::glRender( app->light );
  
      app->tank.draw();
      app->world.draw();
      
      // draw all of the bullets
      std::vector<Bullet *>::const_iterator citr;
      for (citr = app->bullets.begin(); citr != app->bullets.end(); citr++) 
      {
         (*citr)->draw();
      }
      // remove bullets outside our world
      std::vector<Bullet *>::iterator itr;
      itr = app->bullets.begin();
      while (itr != app->bullets.end()) 
      {
         const Vec3<float> pos = (*itr)->position();
         if (fabs(pos[0]) > 1000.0f || fabs(pos[1]) > 1000.0f ||
             fabs(pos[2]) > 1000.0f)
         {
            delete (*itr);
            app->bullets.erase(itr);
         } else {
            itr++;
         }
      }
      
      drawGrid();
   
      // draw last so we get alpha effects correctly./..
      app->hud.draw();
      
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
   app->stopWatch.pulse();
   
   // keep it stable (we're using a shitty integrator)
   float min_fps = 0.4f;
   if (app->stopWatch.timeInstant() > 1.0f/min_fps)
   {
      std::cout<<"WARNING: time < "<<min_fps<<" fps, dropping update loop to keep integrators stable...\n"<<std::flush;
      return;
   }   

   // update the world
   app->world.update( app->stopWatch.timeInstant() );

   // the next 3 commands are dependent upon each other...
   app->tank.update( app->stopWatch.timeInstant() );
   app->camera.setTargetPos( app->tank.matrix() );
   app->camera.update( app->stopWatch.timeInstant() );
   
   // update the hud
   app->hud.setPlayerPos( app->tank.position()[0], app->tank.position()[1], app->tank.position()[2] );
   
   //Update the bullets
   std::vector<Bullet *>::iterator itr;
   for (itr = app->bullets.begin(); itr != app->bullets.end(); itr++) 
   {
      (*itr)->update( app->stopWatch.timeInstant() );
   }
   
   Vec3<float> lightOffset( -10.0f, 0.0f, 0.0f );
   lightOffset = app->camera.position() + lightOffset;
   app->light.setPos( lightOffset[0], lightOffset[1], lightOffset[2], 1.0f );

   
      
   // According to the GLUT specification, the current window is
   // undefined during an idle callback.  So we need to explicitly change
   // it if necessary
   if ( glutGetWindow() != app->mainWin_contextID )
           glutSetWindow( app->mainWin_contextID );

   // tell glut to call redisplay (which then calls OnRedisplay)
   glutPostRedisplay();
}

/////////////////////////////////////////////
// This is called on a Resize of the glut window
/////////////////////////////////////////////
static void OnReshape( int width, int height ) 
{
   // save these params in case your app needs them
   app->width = static_cast<float>( width );
   app->height = static_cast<float>( height );
   
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
   // If user pressed 'ESC', then exit the app->
   // this is really ungraceful, but necessary since GLUT does a while(1)
   // as it's control loop.  There is no GLUT method to exit, unfortunately.
   case 27:
      delete app;
      exit( 0 );
      break;

   case ' ':
   {
      Bullet *bullet = new Bullet();
      bullet->setPos( app->tank.getBarrelEndPos() );
      bullet->setRot( app->tank.rotation() );
      bullet->setRotVel( 20.0f );
      bullet->setVel( app->tank.getForward() * 80.0f );
      app->bullets.push_back( bullet );
      break;
   }
   case 'q':
      app->camera.setFollowDistVel( 40 );
      break;

   case 'e':
      app->camera.setFollowDistVel( -40 );
      break;

   case 'w':
      app->camera.setPitchVel( 40 );
      break;

   case 's':
      app->camera.setPitchVel( -40 );
      break;

   case 'a':
      app->camera.setYawVel( 40 );
      break;

   case 'd':
      app->camera.setYawVel( -40 );
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
   case 'q':
   case 'e':
      app->camera.setFollowDistVel( 0 );
      break;
   case 'w':
   case 's':
      app->camera.setPitchVel( 0 );
      break;
   case 'a':
   case 'd':
      app->camera.setYawVel( 0 );
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
      app->tank.setVelocity( 0.0f, 0.0f, -40.0f );
      break;
   }
   case GLUT_KEY_DOWN:
   {
      app->tank.setVelocity( 0.0f, 0.0f, 40.0f );
      break;
   }
   case GLUT_KEY_RIGHT:
      app->tank.setAngVel( -3.0f );
      break;
   case GLUT_KEY_LEFT:
      app->tank.setAngVel( 3.0f );
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
      app->tank.setVelocity( 0.0f, 0.0f, 0.0f );
      break;
   }
   case GLUT_KEY_RIGHT:
   case GLUT_KEY_LEFT:
      app->tank.setAngVel( 0.0f );
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
   // even before the OpenGL API is initialized 
   // (like before a graphics context is obtained)
   // can cause really bad things to happen...
   
   
   // !!!TODO!!!: put your _data_ initialization code here.
   app->init();
}


int main(int argc, char* argv[])
{
	app = new App;

    // Initialize the application
    // initialize the state of your app here if needed...
    OnApplicationInit();
   
    // Set the window's initial size
    ::glutInitWindowSize( 640, 480 );
    ::glutInit( &argc, argv );
  
    // Set to double buffer to reduce flicker
    ::glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    
    // Set the window title
    app->mainWin_contextID = ::glutCreateWindow( "SpaceTank" );
    
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
   ::glutMouseFunc( OnMouseClick );
   ::glutMotionFunc( OnMousePos );
   ::glutPassiveMotionFunc( OnMousePos );

    // start the application loop, your callbacks will now be called
    // time for glut to sit and spin.
    ::glutMainLoop();

    // the C++ standard implicitly does 'return 0' if control reaches the
    // end of main() but VC++, of course, doesn't support this
    return 0;
}


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
