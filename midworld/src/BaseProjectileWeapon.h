#ifndef MW_BASE_CLASS_FOR_PROJECTILE_WEAPONS_H
#define MW_BASE_CLASS_FOR_PROJECTILE_WEAPONS_H

#include <gmtl/Math.h>
#include "Weapon.h"

namespace mw
{
   class BaseProjectileWeapon : public Weapon
   {
   public:
      BaseProjectileWeapon();

      /** return the Player slot number that the weapon goes in. */
      virtual int getType() = 0;
      
      /** render the weapon using opengl calls. */
      virtual void draw() const = 0;
      
      /// for key pressing edge events
      virtual void trigger( bool firing );

      virtual void update( GameState& g, float dt );
      
   protected:
      virtual void emitBullet( GameState& g ) = 0;

      /** Creates a new bullet object (factory function).
       */
      RigidBody* createBullet();


      // some of these will change to public...
   private:
         
      void addAmmo( int ammount );
      
      /**
       * Triggers a reload sequence.
       */
      void reload();
      
      bool canFire() const;
      
      
      
   protected:
      /// Time left (secs) to wait for the next bullet to be placed in the chamber
      float mBusyCounter;

      /// Time left (secs) to wait for reload to complete
      float mReloadCounter;

      float mReloadRate;
      float mFireRate;

      int mAmmoInClip;
      int mClipSize;
      int mAmmoInBag;
      int mMaxAmmoInBag;
      bool mFiring;
      bool mReloading;

   };
}

#endif
