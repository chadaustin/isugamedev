/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include <iostream>
#include "HomingMissile.h"

namespace mw
{
   HomingMissile::HomingMissile(GameState* gameState)
      : BaseBullet(gameState)
   {
   }

   void HomingMissile::update(float dt)
   {
      BaseBullet::update(dt);
   }

   void HomingMissile::home()
   {
      std::cerr << "Homing..." << std::endl;
   }

   HomingCommand::HomingCommand(HomingMissile *m, Enemy *e)
   {
      mMissile = m;
      mEnemy = e;
   }

   void HomingCommand::execute()
   {
      gmtl::Vec3f vecToBaddie = mMissile->getPos()-mEnemy->getPos();
      gmtl::normalize(vecToBaddie);
      mMissile->setVel(vecToBaddie);
   }

   HomingTesting::HomingTesting(HomingMissile *m, Enemy *e)
   {
      mMissile = m;
      mEnemy = e;
   }

   bool HomingTesting::test()
   {
      return true;
   }
}
