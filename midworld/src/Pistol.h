#ifndef MW_PISTOL_H
#define MW_PISTOL_H

#include <gmtl/Math.h>
#include "Weapon.h"

namespace mw
{
   /*PISTOL,a basic weapon*/
   class Pistol : public Weapon
   {
   public:
      Pistol()
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

      /** return the Player slot number that the weapon goes in. */
      virtual int getType() { return 1; }
      
      /// for key pressing edge events
      virtual void trigger( bool firing )   
      {
         mFiring = firing;
      }

      virtual void update( GameState& g, float dt )
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
            // add the bulllet to the gamestate...
            RigidBody* bullet = this->createBullet();
            bullet->setPos( this->position() );
            bullet->setVel( this->rotation() * bullet->getVel() );
            g.add( bullet ); // bullet is not mine anymore, belongs to GameState
         }
      }
      
      /** render the weapon using opengl calls. */
      virtual void draw() const 
      {
         glPushMatrix();
            glMultMatrixf( this->matrix().getData() );
            glScalef( 0.15f, 0.15f, 0.3f );
            cubeGeometry().render();
         glPopMatrix();
      }

      // some of these will change to public...
   private:
         
      void addAmmo( int ammount )  // for ammo pickup
      {
         mAmmoInBag += ammount;
         if (mAmmoInBag > mMaxAmmoInBag)
         {
            mAmmoInBag = mMaxAmmoInBag;
         }
      }
      
      /**
       * Triggers a reload sequence.
       */
      void reload()
      {
         // Don't bother if we're already reloading or we have no ammo
         if ((! mReloading) && (mAmmoInBag > 0))
         {
            mReloadCounter = mReloadRate;
            mReloading = true;
         }
      }
      
      bool canFire() const
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
      RigidBody* createBullet()
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
      
   private:
      /// Time left (secs) to wait for the next bullet to be placed in the chamber
      float mBusyCounter;

      /// Time left (secs) to wait for reload to complete
      float mReloadCounter;

      float mReloadRate;
      float mFireRate;

      int mAmmoInClip;
      int mClipSize;
      int mAmmoInBag;
      int mMaxAmmoInBag;
      bool mFiring;
      bool mReloading;

   };
}

#endif
