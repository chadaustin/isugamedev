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
 * File:          $RCSfile: Shotgun.cpp,v $
 * Date modified: $Date: 2002-11-26 01:50:09 $
 * Version:       $Revision: 1.11 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <gmtl/Math.h>
#include <stdlib.h>
#include <SDL.h>
#include "BaseBullet.h"
#include "BulletCasing.h"
#include "Shotgun.h"
#include "GameManager.h"
#include "GameState.h"

const static unsigned int NUM_PELLETS = 6;

namespace mw
{
   Shotgun::Shotgun()
      : BaseProjectileWeapon(Weapon::RIFLE, "Shotgun")
   {
      mSpreadAngle = 10.0f;
      mMaxAmmoInBag = 1200;
      mClipSize = 5;

      mReloadRate = 2.0f;
      mCockRate = 0.7f;

      mAmmoInClip = mClipSize;
      mAmmoInBag = 20;
   }

   void Shotgun::discharge(GameState& g)
   {
      // add the bullet to the gamestate...
      for(unsigned int i=0; i<NUM_PELLETS; i++)
      {
         //generate random bullet directions with the sweep of mSpreadAngle
         //degrees
         float angle = gmtl::Math::deg2Rad((mSpreadAngle * float(rand())/RAND_MAX) - (mSpreadAngle/2));

         gmtl::Quatf barrel_rot(gmtl::make<gmtl::Quatf>(gmtl::AxisAnglef(angle, 0.0f, 1.0f, 0.0f)));

         BaseBullet* bullet = createBullet("bullet");
         bullet->setRot(getRot() * barrel_rot); //shoot off at a limited random angle
         bullet->setVel(getRot() * barrel_rot * bullet->getVel());
         g.add(bullet);
      }

      // Do the sound effect
      SoundEffectManager* sfxmgr = GameManager::instance().getSoundManager()->
                                    getSoundEffectManager();
      sfxmgr->playSound("sfx/shotgun.wav");
   }

   void Shotgun::ejectCasing(GameState& g)
   {
      gmtl::Quatf case_rot(gmtl::make<gmtl::Quatf>(gmtl::EulerAngleZYXf(
                  0, gmtl::Math::deg2Rad(-90.0f), gmtl::Math::deg2Rad(85.0f))));

      // Create the shell casing
      BulletCasing* casing = createCasing("casing");
      casing->setRot(getRot() * case_rot);
      casing->setPos(getPos() + casing->getForward() * 1.0f);
      casing->setVel(casing->getRot() * casing->getVel() * 0.2f);
      g.add(casing);
   }
}
