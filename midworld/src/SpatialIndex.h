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
 * File:          $RCSfile: SpatialIndex.h,v $
 * Date modified: $Date: 2002-06-06 04:53:59 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
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
