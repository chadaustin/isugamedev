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
 * File:          $RCSfile: SpreadGun.cpp,v $
 * Date modified: $Date: 2002-10-09 06:57:19 $
 * Version:       $Revision: 1.7 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#include <gmtl/Math.h>
#include <gmtl/AxisAngle.h>
#include <gmtl/EulerAngle.h>
#include "cubeGeometry.h"
#include "SpreadGun.h"
#include "BaseBullet.h"
#include "GameManager.h"
#include "Utility.h"

namespace mw
{
   SpreadGun::SpreadGun()
      : BaseProjectileWeapon(Weapon::AUTOMATIC, "SpreadGun")
      , mSpinning(0.0f)
      , mBarrel(3)
   {
      mMaxAmmoInBag = 600;
      mAmmoInBag = 300;
      mClipSize = 36;
      mAmmoInClip = mClipSize;

      mCockRate = 0.05f;
      mReloadRate = 0.5f;
   }

   void SpreadGun::update(GameState& g, float dt)
   {
      BaseProjectileWeapon::update(g, dt);
      if (mFiring)
      {
         mSpinning += 5.0f * 360.0f * dt; // 5 Revs per sec
      }
   }

   void SpreadGun::discharge(GameState& g)
   {
      // Pick the next barrel to fire out of
      mBarrel = (++mBarrel) % 3;

      // define the spread
      float angle = gmtl::Math::deg2Rad(15.0f);
      gmtl::Quatf barrel_rot;

      if (mBarrel == 0)
      {
         barrel_rot = gmtl::make<gmtl::Quatf>(gmtl::AxisAnglef(angle, 0.0f, 1.0f, 0.0f));
      }
      else if (mBarrel == 2)
      {
         barrel_rot = gmtl::make<gmtl::Quatf>(gmtl::AxisAnglef(-angle, 0.0f, 1.0f, 0.0f));
      }

      BaseBullet* bullet = createBullet("bullet");
      bullet->setRot(getRot() * barrel_rot);
      bullet->setVel(getRot() * barrel_rot * bullet->getVel());
      g.add(bullet);

      // Do the sound effect
      SoundEffectManager* sfxmgr = GameManager::instance().getSoundManager()->
                                       getSoundEffectManager();
      sfxmgr->playSound("sfx/spreadgun.wav");
   }

   void SpreadGun::ejectCasing(GameState& g)
   {
      /// @todo eject some _real_ casings into the game
      
      // Define the angle at which the shell is ejected
      gmtl::Quatf case_rot;

      if (mBarrel == 0)
      {
         case_rot = gmtl::make<gmtl::Quatf>(gmtl::EulerAngleZYXf(
            0, gmtl::Math::deg2Rad(90.0f), gmtl::Math::deg2Rad(88.0f)));
      }
      else if (mBarrel == 1)
      {
         case_rot = gmtl::make<gmtl::Quatf>(gmtl::EulerAngleZYXf(
            0, gmtl::Math::deg2Rad(90.0f), gmtl::Math::deg2Rad(90.0f)));
      }
      else if (mBarrel == 2)
      {
         case_rot = gmtl::make<gmtl::Quatf>(gmtl::EulerAngleZYXf(
            0, gmtl::Math::deg2Rad(-90.0f), gmtl::Math::deg2Rad(88.0f)));
      }

      // Create the shell casing
      BaseBullet* casing = createBullet("casing");
      casing->setRot(getRot() * case_rot);
      casing->setPos(getPos() + casing->getForward() * 1.0f);
      casing->setVel(casing->getRot() * gmtl::Vec3f(0, 0, -5) );
      casing->setRotVel(randomUnitVector() * 4);
      g.add(casing);
   }
}
