/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#include "BoundsCollisionDetector.h"
#include <gmtl/VecOps.h>
#include <gmtl/Generate.h>

namespace mw
{
   BoundsCollisionDetector::BoundsCollisionDetector()
   {
   }

   BoundsCollisionDetector::~BoundsCollisionDetector()
   {
   }

   CollisionDesc* BoundsCollisionDetector::checkCollision(
                                 const RigidBody* body,
                                 const gmtl::Vec3f& path)
   {
      // Calculate a bounding box at the end of the path
      gmtl::AABoxf bounds = body->getBounds();
      bounds.setMin(bounds.getMin() + path);
      bounds.setMax(bounds.getMax() + path);

      // Find all objects whose bounds intersect with this body's bounds
      std::list<RigidBody*> pcs = mSpatialIndex->intersect(bounds);

      // No collisions, return null
      if (pcs.size() == 0)
      {
         return 0;
      }

      // This algorithm collides with the first body found with the normal in
      // the opposite direction of the path travelled.
      gmtl::Vec3f normal = makeNormal(-path);
      return new CollisionDesc(pcs.front(), normal, 1.0f);
   }

   void BoundsCollisionDetector::setSpatialIndex(SpatialIndex* index)
   {
      mSpatialIndex = index;
   }

   SpatialIndex* BoundsCollisionDetector::getSpatialIndex() const
   {
      return mSpatialIndex;
   }
}
