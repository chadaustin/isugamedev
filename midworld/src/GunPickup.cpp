#include "GunPickup.h"

#include "AssaultRifle.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "Spreadgun.h"


namespace mw
{
   GunPickup::GunPickup(GameState* gameState, const std::string& gun)
      : AbstractEntity(gameState)
   {
      mGun = gun;
      mIsExpired = false;
      
      // just make sure the weapon string is valid
      // if it isn't, this will throw an exception
      delete getWeapon();
   }
   
   void GunPickup::giveTo(Player* player)
   {
      player->addWeapon(getWeapon());
      mIsExpired = true;
   }
   
   Weapon* GunPickup::getWeapon()
   {
      if (mGun == "spreadgun")
      {
         return new SpreadGun();
      }
      else if (mGun == "shotgun")
      {
         return new Shotgun();
      }
      else if (mGun == "pistol")
      {
         return new Pistol();
      }
      else if (mGun == "assaultrifle")
      {
         return new AssaultRifle();
      }
      else
      {
         throw std::runtime_error("Unknown weapon type: " + mGun);
      }
   }

}
