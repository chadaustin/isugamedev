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
 * File:          $RCSfile: BaseProjectileWeapon.h,v $
 * Date modified: $Date: 2002-11-11 08:05:52 $
 * Version:       $Revision: 1.14 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_BASE_PROJECTILE_WEAPON_H
#define MW_BASE_PROJECTILE_WEAPON_H

#include <gmtl/Math.h>
#include "Weapon.h"

namespace mw
{
   class BaseBullet;
   class BulletCasing;

   /**
    * An abstract base class for all projectile weapons.
    */
   class BaseProjectileWeapon : public Weapon
   {
   protected:
      /**
       * This class is abstract, you can only create concrete implementations of
       * this class.
       *
       * @param cat     the category this weapon is a member of
       * @param name    the name of this weapon
       * @param uid     the unique id of this weapon
       */
      BaseProjectileWeapon(const WeaponCategory& cat, const std::string& name );

   public:
      /// Gets the Player slot number that this weapon goes in.
      const WeaponCategory& getCategory() const;

      /// Gets the name of this weapon.
      const std::string& getName() const;

      /**
       * Tells this weapon whether or not its trigger is being held down.
       *
       * @param firing     true if the trigger is held down; false otherwise
       */
      void trigger(bool firing);

      /**
       * Tests if the trigger is being held down.
       */
      bool isTriggerDown() const;

      /**
       * Updates the state of this bullet based on the amount of time that has
       * passed.
       *
       * @param dt   the change in time in seconds
       */
      virtual void update(GameState& g, float dt);

      void update(float dt)
      {}

      /**
       * Gets the number of bullets in this weapon's clip.
       */
      virtual int getAmmoInClip() const;

      /**
       * Tests if the current clip is empty.
       */
      virtual bool isClipEmpty() const;

      virtual int getAmmoInBag() const;

      /**
       * Gets the amount of ammo for this gun that is not in the current clip.
       */
      virtual void addAmmo( int ammount );

      /**
       * Gets the position at the end of the barrel. This is the point at which
       * the bullets leave the gun.
       */
      gmtl::Point3f getBarrelEndPos() const;
      
      const std::string& getSource() { return mSource; }
      void setSource(const std::string& source) { mSource = source; }

   protected:
      /**
       * Discharges this weapon, emitting whatever projectile(s) it normally
       * fires into the game.
       */
      virtual void discharge(GameState& g) = 0;

      /**
       * Ejects a spent bullet casing into the game.
       */
      virtual void ejectCasing(GameState& g) = 0;

      /// Creates a new bullet as though fired from this weapon.
      virtual BaseBullet* createBullet(const std::string& model) const;
      BulletCasing* createCasing(const std::string& model) const;

      /**
       * This causes the weapon to cock - as in removing a bullet from the clip
       * and placing it in the chamber. This of course, adds a slight delay
       * before the weapon can be property fired. If the clip is empty, weapon
       * is not cocked and no delay is added.
       */
      void cock();

      /// Tests if this weapon is currently is the process of being cocked.
      bool isCocking() const;

      /// Tests if this weapon is currently cocked
      bool isCocked() const;

      // some of these will change to public...
   private:
      
      /// Triggers a reload sequence.
      void reload();

      /// Tests if this weapon is currently being reloaded
      bool isReloading() const;

   protected:
      /// The type of weapon this is (for weapon slots)
      WeaponCategory mCategory;

      /// The name of this weapon
      std::string mName;
      
      /// The entity firing the weapon
      std::string mSource;

      /// Time left (secs) to wait for reload to complete
      float mReloadCounter;

      float mReloadRate;

      int mAmmoInClip;
      int mClipSize;
      int mAmmoInBag;
      int mMaxAmmoInBag;

      bool mFiring;
      bool mReloading;

      /// The amount of time left to finish cocking the weapon
      float mCockDelayLeft;

      /// The time required to cock the weapon
      float mCockRate;

      /// Internal flag for whether the weapon is currently cocking
      bool mCocking;

      /// Internal flag for whether the weapon is currently cocked
      bool mCocked;
   };
}

#endif
