#ifndef MW_NULL_WEAPON_H
#define MW_NULL_WEAPON_H

#include <gmtl/Math.h>
#include "Weapon.h"

namespace mw
{
   class GameState;

   class NullWeapon : public Weapon
   {
   public:
      NullWeapon()
      {}

      /** return the Player slot number that the weapon goes in. */
      const WeaponCategory& getCategory() const { return Weapon::HAND; }

      const std::string& getName() const { return "Null"; }

      /**
       * Creates a new bullet as though it were fired from this weapon.
       * @pre Weapon can be fired and there is a bullet in the chamber
       */
      void trigger(bool firing)
      {}

      bool isTriggerDown() const
      {
         return false;
      }

      /// Draw nothing, since this weapon is ... null
      void draw() const
      {}

      /// Called each frame
      void update(GameState& g, float dt)
      {
         Weapon::update(g, dt);
      }

      void addAmmo( int ammount )  //for ammo pickup
      {
      }

      int getAmmoInClip() const
      {
         return 0;
      }

      bool isClipEmpty() const
      {
         return true;
      }

      int getAmmoInBag() const
      {
         return 0;
      }
   };
}

#endif
