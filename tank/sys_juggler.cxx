
#ifdef _WIN32
   #include <windows.h> // make the app win32 friendly. :)
#endif

#ifdef _MSC_VER
  // disable 'identifier was truncated to 255 characters in debug information' warning
  #pragma warning(disable: 4786)
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <Kernel/vjKernel.h>
#include <Kernel/GL/vjGlApp.h>
#include <Input/InputManager/vjPosInterface.h>
#include <Input/InputManager/vjDigitalInterface.h>
#include <Kernel/GL/vjGlContextData.h>

#include <iostream>
#include <stdlib.h>

#include "glRenderLight.h"
#include "TankGame.h"
#include "GeodeCache.h"

//: Provide functionality to automatically use different lights.
// Leave the first light (0) alone.
static int nextLightNum = 0;

int GetNextLightNum()
{
   return (nextLightNum++ % 7) + 1;
}

//------------------------------------------------------------------------------

//: Make vj contexts easier to use
class MyContext : public vjGlContextDataBase
{
public:
   int getContext() {
      return getCurContext();
   }
};

//------------------------------------------------------------------------------

//: juggler makes us subclass their vjGlApp class
class vjTankApp : public vjGlApp
{
public:
   vjTankApp() : width( 640 ), height( 480 ), game( NULL )
   {
   }

   virtual void init();
   virtual void preFrame();
   virtual void draw();

public:
   float width,height;
   TankGame *game;

   //input devices
   vjPosInterface mWand;
   vjDigitalInterface mForewardBtn;
   vjDigitalInterface mReverseBtn;
   vjDigitalInterface mTurnLeftBtn;
   vjDigitalInterface mTurnRightBtn;
   vjDigitalInterface mShootBtn;
};
static vjTankApp *app = NULL;

//: Create and init our game here
void
vjTankApp::init()
{
   // Init the input devices
   mWand.init( "VJWand" );
   mForewardBtn.init( "Foreward" );
   mReverseBtn.init( "Reverse" );
   mTurnLeftBtn.init( "TurnLeft" );
   mTurnRightBtn.init( "TurnRight" );
   mShootBtn.init( "Shoot" );

   // Create the game
   game = new TankGame();

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
   safe_ptr<Geode> geode;
   GeodeCache::instance().load( geode, "models/ship.obj" );

   Entity *entity = new Entity();
   entity->setGeode( geode );

   //Put the tank in the world
   game->getWorld().add( entity );
}

//: Update our game here!
void
vjTankApp::preFrame()
{
   // Handle input from the devices
   // Foreward
   if ( mForewardBtn->getData() == vjDigital::TOGGLE_ON ) {
      game->getPlayer( 0 )->getTank()->setVelocity( 0.0f, 0.0f, -40.0f );
   }
   if ( mForewardBtn->getData() == vjDigital::TOGGLE_OFF ) {
      game->getPlayer( 0 )->getTank()->setVelocity( 0.0f, 0.0f, 0.0f );
   }
   // Reverse
   if ( mReverseBtn->getData() == vjDigital::TOGGLE_ON ) {
      game->getPlayer( 0 )->getTank()->setVelocity( 0.0f, 0.0f, 40.0f );
   }
   if ( mReverseBtn->getData() == vjDigital::TOGGLE_OFF ) {
      game->getPlayer( 0 )->getTank()->setVelocity( 0.0f, 0.0f, 0.0f );
   }
   // Turn Left
   if ( mTurnLeftBtn->getData() == vjDigital::TOGGLE_ON ) {
      game->getPlayer( 0 )->getTank()->setAngVel( 3.0f );
   }
   if ( mTurnLeftBtn->getData() == vjDigital::TOGGLE_OFF ) {
      game->getPlayer( 0 )->getTank()->setAngVel( 0.0f );
   }
   // Turn Right
   if ( mTurnRightBtn->getData() == vjDigital::TOGGLE_ON ) {
      game->getPlayer( 0 )->getTank()->setAngVel( -3.0f );
   }
   if ( mTurnRightBtn->getData() == vjDigital::TOGGLE_OFF ) {
      game->getPlayer( 0 )->getTank()->setAngVel( 0.0f );
   }
   // Shoot
   if ( mShootBtn->getData() == vjDigital::TOGGLE_ON ) {
      Bullet *bullet = new Bullet();
      Tank *tank = game->getPlayer( 0 )->getTank();
      bullet->setPos( tank->getBarrelEndPos() );
      bullet->setRot( tank->rotation() );
      bullet->setRotVel( 20.0f );
      bullet->setVel( tank->getForward() * 80.0f );
      game->getBullets().push_back( bullet );
   }

   // Update the state of the game
   game->update();
}

//: Draw the game from player 0's point of view
void
vjTankApp::draw()
{
   MyContext ctx;
   ContextManager::instance().setContext( ctx.getContext() );
   
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

   glMatrixMode( GL_MODELVIEW );
      glPushMatrix();
         // Draw the game!
         game->draw( game->getPlayer( 0 ) );
      glPopMatrix();
   
   glFlush();
}

//------------------------------------------------------------------------------

int
main( int argc, char **argv )
{
   vjKernel *kernel = vjKernel::instance();
   app = new vjTankApp();

   //load the config files
   for ( int i=1; i<argc; i++ ) {
      kernel->loadConfigFile( argv[i] );
   }

   //let juggler do its thing
   kernel->start();
   kernel->setApplication( app );

   while ( 1 ) {
      usleep( 250000 );
   }

   return 0;
}

//------------------------------------------------------------------------------
