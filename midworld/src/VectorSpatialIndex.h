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
 * File:          $RCSfile: VectorSpatialIndex.h,v $
 * Date modified: $Date: 2002-07-06 04:31:09 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_VECTOR_SPATIAL_INDEX_H
#define MW_VECTOR_SPATIAL_INDEX_H

#include <vector>
#include <gmtl/Intersection.h>
#include "SpatialIndex.h"

namespace mw
{
   /**
    * @ingroup CollDet
    *
    * Implementation of the SpatialIndex interface for a world stored as a
    * vector of rigid bodies. This is a worst-case scenario, but very easy to
    * implement.
    *
    * This algorithm works by iterating over each rigid body in the vector and
    * testing if its bounding box intersects with the search region.
    *
    * This algorithm runs in O(n) time.
    */
   class VectorSpatialIndex : public SpatialIndex
   {
   public:
      /**
       * Creates a new spatial index for the given vector of rigid bodies. The
       * vector is passed as a pointer to the real vector. This spatial index
       * does NOT assume ownership of the vector.
       *
       * @param bodies     the vector of bodies to use as the system
       */
      VectorSpatialIndex(std::vector<RigidBody*>* bodies)
         : mBodies(bodies)
      {}

      /**
       * Finds the rigid bodies whose bounds intersect the given region.
       *
       * @param region     the search region that bodies will be tested against
       *
       * @return  a list of intersecting bodies
       */
      std::list<RigidBody*> intersect(const gmtl::AABoxf& region)
      {
         std::list<RigidBody*> result;

         std::vector<RigidBody*>::iterator itr;
         for (itr = mBodies->begin(); itr != mBodies->end(); ++itr)
         {
            RigidBody* body = *itr;
            // Check if the current body's bounds overlap the search region
            if (gmtl::intersect(region, body->getBounds()))
            {
               result.push_back(body);
            }
         }

         return result;
      }

   private:
      std::vector<RigidBody*>* mBodies;
   };
}

#endif