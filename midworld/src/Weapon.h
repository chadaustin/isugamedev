/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#ifndef MW_WEAPON_H
#define MW_WEAPON_H

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
      virtual ~Weapon() {}

      /** return the Player slot number that the weapon goes in. */
      virtual int getType() = 0;

      /**
       * Sets whether this weapon is currently firing. Think of it as though
       * we're setting whether or not the trigger is being held down.
       */
      virtual void trigger( bool firing ) = 0;

      /** render the weapon using opengl calls. */
      virtual void draw() const = 0;
        
      /**
       * Updates the state of this bullet based on the amount of time that has
       * passed.
       *
       * @param dt   the change in time in seconds
       */
      virtual void update( GameState& g, float timeDelta )
      {
         // @todo change rigid body's weird time formating to secs...
         RigidBody::update( (long)(timeDelta * 1000000.0f) );
      }

      /// for ammo pickup
      virtual void addAmmo( int ammount ) = 0;
   };
}

#endif
