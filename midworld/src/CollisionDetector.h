/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#ifndef MW_COLLISION_DETECTOR_H
#define MW_COLLISION_DETECTOR_H

#include <gmtl/Vec.h>
#include "SpatialIndex.h"
#include "CollisionDesc.h"

namespace mw
{
   /**
    * Interface for an algorithm that can determine if a collision has occurred
    * between rigid bodies in a dynamic system.
    */
   class CollisionDetector
   {
   public:
      virtual ~CollisionDetector() {}

      /**
       * Determines if the given rigid body collides with any other rigid bodies
       * as it travels along the given path.
       *
       * @param body    the body that is the collider
       * @param path    the path along which the body must travel
       *
       * @return  a description of the collision, null if there is no collision
       */
      virtual CollisionDesc checkCollision(const RigidBody* body,
                                           const gmtl::Vec3f& path) = 0;

      /**
       * Sets the spatial index to use with this detector.
       *
       * @param index      the spatial index to use
       */
      virtual void setSpatialIndex(SpatialIndex* index) = 0;

      /**
       * Gets the spatial index associated with this detector.
       *
       * @return  the spatial index associated with this detector
       */
      virtual SpatialIndex* getSpatialIndex() = 0;
   };
}

#endif
