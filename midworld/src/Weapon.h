/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
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
   };
}

#endif
