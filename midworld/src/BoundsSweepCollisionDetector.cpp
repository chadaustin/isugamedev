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
 * Date modified: $Date: 2002-11-11 05:03:21 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <vector>
#include <gmtl/VecOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Containment.h>
#include <gmtl/Intersection.h>
#include "BoundsSweepCollisionDetector.h"

namespace mw
{
   CollisionDesc*
   BoundsSweepCollisionDetector::checkCollision(const RigidBody* body,
                                                const gmtl::Vec3f& path)
   {
      const gmtl::AABoxf& bounds = body->getBounds();

      // Calculate an AABox around the body for its travel along the entire path
      gmtl::AABoxf path_bounds(bounds.getMin()+path,
                               bounds.getMax()+path);
      gmtl::extendVolume(path_bounds, bounds);

      // Find all objects that this body may collide with on its travels
      std::list<RigidBody*> pcs = mSpatialIndex->intersect(path_bounds);

      // Init the collision parameters to no collision
      float min_dist = 1.0f; // paramteric distance to collision
      RigidBody* closest_body = 0;

      // Don't attempt to do collision detection if the body is not collidable
      if (!body->isCollidable())
      {
         return 0;
      }

      for (std::list<RigidBody*>::iterator itr = pcs.begin(); itr != pcs.end(); ++itr)
      {
         RigidBody* collidee = *itr;

         // Don't collide against ourself or against non-collidables
         if (body == collidee || !collidee->isCollidable())
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
            // There was a possible collision! Check this collisions against the
            // current best solution.
            if (first_contact < min_dist)
            {
               min_dist = first_contact;
               closest_body = collidee;
            }
         }
      }

      // Pick the best collision if there was one
      if (closest_body)
      {
         // Back up the body a little so that it is no longer in a colliding
         // state.
         min_dist -= 0.05f;
         if (min_dist < 0.0f) min_dist = 0.0f;

         // This algorithm collides with the first body found with the normal in
         // the opposite direction of the path travelled.
         gmtl::Vec3f normal = gmtl::makeNormal(-path);

         return new CollisionDesc(closest_body, normal, min_dist, false);
      }

      // No collisions, return null
      return 0;
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
