#ifndef PLAYER_DEFINED
#define PLAYER_DEFINED

#include <map>
#include <gmtl/Matrix.h>
#include <gmtl/Quat.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Output.h>

#include "Weapon.h"
#include "cubeGeometry.h"
#include "NullWeapon.h"

namespace mw
{
class GameState;

class Player : public RigidBody
{
public:
   Player();

   void init();

   void draw() const;

   bool isWeaponSlotEmpty( int slot );
   
   /**
    * Gets this player's current weapon.
    */
   Weapon& weapon();
   
   /**
    * Gets this player's current weapon.
    */
   const Weapon& weapon() const;
   
   /**
    * Sets the player's current in-use weapon.
    */
   void setWeapon( int slot );
   
   /** adds weapon to player's inventory.
    *  each added weapon may cause that weapon to immediately become active
    *  depending on the player's game preferences.
    */
   void addWeapon( Weapon* w );
   
   /** make the next weapon active.
    *  this will either iterate round-robin through the list
    *  of weapons that the player has, or it may iterate in an 
    *  alternate order specified by player's game preferences.
    */
   void nextWeapon();

   /**
    * Gets the position at the end of the barrel.
    */
   gmtl::Vec3f getBarrelEndPos() const;
   
   gmtl::Vec3f getForward() const;
   
   gmtl::Matrix44f matrix() const;
      
   void update( GameState& gs, float timeDelta );

private:
   std::map<int, Weapon*> mWeapons;
   std::map<int, Weapon*>::iterator mCurrentWeapon;
};
}

#endif
