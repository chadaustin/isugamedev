#include <map>
#include <gmtl/Matrix.h>
#include <gmtl/Quat.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Output.h>

#include "Weapon.h"
#include "Player.h"
#include "GameState.h"
#include "cubeGeometry.h"
#include "NullWeapon.h"

namespace mw
{

   Player::Player() : RigidBody(), mCurrentWeapon( mWeapons.end() )
   {
      // add default weapon...
      this->addWeapon( new NullWeapon );
      assert( !this->isWeaponSlotEmpty( NullWeapon().getType() ) && "NullWeapon not registered, no default weapon!");
      
      this->init();
   }

   void Player::init()
   {
   }

   void Player::draw() const
   {
      //glEnable( GL_TEXTURE_2D );
      glPushMatrix();
         glMultMatrixf( this->matrix().getData() );
         glTranslatef( 0, 1, 0 );
         glPushMatrix();
            glScalef( 0.5f, 0.3f, 0.4f );
            cubeGeometry().render();
         glPopMatrix();
      glPopMatrix();
      
      this->weapon().draw();
   }

   bool Player::isWeaponSlotEmpty( int slot )
   {
      return mWeapons.count( slot ) == 0;
   }
   
   /**
    * Gets this player's current weapon.
    */
   Weapon& Player::weapon()
   {
      if (mCurrentWeapon != mWeapons.end())
      {
         return *(*mCurrentWeapon).second;
      }

      // return something safe :)
      assert( mWeapons.count( NullWeapon().getType() ) > 0 && "huh?" );
      return *(*mWeapons.find( NullWeapon().getType() )).second;
   }
   
   /**
    * Gets this player's current weapon.
    */
   const Weapon& Player::weapon() const
   {
      if (mCurrentWeapon != mWeapons.end())
      {
         return *(*mCurrentWeapon).second;
      }

      // return something safe :)
      assert( mWeapons.count( NullWeapon().getType() ) > 0 && "huh?" );
      return *(*mWeapons.find( NullWeapon().getType() )).second;
   }
   
   /**
    * Sets the player's current in-use weapon.
    */
   void Player::setWeapon( int slot )
   {
      if (!this->isWeaponSlotEmpty( slot ))
      {
         // set current weapon to this one...
         mCurrentWeapon = mWeapons.find( slot );
      }
   }
   
   /** adds weapon to player's inventory.
    *  each added weapon may cause that weapon to immediately become active
    *  depending on the player's game preferences.
    */
   void Player::addWeapon( Weapon* w )
   {
      assert( NULL != w && "bad weapon ptr" );
      
      // if slot already had a weapon, remove it
      if (mWeapons.count( w->getType() ) > 0)
      {
         delete mWeapons[w->getType()];
         mWeapons.erase( w->getType() );
      }
      
      // add the weapon to the slot
      mWeapons[w->getType()] = w;
      
      // set current weapon to the newly added one.
      mCurrentWeapon = mWeapons.find( w->getType() );
   }
   
   /** make the next weapon active.
    *  this will either iterate round-robin through the list
    *  of weapons that the player has, or it may iterate in an 
    *  alternate order specified by player's game preferences.
    */
   void Player::nextWeapon()
   {
      if (!mWeapons.empty())
      {
         ++mCurrentWeapon;
         if (mCurrentWeapon == mWeapons.end())
         {
            mCurrentWeapon = mWeapons.begin();
         }
         
         // call setWeapon for any extra behaviour needed.
         this->setWeapon( (*mCurrentWeapon).second->getType() );
      }
   }

   /**
    * Gets the position at the end of the barrel.
    */
   gmtl::Vec3f Player::getBarrelEndPos() const
   {
      gmtl::Vec3f barrelEndPos = gmtl::Vec3f( 0, 2, -3 );
      return (this->getRot() * barrelEndPos) + this->getPos();
   }
   
   gmtl::Vec3f Player::getForward() const
   {
      gmtl::Vec3f forward( 0,0,-1 );
      return this->getRot() * forward;
   }
   
   gmtl::Matrix44f Player::matrix() const 
   {
      // store the matrix from the pos/rot data...
      gmtl::Matrix44f xform;
      gmtl::set( xform, this->getRot() );
      gmtl::setTrans( xform, gmtl::Vec3f( this->getPos() ) );
      return xform;
   }

   void Player::update( GameState& gs, float timeDelta )
   {
      // @todo, use seconds not this weird range...
      RigidBody::update( (long)(timeDelta * 1000000.0f) );
      
      // update the current weapon
      this->weapon().setPos( this->getPos() + this->getRot() * gmtl::Vec3f( 0, 0, -0.5f ) );
      this->weapon().setRot( this->getRot() );
      this->weapon().update( gs, timeDelta );
   }
}// namespace.
