#include "BaseProjectileWeapon.h"

namespace mw
{
   BaseProjectileWeapon::BaseProjectileWeapon()
   {
      mMaxAmmoInBag = 200;
      mClipSize = 12;
      mFiring = false;
      mReloading = false;
      mBusyCounter = 0;

      mReloadRate = 2.0f;
      mFireRate = 0.5f;

      mAmmoInClip = mClipSize;
      mAmmoInBag = 100;

      // init to no waiting time
      mBusyCounter = 0.0f;
      mReloadCounter = 0.0f;
   }

   /// for key pressing edge events
   void BaseProjectileWeapon::trigger( bool firing )
   {
      mFiring = firing;
   }

   void BaseProjectileWeapon::update( GameState& g, float dt )
   {
      Weapon::update( g, dt );
      
      // Process the reloading state if we're currently reloading the pistol
      if (mReloading)
      {
         mReloadCounter -= dt;
         // Check if we're done reloading
         if (mReloadCounter <= 0.0f)
         {
            // Make sure the counter stays at 0
            mReloadCounter = 0.0f;

            // Try to refill the clip (even if it still has bullets left in it)
            int new_clip = gmtl::Math::Min(mAmmoInBag, mClipSize - mAmmoInClip);
            mAmmoInBag -= new_clip;
            mAmmoInClip += new_clip;

            // We're done reloading ...
            mReloading = false;
         }
      }

      // Handle the placement of a new bullet in the chamber
      mBusyCounter -= dt;
      if (mBusyCounter <= 0.0f)
      {
         //make sure busyCounter is 0
         mBusyCounter = 0.0f;
      }
      
      // Fire the player's weapon if needed
      if (mFiring == true && this->canFire())
      {
         this->emitBullet( g );
      }
   }
   
   void BaseProjectileWeapon::addAmmo( int ammount )  // for ammo pickup
   {
      mAmmoInBag += ammount;
      if (mAmmoInBag > mMaxAmmoInBag)
      {
         mAmmoInBag = mMaxAmmoInBag;
      }
   }

   int BaseProjectileWeapon::getAmmoInClip() const
   {
      return mAmmoInClip;
   }

   int BaseProjectileWeapon::getAmmoInBag() const
   {
      return mAmmoInBag;
   }
   
   /**
    * Triggers a reload sequence.
    */
   void BaseProjectileWeapon::reload()
   {
      // Don't bother if we're already reloading or we have no ammo
      if ((! mReloading) && (mAmmoInBag > 0))
      {
         mReloadCounter = mReloadRate;
         mReloading = true;
      }
   }
   
   bool BaseProjectileWeapon::canFire() const
   {
      if (!mReloading && mFiring && mAmmoInClip>0)
      {
         if ((mBusyCounter <= 0.0f) && (mReloadCounter <= 0.0f))
         {
            return true;
         }
      }
      return false;
   }
   
   /**
    * Creates a new bullet as though it were fired from this weapon.
    * @pre Weapon can be fired and there is a bullet in the chamber
    */
   RigidBody* BaseProjectileWeapon::createBullet()
   {
      RigidBody* bullet = new RigidBody();
      bullet->setVel(gmtl::Vec3f(0,0,-30));

      // Remove the spent ammo from the clip
      --mAmmoInClip;

      // Start the reload process automagically if necessary
      if (mAmmoInClip == 0)
      {
         reload();
      }
      // Pause to put a new bullet in the chamber
      else
      {
         mBusyCounter = mFireRate;
      }

      return bullet;
   }
}
