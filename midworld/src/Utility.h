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
 * File:          $RCSfile: Utility.h,v $
 * Date modified: $Date: 2002-10-01 04:26:42 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#ifndef MW_UTILITY_H
#define MW_UTILITY_H


#include <gmtl/Vec.h>
#include <gmtl/Math.h>


namespace mw
{

   inline bool isPowerOfTwo(int i)
   {
      return (i & (i - 1)) == 0;
   }

   inline gmtl::Vec3f RandomUnitVector()
   {
      float z = gmtl::Math::rangeRandom(-1.0f, 1.0f);
      float a = gmtl::Math::rangeRandom(0.0f, gmtl::Math::PI * 2);
      float r = gmtl::Math::sqrt(1.0f - z*z);
      float x = r * gmtl::Math::cos(a);
      float y = r * gmtl::Math::sin(a);

      return gmtl::Vec3f(x, y, z);
   }

}


#endif
