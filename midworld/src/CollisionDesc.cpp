/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#include "CollisionDesc.h"

namespace mw
{
   CollisionDesc::CollisionDesc()
      : mCollidee(0), mNormal(0,0,0), mDistance(0)
   {}

   CollisionDesc::CollisionDesc(RigidBody* collidee, const gmtl::Vec3f& normal,
                                float distance)
      : mCollidee(collidee), mNormal(normal), mDistance(distance)
   {}

   RigidBody*
   CollisionDesc::getCollidee() const
   {
      return mCollidee;
   }

   const gmtl::Vec3f&
   CollisionDesc::getNormal() const
   {
      return mNormal;
   }

   float
   CollisionDesc::getDistance() const
   {
      return mDistance;
   }
}
