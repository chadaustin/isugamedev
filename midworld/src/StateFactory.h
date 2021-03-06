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
 * File:          $RCSfile: StateFactory.h,v $
 * Date modified: $Date: 2002-10-01 01:00:29 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_STATE_FACTORY_H
#define MW_STATE_FACTORY_H

#include <string>
#include <map>
#include "Application.h"

namespace mw
{
   class State;
   class StateCreator;

   /**
    * This singleton knows how to create States based on a given name
    * association.
    */
   class StateFactory
   {
   private:
      /// This factory is a singleton. Use StateFactory::getInstance() instead.
      StateFactory();

      /// Not implemented on purpose. This is a singleton.
      StateFactory(const StateFactory& factory);

      /// Destroys this factory
      ~StateFactory();

   public:
      /// Gets the singleton instance of this factory.
      static StateFactory& getInstance();

      /**
       * Creates a new state that corresponds with to the given name. If no
       * state is associated with the given name, this method returns NULL.
       *
       * @param name    the name of the state to create
       * @param app     the application in which the state is being used
       *
       * @return  a new State implementation if successful, NULL otherwise
       */
      State* create(const std::string& name, Application* app);

      /**
       * Registers the given StateCreator with this factory under the given
       * name. This factory will assume ownership of the creator.
       *
       * @param name       the name to associated with the created states
       * @param creator    the StateCreator implementation
       */
      void registerCreator(const std::string& name, StateCreator* creator);

      /**
       * Unregister the StateCreator with this factory that is associated with
       * the given name. The StateCreator will be deleted.
       *
       * @param name       the name of the creator to unregister
       */
      void unregisterCreator(const std::string& name);

   private:
      static void destroyInstance();

      typedef std::map<std::string, StateCreator*> CreatorMap;

      /// A mapping of names to Creator implementations
      CreatorMap mCreators;

      /// The singleton instance of this class
      static StateFactory* mSingleton;
   };

   /**
    * Interface for objects that know how to create a specific state object.
    */
   class StateCreator
   {
   public:
      virtual ~StateCreator() {}

      /**
       * Creates a new State object.
       */
      virtual State* create(Application* app) = 0;
   };

   /**
    * A specific implementation of the Creator interface tied to a specific
    * State implementation type. Additionally, it registers itself with the
    * StateFactory when it is constructed.
    */
   template< class StateType >
   class StateCreatorImpl : public StateCreator
   {
   public:
      StateCreatorImpl(const std::string& name)
      {
         StateFactory::getInstance().registerCreator(name, this);
      }

      ~StateCreatorImpl()
      {}

      virtual State* create(Application* app)
      {
         return new StateType(app);
      }
   };
}

#endif
