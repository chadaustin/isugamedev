/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
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
 * File:          $RCSfile: BoundsSweepCollisionDetector.cpp,v $
 * Date modified: $Date: 2002-11-03 08:04:46 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <vector>
#include <algorithm>
#include <gmtl/VecOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Containment.h>
#include <gmtl/Intersection.h>
#include "BoundsSweepCollisionDetector.h"

namespace mw
{
   namespace
   {
      bool
      compareByDistance(const CollisionDesc* lhs, const CollisionDesc* rhs)
      {
         return (lhs->getDistance() < rhs->getDistance());
      }
   }

   CollisionDetector::CollisionList
   BoundsSweepCollisionDetector::checkCollisions(const RigidBody* body,
                                                 const gmtl::Vec3f& path)
   {
      const gmtl::AABoxf& bounds = body->getBounds();

      // Calculate an AABox around the body for its travel along the entire path
      gmtl::AABoxf path_bounds(bounds.getMin()+path,
                               bounds.getMax()+path);
      gmtl::extendVolume(path_bounds, bounds);

      // Find all objects that this body may collide with on its travels
      std::list<RigidBody*> pcs = mSpatialIndex->intersect(bounds);

      // For now, our collision normal is the opposite of the path
      gmtl::Vec3f normal = gmtl::makeNormal(-path);

      // Init the list of detected collisions to empty
      CollisionList collisions;

      for (std::list<RigidBody*>::iterator itr = pcs.begin(); itr != pcs.end(); ++itr)
      {
         RigidBody* collidee = *itr;

         // Don't collide against ourself
         if (body == collidee)
         {
            continue;
         }

         // Do a sweep test between body and the potential collidee.
         // XXX: We need some way to get the path for collidee!
         float first_contact, second_contact;
         if (gmtl::intersect(bounds, path,
                             collidee->getBounds(), gmtl::Vec3f(0,0,0),
                             first_contact, second_contact))
         {
            // There was a collision!
            collisions.push_back(new CollisionDesc(collidee, normal,
                                                   first_contact, false));
         }
      }

      // Sort the list of collisions in order of distance to collision with the
      // closest collisions coming first.
      if (collisions.size() > 1)
      {
         std::cout<<"Found "<<collisions.size()<<" collisions"<<std::endl;
      }
      std::sort(collisions.begin(), collisions.end(), compareByDistance);

      return collisions;
   }

   void
   BoundsSweepCollisionDetector::setSpatialIndex(SpatialIndex* index)
   {
      mSpatialIndex = index;
   }

   SpatialIndex*
   BoundsSweepCollisionDetector::getSpatialIndex() const
   {
      return mSpatialIndex;
   }
}
