/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** siren-cpr beg
 *
 * siren - flexible 3D game engine
 * siren is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
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
 * Date modified: $Date: 2003-01-16 03:32:20 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_RESOURCE_MANAGER_H
#define SIREN_RESOURCE_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <TypeInfo.h>
#include "Utility.h"
#include "Singleton.h"

namespace siren
{
   /**
    * Base class for the resource manager. It is responsible for managing the
    * mapping from resource IDs to the filenames for those resources.
    */
   class ResourceManagerBase
   {
   protected:
      ResourceManagerBase();
      virtual ~ResourceManagerBase();

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

   private:
      /// The map of resource IDs to their string.
      typedef std::map<std::string, std::string> ResourceIDMap;

      /// All known resources IDs
      ResourceIDMap mResourceIDs;
   };

   /**
    * Policy on how to handle cache hits and misses in the ResourceCache. An
    * implementation must contain the methods copy, create, and destroy.
    */
   template< typename T > struct CachePolicy;

   /**
    * The cache for a specific resource type. It uses the CachePolicy to decide
    * how to create items not in the cache and how to copy items that are
    * already in the cache. ResourceCache is a helper class for the
    * ResourceManager.
    *
    * @see ResourceManager
    */
   template< typename T >
   class ResourceCache
   {
   public:
      /// The type of resouce stored in this cache.
      typedef T ResourceType;

   public:
      /**
       * Destroys this cache and the resources contained therein.
       */
      ~ResourceCache()
      {
         clear();
      }

      /**
       * Retrieves the resource with the given name. If the resource is already
       * in the cache, it is returned. Otherwise, the resource is created and
       * added to the cache before it is returned.
       *
       * @param   name     the name of the file containing the resource
       */
      T find(const std::string& name, Type2Type<T> = Type2Type<T>())
      {
         ResMap::iterator itr = mCache.find(name);

         // Cache hit
         if (itr != mCache.end())
         {
            return CachePolicy<T>::copy(itr->second);
         }
         // Cache miss
         else
         {
            std::cout << "[ResourceManager] Cache miss for '" << name << "'" << std::endl;

            T resource = CachePolicy<T>::create(name);
            mCache[name] = resource;
            return CachePolicy<T>::copy(resource);
         }
      }

      /**
       * Empties this cache, destroying all the resources contained therein.
       */
      void clear()
      {
         // Destroy all things in the cache before clearing it
         for (ResMap::iterator itr = mCache.begin(); itr != mCache.end(); ++itr)
         {
            CachePolicy<T>::destroy(itr->second);
         }
         mCache.clear();
      }

   private:
      /// This is a cache of the resource IDs to their string
      typedef std::map<std::string, T> ResMap;
      ResMap mCache;
   };

   /**
    * This class maps resource IDs to strings.
    */
   class ResourceManager : public ResourceManagerBase
   {
   public:
      ResourceManager();
      ResourceManager(const ResourceManager& resmgr);
      ~ResourceManager();
      void operator=(const ResourceManager& resmgr);

   private:
      /// This is a map of typeids to the cache for the type
      typedef std::map<Loki::TypeInfo, void*> CacheMap;

      /// Gets the cache for the given type.
      template< typename T >
      ResourceCache<T>& getCache(const Loki::TypeInfo& type,
                                 Type2Type<T> = Type2Type<T>())
      {
         CacheMap::iterator itr = mCaches.find(type);
         if (itr != mCaches.end())
         {
            return *static_cast<ResourceCache<T>*>(itr->second);
         }
         else
         {
            // Cache doesn't exist, create it now
            mCaches[type] = new ResourceCache<T>();
            return *static_cast<ResourceCache<T>*>(mCaches[type]);
         }
      }

   public:
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

         ResourceCache<T>& cache = getCache<T>(type);
         return cache.find(resource_name);
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

   private:
      /// All resource caches
      CacheMap mCaches;
   };

   /// The singleton resource manager.
   typedef Singleton<ResourceManager> ResourceManagerSingleton;
}

#endif
