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
 * File:          $RCSfile: NullCollisionDetector.h,v $
 * Date modified: $Date: 2002-11-03 08:04:46 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_NULL_COLLISION_DETECTOR_H
#define MW_NULL_COLLISION_DETECTOR_H

#include "CollisionDetector.h"

namespace mw
{
   /**
    * @ingroup CollDet
    *
    * CollisionDetector implementation that does nothing. In other words, it
    * never detects any collisions.
    */
   class NullCollisionDetector : public CollisionDetector
   {
   public:
      /**
       * Creates a new NullCollisionDetector with no spatial index.
       */
      NullCollisionDetector()
         : mSpatialIndex(0)
      {}

      /**
       * Determines if the given rigid body collides with any other rigid bodies
       * as it travels along the given path.
       *
       * @param body    the body that is the collider
       * @param path    the path along which the body must travel
       *
       * @return  a list of all the collisions detected sorted in order of
       *          distance travelled to the collision
       */
      CollisionList checkCollisions(const RigidBody* body,
                                    const gmtl::Vec3f& path)
      {
         return CollisionList();
      }

      /**
       * Sets the spatial index to use with this detector.
       *
       * @param index      the spatial index to use
       */
      virtual void setSpatialIndex(SpatialIndex* index)
      {
         mSpatialIndex = index;
      }

      /**
       * Gets the spatial index associated with this detector.
       *
       * @return  the spatial index associated with this detector
       */
      virtual SpatialIndex* getSpatialIndex() const
      {
         return mSpatialIndex;
      }

   private:
      /// The spatial index for this detector.
      SpatialIndex* mSpatialIndex;
   };
}

#endif
