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
 * File:          $RCSfile: CollisionDesc.cpp,v $
 * Date modified: $Date: 2002-06-06 04:53:59 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
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
