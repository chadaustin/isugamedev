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
 * File:          $RCSfile: Weapon.h,v $
 * Date modified: $Date: 2002-10-01 06:06:13 $
 * Version:       $Revision: 1.12 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_WEAPON_H
#define MW_WEAPON_H

#include <string>
#include <gmtl/Matrix.h>
#include <gmtl/Vec.h>
#include <gmtl/Quat.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Output.h>

#include "RigidBody.h"

namespace mw
{
   class GameState;

   /**
    * Interface for all weapons that the player or enemies may use. A weapon
    * object functions a description of the weapon and is a projectile factory.
    */
   class Weapon : public RigidBody
   {
   public:
      /**
       * Describes the basic categories in which weapons can be a member of.
       */
      enum WeaponCategory
      {
           HAND            ///< Hand weapon types
         , HANDGUN         ///< Pistol weapon types
         , RIFLE           ///< Rifle weapon types
         , AUTOMATIC       ///< Automatic weapon types
         , HEAVY           ///< Heavy weapon types
         , NUM_CATEGORIES  ///< The number of valid weapon categories
      };

   public:
      Weapon()
      {
      }
      virtual ~Weapon() {}

      /// Gets the category in which this weapon lies.
      virtual const WeaponCategory& getCategory() const = 0;

      /// Gets the name of this weapon.
      virtual const std::string& getName() const = 0;

      /**
       * Tells this weapon whether or not its trigger is being held down.
       *
       * @param firing     true if the trigger is held down; false otherwise
       */
      virtual void trigger(bool firing) = 0;

      /**
       * Tests if the trigger is being held down.
       */
      virtual bool isTriggerDown() const = 0;

      /// render the weapon using OpenGL calls.
      virtual void draw() const = 0;

      /**
       * Updates the state of this bullet based on the amount of time that has
       * passed.
       *
       * @param dt   the change in time in seconds
       */
      virtual void update(GameState& g, float timeDelta)
      {
         // @todo change rigid body's weird time formating to secs...
         RigidBody::update(timeDelta);
      }

      // @todo, the hand weapon doesn't have ammo or clips!!!
      
      /// for ammo pickup
      virtual void addAmmo(int ammount) = 0;

      /**
       * Gets the amount of ammo remaining in the current clip.
       */
      virtual int getAmmoInClip() const = 0;

      /**
       * Tests if the current clip is empty.
       */
      virtual bool isClipEmpty() const = 0;

      /**
       * Gets the amount of ammo for this gun that is not in the current clip.
       */
      virtual int getAmmoInBag() const = 0;

      /**
       * Is the weapon a real weapon or not?  Weapons default to being
       * real.
       */
      virtual bool isNull() const
      {
         return false;
      }
   };
}

#endif
