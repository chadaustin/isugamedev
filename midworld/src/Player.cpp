#include <map>
#include <assert.h>
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
      assert( !this->isWeaponSlotEmpty( NullWeapon().getCategory() ) && "NullWeapon not registered, no default weapon!");

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
         glScalef( 0.5f, 0.3f, 0.4f );
         cubeGeometry().render();
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
      assert( mWeapons.count( NullWeapon().getCategory() ) > 0 && "huh?" );
      return *(*mWeapons.find( NullWeapon().getCategory() )).second;
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
      assert( mWeapons.count( NullWeapon().getCategory() ) > 0 && "huh?" );
      return *(*mWeapons.find( NullWeapon().getCategory() )).second;
   }

   /**
    * Sets the player's current in-use weapon.
    */
   void Player::setWeapon( int slot )
   {
      if (!this->isWeaponSlotEmpty( slot ))
      {
         // if requesting to change to the same slot
         if (mLastSlot == slot)
         {
            ++mLastWeapon[slot];
            // wraparound if needed.
            if (mLastWeapon[slot] >= mWeapons.count( slot ))
            {
               mLastWeapon[slot] = 0;
            }
         }
         // if requesting to change to a different slot
         else
         {
            mLastSlot = slot;
         }

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

      mLastSlot = w->getCategory();

      // add the weapon to the slot
      int c = mWeapons.count( w->getCategory() );
      std::multimap<int, Weapon*>::iterator f = mWeapons.find( w->getCategory() );
      bool foundit = false;
      for (int x = 0; x < c; ++x, ++f)
      {
         // if we find the same weapon here, then transfer ammo
         if ((*f).second->getName() == w->getName())
         {
            foundit = true;
            (*f).second->addAmmo( w->getAmmoInClip() + w->getAmmoInBag() );
            delete w;
            w = NULL;
         }
      }

      // if not already in the inventory, then add it.
      if (false == foundit)
      {
         // also set current weapon to the newly added one.
         mCurrentWeapon = mWeapons.insert(
               std::pair<int,Weapon*>( w->getCategory(), w ) );
      }
   }

   /** make the next weapon active.
    *  this will either iterate round-robin through the list
    *  of weapons that the player has, or it may iterate in an
    *  alternate order specified by player's game preferences.
    */
   void Player::nextWeapon()
   {
      mLastSlot = -1; // figure out how to set this... maybe not needed.
      if (!mWeapons.empty())
      {
         ++mCurrentWeapon;
         if (mCurrentWeapon == mWeapons.end())
         {
            mCurrentWeapon = mWeapons.begin();
         }
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

   void Player::update( GameState& gs, float timeDelta )
   {
      RigidBody::update(timeDelta);

      // update the current weapon
      this->weapon().setPos( this->getPos() + this->getRot() * gmtl::Vec3f( 0, 0, -0.5f ) );
      this->weapon().setRot( this->getRot() );
      this->weapon().update( gs, timeDelta );
   }
}
