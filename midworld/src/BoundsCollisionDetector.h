/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Johnathan Gurley, Andres Reinot, Ben Scott
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
 * File:          $RCSfile: BoundsCollisionDetector.h,v $
 * Date modified: $Date: 2002-06-06 05:19:46 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_BOUNDS_COLLISION_DETECTOR_H
#define MW_BOUNDS_COLLISION_DETECTOR_H

#include "CollisionDetector.h"

namespace mw
{
   /**
    * @ingroup CollDet
    *
    * This implementation of the CollisionDetector interface moves the rigid
    * body to the end of the path and does the collision check there. The check
    * is done by doing only a bounding volume intersection test.
    */
   class BoundsCollisionDetector : public CollisionDetector
   {
   public:
      /**
       * Creates a new BoundsCollisionDetector.
       */
      BoundsCollisionDetector();

      /**
       * Destroys this BoundsCollisionDetector.
       */
      ~BoundsCollisionDetector();

      /**
       * Determines if the given rigid body collides with any other rigid bodies
       * as it travels along the given path.
       *
       * @param body    the body that is the collider
       * @param path    the path along which the body must travel
       *
       * @return  a description of the collision, null if there is no collision
       */
      CollisionDesc* checkCollision(const RigidBody* body,
                                    const gmtl::Vec3f& path);

      /**
       * Sets the spatial index to use with this detector.
       *
       * @param index      the spatial index to use
       */
      void setSpatialIndex(SpatialIndex* index);

      /**
       * Gets the spatial index associated with this detector.
       *
       * @return  the spatial index associated with this detector
       */
      SpatialIndex* getSpatialIndex() const;

   private:
      /// The spatial index into the world.
      SpatialIndex* mSpatialIndex;
   };
}

#endif
