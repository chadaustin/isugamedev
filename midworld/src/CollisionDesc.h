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
 * File:          $RCSfile: CollisionDesc.h,v $
 * Date modified: $Date: 2002-11-01 12:27:21 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_COLLISION_DESC_H
#define MW_COLLISION_DESC_H

#include <gmtl/Vec.h>
#include "RigidBody.h"

namespace mw
{
   /**
    * @ingroup CollDet
    *
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
       * @param contact       true if this is a contact collision
       */
      CollisionDesc(RigidBody* collidee, const gmtl::Vec3f& normal,
                    float distance, bool contact);

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

      /**
       * Tests if this is a contact collision.
       *
       * @return  true if the objects are merely in contact; false otherwise
       */
      bool isContact() const;

   private:
      /// The body that the collider hits.
      RigidBody* mCollidee;

      /// The normal of the surface of the collidee at the point of collision.
      gmtl::Vec3f mNormal;

      /// The parametric distance travelled along the path to the collision.
      float mDistance;

      /// Flag for whether this is a contact collisions.
      bool mContact;
   };
}

#endif
