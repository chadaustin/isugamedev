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
 * File:          $RCSfile: CollisionEvent.h,v $
 * Date modified: $Date: 2002-07-29 05:48:35 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_COLLISION_EVENT_H
#define MW_COLLISION_EVENT_H

#include "CollisionDesc.h"

namespace mw
{
   /**
    * @ingroup CollDet
    *
    * An event which indicates that a collision action has occurred with respect
    * to a rigid body.
    */
   class CollisionEvent
   {
   public:
      /**
       * Constructs a CollisionEvent object with the specified source object and
       * collision description.
       *
       * @param source     the RigidBody that is the collider
       * @param desc       a description of the collision
       */
      CollisionEvent(RigidBody* source, CollisionDesc* desc)
         : mSource(source), mDesc(desc)
      {}

      /**
       * Gets the source of the collision. This is the collider.
       */
      RigidBody* getSource() const
      {
         return mSource;
      }

      /**
       * Gets a description of the collision.
       */
      CollisionDesc* getDesc() const
      {
         return mDesc;
      }

   private:
      /// The source, or collider, of the collision.
      RigidBody* mSource;

      /// The description of the collision.
      CollisionDesc* mDesc;
   };
}

#endif
