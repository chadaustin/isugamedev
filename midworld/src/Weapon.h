/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#ifndef MW_WEAPON_H
#define MW_WEAPON_H

#include "RigidBody.h"

namespace mw
{
   /**
    * Interface for all weapons that the player or enemies may use. A weapon
    * object functions a description of the weapon and is a projectile factory.
    */
   class Weapon
   {
   public:
      virtual ~Weapon() {}

      /**
       * Sets whether this weapon is currently firing. Think of it as though
       * we're setting whether or not the trigger is being held down.
       */
      virtual void setFiring(bool firing) = 0;

      /**
       * Gets whether this weapon is firing.
       */
      virtual bool isFiring() = 0;

      /**
       * Creates a new bullet from this weapon.
       */
      virtual RigidBody* createBullet() = 0;

      /**
       * Checks if this weapon is ready to emit a bullet.
       */
      virtual bool canFire() const = 0;

      /**
       * Updates the state of this bullet based on the amount of time that has
       * passed.
       *
       * @param dt   the change in time in seconds
       */
      virtual void update(float dt) = 0;
   };
}

#endif
