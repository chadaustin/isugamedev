#ifndef MW_GUN_PICKUP_H
#define MW_GUN_PICKUP_H


#include <stdexcept>

#include "AbstractEntity.h"

namespace mw
{
   class Player;
   class Weapon;

   class GunPickup : public AbstractEntity
   {
   public:
      GunPickup(GameState* gameState, const std::string& gun);
      void giveTo(Player* player);
      
      bool isExpired() const
      {
         return mIsExpired;
      }
   
   private:
      Weapon* getWeapon();
   
      std::string mGun;
      bool mIsExpired;
   };

}


#endif
