#ifndef MW_PISTOL_H
#define MW_PISTOL_H

#include "Weapon.h"

namespace mw
{
   /*PISTOL,a basic weapon*/
   class Pistol : public Weapon
   {
   private:
      int mBusyCounter;
      int mReloadRate;
      int mFireRate;

      int mAmmoInClip;
      int mClipSize;
      int mAmmoInBag;
      int mMaxAmmoInBag;
      bool mFiring;
      bool mReloading;

   public:
      Pistol()
      {
         mMaxAmmoInBag = 200;
         mClipSize = 12;
         mFiring = false;
         mReloading = false;
         mBusyCounter = 0;

         mReloadRate = 1000;
         mFireRate = 500;
      }

      void addAmmo(int ammount)  //for ammo pickup
      {
         mAmmoInBag += ammount;
         if (mAmmoInBag > mMaxAmmoInBag)
         {
            mAmmoInBag = mMaxAmmoInBag;
         }
      }

      void setFiring(bool firing)   //for key pressing edge events
      {
         mFiring = firing;
         if (firing == true)
         {
            //TODO: This does not belong here!
            mBusyCounter = mFireRate;
         }
      }

      void setReloading(bool reloading)   //for key pressing edge events
      {
         mReloading = reloading;
         if (reloading == true)
         {
            //TODO: This does not belong here!
            mBusyCounter = mReloadRate;
         }
      }

      bool isFiring()
      {
         return mFiring;
      }

      bool isReloading()
      {
         return mReloading;
      }

      //pre:  Weapon can be fired, and there
      //      is a bullet in the chamber
      RigidBody* createBullet()
      {
         RigidBody* bullet = new RigidBody();

         //TODO: set bullet properties here

         --mAmmoInClip;
         return bullet;
      }

      bool canFire() const
      {
         if (!mReloading && !mFiring && mAmmoInClip>0)
         {
            return true;
         }
         return false;
      }

      void update(u64 dt)
      {
         dt /= 1000;
         mBusyCounter -= dt;
         if (mBusyCounter <= 0)
         {
            //make sure busyCounter is 0
            mBusyCounter = 0;

            //reset flags
            mReloading = false;
            mfiring = false;
         }
      }
   };
}

#endif
