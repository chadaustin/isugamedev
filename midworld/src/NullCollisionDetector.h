/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#ifndef MW_NULL_COLLISION_DETECTOR_H
#define MW_NULL_COLLISION_DETECTOR_H

#include "CollisionDetector.h"

namespace mw
{
   /**
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
       * @return  a description of the collision, null if there is no collision.
       *          The caller is responsible for freeing the CollisionDesc.
       */
      CollisionDesc* checkCollision(const RigidBody* body,
                                    const gmtl::Vec3f& path)
      {
         return 0;
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
      virtual SpatialIndex* getSpatialIndex()
      {
         return mSpatialIndex;
      }

   private:
      /// The spatial index for this detector.
      SpatialIndex* mSpatialIndex;
   };
}

#endif
