/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#ifndef MW_BOUNDS_COLLISION_DETECTOR_H
#define MW_BOUNDS_COLLISION_DETECTOR_H

#include "CollisionDetector.h"

namespace mw
{
   /**
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
