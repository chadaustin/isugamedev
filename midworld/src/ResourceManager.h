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
 * File:          $RCSfile: ResourceManager.h,v $
 * Date modified: $Date: 2002-11-25 10:08:03 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_RESOURCE_MANAGER_H
#define MW_RESOURCE_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include "Utility.h"
#include "LokiTypeInfo.h"
#include "Singleton.h"

namespace mw
{
   /**
    * This class maps resource IDs to strings.
    */
   class ResourceManager
   {
   public:
      /// A factory function for creating a resource with the given name.
      typedef void* (*Factory)(const std::string& name);

   private:
      /// This is a cache of the resource IDs to their string
      typedef std::map<std::string, void*> Cache;

      /// This is a map of typeids to the cache for the type
      typedef std::map<Loki::TypeInfo, Cache> CacheMap;

      /// Gets the cache for the given type.
      Cache& getCache(const Loki::TypeInfo& type);

      /// Gets the factory for the given type.
      Factory getFactory(const Loki::TypeInfo& type);

   public:
      ResourceManager();

      ResourceManager(const ResourceManager& resmgr);
      void operator=(const ResourceManager& resmgr);
      ~ResourceManager();

   public:
      /**
       * Gets the string associated with the given resource identifier.
       *
       * @param resid   the ID of the resource to retrieve
       *
       * @return  the string value associated with the resource
       *
       * @throws  std::runtime_error if the resource ID is unknown
       */
      const std::string& lookup(const std::string& resid) const;

      /**
       * Gets the resource associated with the given resource ID. If the
       * resource is already in cache, the cached version is returned.
       *
       * @param resid      the ID of the resource to retrieve
       *
       * @return  the resource object
       *
       * @throws  std::runtime_error if there was an error getting the resource
       */
      template< typename T >
      T get(const std::string& resid, Type2Type<T> = Type2Type<T>())
      {
         Loki::TypeInfo type(typeid(T));
         const std::string& resource_name = lookup(resid);

         // Get the cache and check it first
         Cache& cache = getCache(type);
         Cache::iterator itr = cache.find(resource_name);

         // Cache hit
         if (itr != cache.end())
         {
            return static_cast<T>(itr->second);
         }
         // Cache miss
         {
            std::cout << "[ResourceManager] Cache miss for '" << resid << "'" << std::endl;

            // Get the factory for the given type
            Factory factory = getFactory(type);
            if (factory == 0)
            {
               // No factory available
               throw std::runtime_error("No factory registered for given type");
            }

            // Create the resource we need and cache it. This may throw an
            // exception if the creation fails.
            T resource = static_cast<T>(factory(resource_name));
            cache[resource_name] = resource;
            return resource;
         }
      }

      /**
       * Preloads the resource with the given ID and stores it in the cache for
       * later use.
       *
       * @param resid   the ID of the resource to cache
       *
       * @return  true if the resource was cached successfully, false otherwise
       */
      template< typename T >
      bool preload(const std::string& resid)
      {
         try
         {
            get<T>(resid);
            return true;
         }
         catch (const std::runtime_error& error)
         {
            std::cout << "[ResourceManager] Error: " << error.what() << std::endl;
         }
         return false;
      }

      /**
       * Removes all resources of the given type from cache.
       */
      template< typename T >
      void emptyCache()
      {
         Loki::TypeInfo type(typeid(T));
         getCache(type).clear();
      }

      /**
       * Adds the given resource into this manager such that the given value is
       * associated with the given resource ID.
       *
       * @param resid   the ID of the resource to add
       * @param value   the string value of the resource
       *
       * @throws  std::runtime_error if the resource ID is already in use
       */
      void defineResourceID(const std::string& resid, const std::string& value);

      /**
       * Removes the resource with the given ID.
       *
       * @param resid   the ID of the resource to remove
       *
       * @throws  std::runtime_error if the resource ID is unknown
       */
      void removeResourceID(const std::string& resid);

      /**
       * Defines the factory function for the given type.
       */
      template< typename T >
      void defineFactory(Factory factory, Type2Type<T> = Type2Type<T>())
      {
         Loki::TypeInfo type(typeid(T));
         mFactories[type] = factory;
      }

   private:
      /// The map of resource IDs to their string.
      typedef std::map<std::string, std::string> ResourceIDMap;

      /// Mapping of types to the factory that creates those types
      typedef std::map<Loki::TypeInfo, Factory> FactoryMap;

      /// All known resources IDs
      ResourceIDMap mResourceIDs;

      /// All resource caches
      CacheMap mCaches;

      /// The registered factory functions
      FactoryMap mFactories;
   };

   typedef Singleton<ResourceManager> ResourceManagerSingleton;
}

#endif
