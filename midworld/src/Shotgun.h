#ifndef MW_SHOTGUN_H
#define MW_SHOTGUN_H

#include <gmtl/Math.h>
#include <stdlib.h>
#include "BaseProjectileWeapon.h"
#include "RigidBody.h"

const unsigned int NUM_PELLETS = 10;

namespace mw
{
   /*SHOTGUN,a basic weapon*/
   class  Shotgun: public BaseProjectileWeapon
   {
   public:
      Shotgun()
         : BaseProjectileWeapon(Weapon::RIFLE, "Shotgun")
      {
         mSpreadAngle=10.f;
         srand(SDL_GetTicks());
         mMaxAmmoInBag = 1200;
         mClipSize = 6;
         mFiring = false;
         mReloading = false;

         mReloadRate = 2.0f;
         mCockRate = 0.7f;

         mAmmoInClip = mClipSize;
         mAmmoInBag = 100;

         // init to no waiting time
         mReloadCounter = 0.0f;
      }

      /** render the weapon using opengl calls. */
      virtual void draw() const
      {
         glPushMatrix();
            glMultMatrixf(this->matrix().getData());
            glScalef(0.15f, 0.15f, 0.8f);
            cubeGeometry().render();
         glPopMatrix();
      }

      // some of these will change to public...
   protected:
      void discharge(GameState& g)
      {
         // add the bullet to the gamestate...
         RigidBody** bullet;
         bullet = new RigidBody*[NUM_PELLETS];

         for(unsigned int i=0; i<NUM_PELLETS; i++)
         {
            //TODO:  seed this according to world time?


            //generate random bullet directions with the sweep of mSpreadAngle
            //degrees
            float angle = gmtl::Math::deg2Rad((mSpreadAngle* float(rand())/RAND_MAX) - (mSpreadAngle/2));

            gmtl::Quatf r(gmtl::make<gmtl::Quatf>(gmtl::AxisAnglef(angle, 0.0f, 1.0f, 0.0f)));

            bullet[i] = this->createBullet();

            bullet[i]->setRot(this->getRot() * r); //shoot off at a limited random angle
            bullet[i]->setPos(this->getPos());
            bullet[i]->setVel(this->getRot() * r * bullet[i]->getVel());

            g.add(bullet[i]); // bullet is not mine anymore, belongs to GameState

         }
      }

      void ejectCasing(GameState& g)
      {
         /// @todo eject a casing into the game
      }

   private:
      float mSpreadAngle;
   };
}

#endif
