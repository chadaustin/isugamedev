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
 * File:          $RCSfile: AssaultRifle.h,v $
 * Date modified: $Date: 2002-10-01 04:26:42 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#ifndef MW_ASSAULTRIFLE_H
#define MW_ASSAULTRIFLE_H

#include "RigidBody.h"
#include "BaseBullet.h"
#include <gmtl/Math.h>

namespace mw
{
   /**
    * The assault rifle class used to represent the assault rifle.
    */
   class AssaultRifle: public BaseProjectileWeapon
   {
   public:
      AssaultRifle() : BaseProjectileWeapon( Weapon::RIFLE, "Assault Rifle" )
      {
         mMaxAmmoInBag = 500;
         mClipSize = 30;
         
         mFiring = false;
         mReloading = false;
         
         mReloadRate = 4.0f;
         mAmmoInClip = mClipSize;
         mAmmoInBag = 250;
         
         mReloadCounter = 0.0f;
         
         mCockDelayLeft = 0.0f;
         mCockRate = 0.01f;
         mCocking = false;
         mCocked = true;
      }

      /**
       * Draw the weapon onto the screen
       */
      void draw() const
      {
         glPushMatrix();
            glMultMatrixf( this->matrix().getData() );
            glScalef( 0.15f, 0.15f, 0.3f );
            cubeGeometry().render();
         glPopMatrix();
      }
   protected:
      /**
       * Discharges this weapon, emitting whatever projectiles it fires.
       * @param g the current GameState.
       */
      virtual void discharge(GameState& g)
      {
         //Slight spread with the assualt rifle.
         float angle = gmtl::Math::deg2Rad(0.5f);
         gmtl::Quatf r0( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( angle, 0.0f, 1.0f, 0.0f ) ) ),                     r1, 
                     r2( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( -angle, 0.0f, 1.0f, 0.0f) ) );
         //make a three round burst.
         BaseBullet* bullet0 = createBullet("bullet");
         bullet0->setVel(gmtl::Vec3f(0, 0, -200));
         bullet0->setRot(getRot() * r0);
         bullet0->setPos(getPos());
         bullet0->setVel(getRot() * r0 * bullet0->getVel());
         
         BaseBullet* bullet1 = createBullet("bullet");
         bullet1->setVel(gmtl::Vec3f(0, 0, -200));
         bullet1->setRot(getRot() * r1);
         bullet1->setPos(getPos());
         bullet1->setVel(getRot() * r1 * bullet1->getVel());

         BaseBullet* bullet2 = createBullet("bullet");
         bullet2->setVel(gmtl::Vec3f(0, 0, -200));
         bullet2->setRot(getRot() * r2);
         bullet2->setPos(getPos());
         bullet2->setVel(getRot() * r2 * bullet2->getVel());
         
         g.add(bullet0);
         g.add(bullet1);
         g.add(bullet2);
      }

      void ejectCasing(GameState& g)
      {
         ///@TODO Eject casings.
      }
   };
}//end of namespace mw

#endif
