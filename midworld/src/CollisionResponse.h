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
 * Date modified: $Date: 2002-10-31 08:35:58 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_COLLISION_RESPONSE_H
#define MW_COLLISION_RESPONSE_H

#include <map>
#include <utility>
#include "RigidBody.h"
#include "LokiTypeInfo.h"

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
   private:
      class Response
      {
      public:
         virtual void onCollide(RigidBody* e1, RigidBody* e2) = 0;
      };
   
      template<typename T1, typename T2>
      class TypedResponse : public Response
      {
      public:
         TypedResponse(void (*response)(T1*, T2*))
         {
            mResponse = response;
         }
      
         void onCollide(RigidBody* e1, RigidBody* e2)
         {
            mResponse(dynamic_cast<T1*>(e1), dynamic_cast<T2*>(e2));
         }
         
      private:
         void (*mResponse)(T1*, T2*);
      };

      template<typename T1, typename T2>
      class ReverseResponse : public Response
      {
      public:
         ReverseResponse(void (*response)(T1*, T2*))
         {
            mResponse = response;
         }

         void onCollide(RigidBody* e1, RigidBody* e2)
         {
            mResponse(dynamic_cast<T1*>(e2), dynamic_cast<T2*>(e1));
         }
         
      private:
         void (*mResponse)(T1*, T2*);
      };
   
   public:
      CollisionResponse();
      ~CollisionResponse();
   
      /**
       * Defines a response that will be invoked when the given pair of entity
       * types collide.
       */
      template<typename T1, typename T2>
      void defineResponse(void (*responseFunc)(T1*, T2*))
      {
         Loki::TypeInfo type1(typeid(T1));
         Loki::TypeInfo type2(typeid(T2));
         TypePair pair1(type1, type2);
         TypePair pair2(type2, type1);
         delete mResponseMap[pair1];
         delete mResponseMap[pair2];
         mResponseMap[pair1] = new TypedResponse<T1, T2>(responseFunc);
         mResponseMap[pair2] = new ReverseResponse<T1, T2>(responseFunc);
      }
      
      void collide(RigidBody* e1, RigidBody* e2)
      {
         Loki::TypeInfo type1(typeid(*e1));
         Loki::TypeInfo type2(typeid(*e2));
         Response* response = mResponseMap[std::make_pair(type1, type2)];
         if (response)
         {
            response->onCollide(e1, e2);
         }
      }

   private:
      typedef std::pair<Loki::TypeInfo, Loki::TypeInfo> TypePair;
      typedef std::map<TypePair, Response*> ResponseMap;

      /**
       * The mapping of entity TypePairs to the function that defines the response.
       * In this map, the pair has the restriction such that type1 <= type2.
       */
      ResponseMap mResponseMap;
   };
}

#endif
