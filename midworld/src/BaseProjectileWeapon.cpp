#include "BaseProjectileWeapon.h"

namespace mw
{
   BaseProjectileWeapon::BaseProjectileWeapon(const WeaponCategory& cat,
                                              const std::string& name)
      : mCategory(cat), mName(name)
   {
      mMaxAmmoInBag = 200;
      mClipSize = 12;
      mFiring = false;
      mReloading = false;

      mReloadRate = 2.0f;

      mAmmoInClip = mClipSize;
      mAmmoInBag = 100;

      // init to no waiting time
      mReloadCounter = 0.0f;

      // Cocking related variables
      mCockDelayLeft = 0.0f;
      mCockRate = 0.5f;
      mCocking = false;
      mCocked = true;
   }

   const Weapon::WeaponCategory& BaseProjectileWeapon::getCategory() const
   {
      return mCategory;
   }

   const std::string& BaseProjectileWeapon::getName() const
   {
      return mName;
   }

   /// for key pressing edge events
   void BaseProjectileWeapon::trigger(bool firing)
   {
      mFiring = firing;
   }

   bool BaseProjectileWeapon::isTriggerDown() const
   {
      return mFiring;
   }

   void BaseProjectileWeapon::update(GameState& g, float dt)
   {
      Weapon::update(g, dt);

      // Process the reloading state if we're currently reloading the weapon
      if (isReloading())
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
            cock();
         }
      }
      // If we're not reloading, check if we need to cock the weapon
      else if (isCocking())
      {
         mCockDelayLeft -= dt;
         // Check if we're done cocking
         if (mCockDelayLeft <= 0.0f)
         {
            // Make sure the delay stays at 0
            mCockDelayLeft = 0.0f;

            // We're done cocking
            mCocking = false;
            mCocked = true;
         }
      }
      // Fire the player's weapon if loaded, cocked and the trigger is down
      else if (isTriggerDown() && isCocked())
      {
         // Discharge the weapon
         discharge(g);

         // Discharging, of course, uncocks the weapon
         mCocked = false;

         // Remove the spent ammo from the chamber
         --mAmmoInClip;

         // Eject the spent casing
         ejectCasing(g);

         // Reload or re-cock the weapon
         if (isClipEmpty())
         {
            reload();
         }
         else
         {
            cock();
         }
      }
   }

   void BaseProjectileWeapon::cock()
   {
      // Don't bother if we're already cocking or the clip is empty
      if ((! isCocked()) && (! isCocking()) && (! isClipEmpty()))
      {
         mCockDelayLeft = mCockRate;
         mCocking = true;
      }
   }

   bool BaseProjectileWeapon::isCocking() const
   {
      return mCocking;
   }

   bool BaseProjectileWeapon::isCocked() const
   {
      return mCocked;
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

   bool BaseProjectileWeapon::isClipEmpty() const
   {
      return (mAmmoInClip == 0);
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

   bool BaseProjectileWeapon::isReloading() const
   {
      return mReloading;
   }

   /**
    * Creates a new bullet as though it were fired from this weapon.
    * @pre Weapon can be fired and there is a bullet in the chamber
    */
   RigidBody* BaseProjectileWeapon::createBullet() const
   {
      RigidBody* bullet = new RigidBody();
      bullet->setVel(gmtl::Vec3f(0,0,-30));
      return bullet;
   }

   /**
    * Removes a bullet from the clip and places it in the chamber. This will
    * add a pause while the weapon waits for the bullet to enter the chamber. If
    * the clip is empty, this will invoke a reloading action.
    */
//   void BaseProjectileWeapon::removeBulletFromClip()
//   {
//      // Remove the spent ammo from the clip
//      --mAmmoInClip;
//
//      // Start the reload process automagically if necessary
//      if (mAmmoInClip == 0)
//      {
//         reload();
//      }
//      // Pause to put a new bullet in the chamber
//      else
//      {
//         mBusyCounter = mFireRate;
//      }
//   }
}
