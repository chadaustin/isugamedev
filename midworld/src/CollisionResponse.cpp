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
 * File:          $RCSfile: CollisionResponse.cpp,v $
 * Date modified: $Date: 2002-10-30 09:48:05 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "CollisionResponse.h"

namespace mw
{
   CollisionResponse::CollisionResponse()
   {}

   CollisionResponse::~CollisionResponse()
   {}

   void
   CollisionResponse::defineResponse(const Loki::TypeInfo& colliderType,
                                     const Loki::TypeInfo& collideeType,
                                     ResponseFunc* response)
   {
      mResponseMap[TypePair(colliderType, collideeType)] = response;
   }

   bool
   CollisionResponse::isDefined(const Loki::TypeInfo& colliderType,
                                const Loki::TypeInfo& collideeType) const
   {
      TypePair type(colliderType, collideeType);

      ResponseMap::const_iterator itr = mResponseMap.find(type);
      return (itr != mResponseMap.end());
   }

   CollisionResponse::ResponseFunc*
   CollisionResponse::getResponse(const Loki::TypeInfo& colliderType,
                                  const Loki::TypeInfo& collideeType)
   {
      TypePair type(colliderType, collideeType);

      if (isDefined(type.first, type.second))
      {
         return mResponseMap[type];
      }
      return 0;
   }
}
