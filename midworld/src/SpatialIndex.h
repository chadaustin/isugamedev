/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#ifndef MW_SPATIAL_INDEX_H
#define MW_SPATIAL_INDEX_H

#include <list>
#include <gmtl/AABox.h>
#include "RigidBody.h"

namespace mw
{
   /**
    * Interface for an index into a collection of rigid bodies organized by
    * their spatial properties.
    */
   class SpatialIndex
   {
   public:
      virtual ~SpatialIndex() {}

      /**
       * Finds the rigid bodies whose bounds intersect the given region.
       *
       * @param region     the search region that bodies will be tested against
       *
       * @return  a list of intersecting bodies
       */
      virtual std::list<RigidBody*> intersect(const gmtl::AABoxf& region) = 0;
   };
}

#endif
