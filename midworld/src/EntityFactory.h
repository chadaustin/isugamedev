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
 * File:          $RCSfile: EntityFactory.h,v $
 * Date modified: $Date: 2002-11-04 19:17:57 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_ENTITY_FACTORY_H
#define MW_ENTITY_FACTORY_H

#include <map>
#include <iostream>
#include "Entity.h"
#include "GameState.h"
#include "Utility.h"

namespace mw
{
   /**
    * This factory knows how to create Entities based on a string type.
    *
    * This object implements the Singleton pattern.
    */
   class EntityFactory
   {
   public:
      /// Creates a new Entity of the given type.
      template<class T>
      T* create(Type2Type<T> = Type2Type<T>())
      {
         // Create the typeinfo object to search with
         return new T(mGameState);
      }
      
      template<typename T, typename P1>
      T* create(P1 p1, Type2Type<T> = Type2Type<T>())
      {
         return new T(mGameState, p1);
      }
      
      void add(Entity* e)
      {
         mGameState->add(e);
      }

      /// Sets the game state this factory uses.
      void setGameState(GameState* gameState);
      
      GameState* getGameState()
      {
         return mGameState;
      }

      /// Gets the singleton instance of this class.
      static EntityFactory& instance();

   protected:
      /**
       * This object is a singleton. Use EntityFactory::instance() instead.
       */
      EntityFactory();

      /// Not implemented on purpose to cause a compile-time error on usage.
      EntityFactory(const EntityFactory& factory);

      /// Destroys this factory.
      ~EntityFactory();

   private:
      /**
       * The game state this factory is associated with. This factory does NOT
       * own the memory to this object.
       */
      GameState* mGameState;

      /// The singleton instance of this class.
      static EntityFactory* mInstance;
   };
}

#endif
