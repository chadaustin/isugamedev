
#include "glRenderLight.h"
#include "TankGame.h"

//------------------------------------------------------------------------------

TankGame::TankGame()
{
}

//------------------------------------------------------------------------------

TankGame::~TankGame()
{
}

//------------------------------------------------------------------------------

void
TankGame::init()
{
   //TODO: parse a scene descriptor file and load the scene

   //Init the HUD for each player
   std::map< Player::UID, PlayerPtr >::iterator itr;
   for (itr = mPlayers.begin(); itr != mPlayers.end(); itr++ ) {
      itr->second->getHUD().init();
   }

   // call this last to minimize integrator instability
   mStopWatch.pulse();
}

//------------------------------------------------------------------------------

void
TankGame::draw( const PlayerPtr player ) const
{
   // Setup the view for the given camera
   player->getCamera().draw();

   // Draw the world (this will also setup the lighting)
   mWorld.draw();

   // HACK!! TODO: Manually draw the tank and bullets until we make them based
   // on entities.
   player->getTank()->draw();
   std::vector<Bullet *>::const_iterator citr;
   for (citr = mBullets.begin(); citr != mBullets.end(); citr++)
   {
      (*citr)->draw();
   }

   // draw the ground as a grid until we replace it with something more visually
   // appealing ... like cool terrain
   drawGrid();

   // draw HUD last to get alpha effects done correctly
   player->getHUD().draw();
}

//------------------------------------------------------------------------------

void
TankGame::update()
{
   mStopWatch.pulse();

   // keep it stable (we're using a shitty integrator)
   float min_fps = 0.4f;
   if (mStopWatch.timeInstant() > 1.0f/min_fps)
   {
      std::cout<<"WARNING: time < "<<min_fps<<" fps, dropping update loop to keep integrators stable...\n"<<std::flush;
      return;
   }

   // update the world
   mWorld.update( mStopWatch.timeInstant() );

   // update the tank and camera for each player
   std::map< Player::UID, PlayerPtr >::iterator itr;
   for ( itr = mPlayers.begin(); itr != mPlayers.end(); itr++ ) {
      PlayerPtr player = itr->second;
      Tank *tank = player->getTank();
      
      // the next 3 commands are dependent upon each other...
      tank->update( mStopWatch.timeInstant() );
      player->getCamera().setTargetPos( tank->matrix() );
      player->getCamera().update( mStopWatch.timeInstant() );

      // update the player's HUD
      const Vec3f pos = tank->position();
      HUD *hud = &( player->getHUD() );
      hud->setPlayerPos( pos[0], pos[1], pos[2] );
      hud->setFPS( mStopWatch.fpsAverage() );

      //XXX: Hack to make the headlight for the drawing player follow the
      //player's tank. We really need to make the light follow and entity and
      //not specify a position every time.
      if ( player->getUID() == 0L ) {
         Vec3<float> lightOffset( -10.0f, 0.0f, 0.0f );
         lightOffset = player->getCamera().position() + lightOffset;
         mWorld.getLight( 0 ).setPos( lightOffset[0], lightOffset[1],
                            lightOffset[2], 1.0f );
      }
   }

   // XXX: Hack to update the bullets until they become entities
   std::vector<Bullet *>::iterator bulitr;
   for (bulitr = mBullets.begin(); bulitr != mBullets.end(); bulitr++) 
   {
      (*bulitr)->update( mStopWatch.timeInstant() );
   }
   // remove bullets outside our world
   bulitr = mBullets.begin();
   while (bulitr != mBullets.end()) 
   {
      const Vec3<float> pos = (*bulitr)->position();
      if (fabs(pos[0]) > 1000.0f || fabs(pos[1]) > 1000.0f ||
          fabs(pos[2]) > 1000.0f)
      {
         delete (*bulitr);
         mBullets.erase(bulitr);
      } else {
         bulitr++;
      }
   }
}

//------------------------------------------------------------------------------

void
TankGame::addPlayer( PlayerPtr player )
{
   assert( player.get() != NULL );
   mPlayers[player->getUID()] = player;
}

//------------------------------------------------------------------------------

void
TankGame::removePlayer( const Player::UID& id )
{
   std::map< Player::UID, PlayerPtr >::iterator itr;
   itr = mPlayers.find( id );

   //We should not be removing players that aren't in the game!
   assert( itr != mPlayers.end() );
   mPlayers.erase( itr );
}

//------------------------------------------------------------------------------

PlayerPtr
TankGame::getPlayer( const Player::UID& id )
{
   std::map< Player::UID, PlayerPtr >::iterator itr;
   itr = mPlayers.find( id );
   if ( itr != mPlayers.end() ) {
      return itr->second;
   }
   return PlayerPtr( NULL );
}

//------------------------------------------------------------------------------

World&
TankGame::getWorld()
{
   return mWorld;
}

//------------------------------------------------------------------------------

const World&
TankGame::getWorld() const
{
   return mWorld;
}

//------------------------------------------------------------------------------

void
TankGame::drawGrid() const
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

//------------------------------------------------------------------------------
