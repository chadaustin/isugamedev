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
 * Date modified: $Date: 2002-07-29 00:38:26 $
 * Version:       $Revision: 1.5 $
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

      for (std::list<RigidBody*>::iterator itr = pcs.begin(); itr != pcs.end(); ++itr)
      {
         RigidBody* collidee = *itr;

         // Don't collide against ourself
         if (body == collidee)
         {
            continue;
         }

         // This algorithm collides with the first body found with the normal in
         // the opposite direction of the path travelled.
         gmtl::Vec3f normal = gmtl::makeNormal(-path);

         // In this simple algorithm, we return the first collidee found
         return new CollisionDesc(collidee, normal, 1.0f);
      }

      // No collisions, return null
      return 0;
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
