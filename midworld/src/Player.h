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
 * File:          $RCSfile: Player.h,v $
 * Date modified: $Date: 2002-10-01 08:38:12 $
 * Version:       $Revision: 1.17 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_PLAYER_H
#define MW_PLAYER_H

#include <map>
#include <gmtl/Vec.h>

#include "AbstractEntity.h"
#include "Weapon.h"
#include "cubeGeometry.h"
#include "NullWeapon.h"

namespace mw
{
class GameState;

class Player : public AbstractEntity
{
public:
   Player();

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
   
   void update( GameState& gs, float timeDelta );

   bool isExpired() const
   {
      return false;
   }

   void onCollisionEntry(const CollisionEvent& evt)
   {
   }

   void onCollisionMovement(const CollisionEvent& evt)
   {
   }

   void onCollisionExit(const CollisionEvent& evt)
   {
   }

private:
   std::multimap<int, Weapon*> mWeapons;
   std::map<int, int> mLastWeapon;
   std::multimap<int, Weapon*>::iterator mCurrentWeapon;
   int mLastSlot;
};
}

#endif
