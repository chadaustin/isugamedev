/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Player.cpp,v $
 * Date modified: $Date: 2002-10-28 07:41:20 $
 * Version:       $Revision: 1.20 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
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

   Player::Player(GameState* gameState)
      : AbstractEntity(gameState)
      , mCurrentWeapon(mWeapons.end())
   {
      mLastSlot = 0;
      setModel("player");
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
      static NullWeapon nw;
      return nw;
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
      static NullWeapon nw;
      return nw;
   }

   /**
    * Sets the player's current in-use weapon.
    */
   void Player::setWeapon( int slot )
   {
      if (!isWeaponSlotEmpty( slot ))
      {
         // if requesting to change to the same slot
         if (mLastSlot == slot)
         {
            ++mLastWeapon[slot];
            // wraparound if needed.
            if (mLastWeapon[slot] >= (int)mWeapons.count( slot ))
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
         for (int x = 0; x < mLastWeapon[slot]; ++x)
         {
            ++mCurrentWeapon;
         }
      }
   }

   /** adds weapon to player's inventory.
    *  each added weapon may cause that weapon to immediately become active
    *  depending on the player's game preferences.
    */
   void Player::addWeapon( Weapon* w )
   {
      assert( NULL != w && "bad weapon ptr" );

      // make sure this is initialized
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

      // make sure this is initialized
      mLastWeapon[mLastSlot] = c - 1;

      // if not already in the inventory, then add it.
      if (!foundit)
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


   AmmoBag&
   Player::getAmmoBag()
   {
      return mAmmoBag;
   }

   const AmmoBag&
   Player::getAmmoBag() const
   {
      return mAmmoBag;
   }

   gmtl::Vec3f Player::getBarrelEndPos() const
   {
      gmtl::Vec3f barrelEndPos = gmtl::Vec3f( 0, 2, -3 );
      return (getRot() * barrelEndPos) + getPos();
   }

   void Player::update( GameState& gs, float timeDelta )
   {
      RigidBody::update(timeDelta);

      // update the current weapon
      weapon().setPos( getPos() + getRot() * gmtl::Vec3f( 0, 0, -0.5f ) );
      weapon().setRot( getRot() );
      weapon().update( gs, timeDelta );
   }
}
