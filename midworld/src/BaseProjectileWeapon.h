#ifndef MW_BASE_CLASS_FOR_PROJECTILE_WEAPONS_H
#define MW_BASE_CLASS_FOR_PROJECTILE_WEAPONS_H

#include <gmtl/Math.h>
#include "Weapon.h"

namespace mw
{
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
       */
      BaseProjectileWeapon(const WeaponCategory& cat, const std::string& name);

   public:
      /// Gets the Player slot number that this weapon goes in.
      const WeaponCategory& getCategory() const;

      /// Gets the name of this weapon.
      const std::string& getName() const;

      /// Render the weapon using opengl calls.
      void draw() const = 0;

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

      /**
       * Gets the number of bullets in this weapon's clip.
       */
      virtual int getAmmoInClip() const;

      /**
       * Tests if the current clip is empty.
       */
      virtual bool isClipEmpty() const;

      virtual int getAmmoInBag() const;

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
      RigidBody* createBullet() const;

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
      void addAmmo( int ammount );

      /// Triggers a reload sequence.
      void reload();

      /// Tests if this weapon is currently being reloaded
      bool isReloading() const;

   protected:
      /// The type of weapon this is (for weapon slots)
      WeaponCategory mCategory;

      /// The name of this weapon
      std::string mName;

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
