/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_MISSILELAUNCHER_H
#define MW_MISSILELAUNCHER_H

#include "BaseProjectileWeapon.h"
#include "BaseBullet.h"
#include "GameState.h"
#include "HomingMissile.h"
#include <loom/aiSystem.h>
#include <loom/unit.h>

namespace mw
{
   /**
    * This class represents the missile launcher in game.
    */
   class MissileLauncher : public BaseProjectileWeapon
   {
   public:
      MissileLauncher();
      
   protected:
      virtual void discharge(GameState &g);

      virtual void ejectCasing(GameState &g);

      virtual BaseBullet* createBullet(const std::string& model) const;

      virtual void update(GameState &g, float dt);
      
   private:
      ///Represents the AI used for homing missiles.
      lm::command    *mMissileCommand;
      lm::behavior   *mMissileBehavior;
      lm::testing    *mMissileTesting;
      Testing *mAITest;
   };
   
}//end of namespace mw
#endif
