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

class Player
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
   
   const gmtl::Matrix44f& matrix() const;
      
   void setPos( const gmtl::Vec3f& pos );
      
   void update( GameState& gs, float timeDelta );

   const gmtl::Vec3f& velocity() const;
   
   // with repect to tank local coordinate system.
   // i.e. if tank is rotated, then 0,0,-1 is always "forward" for the tank.
   void setVelocity( const gmtl::Vec3f& vel );
   
   // with repect to tank local coordinate system.
   // i.e. if tank is rotated, then 0,0,-1 is always "forward" for the tank.
   void setVelocity( float x, float y, float z );
   
   void translate( const gmtl::Vec3f& offset );

   void setRot( gmtl::Quatf );

   // true ang velocity vector
   // w = [0, mag, 0]
   void setAngVel( float magnitude );

   const gmtl::Vec3f& position() const;

   const gmtl::Quatf& rotation() const;

private:
   gmtl::Matrix44f mXForm;
   gmtl::Vec3f mPos, mVel;
   gmtl::Quatf mRot;

   std::map<int, Weapon*> mWeapons;
   std::map<int, Weapon*>::iterator mCurrentWeapon;
};
}

#endif
