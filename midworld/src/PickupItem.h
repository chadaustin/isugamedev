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
 * File:          $RCSfile: PickupItem.h,v $
 * Date modified: $Date: 2002-10-03 10:47:48 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_PICKUP_ITEM_H
#define MW_PICKUP_ITEM_H

#include "AbstractEntity.h"
#include "Player.h"

namespace mw
{
   /**
    * Defines a pickup item containing a bunch of ammo.
    */
   class PickupItem : public AbstractEntity
   {
   public:
      ~PickupItem() {}

      /**
       * This pickup item only cares when a player collides with it. If such a
       * situation occurs, then the object is told that it has been picked up by
       * the given player.
       */
      void onCollisionEntry(const CollisionEvent& evt)
      {
         RigidBody* body = 0;
         if (evt.getSource() == this)
         {
            body = evt.getDesc()->getCollidee();
         }
         else
         {
            body = evt.getSource();
         }

         // Check if the body is a player
         Player* player = dynamic_cast<Player*>(body);
         if (player != 0)
         {
            pickedUp(player);
         }
      }

      void onCollisionMovement(const CollisionEvent& evt)
      {
      }

      void onCollisionExit(const CollisionEvent& evt)
      {
      }

   protected:
      /**
       * Notifies this pickup item that it has been picked up by the given
       * player.
       *
       * @param player     the player that picked up the item
       */
      virtual void pickedUp(Player* player) = 0;
   };
}

#endif
