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
 * File:          $RCSfile: Enemy.h,v $
 * Date modified: $Date: 2002-10-16 08:35:10 $
 * Version:       $Revision: 1.9 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_ENEMY_H
#define MW_ENEMY_H

#include <cstdlib>
#include "AbstractEntity.h"

namespace mw
{
   /**
    * Base class for all enemy types.
    */
   class Enemy: public AbstractEntity
   {
   public:

      /**
       * Constructor
       */
      Enemy()
         : mHealth(10)
      {
         srand(5);
      }

      /**
       * Destructor
       */
      ~Enemy()
      {
      }

      /**
       * Gets the current health value of this enemy.
       * @return the amount of health this enemy has left.
       */
      long int getHealth() { return mHealth; }

      /**
       * Sets the current health value of this enemy.
       * @param health the amount of health to set this enemy at.
       */
      void setHealth(long int health) { mHealth = health; }

      /**
       * Updates the internal state of this enemy taking into account
       * the amount of time that has passed.
       * @param timeDelta the change in time that has occurred since the last
       * update
       */
      virtual void update(float timeDelta);

      /**
       * Tests if this entity would like to be removed from the game.
       */
      bool isExpired() const
      {
         /// @todo   some complicated test of our state
         return (mHealth <= 0);
      }

      void onCollisionEntry(const CollisionEvent& evt)
      {
         --mHealth;
      }

      void onCollisionMovement(const CollisionEvent& evt)
      {
      }

      void onCollisionExit(const CollisionEvent& evt)
      {
      }

      void walkRandom();

      void rotate();
      

   protected:
      long int mHealth;
   };

}//end of namespace mw

#endif
