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
 * File:          $RCSfile: CollisionResponse.h,v $
 * Date modified: $Date: 2002-10-30 09:48:05 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_COLLISION_RESPONSE_H
#define MW_COLLISION_RESPONSE_H

#include <map>
#include <utility>
#include "LokiTypeInfo.h"
#include "CollisionEvent.h"

namespace mw
{
   /**
    * @ingroup CollDet
    *
    * This object manages a table of responses that should be done when a
    * specific set of entity types collide.
    */
   class CollisionResponse
   {
   public:
      /// The response function pointer type.
      typedef void (*ResponseFunc)(const CollisionEvent&);

   public:
      CollisionResponse();
      ~CollisionResponse();

      /**
       * Sets the response that will be invoked when the given pair of entity
       * types collide.
       */
      void defineResponse(const Loki::TypeInfo& colliderType,
                          const Loki::TypeInfo& collideeType,
                          ResponseFunc* response);

      /**
       * Checks if a response has been defined for the given collision pair.
       */
      bool isDefined(const Loki::TypeInfo& colliderType,
                     const Loki::TypeInfo& collideeType) const;

      /**
       * Gets the response for a collision between the two given types.
       *
       * @return  a pointer to the response function; NULL if there is no match
       */
      ResponseFunc* getResponse(const Loki::TypeInfo& colliderType,
                                const Loki::TypeInfo& collideeType);

   private:
      /// A pair (ordering is important) of entity types <collider, collidee>.
      typedef std::pair<Loki::TypeInfo, Loki::TypeInfo> TypePair;

      /// The mapp of entity TypePairs to response functions
      typedef std::map<TypePair, ResponseFunc*> ResponseMap;

      /// The mapping of entity TypePairs to the function that defines the response
      ResponseMap mResponseMap;
   };
}

#endif
