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
 * File:          $RCSfile: BoundsCollisionDetector.cpp,v $
 * Date modified: $Date: 2002-11-06 01:40:14 $
 * Version:       $Revision: 1.9 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
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

   CollisionDetector::CollisionList
   BoundsCollisionDetector::checkCollisions(const RigidBody* body,
                                            const gmtl::Vec3f& path)
   {
      static const float delta = 1.0f / 16;

      CollisionList collisions;
      
      if (!body->isCollidable())
      {
         return collisions;
      }
      
      // try 16 steps along the path
      for (float i = 0; i < 1; i += delta) {
      
         // Calculate a bounding box at the end of the path
         gmtl::AABoxf bounds = body->getBounds();
         bounds.setMin(bounds.getMin() + path * i);
         bounds.setMax(bounds.getMax() + path * i);

         // Find all objects whose bounds intersect with this body's bounds
         std::list<RigidBody*> pcs = mSpatialIndex->intersect(bounds);

         for (std::list<RigidBody*>::iterator itr = pcs.begin(); itr != pcs.end(); ++itr)
         {
            RigidBody* collidee = *itr;

            // Don't collide against ourself or against noncollidables
            if (body == collidee || !collidee->isCollidable())
            {
               continue;
            }

            // This algorithm collides with the first body found with the normal in
            // the opposite direction of the path travelled.
            gmtl::Vec3f normal = gmtl::makeNormal(-path);

            // In this simple algorithm, we return the first collidee found
            collisions.push_back(new CollisionDesc(collidee, normal,
                                 std::max(i - delta, 0.0f), false));
            break;
         }
         
      }

      return collisions;
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
