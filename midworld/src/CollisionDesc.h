/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#ifndef MW_COLLISION_DESC_H
#define MW_COLLISION_DESC_H

#include <gmtl/Vec.h>
#include "RigidBody.h"

namespace mw
{
   /**
    * Describes the details of a collision between two rigid bodies. Objects of
    * this class should provide enough information to calculate the collision
    * response.
    */
   class CollisionDesc
   {
   public:
      /**
       * Creates a new collision description with default, uninitialized values.
       */
      CollisionDesc();

      /**
       * Creates a new collision description with the given values.
       *
       * @param collidee      the body that the collider hits
       * @param normal        the normal of the surface of the collidee at the
       *                      point of collision
       * @param distance      the distance travelled along the path to the point
       *                      of collision
       */
      CollisionDesc(RigidBody* collidee, const gmtl::Vec3f& normal,
                    float distance);

      /**
       * Gets the body that the collider has hit.
       *
       * @return  the collidee
       */
      RigidBody* getCollidee() const;

      /**
       * Gets the normal of the surface of the collidee at the point of
       * collision.
       *
       * @return  the surface normal
       */
      const gmtl::Vec3f& getNormal() const;

      /**
       * Gets the distance that was travelled along the collider's movement path
       * to the point of collision. The value is parametric; 0 corresponds to
       * the beginning of the path; 1 to the end of the path.
       *
       * @return  the distance to the collision in the range [0,1].
       */
      float getDistance() const;

   private:
      /// The body that the collider hits.
      RigidBody* mCollidee;

      /// The normal of the surface of the collidee at the point of collision.
      gmtl::Vec3f mNormal;

      /// The parametric distance travelled along the path to the collision.
      float mDistance;
   };
}

#endif
