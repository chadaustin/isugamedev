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
 * File:          $RCSfile: NullWeapon.h,v $
 * Date modified: $Date: 2002-11-14 11:34:40 $
 * Version:       $Revision: 1.11 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_NULL_WEAPON_H
#define MW_NULL_WEAPON_H

#include <gmtl/Math.h>
#include "Weapon.h"

namespace mw
{
   class GameState;

   class NullWeapon : public Weapon
   {
   public:
      NullWeapon()
         : mCategory(Weapon::HAND), mName("Null")
      {}

      /** return the Player slot number that the weapon goes in. */
      const WeaponCategory& getCategory() const { return mCategory; }

      const std::string& getName() const { return mName; }
      
      const std::string& getSource() const { return mSource; }
      void setSource(const std::string& source) { mSource = source; }

      /**
       * Creates a new bullet as though it were fired from this weapon.
       * @pre Weapon can be fired and there is a bullet in the chamber
       */
      void trigger(bool firing)
      {}

      bool isTriggerDown() const
      {
         return false;
      }

      /// Draw nothing, since this weapon is ... null
      void draw() const
      {}

      /// Called each frame
      void update(GameState& g, float dt)
      {}

      void update(float dt)
      {}

      void addAmmo( int ammount )  //for ammo pickup
      {
      }

      int getAmmoInClip() const
      {
         return 0;
      }

      bool isClipEmpty() const
      {
         return true;
      }

      int getAmmoInBag() const
      {
         return 0;
      }

      bool isNull() const
      {
         return true;
      }

   private:
      WeaponCategory mCategory;
      std::string mName;
      std::string mSource;
   };
}

#endif
