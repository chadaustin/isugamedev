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
 * File:          $RCSfile: MissileLauncher.cpp,v $
 * Date modified: $Date: 2002-10-28 07:41:20 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "MissileLauncher.h"
#include "EntityFactory.h"

namespace mw
{
   MissileLauncher::MissileLauncher()
      : BaseProjectileWeapon(Weapon::HEAVY, "Missile Launcher")
   {
      mMaxAmmoInBag = 100;
      mClipSize = 3;

      mFiring = false;
      mReloading = false;

      mReloadRate = 4.0f;
      mAmmoInClip = mClipSize;
      mAmmoInBag = 50;

      mReloadCounter = 0.0f;

      mCockDelayLeft = 1.0f;
      mCockRate = 0.1f;
      mCocking = false;
      mCocked = true;
      
      mAITest = new Testing;
   }

   void MissileLauncher::discharge(GameState &g)
   {
      BaseBullet* missile;
      missile = MissileLauncher::createBullet("bullet");
      missile->setVel(gmtl::Vec3f(0, 0, -20));
      missile->setVel(getRot() * missile->getVel());
      //Homing AI
      lm::aiNode     *missileNode;
      lm::reflex     *missileInstinct;
      missileNode = new lm::aiNode("John", NULL, -1, 1);
      mMissileCommand = new lm::simpleCommand<HomingMissile>(dynamic_cast<HomingMissile*>(missile), &HomingMissile::home);
      mMissileBehavior = new lm::behavior;
      mMissileBehavior->addCommand(mMissileCommand);
      mMissileTesting = new lm::nodeTestCommand<Testing>(mAITest, &Testing::alwaysTrue);
      missileInstinct = new lm::reflex(missileNode, mMissileBehavior, mMissileTesting);
      g.addSmart(missile, missileNode);
   }

   BaseBullet* MissileLauncher::createBullet(const std::string& model) const
   {
      BaseBullet* missile = EntityFactory::instance().create<HomingMissile>();
      missile->setVel(gmtl::Vec3f(0,0,-30));
      missile->setPos(getBarrelEndPos());
      missile->setModel(model);
      return missile;
   }

   void MissileLauncher::ejectCasing(GameState& g)
   {
      ///@TODO: eject casings.
   }

   void MissileLauncher::update(GameState &g, float dt)
   {
      BaseProjectileWeapon::update(g, dt);
   }
}//end of namespace mw
