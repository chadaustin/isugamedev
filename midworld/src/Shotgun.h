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
 * File:          $RCSfile: Shotgun.h,v $
 * Date modified: $Date: 2002-07-07 02:21:11 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
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
         : BaseProjectileWeapon( Weapon::RIFLE, "Shotgun" )
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
