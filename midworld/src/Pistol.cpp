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
 * File:          $RCSfile: Pistol.cpp,v $
 * Date modified: $Date: 2002-11-25 09:25:15 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <gmtl/Math.h>
#include "Pistol.h"
#include "BaseBullet.h"
#include "BulletCasing.h"
#include "GameManager.h"

namespace mw
{
   Pistol::Pistol()
      : BaseProjectileWeapon(Weapon::HANDGUN, "Pistol")
   {}

   void
   Pistol::discharge(GameState& g)
   {
      // add the bullet to the game...
      BaseBullet* bullet = createBullet("bullet");
      bullet->setRot(getRot());
      bullet->setVel(getRot() * bullet->getVel());
      g.add(bullet); // bullet is not mine anymore, belongs to GameState

      // Do the sound effect
      SoundEffectManager* sfxmgr = GameManager::instance().getSoundManager()->
                                    getSoundEffectManager();
      sfxmgr->playSound("sfx/pistol.wav");
   }

   void
   Pistol::ejectCasing(GameState& g)
   {
      /// @todo eject a _real_ casings into the game
      
      // Define the angle at which the shell is ejected
      gmtl::Quatf case_rot;
      case_rot = gmtl::make<gmtl::Quatf>(gmtl::EulerAngleZYXf(
         0, gmtl::Math::deg2Rad(90.0f), gmtl::Math::deg2Rad(88.0f)));

      // Create the shell casing
      BulletCasing* casing = createCasing("casing");
      casing->setRot(getRot() * case_rot);
      casing->setPos(getPos() + casing->getForward() * 1.0f);
      casing->setVel(casing->getRot() * gmtl::Vec3f(0, 0, -5) );
      casing->setRotVel(randomUnitVector() * 4);
      g.add(casing);
   }
}
