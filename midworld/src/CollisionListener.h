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
 * File:          $RCSfile: CollisionListener.h,v $
 * Date modified: $Date: 2002-07-29 05:48:35 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_COLLISION_LISTENER_H
#define MW_COLLISION_LISTENER_H

#include "CollisionEvent.h"

namespace mw
{
   /**
    * Interface for objects that wish to be notified when two bodies collide.
    */
   class CollisionListener
   {
   public:
      /**
       * Invoked when the subject has begun to collide with another object.
       */
      virtual void onCollisionEntry(const CollisionEvent& evt) = 0;

      /**
       * Invoked when the subject moves while in a collision state with another
       * object.
       */
      virtual void onCollisionMovement(const CollisionEvent& evt) = 0;

      /**
       * Invoked when the subject no longer collides with any other object.
       */
      virtual void onCollisionExit(const CollisionEvent& evt) = 0;
   };
}

#endif
