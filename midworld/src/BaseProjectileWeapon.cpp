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
 * File:          $RCSfile: BaseProjectileWeapon.cpp,v $
 * Date modified: $Date: 2002-11-14 11:46:56 $
 * Version:       $Revision: 1.17 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "BaseBullet.h"
#include "BaseProjectileWeapon.h"
#include "BulletCasing.h"
#include "EntityFactory.h"

namespace mw
{
   BaseProjectileWeapon::BaseProjectileWeapon( const WeaponCategory& cat,
                                               const std::string& name )
      : Weapon(), mCategory( cat ), mName( name )
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

   gmtl::Point3f BaseProjectileWeapon::getBarrelEndPos() const
   {
//      gmtl::Vec3f extents = (getBounds().getMax() - getBounds().getMin()) * 0.5f;
      gmtl::Vec3f extents(0, 0, 4);
      return getPos() + gmtl::Point3f(0, 1, 0) + getRot() * (gmtl::Vec3f(0,0,-1) * gmtl::length(extents));
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
   void
   BaseProjectileWeapon::reload()
   {
      // Don't bother if we're already reloading or we have no ammo
      if ((! mReloading) && (mAmmoInBag > 0))
      {
         mReloadCounter = mReloadRate;
         mReloading = true;
      }
   }

   bool
   BaseProjectileWeapon::isReloading() const
   {
      return mReloading;
   }

   /**
    * Creates a new bullet as though it were fired from this weapon.
    * @pre Weapon can be fired and there is a bullet in the chamber
    */
   BaseBullet*
   BaseProjectileWeapon::createBullet(const std::string& model) const
   {
      BaseBullet* bullet = EntityFactory::instance().create<BaseBullet>();
      bullet->setVel(gmtl::Vec3f(0,0,-30));
      bullet->setPos(getBarrelEndPos());
      bullet->setModel(model);
      bullet->setSource(getSource());
      return bullet;
   }

   /**
    * Creates a new bullet as though it were fired from this weapon.
    * @pre Weapon can be fired and there is a bullet in the chamber
    */
   BulletCasing*
   BaseProjectileWeapon::createCasing(const std::string& model) const
   {
      BulletCasing* casing = EntityFactory::instance().create<BulletCasing>();
      casing->setVel(gmtl::Vec3f(0,10,0));
      casing->setPos(getBarrelEndPos());
      casing->setModel(model);
      return casing;
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
