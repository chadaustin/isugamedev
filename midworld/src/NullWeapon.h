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
      {
      }

      /** return the Player slot number that the weapon goes in. */
      virtual int getType() { return 0; }
      
      /**
       * Creates a new bullet as though it were fired from this weapon.
       * @pre Weapon can be fired and there is a bullet in the chamber
       */
      virtual void trigger( bool firing )
      {
      }

      /** render the weapon using opengl calls. */
      virtual void draw()  const 
      {
      }
      
      /** called each frame */
      virtual void update( GameState& g, float dt )
      {
         Weapon::update( g, dt );
      }

   public:
      void addAmmo( int ammount )  //for ammo pickup
      {
      }
   };
}

#endif
