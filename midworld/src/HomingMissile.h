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
 * File:          $RCSfile: HomingMissile.h,v $
 * Date modified: $Date: 2002-10-28 07:41:20 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_HOMING_MISSILE_H
#define MW_HOMING_MISSILE_H

#include <gmtl/Vec.h>
#include <loom/reflex.h>
#include <loom/behavior.h>
#include <loom/command.h>
#include <loom/unit.h>
#include <loom/reflexManager.h>

#include "BaseBullet.h"
#include "Enemy.h"

namespace mw
{
   /**
    * Represents a Homing Missile that is fired by the missile launcher.
    */
   class HomingMissile : public BaseBullet
   {
   public:
      HomingMissile(GameState* gameState);

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
}

#endif
