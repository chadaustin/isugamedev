/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#ifndef MW_RIGID_BODY_H
#define MW_RIGID_BODY_H

#include <gmtl/AABox.h>
#include <gmtl/Point.h>

namespace mw
{
   /**
    * Interface for a physical body that cannot be deformed.
    */
   class RigidBody
   {
   public:
      virtual ~RigidBody() {}

      /**
       * Gets the axis-aligned bounding box that tightly contains this body.
       *
       * @return  the bounding volume for this body
       */
      virtual const gmtl::AABoxf& getBounds() const;

      /**
       * Gets the position of this rigid body relative to the world's origin.
       *
       * @return  this body's position.
       */
      virtual const gmtl::Point3f& getPosition() const;
   };
}

#endif
