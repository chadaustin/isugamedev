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
 * File:          $RCSfile: SpreadGun.h,v $
 * Date modified: $Date: 2002-09-08 22:17:45 $
 * Version:       $Revision: 1.10 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_SPREADGUN_H
#define MW_SPREADGUN_H

#include <gmtl/Math.h>
#include <gmtl/AxisAngle.h>
#include <gmtl/EulerAngle.h>
#include "BaseProjectileWeapon.h"
#include "BaseBullet.h"
#include "GameManager.h"

namespace mw
{
   /*PISTOL,a basic weapon*/
   class SpreadGun : public BaseProjectileWeapon
   {
   public:
      SpreadGun()
         : BaseProjectileWeapon( Weapon::AUTOMATIC, "SpreadGun" )
         , mSpinning( 0.0f )
      {
         mCockRate = 0.1f;
         mReloadRate = 0.5f;
      }

      /** render the weapon using opengl calls. */
      virtual void draw() const
      {
         glPushMatrix();
            glMultMatrixf( this->matrix().getData() );
            glScalef( 0.3f, 0.3f, 0.4f );
            glRotatef( mSpinning, 0, 0, 1 );
            cubeGeometry().render();
         glPopMatrix();
      }

      virtual void update( GameState& g, float dt )
      {
         BaseProjectileWeapon::update( g, dt );
         if (mFiring)
         {
            mSpinning += 5.0f * 360.0f * dt; // 5 Revs per sec
         }
      }

   protected:
      void discharge(GameState& g)
      {
         // define the spread
         float angle = gmtl::Math::deg2Rad( 15.0f );
         gmtl::Quatf r0( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( angle, 0.0f, 1.0f, 0.0f ) ) ),
                     r1,
                     r2( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( -angle, 0.0f, 1.0f, 0.0f ) ) );

         // define the 3 bullets in the spread weapon.
         BaseBullet* bullet0 = this->createBullet();
         bullet0->setRot( this->getRot() * r0 );
         bullet0->setPos( this->getPos() );
         bullet0->setVel( this->getRot() * r0 * bullet0->getVel() );

         BaseBullet* bullet1 = this->createBullet();
         bullet1->setRot( this->getRot() * r1 );
         bullet1->setPos( this->getPos() );
         bullet1->setVel( this->getRot() * r1 * bullet1->getVel() );

         BaseBullet* bullet2 = this->createBullet();
         bullet2->setRot( this->getRot() * r2 );
         bullet2->setPos( this->getPos() );
         bullet2->setVel( this->getRot() * r2 * bullet2->getVel() );

         // add the three bullets to the game
         // bullet is not mine anymore, belongs to GameState
         g.add( bullet0 );
         g.add( bullet1 );
         g.add( bullet2 );

         // Do the sound effect
         SoundEffectManager* sfxmgr = GameManager::instance().getSoundManager()->
                                          getSoundEffectManager();
         sfxmgr->playSound("sfx/spreadgun.wav");
      }

      void ejectCasing(GameState& g)
      {
         /// @todo eject some _real_ casings into the game

         // Define the angles at which the shells are ejected
         gmtl::Quatf case1_rot = gmtl::make<gmtl::Quatf>(gmtl::EulerAngleZYXf(
                  0, gmtl::Math::deg2Rad(90.0f), gmtl::Math::deg2Rad(85.0f)));
         gmtl::Quatf case2_rot = gmtl::make<gmtl::Quatf>(gmtl::EulerAngleZYXf(
                  0, gmtl::Math::deg2Rad(90.0f), gmtl::Math::deg2Rad(90.0f)));
         gmtl::Quatf case3_rot = gmtl::make<gmtl::Quatf>(gmtl::EulerAngleZYXf(
                  0, gmtl::Math::deg2Rad(-90.0f), gmtl::Math::deg2Rad(85.0f)));

         // Create three shell casings
         BaseBullet* casing1 = createBullet();
         casing1->setRot(getRot() * case1_rot);
         casing1->setPos(getPos() + casing1->getForward() * 1.0f);
         casing1->setVel(casing1->getRot() * casing1->getVel() * 0.50f );

         BaseBullet* casing2 = createBullet();
         casing2->setRot(getRot() * case2_rot);
         casing2->setPos(getPos() + casing2->getForward() * 1.0f);
         casing2->setVel(casing2->getRot() * casing2->getVel() * 0.50f );

         BaseBullet* casing3 = createBullet();
         casing3->setRot(getRot() * case3_rot);
         casing3->setPos(getPos() + casing3->getForward() * 1.0f);
         casing3->setVel(casing3->getRot() * casing3->getVel() * 0.50f );

         // Add the casings into the game
//         g.add(casing1);
         g.add(casing2);
         g.add(casing3);
      }

      float mSpinning;
   };
}

#endif
