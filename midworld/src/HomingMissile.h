/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_HOMINGMISSILE_H
#define MW_HOMINGMISSILE_H

#include "BaseBullet.h"
#include "Enemy.h"
#include <gmtl/Vec.h>
#include <loom/reflex.h>
#include <loom/behavior.h>
#include <loom/command.h>
#include <loom/unit.h>

namespace mw
{
   /**
    * Represents a Homing Missile that is fired by the missile launcher.
    */
   class HomingMissile : public BaseBullet
   {
   public:
      HomingMissile();

      void update(float dt);
      /**
       * Homes on a target
       */
      void home();
   protected:
      
   private:

   };

   /**
    * Used for the Homing Missile AI
    * A lm::command represent the command
    * to seek and destroy
    */
   class HomingCommand : public lm::command
   {
   public:
      HomingCommand(HomingMissile *m, Enemy *e);

      virtual void execute();

   private:
      ///The homing missile
      HomingMissile *mMissile;
      ///The homing missile prey
      Enemy         *mEnemy;
   };
   
   /**
    * Used for the Homing Missile AI
    * Tests used by loom
    */
   class HomingTesting : public lm::testing
   {
   public:
      HomingTesting(HomingMissile* m, Enemy* e);
      
      virtual bool test();

   private:
      ///The homing missile
      HomingMissile *mMissile;
      ///The homing misssile prey
      Enemy         *mEnemy;
   };

   /**
    * For AI testing
    */
   class Testing : public lm::testing
   {
   public:
      Testing() {}
      bool alwaysTrue()
      {
         return true;
      }
      bool alwaysFalse()
      {
         return false;
      }
   };      
}//end of namespace mw
#endif
