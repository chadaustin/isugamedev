#ifndef TANKGAME_H_INCLUDED
#define TANKGAME_H_INCLUDED

#ifdef _MSC_VER
  // disable 'identifier was truncated to 255 characters in debug information' warning
  #pragma warning(disable: 4786)
#endif

#include <map>
#include <vector> //remove when bullets are made into entities
#include "Player.h"
#include "World.h"
#include "HUD.h"
#include "StopWatch.h"
#include "Bullet.h"

class TankGame
{
public:
   TankGame();
   virtual ~TankGame();

   //: Called when the app starts, but before the OpenGL has been initialized.
   //  We prefetch our models and textures here and load the scene.
   void init();

   //: Draws the game for the given player.
   void draw( const Player *player ) const;

   //: Updates the state of the game based on the amount of time that has passed
   //  since the last call to update.
   void update();

   //: Adds a player to the game. TankGame will maintain a reference to the
   //  player object passed in, so don't delete it! If a player with the same ID
   //  already exists in the game, that player will be replaced with the given
   //  player.
   void addPlayer( Player *player );

   //: Removes a player from the game. TankGame will maintain a reference to the
   //  player object passed in, so don't delete it! If no player with the given
   //  ID is in the game, no players are removed.
   void removePlayer( const Player::UID& id );

   //: Gets a pointer to the player with the given ID. Returns NULL if there is
   //  no such player with the given ID.
   Player* getPlayer( const Player::UID& id );

   //: Gets the world container for the entities
   World& getWorld();
   const World& getWorld() const;

   //: XXX: Remove when the bullets have been ported to entities
   std::vector< Bullet* >& getBullets() { return mBullets; }

private:
   //: XXX: Remove when the world is no longer drawn as a grid
   void drawGrid() const;

private:
   //: Hash of players indexed by their unique ID
   std::map< Player::UID, safe_ptr<Player> > mPlayers;

   //: Hack for storing bullets until they become entities
   std::vector< Bullet* > mBullets;

   //: World container for all entities currently in the game.
   World mWorld;

   //: Keeps the game time
   StopWatch mStopWatch;
};

#endif // ! TANKGAME_H_INCLUDED
